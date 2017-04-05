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
    mvtime time_;
    string content_;
public:
    Subtitle(mvtime time, string content){
        time_=time;
        content_=content;
    }
    Subtitle& shiftTime(int disp, dir direction){
        time_.shift(disp, direction);
        return *this;
    }
};


#endif //POOP_SUBTITLE_H
