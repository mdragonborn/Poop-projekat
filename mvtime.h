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
    enum dir{LEFT, RIGHT};
    virtual string toString()=0;
    virtual shift(int dipsplacement, dir direction)=0;
    friend ostream& operator<<(ostream& os, mvtime& mv){
        os << mv.toString(); return os;
    }
    virtual void assign(mvtime * newval)=0;
};

//izvesti za svaki format vremena

#endif //POOP_MVTIME_H
