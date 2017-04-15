//
// Created by Milena on 07/04/2017.
//

#include "Subtitles.h"

SubtitleIter Subtitles::findClosestTime(mvTime targetTime){
    SubtitleIter begin=SubLines.begin();
    SubtitleIter end=SubLines.end();
    SubtitleIter mid=SubLines.begin()+(end-begin)/2;
    if (targetTime>(*end).getTime().getEnd()) throw TimeOutOfRange();
    while(begin!=end){
        if((*mid).getTime().contains(targetTime)) break;
        if((*mid).getTime().getEnd()<targetTime)
            begin=mid+1;
        else
            end=mid-1;
        mid=begin+(end-begin)/2;
    }
    return mid;
};

Subtitle& Subtitles::getSubtitleAtTime(mvTime time){
    return *findClosestTime(time);
};

SubtitleIter Subtitles::begin(){
    return SubLines.begin();
}

SubtitleIter Subtitles::end(){
    return SubLines.end();
}

void Subtitles::pushBackNew(Subtitle subt){
    SubLines.push_back(subt);
};

void Subtitles::insertBefore(SubtitleIter iter, Subtitle sub){
    if ((*iter).getTime().checkOverlap(sub.getTime()) || (iter!=SubLines.begin() && (*(iter-1)).getTime().checkOverlap(sub.getTime())))
        throw OverlappingTimeRange();
    else SubLines.insert(iter,sub);
};