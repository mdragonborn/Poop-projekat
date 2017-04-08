//
// Created by Milena on 07/04/2017.
//

#ifndef POOP_SUBTITLES_H
#define POOP_SUBTITLES_H

#include "Subtitle.h"
#include <vector>
using std::vector;

class Subtitles {
private:
    vector <Subtitle> SubLines;  //mapa?
    string filename;
    FILE source_file; //FILE ili string? da li drzati fajl sve vreme otvorenim tak oda druge aplikacije ne mogu da ga diraju?
    void append(mvTimeRange time, string content);
public:
    Subtitles(){};
    void insertNew(Subtitle subt);
    void alterAtTime(mvTimeRange time);
    Subtitle& getSubtitleAtTime(mvTimeRange time);

    typedef std::vector<Subtitle>::const_iterator SubtitleIter;
    SubtitleIter begin()const{
        return SubLines.begin();
    }
    SubtitleIter end()const{
        return SubLines.end();
    }
};


#endif //POOP_SUBTITLES_H
