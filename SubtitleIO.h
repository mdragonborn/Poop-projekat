//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitles.h"
#include <vector>
#include <string>
#include <iterator>

//using std::vector;
//using std::string;

template <class Format> class SubtitleIO{
protected:
    static Format * instance_= nullptr;
public:
    static Format * createObject(){
        if (!instance_)
            instance_=new Format();
        return instance_;
    };
    virtual Subtitle * loadSubtitle(); //vidi implementaciono kako ti odgovara
    virtual bool export(string path, Subtitle& subtitle)=0;
};

class SubRipIO: public SubtitleIO<SubRipIO>{
private:
    SubipIO():{};
};
//static SubRipIO * SubRipIO::instance_=nullptr;


class MicroDVDIO: public SubtitleIO{
private:
    SubipIO():{};
};
//static MicroDVDIO * MicroDVDIO::instance_=nullptr;


class MplayerIO: public SubtitleIO{
private:
    SubipIO():{};
};
//static MplayerIO * MplayerIO::instance_=nullptr;


#endif //POOP_SUBTITLEIO_H