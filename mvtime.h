//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_MVTIME_H
#define POOP_MVTIME_H

using std::ostream;

class mvtime {
protected:
    virtual void assign(mvtime newval)=0;
public:
    enum dir{LEFT, RIGHT};
    virtual string toString()=0;
    virtual shift(int dipsplacement, dir direction)=0;
    friend ostream& operator<<(ostream& os, mvtime& mv){
        os << mv.toString(); return os;
    }
    mvtime& operator=(mvtime newval){
        assign(newval);
        return *this;
    }
};

//izvesti za svaki format vremena

#endif //POOP_MVTIME_H
