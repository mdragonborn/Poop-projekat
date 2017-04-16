//
// Created by Milena on 05/04/2017.
//

#include "Subtitle.h"

Subtitle& Subtitle::operator=(const Subtitle& s){
    time_=s.time_;
    content_=s.content_;
    return *this;
};
Subtitle& Subtitle::operator=(Subtitle& s){
    *this=s;
    return *this;
};