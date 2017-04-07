//
// Created by Milena on 07/04/2017.
//

#include "SubtitleIO.h"

SubtitleIO * SubRipIO::createObject(){
    if (!instance_)
        instance_=new SubRipIO();
    return instance_;
}

MicroDVDIO * MicroDVDIO::createObject(){
    if (!instance_)
        instance_=new MicroDVDIO();
    return instance_;
}

MplayerIO * MplayeIO::createObject() {
    if (!instance_)
        instance_ = new MplayerIO();
    return instance_;
}



