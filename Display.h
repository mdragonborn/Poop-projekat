//
// Created by Milena on 01/05/2017.
//

#ifndef POOP_DISPLAY_H
#define POOP_DISPLAY_H


#include "Subtitles.h"
#include <curses.h>
#include <functional>

class Coord{
private:
    int x, y;
public:
    Coord(int X=0, int Y=0):x(X),y(Y){}
    Coord(Coord& c):x(c.x),y(c.y){}
    Coord(Coord&& c):x(c.x),y(c.y){}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
};

class AsciiPicture{
protected:
    Coord upperLeftCorner;
    int height, width;
    string** art;
public:
    AsciiPicture(Coord upperLeft, int h, int w):upperLeftCorner(upperLeft),height(h),width(w){};

    virtual int getColorPair(int x, int y)=0;
    char getCh(int x, int y){
        return (*art)[x][y];
    }
    const string getLine(int x){
        return (*art)[x];
    }

    const Coord &getUpperLeftCorner() const {
        return upperLeftCorner;
    }
    int getHeight() const {
        return height;
    }
    int getWidth() const {
        return width;
    }
};
class Yoda: public AsciiPicture{
private:
    string *__yoda=new string[11]{"        .--.\n",
                              "\\`--._.'.::.`._.--'/\n",
                              " :.  ` __::__ '_ .:\n",
                              "   :-:.`'..`'.| |\n",
                              "     _\\_`--' /| |__\n",
                              "    / __| | | | '_ \\    \n",
                              "    \\__ \\ |_| | |_) |   \n",
                              "__  |___/\\__,_|_,__/___ \n",
                              "\\ \\ /\\ / / _` | '__/ __|\n",
                              " \\ V  V / (_| | |  \\__ \\\n",
                              "  \\_/\\_/ \\__,_|_|  |___/"};
public:
    Yoda(Coord upperLeft):AsciiPicture(upperLeft,11,24){
        art=(&__yoda);
    };
    virtual int getColorPair(int x, int y);
};
class C3P0: public AsciiPicture{
private:
    string * __c3p0=new string[16]{"  \\  .-.\n",
                            "    /_ _\\\n",
                            "    |o^o|\n",
                            "    \\ _ /\n",
                            "   .-'-'-. \n",
                            " /`)  .  (`\\\n",
                            "/ /|.-'-.|\\ \\\n",
                            "\\ \\| (_) |/ /\n",
                            " \\_\\'-.-'/_/\n",
                            " /_/ \\_/ \\_\\\n",
                            "   |'._.'|\n",
                            "   |  |  |\n",
                            "    \\_|_/\n",
                            "    |-|-|\n",
                            "    |_|_|\n",
                            "   /_/ \\_\\ "};
public:
    C3P0(Coord upperLeft):AsciiPicture(upperLeft,16,14){
        art=&__c3p0;
    };
    virtual int getColorPair(int x, int y);
};
class R2D2: public AsciiPicture{
private:
    string * __r2d2=new string[10]{"         /\n",
                            "   .-\"\"-.\n",
                            "  /[] _ _\\\n",
                            " _|_o_LII|_\n",
                            "/ | ==== | \\\n",
                            "|_| ==== |_|\n",
                            " ||\" ||  ||\n",
                            " ||LI  o ||\n",
                            " ||'----'||\n",
                            "/__|    |__\\"};
public:
    R2D2(Coord upperLeft): AsciiPicture(upperLeft,10,12){
        art=&__r2d2;
    };
    virtual int getColorPair(int x, int y);
};
class TIEfighter: public AsciiPicture{
private:
    string *__tie=new string[12]{"  _                   _  \n",
                          " | |                 | | \n",
                          " | |                 | | \n",
                          " | |                 | | \n",
                          " | |      .---.      | | \n",
                          " | |   _.'\\   /'._   | | \n",
                          "/  b_-- | .'\"'. | --_d  \\\n",
                          "\\  p\"--_| '._.' |_--\"q  /\n",
                          " | |     ./   \\.     | | \n",
                          " | |      '---'      | | \n",
                          " | |                 | | \n",
                          " |_|                 |_| "};
public:
    TIEfighter(Coord upperLeft): AsciiPicture(upperLeft,12,26){
        art=&__tie;
    };
    virtual int getColorPair(int x, int y);
};

class Display {
private:
    friend class AsciiPicture;
    friend class Yoda;
    friend class C3P0;
    friend class R2D2;
    friend class TIEfighter;
    static const short BASE_PAIR=1, C3P0_PAIR=2, R2D2W_PAIR=3, R2D2B_PAIR=4, R2D2R_PAIR=5, YODA_PAIR=6; //TODO osmisliti koji us potrebni
    // Subtitles* currentSubs_= nullptr;
    short BCGD_COLOR, TEXT_COLOR, SELECTION_COLOR;
    int winW, winH;
    AsciiPicture** asciiArt;
    void initAscii();
    string ** currentMenu= nullptr;
    int menuOptions=0;
    Coord sub1,sub2, sub3;
    int selectedSub;
public:
    Display(int h, int w);
    void generateHomeScr(bool loaded=false);
    void putpictureMultiColor(int picID);
    void generateFrame(int h, int w, Coord upperLeft);
    void initScrolling(Subtitles * subs);
    void setNewMenu(string * newOptions[], int optionCount);  //TODO cuva u currentMenu i menuOpotions
    void initSearch();
    void displayMain();
    void mainUp();
    void mainDown();
    void displaySettings();
    void displayGetAddress();
    void quitSavePrompt();  //TODO do you want to save before you exit?
    void savePromptShift();
    void scrollUp(Subtitle* prev);
    void scrollDown(Subtitle* next);
    void setCurentSubs(Subtitles& subs);
    void editableText(string str, Coord upperLeft);
    void displayText(string str);
    string stringInput(Coord upperLeft, string prompt);
};

#endif //POOP_DISPLAY_H
