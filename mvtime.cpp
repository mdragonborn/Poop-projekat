//
// Created by Milena on 08/04/2017.
//

#include "mvtime.h"

using namespace std;

mvTime mvTime::operator+(mvTime t2){
    return mvTime(hour_+t2.hour_, minute_+t2.hour_, second_+t2.second_, millisec_+t2.millisec_);
}
mvTime mvTime::operator+(double sec){
    return mvTime(hour_, minute_, second_+(long)sec, millisec_+(int)(1000*(sec-(long)sec)));  //TODO teeba sec mod 1
}
mvTime mvTime::operator-(mvTime t2){
    cout<<"t1 "<<*this<<" t2 "<<t2<<endl;
    mvTime temp(hour_-t2.hour_, minute_-t2.minute_, second_-t2.second_, millisec_-t2.millisec_);
    if(temp.millisec_<0) {
        temp.millisec_ += 1000;
        temp.second_--;
    }
    if(temp.second_<0){
        temp.second_+=60;
        temp.minute_--;
    }
    if(temp.minute_<0){
        temp.minute_+=60;
        temp.hour_--;
    }
    if(temp.hour_<0 || temp.minute_<0 || temp.second_<0 || millisec_<0) throw NegativeTime();
    else return temp;
}
mvTime mvTime::operator-(double sec){
    cout<<"t1 "<<*this<<" s "<<sec<<endl;
    mvTime temp(hour_, minute_, second_-(long)sec, millisec_-(int)(1000*(sec-(long)sec)));
    if(temp.millisec_<0) {
        temp.millisec_ += 1000;
        temp.second_--;
    }
    if(temp.second_<0){
        temp.second_+=60;
        temp.minute_--;
    }
    if(temp.minute_<0){
        temp.minute_+=60;
        temp.hour_--;
    }
    if(temp.hour_<0 || temp.minute_<0 || temp.second_<0 || millisec_<0) throw NegativeTime();
    else return temp;
}
bool mvTime::operator>(mvTime t2){
    if (hour_>t2.hour_) return true;
    else if (hour_==t2.hour_) {
        if (minute_ > t2.minute_) return true;
        else if (minute_ == t2.minute_) {
            if (second_ > t2.second_) return true;
            else if (second_==t2.second_){
                if (millisec_ > t2.millisec_) return true;
                else return false;
            }
        }
    }
    return false;
}

bool mvTime::operator<(mvTime t2){
    return (t2>*this);
}

bool mvTime::operator!=(mvTime t2){
    return !(*this==t2);
}

bool mvTime::operator==(mvTime t2){
    return hour_==t2.hour_ && minute_==t2.minute_ && second_==t2.second_ && millisec_==t2.millisec_;
}

bool mvTime::operator>=(mvTime t2){
    return *this==t2 || *this>t2;
};
bool mvTime::operator<=(mvTime t2){
    return *this==t2 || *this<t2;
};

mvTimeRange& mvTimeRange::shift(mvTime disp, dir direction){
    mvTime tempEnd, tempStart;
    if(direction==FWD){
        endTime=endTime+disp;
        startTime=startTime+disp;
    }
    else{
        try{
            tempEnd=endTime-disp;
            tempStart=startTime-disp;
        }catch(NegativeTime) { throw; }
        endTime=tempEnd;
        startTime=tempStart;
    }
    return *this;
}

mvTimeRange& mvTimeRange::shiftStart(mvTime disp, dir direction){
    if(direction==FWD){
        startTime=startTime+disp;
        if(startTime>endTime) throw  ImpossibleTimeRange();
    } else{
        try{
            startTime=startTime-disp;
        }catch(NegativeTime) { throw; }
    }
    return *this;
}

mvTimeRange& mvTimeRange::shiftEnd(mvTime disp, dir direction){
    if(direction==FWD){
        endTime=endTime+disp;
    } else{
        try{
            endTime=endTime-disp;
        } catch(NegativeTime){ throw; }
        if (startTime>endTime) throw  ImpossibleTimeRange();
    }
    return *this;
}

mvTimeRange& mvTimeRange::setStart(mvTime newStart){
    if (newStart>endTime) throw ImpossibleTimeRange();
    startTime=newStart;
    return *this;
}

mvTimeRange& mvTimeRange::setEnd(mvTime newEnd){
    if (startTime>newEnd) throw ImpossibleTimeRange();
    endTime=newEnd;
    return *this;
}

bool mvTimeRange::checkOverlap(mvTimeRange range){
    return (range.startTime>startTime && endTime>range.startTime) || (startTime>range.startTime && range.endTime>startTime);
};

bool mvTimeRange::contains(mvTime time){
    return time>startTime && time<endTime;
};

mvTimeRange& mvTimeRange::operator=(mvTimeRange r2){
    startTime=r2.startTime;
    endTime=r2.endTime;
    return *this;
};