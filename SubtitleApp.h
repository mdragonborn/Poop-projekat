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
#define Q 666
#define R 666
#define I 666
#define H 666
#define E 666
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ARROW 224
#define ENTER 13


using std::map;
using std::cout;
using std::endl;

class SubtitleApp {
private:
    typedef void(*fun_ptr)();
    static map<int, fun_ptr> * listingOptions;
    static map<int, fun_ptr> * mainOptions;
    static SubtitleIter begin, iter, end;
    static Display* display;
    static Subtitles * loaded;
    static fun_ptr mainLoaded[4];
    static string mainLoadedStr[4];
    static fun_ptr mainNotLoaded[3];
    static string mainNotLoadedStr[3];

    static int mainCursor;
    static int mainCursorMax;
    static void callMainOption();

    //Navigacija unutar listSubtitles
    static void listSubtitles(Subtitles &subs);
    static void goBack(){
        //if(iter!=begin) iter--;
    }
    static void goForward(){
        //if(iter!=end) iter++;
    }

    //opcije iz menija
    static void insertTitle();
    static void removeTitle();
    static void shiftAll();

    static void printListingHelp();
    static void initListingOptions();
    static void initMainOptions();
    static void printMenu();

    static void splitTitle();
    static void mergeTitles();

    static void mainGoUp();
    static void mainGoDown();
    static void mainSelect();

    static void subExport();
    static void edit();
    static void showAbout();
    static void quitApp();
    static void load();
public:
    static int main_app();
};

map<int, void(*)()> * SubtitleApp::listingOptions=nullptr;
map<int, void(*)()> * SubtitleApp::mainOptions=nullptr;
Display* SubtitleApp::display=nullptr;
SubtitleIter SubtitleApp::begin=SubtitleIter(), SubtitleApp::iter=SubtitleIter(), SubtitleApp::end=SubtitleIter();
Subtitles * SubtitleApp::loaded;
SubtitleApp::fun_ptr SubtitleApp::mainLoaded[4]={&SubtitleApp::subExport, &SubtitleApp::edit, &SubtitleApp::showAbout, &SubtitleApp::quitApp};
SubtitleApp::fun_ptr SubtitleApp::mainNotLoaded[3]={&SubtitleApp::load, &SubtitleApp::showAbout, &SubtitleApp::quitApp};
string SubtitleApp::mainLoadedStr[4]={"Export", "Edit", "About subWars", "Exit"};
string SubtitleApp::mainNotLoadedStr[3]={"Load","About subWars", "Exit"};
int SubtitleApp::mainCursor=0;
int SubtitleApp::mainCursorMax=0;

#endif //POOP_SUBTITLEAPP_H
