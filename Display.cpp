//
// Created by Milena on 01/05/2017.
//
#include <conio.h>
#include "Display.h"
#include <vector>
#include <windows.h>
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

//TODO hardcodovane koordinate odredi racunski sub[0](3,5),sub2(13,5), sub3(20,5)
Display::Display(int h, int w):winW(w), winH(h){
    initscr();
    if(w<50) {
        w=50; winW=50;
    }
    timeInputCoord=Coord(30,w-16);
    subCoord[0]=Coord(3,5);
    subCoord[1]=Coord(13,5);
    subCoord[2]=Coord(23,5);

    TEXT_WIDTH=(unsigned)w-30;
    TEXT_HEIGHT=8; //TODO
    TIMEIN_WIDTH=16;
    TIMEIN_HEIGHT=5;

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
        init_pair(SELECTION_PAIR,TEXT_COLOR,COLOR_GREEN);
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
    clear();
    putpictureMultiColor(0);
    //putpictureMultiColor(1);
    chtype format=A_BOLD|COLOR_PAIR(SELECTION_PAIR)|A_REVERSE;
    for(int i=0; i<menuOptions; i++,format=A_BOLD|COLOR_PAIR(BASE_PAIR)){
        const char * currentOption=(*currentMenu)[i].c_str();
        for(int j=0;j<(*currentMenu)[i].length();j++)
            mvaddch(20+2*i,winW/2-(*currentMenu)[i].length()/2+j,currentOption[j]|format);
    }
    currentMenuOption=0;
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
    if(prev && currentSub==1){
        lastThree[2]=lastThree[1];
        lastThree[1]=lastThree[0];
        lastThree[0]=prev;
        putLastThree();
        scrollBox(1); currentSub=1;
    } else if(prev && currentSub==2) {
        scrollBox(1); currentSub=1;
    }
    else {
        scrollBox(0); currentSub=0;
    }
    refresh();
};
void Display::scrollDown(Subtitle* next){
    if(next && currentSub==1){
        lastThree[0]=lastThree[1];
        lastThree[1]=lastThree[2];
        lastThree[2]=next;
        putLastThree();
        scrollBox(1); currentSub=1;
    } else if(next && currentSub==0){
        scrollBox(1); currentSub=1;
    }else {
        scrollBox(2);
        currentSub = 2;
    }
    refresh();
};
char * Display::clearBlock(int size){
    char* clearblock=new char[size+1];
    for(int i=0;i<size;i++) clearblock[i]=' ';
    clearblock[size]=0;
    return clearblock;
}

void  Display::clearScrollWindow(){
    char* clearblock=clearBlock(TEXT_WIDTH+2); Coord start(subCoord[0].getX()-1, subCoord[1].getY()-1);
    for(int i=0;i<(3*TEXT_HEIGHT+6);i++)
        mvaddstr(start.getX()+i,start.getY(),clearblock);
    delete clearblock;
}

void Display::displayMain(){

};
bool Display::menuUp(){
    if(currentMenuOption!=0) {
        chtype format = A_BOLD | COLOR_PAIR(BASE_PAIR);
        for (int i = 0; i < 2; i++, currentMenuOption--, format = A_BOLD
                            | COLOR_PAIR(SELECTION_PAIR) | A_REVERSE) {
            const char *currentOption = (*currentMenu)[currentMenuOption].c_str();
            for (int j = 0; j < (*currentMenu)[currentMenuOption].length(); j++)
                mvaddch(20 + 2 * currentMenuOption, winW / 2 -
                        (*currentMenu)[currentMenuOption].length() / 2 + j,
                        currentOption[j] | format);
        }
        return true;
    }
    return false;
};
bool Display::menuDown(){
    if(currentMenuOption!=menuOptions-1) {
        chtype format = A_BOLD | COLOR_PAIR(BASE_PAIR);
        for (int i = 0; i < 2; i++, currentMenuOption++, format = A_BOLD
                               | COLOR_PAIR(SELECTION_PAIR) | A_REVERSE) {
            const char *currentOption = (*currentMenu)[currentMenuOption].c_str();
            for (int j = 0; j < (*currentMenu)[currentMenuOption].length(); j++)
                mvaddch(20 + 2 * currentMenuOption, winW / 2 -
                        (*currentMenu)[currentMenuOption].length() / 2 + j,
                        currentOption[j] | format);
        }
        return true;
    }
    return false;
};

