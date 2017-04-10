//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_MVTIME_H
#define POOP_MVTIME_H

#include <string>
#include <exception>

using std::ostream;
using std::string;
using std::exception;

class ImpossibleTimeRange: public exception{};
class NegativeTime: public exception{};

class mvTime {
protected:
    int hour_, minute_, second_, millisec_;
    static const int minuteMod=60, secondMod=60, milliMod=1000;
public:
    mvTime(int hour=0, int minute=0, int second=0, int millisec=0) {
        millisec_ = millisec % milliMod;
        second_ = (second + millisec / milliMod) % secondMod;
        minute_ = (minute + (second + millisec / milliMod) / secondMod) % minuteMod;
        hour_ = hour + (minute + (second + millisec / milliMod) / secondMod) / minuteMod;
    }
    mvTime operator+(mvTime t2);
    mvTime operator+(double sec);
    mvTime operator-(mvTime t2);
    mvTime operator-(double sec);
    bool operator>(mvTime t2);
    bool operator<(mvTime t2);
    friend ostream& operator<<(ostream& os, mvTime mvt){
        os<<mvt.hour_<<":"<<mvt.minute_<<":"<<mvt.second_<<"."<<mvt.millisec_;
        return os;
    }
    int getHour() const{ return hour_; }
    int getMinute() const { return minute_; }
    int getSecond() const { return second_; }
    int getMilli() const { return millisec_; }
    int toMillisec() const {
        return millisec_+second_*1000+minute_*60000+ hour_*360000;
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

    mvTime getStart() const{ return startTime; }
    mvTime getEnd() const { return endTime; }
};
//izvesti za svaki format vremena

#endif //POOP_MVTIME_H
