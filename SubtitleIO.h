//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEIO_H
#define POOP_SUBTITLEIO_H

#include "Subtitles.h"
#include "mvtime.h"
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


template <typename Format> class SingletonClass{
public:
    static Format * instance_;
public:
    static Format * createObject(){
        if (!instance_)
            instance_= new Format();
        return (Format*)instance_;
    };
    static void removeObject(){
        delete instance_; instance_=nullptr;
    }
    ~SingletonClass(){
        if (instance_!=nullptr) delete (Format*)instance_;
    };
};


class SubtitleIO{
protected:
    struct inputError{
    public:
        string badFood;
        int positionInVector;
        inputError(){};
        inputError(string input, int position):badFood(input),positionInVector(position){};
    };
    virtual bool handleInputError(inputError& inpError)=0;
    bool handleInputErrors(queue<inputError> errorList);
public:
    Subtitles * loadSubtitles(string file_path);
    virtual string getInputData(ifstream& file)=0;
    virtual Subtitle * parseInputData(string inputData)=0;
    virtual string getExportString(Subtitle& sub)=0;
    virtual ~SubtitleIO(){};
};


class SubRipIO: public SingletonClass<SubRipIO>, public SubtitleIO {
private:
    SubRipIO(){};
    friend class SingletonClass<SubRipIO>;
    virtual bool handleInputError(inputError& inpError);
public:
    virtual string getInputData(ifstream& file);

    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);
    ~SubRipIO(){}
};

//TODO podrska za komentare?
class MplayerIO: public SingletonClass<MplayerIO>, public SubtitleIO{
private:
    int lastTime=0;
    mvTime lastExportTime={0,0,0,0};
    friend class SingletonClass<MplayerIO>;
    MplayerIO(){};
    virtual bool handleInputError(inputError& inpError){return false;};
public:
    virtual string getInputData(ifstream& file);
    virtual Subtitle * parseInputData(string inputData);
    virtual string getExportString(Subtitle& sub);

    mvTime getTime(string extractedTime){
        lastTime+=(stod(extractedTime))*1000;
        return mvTime(0,0,0,lastTime);
    }
    ~MplayerIO(){};
};

class MDVDIO: public SingletonClass<MDVDIO>, public SubtitleIO {
private:
    double fps=25;
    double lastTime;
    bool handleInputError(inputError& inpError) override;
    friend class SingletonClass<MDVDIO>;
    MDVDIO(){};
public:
    string getInputData(ifstream& file) override;
    Subtitle * parseInputData(string inputData) override;
    string getExportString(Subtitle& sub) override;
    mvTime convertFromFps(int input);
    int convertToFps(mvTime time);
    string replacePipe(string content);
    string setPipe(string content);
};

template <typename Format> Format * SingletonClass<Format>::instance_=nullptr;

template class SingletonClass<MDVDIO>;
template class SingletonClass<MplayerIO>;


#endif //POOP_SUBTITLEIO_H