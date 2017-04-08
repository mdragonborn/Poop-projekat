//
// Created by Milena on 08/04/2017.
//

#include "mvtime.h"

mvTime mvTime::operator+(mvTime t2){
    return mvTime(hour_+t2.hour_, minute_+t2.hour_, second_+t2.second_, millisec_+t2.millisec_);
}
mvTime mvTime::operator+(double sec){
    return mvTime(hour_, minute_, second_+sec/1, millisec_+sec%1);
}
mvTime mvTime::operator-(mvTime t2){
    mvtime temp(hour_-t2.hour_, minute_-t2.hour_, second_-t2.second_, millisec_-t2.millisec_);
    if(temp.hour_<0 || temp.minute_<0 || temp.second_<0 || millisec_<0) return mvtime();
    else return temp;
}
mvTime mvTime::operator-(double sec){
    mvTime temp(hour_, minute_, second_-sec/1, millisec_-sec%1);
    if(temp.hour_<0 || temp.minute_<0 || temp.second_<0 || millisec_<0) return mvtime();
    else return temp;
}
bool mvTime::operator>(mvtime t2){
    if (hour_>t2.hour_) return true;
    else if (hour_==t2.hour)
        if(minute_>t2.minute_) return true;
        else if (minute_==t2.minute_)
            if(second_>t2.second_) return true;
            else if (millisec_>t2.millisec_) return true;
            else return false;
}