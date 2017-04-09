//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLE_H
#define POOP_SUBTITLE_H

#include "mvtime.h"
#include <string.h>
using std::string;


//TODO nakon projektovanja Subtitles implementirati sve sto treba u Subtitle
class Subtitle {
private:
    mvTimeRange time_;
    string content_;
public:
    Subtitle(mvTimeRange time, string content):content_(content), time_(time){}; //vidi ovde sa ovim polimorfizmom sta ces
    Subtitle& shiftTime(int disp, mvTimeRange::dir direction){
        time_.shift(disp, direction);
        return *this;
    }
    Subtitle& extendFront(int disp, mvTimeRange::dir direction){
        time_.shiftStart(disp, diection);
        return *this;
    }
    Subtitle& extendBack(int disp, mvTimeRange::dir direction){
        time_.shiftEnd(disp,direction);
        retun *this;
    }
    Subtitle& setTime(mvTimeRange time){
        time_=time;
        return *this;
    }
    Subtitle& changeContent(string newContent){
        content_=newContent;
        return *this;
    }
    string getContent() const {
        return content_;
    }
    mvTimeRange getTime() const {
        return time_;
    };
};


#endif //POOP_SUBTITLE_H