void Display::quitSavePrompt(){};  //TODO do you want to save before you exit?
void Display::savePromptShift(){};
void Display::displayText(string str){};
string Display::stringInput(Coord upperLeft, string prompt){};

vector<string *> * Display::wordWrap(string str, int lineSize, bool editable) {
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
        if(str[i]==' ' && !editable)newstr->append(" (->)");
        else if(str[i]=='\n' && editable) newstr->append("\n");
        lineBuffer->push_back(newstr);
        if(isspace(str[i])) i++;
        newstr=new string();
    }
    return lineBuffer;
};

void Display::freeWordWrapBuffer(vector<string*> * v){
    for(vector<string*>::iterator i=v->begin(); i<v->end(); i++);
        //if((*i)!= nullptr) delete (*i);
    delete v;
};

string Display::unwrap(vector<string*>* buffer){
    string rtVal="";
    for(vector<string*>::iterator i=buffer->begin(); i<buffer->end(); i++) {
        if ((*i)->length()>7 && !(*i)->substr((*i)->length() - 6, (*i)->length() - 1).compare(" (->)"))
            (*i)->erase((*i)->length() - 5, (*i)->length() - 1);
        rtVal.append(**i);
    }
    freeWordWrapBuffer(buffer);
    return rtVal;
};

void Display::putVector(vector<string*> * lines, Coord c, bool del){
    int i=0;
    for(vector<string*>::iterator it=lines->begin();it<lines->end();it++, i++){
        mvaddstr(c.getX()+i,c.getY(),(*it)->c_str());
    }
    if(del) freeWordWrapBuffer(lines);
}

void Display::testWW() {
    string s = "Subtitles downloaded from www.OpenSubtitles.org";
    vector<string *> *v = wordWrap(s, 23, false);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
    s = "- Captain.\n- Yes, sir?";
    v = wordWrap(s, 23, false);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
    s = "the ambassadors for the supreme\nchancellor wish to board immediately.";
    v = wordWrap(s, 23, false);
    for (vector<string *>::iterator i = v->begin(); i < v->end(); i++)
        cout << (**i) << endl;
}

