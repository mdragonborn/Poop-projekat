//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEAPP_H
#define POOP_SUBTITLEAPP_H

#include <conio.h>
#include <map>
#include "SubtitleIO.h"
#include "Display.h"
#include <iostream>

#define W 119
#define A 97
#define S 115
#define D 100
#define Q 113
#define R 114
#define I 105
#define H 104
#define E 101
#define F 102 //? vrv
#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT 75
#define RIGHT 77
#define ARROW_KEY 224
#define ENTER_KEY 13


using std::map;
using std::cout;
using std::endl;

class SubtitleApp {
private:
    typedef void(SubtitleApp::*fun_ptr)();

    map<int, fun_ptr> *listingOptions=nullptr;
    map<int, fun_ptr> *mainOptions=nullptr;
    map<int, fun_ptr> *editOptions=nullptr;
    SubtitleIter begin, iter, end, back;
    Display *display=nullptr;
    Subtitles *loaded=nullptr;
    fun_ptr mainLoaded[4];
    string * mainLoadedStr;
    fun_ptr mainNotLoaded[3];
    string * mainNotLoadedStr;
    int mainCursor;
    int mainCursorMax;

    void callMainOption();

    //Navigacija unutar listSubtitles
    void listSubtitles(Subtitles &subs);

    void goBack() {
        //if(iter!=begin) iter--;
    }

    void goForward() {
        //if(iter!=end) iter++;
    }

    //opcije iz menija
    void insertTitle();

    void removeTitle();

    void shiftAll();

    void printListingHelp();

    void initListingOptions();

    void initMainOptions();

    void initEditOptions();

    /*
     * MAIN MENU NAVIGATION
     * */
    void mainGoUp();

    void mainGoDown();

    void mainSelect();

    /*
     * MAIN MENU OPTIONS
     * */
    void subExport();

    void edit();

    void showAbout();

    void quitApp();

    void load();

    /*
     * EDITING MENU METHODS
     * */
    void removeCurrent();

    void insertNew();

    void scrollUp();

    void scrollDown();

    void find();

    void splitTitle();

    void mergeTitles();

    void editContent();

public:
    SubtitleApp() {
        begin = SubtitleIter();
        iter = SubtitleIter();
        end = SubtitleIter();
        back = SubtitleIter();
        loaded = nullptr;
        mainLoaded[0] = &SubtitleApp::subExport;
        mainLoaded[1] = &SubtitleApp::edit;
        mainLoaded[2] = &SubtitleApp::showAbout;
        mainLoaded[3] = &SubtitleApp::quitApp;
        mainNotLoaded[0] = &SubtitleApp::load;
        mainNotLoaded[1] = &SubtitleApp::showAbout;
        mainNotLoaded[2] = &SubtitleApp::quitApp;
        mainLoadedStr=new string[4];
        mainNotLoadedStr=new string[3];
        mainLoadedStr[0] = "Export";
        mainLoadedStr[1] = "Edit";
        mainLoadedStr[2] = "About subWars";
        mainLoadedStr[3] = "Exit";
        mainNotLoadedStr[0] = "Load";
        mainNotLoadedStr[1] = "About subWars";
        mainNotLoadedStr[2] = "Exit";
        mainCursor = 0;
        mainCursorMax = 2;
    }

    int main_app();
};










#endif //POOP_SUBTITLEAPP_H
