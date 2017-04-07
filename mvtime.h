//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_MVTIME_H
#define POOP_MVTIME_H

#include <string>

using std::ostream;
using std::string;

class mvtime {
protected:
public:
    struct mvtimeRange{
        mvtime startTime;
        mvtime endTime;
        mvtimeRange(mvtime start, mvtime end){
            startTime=start;
            endTime=end;
        }
    };
    string toString();
    shift(int displacement);
    ostream& operator<<(ostream& os, mvtime& mv){
        os << mv.toString(); return os;
    }
};

//izvesti za svaki format vremena

#endif //POOP_MVTIME_H
