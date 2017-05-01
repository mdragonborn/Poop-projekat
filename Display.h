//
// Created by Milena on 01/05/2017.
//

#ifndef POOP_DISPLAY_H
#define POOP_DISPLAY_H


#include "Subtitles.h"

class Display {
private:
    struct Coord{
        int x, y;
        Coord(int X=0, int Y=0):x(X),y(Y){}
    };
    Subtitles* currentSubs_= nullptr;
    static const int BLUE, RED, GREEN, WHITE, YELLOW, ORANGE, BLACK, GREY;
    static const int colorPairs; //TODO osmisliti koji us potrebni
    int BCGD_COLOR, TEXT_COLOR, SELECTION_COLOR;
    int winW, winH;
    Coord importantCoords[10]; //TODO isto osmisliti koji su potrebni
    char ** asciiArt;
public:
    Display();
    void generateHomeScr();
    void initSc();
    void displayTitles();
    void displayMain();
    void displaySettings();
    void displayGetAddress();
    void scrollUp();
    void scrollDown();
    void setCurentSubs(Subtitles& subs);
    void editableText(string str);
    string retEdited();
};


#endif //POOP_DISPLAY_H
