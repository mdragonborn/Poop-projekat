//
// Created by Milena on 05/04/2017.
//

#include "Subtitle.h"
using namespace std;
Subtitle& Subtitle::operator=(const Subtitle& s){
    time_=s.time_;
    content_=s.content_;
    return *this;
};
Subtitle& Subtitle::operator=(Subtitle& s){
    *this=s;
    return *this;
};

Subtitle::operator string() {
    string rtvalue;
    char buffer[3];
    rtvalue+=mvTime::itos(time_.getStart().getHour())+":"+mvTime::itos(time_.getStart().getMinute());
    rtvalue+=":"+mvTime::itos(time_.getStart().getSecond())+"."+mvTime::itos(time_.getStart().getMilli()).append(" - ");
    rtvalue.append(mvTime::itos(time_.getEnd().getHour())+":"+mvTime::itos(time_.getEnd().getMinute()));
    rtvalue+=":"+mvTime::itos(time_.getEnd().getSecond())+"."+mvTime::itos(time_.getEnd().getMilli());
    rtvalue+=content_;
    return rtvalue;
}

string* Subtitle::splitInLines(int n, int len){
    string * rtValue=new string[n]();
};
