//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitles.h"
#include <vector>
#include <string>
#include <iterator>

using std::vector;
using std::string;

class SubtitleIO {
protected:
    SubtitleIO();
    static SubtitleIO * instance_;
public:
    virtual static SubtitleIO * createObject()=0;

};


#endif //POOP_SUBTITLEIO_H
