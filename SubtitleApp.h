//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEAPP_H
#define POOP_SUBTITLEAPP_H

#include <conio.h>
#include <map>
#include "SubtitleIO.h"
#include <iostream>

#define W 119
#define A 97
#define S 115
#define D 100
#define Q 666
#define R 666
#define I 666
#define UP 72
#define DOWN 80


using std::map;
using std::cout;
using std::endl;

class SubtitleApp {
private:
    static map<int, void(*)()> * listingOptions;
    static SubtitleIO::SubtitleIter begin, iter, end;
    static void goBack(){
        if(iter!=begin) iter--;
    }
    static void goForward(){
        if(iter!=end) iter++;
    }
    static void insertTitle();
    static void removeTitle();
    static void shiftAll();
    static void printListingHelp(){
        cout<<"Opcije: A - pomeranje svih titlova;"
        <<endl<<"R - brisanje trenutnog titla"
        <<endl<<"I - dodavanje novog titla"
        <<endl<<"E - razdvajanje jednog titla na dva; "
        <<endl<<"D - spajanje dva titla u jedan;"
        <<endl<<"Navigacija W-S/Strelice"
        <<endl<<"Q - kraj rada"<<endl;
        while(!_kbhit());
        return;
    }
    static void initListingOptions();
    static void printMenu(){
        cout<<"Program za rukovanje DivX titlovima\nMilena Markovic, projektni zadatak za predmet POOP"
        <<endl<<"1. Prolazak kroz titlove"
        <<endl<< "2. Kraj rada sa trenutnim fajlom"
        <<endl<<"0. Kraj programa"
        <<endl;
    }
    static void listSubtitles(SubtitleIO& io);
public:
    static int main_app(){
    }
};

static map<int, void(*)()> * listingOptions=nullptr;

#endif //POOP_SUBTITLEAPP_H
