//
// Created by Milena on 01/05/2017.
//

#include "Display.h"
extern "C" {
#include <curses.h>
};
using namespace std;

chtype  * strtoch(char * string){
    int len=strlen(string), i;
    chtype * converted=new chtype[len+1];
    for (i=0;i<len+1;i++)
        converted[i]=(chtype)string[i];
    return converted;
}

int Yoda::getColorPair(int x, int y){
    int rt=1;
    switch(getCh(x,y)){
        case '-':case'.':case'\'':case ':':case '`': rt=Display::YODA_PAIR; break;
        default: rt=Display::BASE_PAIR; break;
    }
    return rt;
};

int C3P0::getColorPair(int x, int y) {
    return Display::C3P0_PAIR;
}

int R2D2::getColorPair(int x, int y){
    int rt = 0;
    switch (getCh(x,y)) {
        case 'L': case 'I': case '=':  rt=Display::R2D2B_PAIR;  break;
        case 'o':  rt=Display::R2D2R_PAIR;  break;
        default: rt= Display::R2D2W_PAIR;break;
    }
    return rt;
}

int TIEfighter::getColorPair(int x, int y){
    return Display::R2D2W_PAIR;
};

//TODO hardcodovane koordinate odredi racunski
Display::Display(int h, int w):winW(w), winH(h), sub1(3,5),sub2(13,5), sub3(20,5) {
    initscr();
    BCGD_COLOR=COLOR_BLACK;
    TEXT_COLOR=COLOR_YELLOW;
    SELECTION_COLOR=COLOR_BLACK; //TODO ???
    if (has_colors()) {
        start_color();
        init_pair(BASE_PAIR, TEXT_COLOR, BCGD_COLOR);
        init_pair(C3P0_PAIR, COLOR_YELLOW,BCGD_COLOR);
        init_pair(R2D2W_PAIR,COLOR_WHITE,BCGD_COLOR);
        init_pair(R2D2B_PAIR, COLOR_BLUE,BCGD_COLOR);
        init_pair(R2D2R_PAIR,COLOR_RED,BCGD_COLOR);
        init_pair(YODA_PAIR,COLOR_GREEN,BCGD_COLOR);
    }
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    raw();
    resize_term(h,w);
    initAscii();

};

void Display::initAscii(){
    asciiArt=new AsciiPicture*[6];
    asciiArt[0]=new Yoda(Coord(6,38));
    asciiArt[1]=new C3P0(Coord(12,20));
    asciiArt[2]=new R2D2(Coord(12,20));
    asciiArt[3]=new TIEfighter(Coord(20,20));
    asciiArt[4]=new Yoda(Coord(0,winW-24));
    asciiArt[5]=new R2D2(Coord(winH-4, winW-13));
}

void Display::generateHomeScr(bool loaded) {
    putpictureMultiColor(0);
   // putpictureMultiColor(1);
    refresh();
};

void Display::putpictureMultiColor(int picID){
    AsciiPicture * picture=asciiArt[picID];
    int noLine=0;
    while(noLine<picture->getHeight()){
        string line=picture->getLine(noLine);
        for(int i=0; i<line.length();i++){
            int pair=picture->getColorPair(noLine,i);
            mvaddch(picture->getUpperLeftCorner().getX()+noLine,picture->getUpperLeftCorner().getY()+i,(chtype)line[i]|COLOR_PAIR(pair)|A_BOLD);
        }
        noLine++;
    }
};

void Display::generateFrame(int h, int w, Coord upperLeft){
    mvaddch(upperLeft.getX(),upperLeft.getY(),ACS_ULCORNER|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX(),upperLeft.getY()+w+1,ACS_ULCORNER|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX()+h+1,upperLeft.getY(),ACS_ULCORNER|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX()+h+1,upperLeft.getY()+w+1,ACS_ULCORNER|COLOR_PAIR(BASE_PAIR));

    for(int i=1; i<=w;i++) {
        mvaddch(upperLeft.getX(), upperLeft.getY() + i, ACS_HLINE | COLOR_PAIR(BASE_PAIR));
        mvaddch(upperLeft.getX()+h, upperLeft.getY() + i, ACS_HLINE | COLOR_PAIR(BASE_PAIR));
    }
    for(int i=1;i<=h;i++){
        mvaddch(upperLeft.getX()+i, upperLeft.getY(), ACS_VLINE|COLOR_PAIR(BASE_PAIR));
        mvaddch(upperLeft.getX()+i, upperLeft.getY()+w, ACS_VLINE|COLOR_PAIR(BASE_PAIR));
    }
};

void Display::initScrolling(Subtitles * subs){
    clear();
    putpictureMultiColor(4);
    putpictureMultiColor(5);
    string str="Press h";
    mvaddstr(winH-8, winW-12, str.c_str());
    str="H for";
    mvaddstr(winH-7,winW-12,str.c_str());
    str="help!";
    mvaddstr(winH-6,winW-12,str.c_str());
    SubtitleIter iter=subs->begin();

    mvaddstr(sub1.getX(),sub1.getY(),((string)(*iter).getTime().getStart()).c_str());
    mvaddstr(sub1.getX()+1,sub1.getY(),((string)(*iter).getTime().getEnd()).c_str());
    mvaddstr(sub1.getX()+2,sub1.getY(),(*iter).getContent().c_str());

    iter++;

    mvaddstr(sub2.getX(),sub2.getY(),((string)(*iter).getTime().getStart()).c_str());
    mvaddstr(sub2.getX()+1,sub2.getY(),((string)(*iter).getTime().getEnd()).c_str());
    mvaddstr(sub2.getX()+2,sub2.getY(),(*iter).getContent().c_str());

    iter++;

    mvaddstr(sub3.getX(),sub3.getY(),((string)(*iter).getTime().getStart()).c_str());
    mvaddstr(sub3.getX()+1,sub3.getY(),((string)(*iter).getTime().getEnd()).c_str());
    mvaddstr(sub3.getX()+2,sub3.getY(),(*iter).getContent().c_str());

    refresh();

};

void Display::displayMain(){};
void Display::mainUp(){};
void Display::mainDown(){};
void Display::quitSavePrompt(){};  //TODO do you want to save before you exit?
void Display::savePromptShift(){};
void Display::displayText(string str){};
string Display::stringInput(Coord upperLeft, string prompt){};

/*void Display::displayTitles();
void Display::displayMain();
void Display::displaySettings();
void Display::displayGetAddress();
void Display::scrollUp();
void Display::scrollDown();
void Display::setCurentSubs(Subtitles& subs);
string Display::editableText(string str, Coord upperLeft);
string Display::stringInput(Coord upperLeft);
*/