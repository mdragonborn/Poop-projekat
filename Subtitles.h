//
// Created by Milena on 07/04/2017.
//

#ifndef POOP_SUBTITLES_H
#define POOP_SUBTITLES_H

#include "Subtitle.h"
#include <vector>
#include <exception>

using std::vector;
using std::exception;

class TimeOutOfRange: public exception{};
class OverlappingTimeRange: public exception{};

class Subtitles {
private:
    vector <Subtitle> SubLines;  //mapa?
    string filename;
    void appendSubLine(Subtitle sub){};
public:
    Subtitles(){};
    //TODO istrazi ispavnu implementaciju SubtitleIter
    //Navigacija kroz titlove
    typedef std::vector<Subtitle>::iterator SubtitleIter;
    SubtitleIter begin();
    SubtitleIter end();
    SubtitleIter findClosestTime(mvTime targetTime);

    //Izmene titlova
    void pushBackNew(Subtitle subt);
    Subtitle& getSubtitleAtTime(mvTime time);
    void insertBefore(SubtitleIter iter, Subtitle sub);
    void insertAfter(Subtitle iter, Subtitle sub);

    //vremenska izmena
    void shiftCurrent(SubtitleIter current, mvTime displacement, mvTimeRange::dir direction){};
    void shiftInRange(mvTimeRange range, mvTime displacement, mvTimeRange::dir direction){};
    void mergeWithNext(SubtitleIter current){};
    void splitCurrent(SubtitleIter current){};
};


#endif //POOP_SUBTITLES_H
