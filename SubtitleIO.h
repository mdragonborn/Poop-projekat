//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitle.h"
#include <vector.h>
#include <sting.h>

using std::vector;
using std::string;

class SubtitleIO {
private:
    vector <Subtitle> SubLines;  //mapa?
    FILE source_file; //FILE ili string? da li drzati fajl sve vreme otvorenim tak oda druge aplikacije ne mogu da ga diraju?
public:
    SubtitleIO(string source_path);
    virtual SubtitleIO& merge_title()=0; //args?
    virtual SubtitleIO& split_title()=0; //args?
    virtual SubtitleIO& shift_title(mvtime start, mvtime end)=0;
};


#endif //POOP_SUBTITLEIO_H
