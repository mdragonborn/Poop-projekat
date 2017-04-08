//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_MVTIME_H
#define POOP_MVTIME_H

#include <string>

using std::ostream;
using std::string;

class mvTime {
protected:
    int hour_, minute_, second_, millisec_;
    static const int minuteMod=60, secondMod=60, milliMod=1000;
public:
    mvTime(int hour=0, int minute=0, int second=0, int millisec=0) {
        millisec_ = millisec % milliMod;
        second_ = (second + millisec / milliMod) % secondMod;
        minute_ = (minute + (second + millisec / milliMod) / secondMod) % minutueMod;
        hour_ = hour + (minute + (second + millisec / milliMod) / secondMod) / minutueMod;
    }
    mvTime operator+(mvTime t2);
    mvTime operator+(double sec);
    mvTime operator-(mvTime t2);
    mvTime operator-(double sec);
    bool operator>(mvtime t2);
    ostream& operator<<(ostream& os, mvtime& mv){
        os << mv.toString(); return os;
    }
};

class mvTimeRange{
    mvTime startTime;
    mvTime endTime;
public:
    enum dir{FWD, BACK};
    mvTimeRange(mvTime start, mvTime end){
        startTime=start;
        endTime=end;
    }
    mvTimeRange& shift(mvTime disp, dir direction);
    mvTimeRange& shiftStart(mvTime disp, dir direction);
    mvTimeRange& shiftEnd(mvTime disp, dir direction);
    mvTimeRange& setStart(mvTime newStart);
    mvTimeRange& setEnd(mvTime newEnd);
    bool checkOverlap(mvTimeRange range);
};
//izvesti za svaki format vremena

#endif //POOP_MVTIME_H
