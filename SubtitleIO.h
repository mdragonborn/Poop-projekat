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

//Exceptions
class FailedToOpenFile: public exception{};
class ParsingError: public exception{};
class TooBadFile: public exception{};

//TODO Da li je bezbednije da se svaki put brise i realocira instanca?
template <class Format> class SingletonClass{
protected:
    static Format * instance_;
public:
    static Format * operator new(std::size_t size){
        if (!instance_)
            instance_= new Format();
        return instance_;
    };
    void operator delete(){
        delete instance_;
    }
};

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
    SubtitleIO(){};
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
    SubRipIO(){};
    friend SingletonClass<SubRipIO>;
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
    MicroDVDIO(){};
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
    friend SingletonClass<MplayerIO>;
    MplayerIO(){};
    virtual bool handleInputError(inputError& inpError);
    friend SingletonClass<MplayerIO>;
public:
    virtual string getInputData(ifstream& file);
    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);
};


#endif //POOP_SUBTITLEIO_H