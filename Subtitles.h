//
// Created by Milena on 07/04/2017.
//

#ifndef POOP_SUBTITLES_H
#define POOP_SUBTITLES_H

#include "Subtitle.h"
#include <vector>
using std::vector;

//TODO projektovati Subtitles tako da sve obrade moze da radi sama
class Subtitles {
private:
    vector <Subtitle> SubLines;  //mapa?
    string filename;
    void appendSubLine(Subtitle sub);
public:
    Subtitles(){};

    //TODO istrazi ispavnu implementaciju SubtitleIter
    //Navigacija kroz titlove
    typedef std::vector<Subtitle>::const_iterator SubtitleIter;
    SubtitleIter begin()const{ return SubLines.begin(); }
    SubtitleIter end()const{ return SubLines.end(); }
    SubtitleIter findClosestTime(mvTime targetTime); //bin search, da li int ili iterator?

    //Izmene titlova
    void insertNew(Subtitle subt);
    void alterAtTime(mvTimeRange time);
    void removeSubtitle(SubtitleIter sub); //???

    //vremenska izmena
    void shiftCurrent(SubtitleIter current, mvTime displacement, mvTimeRange::dir direction);
    void shiftInRange(mvTimeRange range, mvTime displacement, mvTimeRange::dir direction);
    void mergeWithNext(SubtitleIter current);
    void splitCurrent(SubtitleIter current);
};


#endif //POOP_SUBTITLES_H
