//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLE_H
#define POOP_SUBTITLE_H

#include "mvtime.h"
#include <string.h>
using std::string;

class Subtitle {
private:
    mvTimeRange time_;
    string content_;
public:
    Subtitle(const Subtitle& copy):time_(copy.time_), content_(copy.content_){};
    Subtitle(Subtitle& copy):time_(copy.time_), content_(copy.content_){};
    Subtitle(Subtitle&& copy):time_(copy.time_), content_(copy.content_){};
    Subtitle(mvTimeRange time, string content):content_(content), time_(time){};

    Subtitle& shiftTime(mvTime disp, mvTimeRange::dir direction){
        time_.shift(disp, direction);
        return *this;
    }
    Subtitle& extendFront(mvTime disp, mvTimeRange::dir direction){
        time_.shiftStart(disp, direction);
        return *this;
    }
    Subtitle& extendBack(mvTime disp, mvTimeRange::dir direction){
        time_.shiftEnd(disp,direction);
        return *this;
    }
    Subtitle& setTime(mvTimeRange time){
        time_=time;
        return *this;
    }
    Subtitle& changeContent(string newContent){
        content_=newContent;
        return *this;
    }
    string getContent(){
        return content_;
    }
    mvTimeRange getTime(){
        return time_;
    };

    Subtitle& operator=(const Subtitle& s);
    Subtitle& operator=(Subtitle& s);
};


#endif //POOP_SUBTITLE_H