void Display::putWrappedString(string content, Coord upperLeft, int lineW){
    if(lineW=-1) lineW=TEXT_WIDTH;
    vector<string*> *printbuffer= wordWrap(content, lineW, false);
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

string Display::editableText(string str, Coord upperLeft, int winh, int winw){
    //Coord winCursor=upperLeft;
    if(winw==-1) winw=20;
    if(winh==-1) winh=TEXT_HEIGHT;
    const char* clear=clearBlock(winw);
    Coord textCursor=Coord(0,0);
    vector<string*>* wrapped= wordWrap(str, winw, true);
    putVector(wrapped,upperLeft, false);
    textCursor=Coord(wrapped->size()-1,wrapped->back()->length()-2);
    auto winCursor=Coord(textCursor.getX()+upperLeft.getX(),textCursor.getY()+upperLeft.getY());
    mvaddch(winCursor.getX(),winCursor.getY(),(*(*wrapped)[textCursor.getX()])[textCursor.getY()]|A_REVERSE|COLOR_PAIR(BASE_PAIR));
    refresh();
    int input=0;
    short shiftKeyState;
    while (1) {
        while(1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW_KEY) input=_getch();
                break;
            }
        }
        if (input == ENTER_KEY) { delete clear; return unwrap(wrapped);}
        switch(input){
            case UP_KEY:{
                if(textCursor.getX()!=0){
                    textCursor.setX(textCursor.getX()-1);
                    if((*wrapped)[textCursor.getX()]->length() && (*wrapped)[textCursor.getX()]->length()<=textCursor.getY())
                        textCursor.setY((*wrapped)[textCursor.getX()]->length()-1);
                    else if(!(*wrapped)[textCursor.getX()]->length()) textCursor.setY(0); //TODO ?????
                }
                break;
            }
            case DOWN_KEY:{
                if(textCursor.getX()!=wrapped->size()-1){
                    textCursor.setX(textCursor.getX()+1);
                    if((*wrapped)[textCursor.getX()]->length() && (*wrapped)[textCursor.getX()]->length()<=textCursor.getY())
                        textCursor.setY((*wrapped)[textCursor.getX()]->length()-1);
                    else if(!(*wrapped)[textCursor.getX()]->length()) textCursor.setY(0); //TODO ?????
                }
                break;
            }
            case RIGHT_KEY:{
                string*thisRow=(*wrapped)[textCursor.getX()];
                if(textCursor.getY()!=thisRow->length()-1 && (*thisRow)[textCursor.getY()+1]!='\n'){
                    textCursor.setY(textCursor.getY()+1);
                }else if(textCursor.getX()!=wrapped->size()-1){
                    textCursor.set(textCursor.getX()+1,0);
                }
                break;
            }
            case LEFT_KEY:{
                if(textCursor.getY()!=0){
                    textCursor.setY(textCursor.getY()-1);
                }else if(textCursor.getX()!=0){
                    string * current=(*wrapped)[textCursor.getX()];
                    textCursor.set(textCursor.getX()-1,(*wrapped)[textCursor.getX()-1]->length()-1);
                    if((*current)[current->length()-1]=='\n') textCursor.setY(textCursor.getY()-1);
                }  //TODO sta ako je prazan red?
                break;
            }
            case BACKSPACE_KEY:{
                if(textCursor.getY()!=0){
                    (*wrapped)[textCursor.getX()]->erase(textCursor.getY()-1,1);
                    textCursor.setY(textCursor.getY()-1);
                }else{
                    if(textCursor.getX()!=0){
                        string*prev=(*wrapped)[textCursor.getX()-1];
                        int nextY=prev->length()-1;
                        if((*prev)[prev->length()-1]=='\n')
                            prev->erase(prev->length()-1,1);
                        prev->append(*(*wrapped)[textCursor.getX()]);
                        wrapped->erase(((*wrapped).begin()+textCursor.getX()));
                        textCursor.set(textCursor.getX()-1, nextY);
                    }
                } break;
            }
            case DEL_KEY:{
                if(textCursor.getY()!=(*wrapped)[textCursor.getX()]->length()-1){
                    (*wrapped)[textCursor.getX()]->erase(textCursor.getY(),1);
                }else{
                    if(textCursor.getX()!=wrapped->size()-1){
                        int newY=(*wrapped)[textCursor.getX()]->length();
                        string *current=(*wrapped)[textCursor.getX()];
                        current->append(*(*wrapped)[textCursor.getX()+1]);
                        wrapped->erase(((*wrapped).begin()+textCursor.getX()+1));
                    }
                } break;
            }
            default:{
                if(input>=0 && input<=127){
                    (*wrapped)[textCursor.getX()]->insert(textCursor.getY(),1,(char)input);
                    textCursor.setY(textCursor.getY()+1);
                }
                break;
            }
        }
        for(int i=0;i<winh;i++) {
            mvaddstr(upperLeft.getX() + i, upperLeft.getY(), clear);
            refresh();
        }
        putVector(wrapped,upperLeft,false);
        winCursor=Coord(textCursor.getX()+upperLeft.getX(),textCursor.getY()+upperLeft.getY());
        mvaddch(winCursor.getX(),winCursor.getY(),(*(*wrapped)[textCursor.getX()])[textCursor.getY()]|A_REVERSE|A_BOLD|COLOR_PAIR(BASE_PAIR));
        refresh();
    }
}

string Display::contentEditCurrent(){
    string rtvalue=editableText(lastThree[currentSub]->getContent(),Coord(subCoord[currentSub].getX()-2, subCoord[currentSub].getY()), TEXT_HEIGHT-2, TEXT_WIDTH);
    return rtvalue;
};

void Display::refreshScrolled(){
    putLastThree();
    scrollBox(currentSub);

};

void Display::setNewMenu(string ** newOptions, int optionCount){
    menuOptions=optionCount;
    currentMenu=newOptions;
};
/*void Display::displayTitles();
void Display::displayMain();
void Display::displaySettings();
void Display::displayGetAddress();
void Display::scrollUp();
void Display::scrollDown();
void Display::setCurentSubs(Subtitles& subs);
string Display::stringInput(Coord upperLeft);
*/