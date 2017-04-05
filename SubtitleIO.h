//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitle.h"
#include <vector.h>
#include <sting.h>
#include <iterator>

using std::vector;
using std::string;

class SubtitleIO {
private:
    vector <Subtitle> SubLines;  //mapa?
    string filename;
    FILE source_file; //FILE ili string? da li drzati fajl sve vreme otvorenim tak oda druge aplikacije ne mogu da ga diraju?
public:
    typedef vector<Subtitle>::iterator SubtitleIter;
    SubtitleIO(string source_path):filename(source_path){};
    virtual SubtitleIO& merge_title()=0; //args?
    virtual SubtitleIO& split_title()=0; //args?
    virtual SubtitleIO& shift_title(mvtime start, mvtime end, int disp)=0;
    string fileName()const{
        return filename;
    }
    SubtitleIter begin()const{
        return SubLines.begin();
    }
    SubtitleIter end()const{
        return SubLines.end();
    }
    virtual string unit()const =0;
};


#endif //POOP_SUBTITLEIO_H
