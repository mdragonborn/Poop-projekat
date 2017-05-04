//
// Created by Milena on 01/05/2017.
//

#include "Display.h"
extern "C" {
#include <curses.h>
};

#include <vector>
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

//TODO hardcodovane koordinate odredi racunski sub[0](3,5),sub2(13,5), sub3(20,5)
Display::Display(int h, int w):winW(w), winH(h){
    initscr();
    if(w<50) {
        w=50; winW=50;
    }
    subCoord[0]=Coord(3,5);
    subCoord[1]=Coord(13,5);
    subCoord[2]=Coord(23,5);
    TEXT_WIDTH=(unsigned)w-30;
    TEXT_HEIGHT=8; //TODO
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

void Display::generateFrame(int h, int w, Coord upperLeft, int pair){
    mvaddch(upperLeft.getX(),upperLeft.getY(),ACS_ULCORNER|COLOR_PAIR(pair));
    mvaddch(upperLeft.getX(),upperLeft.getY()+w,ACS_URCORNER|COLOR_PAIR(pair));
    mvaddch(upperLeft.getX()+h,upperLeft.getY(),ACS_LLCORNER|COLOR_PAIR(pair));
    mvaddch(upperLeft.getX()+h,upperLeft.getY()+w,ACS_LRCORNER|COLOR_PAIR(pair));

    for(int i=1; i<w;i++) {
        mvaddch(upperLeft.getX(), upperLeft.getY() + i, ACS_HLINE | COLOR_PAIR(pair));
        mvaddch(upperLeft.getX()+h, upperLeft.getY() + i, ACS_HLINE | COLOR_PAIR(pair));
    }
    for(int i=1;i<h;i++){
        mvaddch(upperLeft.getX()+i, upperLeft.getY(), ACS_VLINE|COLOR_PAIR(pair));
        mvaddch(upperLeft.getX()+i, upperLeft.getY()+w, ACS_VLINE|COLOR_PAIR(pair));
    }
};
void Display::clearFrame(int h, int w, Coord upperLeft){
    mvaddch(upperLeft.getX(),upperLeft.getY(),' '|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX(),upperLeft.getY()+w+1,' '|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX()+h+1,upperLeft.getY(),' '|COLOR_PAIR(BASE_PAIR));
    mvaddch(upperLeft.getX()+h+1,upperLeft.getY()+w+1,' '|COLOR_PAIR(BASE_PAIR));

    for(int i=1; i<=w;i++) {
        mvaddch(upperLeft.getX(), upperLeft.getY() + i, ' ' | COLOR_PAIR(BASE_PAIR));
        mvaddch(upperLeft.getX()+h, upperLeft.getY() + i, ' ' | COLOR_PAIR(BASE_PAIR));
    }
    for(int i=1;i<=h;i++){
        mvaddch(upperLeft.getX()+i, upperLeft.getY(), ' '|COLOR_PAIR(BASE_PAIR));
        mvaddch(upperLeft.getX()+i, upperLeft.getY()+w, ' '|COLOR_PAIR(BASE_PAIR));
    }
};

void Display::scrollBox(int i){
    if(i==1 && currentSub==1)
        generateFrame(TEXT_HEIGHT+2, TEXT_WIDTH+2,Coord(subCoord[i].getX()-1, subCoord[i].getY()-1),R2D2R_PAIR);
    else{
        clearFrame(TEXT_HEIGHT+2, TEXT_WIDTH+2,Coord(subCoord[currentSub].getX()-1, subCoord[currentSub].getY()-1));
        generateFrame(TEXT_HEIGHT+2, TEXT_WIDTH+2,Coord(subCoord[i].getX()-1, subCoord[i].getY()-1),R2D2R_PAIR);
    }
};


void Display::initScrolling(Subtitles * subs){
    clear();
    putpictureMultiColor(4);
    putpictureMultiColor(5);
    putWrappedString("Press H for help!",Coord(winH-7, winW-12),7);

    SubtitleIter iter=subs->begin();
    for(int i=0; i<3; i++, iter++) lastThree[i]=&(*iter);
    putLastThree();
    currentSub=0;
    scrollBox(0);
    refresh();
};

void Display::scrollUp(Subtitle* prev){
    if(prev!=prev!=lastThree[1]){
        lastThree[2]=lastThree[1];
        lastThree[1]=lastThree[0];
        putLastThree();
        scrollBox(1);
    } else if(prev==lastThree[1]) scrollBox(1);
    else scrollBox(0);
    refresh();
};
void Display::scrollDown(Subtitle* next){
    if(next && next!=lastThree[1]){
        lastThree[0]=lastThree[1];
        lastThree[1]=lastThree[2];
        putLastThree();
        scrollBox(1);
    } else if(next!=lastThree[1]){
        scrollBox(1);
    }else
        scrollBox(2);
    refresh();
};

void  Display::clearScrollWindow(){
    string clearBlock; Coord start(subCoord[0].getX()-1, subCoord[1].getY()-1);
    for(int i=0;i<TEXT_WIDTH+2;i++) clearBlock+=' ';
    for(int i=0;i<(3*TEXT_HEIGHT+6);i++)
        mvaddstr(start.getX()+i,start.getY(),clearBlock.c_str());
}

void Display::displayMain(){

};
void Display::mainUp(){};
void Display::mainDown(){};
void Display::quitSavePrompt(){};  //TODO do you want to save before you exit?
void Display::savePromptShift(){};
void Display::displayText(string str){};
string Display::stringInput(Coord upperLeft, string prompt){};

vector<string*> * Display::wordWrap(string str, int lineSize){
    int i=0, cnt;
    std::vector <string*> * lineBuffer=new vector<string*>;
    string * newstr;
    while(i<str.length()){
        newstr=new string();
        for(cnt=1; cnt<=lineSize;cnt++){
            if(i==str.length()){
                lineBuffer->push_back(newstr);
                return lineBuffer;
            }
            if(str[i]=='\n') {
                break;
            }
            (*newstr)+=str[i];
            i++;
        }
        if(!isspace(str[i])){
            for(int j=i;j>0;j--){
                if(isspace(str[j])){
                    if(i-j>0) {
                        newstr->erase(cnt-(i-j),cnt);
                        newstr->append(" (->)");
                        i=j+1; //valjda?
                        break;
                    }
                    else throw WordWrapError();
                }
            }
        }
        if(str[i]==' ') newstr->append(" (->)");
        lineBuffer->push_back(newstr);
        if(isspace(str[i])) i++;
        newstr=new string();
    }
    return lineBuffer;
};

void Display::freeWordWrapBuffer(vector<string*> * v){
    for(vector<string*>::iterator i=v->begin(); i<v->end(); i++)
        //if((*i)!= nullptr) delete (*i);
    delete v;
};

void Display::putVector(vector<string*> * lines, Coord c){
    int i=0;
    for(vector<string*>::iterator it=lines->begin();it<lines->end();it++, i++){
        mvaddstr(c.getX()+i,c.getY(),(*it)->c_str());
    }
    freeWordWrapBuffer(lines);
}

void Display::testWW() {
    string s = "Subtitles downloaded from www.OpenSubtitles.org";
    vector<string *> *v = wordWrap(s, 23);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
    s = "- Captain.\n- Yes, sir?";
    v = wordWrap(s, 23);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
    s = "the ambassadors for the supreme\nchancellor wish to board immediately.";
    v = wordWrap(s, 23);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
}

void Display::putWrappedString(string content, Coord upperLeft, int lineW){
    if(lineW=-1) lineW=TEXT_WIDTH;
    vector<string*> *printbuffer=wordWrap(content,lineW);
    putVector(printbuffer,upperLeft);
    freeWordWrapBuffer(printbuffer);
};

void Display::putLastThree(){
    clearScrollWindow();
    refresh();
    for(int i=0; i<3 && lastThree[i]!= nullptr;i++) {
        mvaddstr(subCoord[i].getX(), subCoord[i].getY(), ((string) lastThree[i]->getTime().getStart()).c_str());
        refresh();
        mvaddstr(subCoord[i].getX() + 1, subCoord[i].getY(), ((string)  lastThree[i]->getTime().getEnd()).c_str());
        refresh();
        putWrappedString( lastThree[i]->getContent(), Coord(subCoord[i].getX() + 2, subCoord[i].getY()));
        refresh();
    }
};


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