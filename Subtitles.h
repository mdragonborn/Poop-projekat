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
class BadIterator: public exception{};
typedef std::vector<Subtitle>::iterator SubtitleIter;

class Subtitles {
private:
    vector <Subtitle> SubLines;  //mapa?
    string filename;
    void shiftEdges(SubtitleIter begin, SubtitleIter end, mvTimeRange range, mvTime disp, mvTimeRange::dir direction);
public:
    Subtitles(){};
    //TODO destruktor treba da unistava elemente iz vektora jer su dinamicki alocirani
    //TODO istrazi ispavnu implementaciju SubtitleIter
    //Navigacija kroz titlove
    SubtitleIter begin();
    SubtitleIter end();
    SubtitleIter findClosestTime(mvTime targetTime);

    //Izmene titlova
    Subtitles& pushBackNew(Subtitle subt);
    Subtitle& getSubtitleAtTime(mvTime timePoint);
    Subtitles& insertBefore(SubtitleIter iter, Subtitle sub);
    Subtitles& insert(Subtitle sub);

    //vremenska izmena
    Subtitles& shiftCurrent(SubtitleIter current, mvTime displacement, mvTimeRange::dir direction);
    Subtitles& shiftInRange(mvTimeRange range, mvTime displacement, mvTimeRange::dir direction);
    Subtitles& mergeWithNext(SubtitleIter current);
    Subtitles& splitCurrent(SubtitleIter current);
    Subtitles& removeAtTime(mvTime timePoint);
    Subtitles& remove(SubtitleIter iter);
};


#endif //POOP_SUBTITLES_H
