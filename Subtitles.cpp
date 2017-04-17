//
// Created by Milena on 07/04/2017.
//

#include "Subtitles.h"

SubtitleIter Subtitles::findClosestTime(mvTime targetTime){
    SubtitleIter begin=SubLines.begin();
    SubtitleIter end=SubLines.end()-1;
    SubtitleIter mid=SubLines.begin()+(end-begin)/2;
    if (targetTime>(*(end)).getTime().getEnd()) throw TimeOutOfRange();
    while(begin!=end){
        if((*mid).getTime().contains(targetTime)) {
            std::cout<<(*mid).getTime().contains(targetTime);
            break;
        }
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

Subtitles& Subtitles::pushBackNew(Subtitle subt){
    if(!SubLines.empty() && subt.getTime().checkOverlap(SubLines.back().getTime())){
        subt.getTime().checkOverlap(SubLines.back().getTime());
        throw OverlappingTimeRange(subt);
    }
    SubLines.push_back(subt);
    return *this;
};

Subtitles& Subtitles::insertBefore(SubtitleIter iter, Subtitle sub){
    if ((iter!=end())&&((*iter).getTime().checkOverlap(sub.getTime()) || (iter!=SubLines.begin() && (*(iter-1)).getTime().checkOverlap(sub.getTime()))))
        throw OverlappingTimeRange(sub);
    else SubLines.insert(iter,sub);
    return *this;
};

Subtitles& Subtitles::shiftCurrent(SubtitleIter current, mvTime displacement, mvTimeRange::dir direction){
    mvTimeRange temp((*current).getTime());
    temp.shift(displacement,direction);
    if(direction==mvTimeRange::FWD && current!=SubLines.end()) {
        if (temp.checkOverlap((*(current + 1)).getTime()))
            throw OverlappingTimeRange(*current);
    } else if (direction==mvTimeRange::BACK && current!=SubLines.begin())
        if (temp.checkOverlap((*(current - 1)).getTime()))
            throw OverlappingTimeRange(*current);

    (*current).shiftTime(displacement, direction);
    return *this;
};

Subtitles& Subtitles::shiftInRange(mvTimeRange range, mvTime displacement, mvTimeRange::dir direction){
    SubtitleIter begin,end;
    try {
        begin = findClosestTime(range.getStart());
    } catch(TimeOutOfRange){ throw; }

    try {
        end = findClosestTime(range.getEnd());
    } catch(TimeOutOfRange){ end=SubLines.end(); }

    try {
        shiftEdges(begin, end, range, displacement, direction);
    }catch(OverlappingTimeRange){throw;}
    catch(ImpossibleTimeRange){throw;}
    catch(NegativeTime){throw;}

    for(begin++; begin!=end; begin++)
        (*begin).shiftTime(displacement,direction);
    return *this;
};

Subtitles& Subtitles::mergeWithNext(SubtitleIter current){
    if(current==SubLines.end()) throw BadIterator();
    SubtitleIter next=current+1;
    (*current).getTime().setEnd((*next).getTime().getEnd());
    (*current).changeContent((*current).getContent().append("\n").append((*next).getContent()));
    SubLines.erase(next);
    return *this;
};

//TODO splitCurrent
Subtitles& Subtitles::splitCurrent(SubtitleIter current){
    return *this;
}; //???

void Subtitles::shiftEdges(SubtitleIter begin, SubtitleIter end, mvTimeRange range, mvTime disp, mvTimeRange::dir direction){
    mvTimeRange tempBegin((*begin).getTime()), tempEnd((*end).getTime());

    try{
        if (tempBegin.getStart() < range.getStart())
            tempBegin.shiftEnd(disp, direction);
        else
            tempBegin.shift(disp, direction);
        if (tempEnd.getEnd() > range.getEnd())
            tempEnd.shiftEnd(disp, direction);
        else
            tempEnd.shift(disp, direction);
    }catch(ImpossibleTimeRange){ throw; }
    catch(NegativeTime){ throw; }

    if(begin!=SubLines.begin() && tempBegin.checkOverlap((*(begin-1)).getTime()) )throw OverlappingTimeRange();
    if(end!=SubLines.end() && tempEnd.checkOverlap((*(end+1)).getTime()) ) throw OverlappingTimeRange();

    (*begin).setTime(tempBegin);
    (*end).setTime(tempEnd);

    return;
}

Subtitles& Subtitles::removeAtTime(mvTime timePoint){
    SubtitleIter targetSub;
    try {
        targetSub = findClosestTime(timePoint);
    }catch(TimeOutOfRange){throw;}

    return remove(targetSub);
};

Subtitles& Subtitles::remove(SubtitleIter iter){
    SubLines.erase(iter);
    return *this;
};

Subtitles& Subtitles::insert(Subtitle sub){
    SubtitleIter place;
    if(!SubLines.empty())try {
        place = findClosestTime(sub.getTime().getStart());
    }catch(TimeOutOfRange){  pushBackNew(sub);  return *this; }
    else {
        pushBackNew(sub);
        return *this;
    }
    //TODO kad testiras findClosestTime razmotri slucajeve ovde
    if(!(*place).getTime().checkOverlap(sub.getTime()))
        if((*place).getTime().getStart()>sub.getTime().getEnd())
            insertBefore(place,sub);
        else
            insertBefore(++place,sub);
    return *this;
};
