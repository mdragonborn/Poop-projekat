//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitles.h"
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <exception>
#include <regex>
//????

using std::string;
using std::queue;
using std::exception;
using std::ifstream;

template <class Format> class SingletonClass{
protected:
    static Format * instance_;
public:
    static Format * createObject(){
        if (!instance_)
            instance_=new Format();
        return instance_;
    };
};


class FailedToOpenFile: public exception{};
class ParsingError: public exception{};
class TooBadFile: public exception{};

class SubtitleIO{
protected:
    struct inputError{
    public:
        string badFood;
        int positionInVector;
        inputError(string input, int position);
    };
    virtual bool handleInputError(inputError& inpError)=0;
    bool handleInputErrors(queue<inputError> errorList);
public:
    struct SubtitleIter{
        //nesto?
    };
    virtual string getInputData(ifstream& file)=0;
    virtual Subtitle * parseInputData(string inputData)=0;
    virtual string getExportString(Subtitle& sub)=0;
    Subtitles * loadSubtitles(string file_path);
};

class SubRipIO: public SingletonClass<SubRipIO>, public SubtitleIO{
private:
    friend SingletonClass<SubRipIO>;
    SubRipIO(){instance_=this;};
    virtual bool handleInputError(inputError& inpError);
public:
    virtual string getInputData(ifstream& file);
    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);
};

class MicroDVDIO: public SingletonClass<MicroDVDIO>, public SubtitleIO{
private:
    mvTime lastTime;
    friend SingletonClass<MicroDVDIO>;
    MicroDVDIO(){instance_=this;};
    virtual bool handleInputError(inputError& inpError);
public:
    virtual string getInputData(ifstream& file);
    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);
};


class MplayerIO: public SingletonClass<MplayerIO>, public SubtitleIO{
private:
    mvTime lastTime;
    double fps; //??????
    MplayerIO(){instance_=this;};
    virtual bool handleInputError(inputError& inpError);
    friend SingletonClass<MplayerIO>;
public:
    virtual string getInputData(ifstream& file);
    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);
};
#endif //POOP_SUBTITLEIO_H