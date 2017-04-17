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
#include <iostream>

using std::string;
using std::queue;
using std::exception;
using std::ifstream;

//Exceptions
class FailedToOpenFile: public exception{};
class ParsingError: public exception{};
class TooBadFile: public exception{};
struct OutputSubs;

template <typename Format> class SingletonClass{
public:
    static Format * instance_;
public:
    static Format * createObject(){
        if (!instance_)
            instance_= new Format();
        return instance_;
    };
    static void removeObject(){
        delete instance_; instance_=nullptr;
    }
    ~SingletonClass(){
        if (instance_!=nullptr) delete instance_;
    };
};


class SubtitleIO{
protected:
    struct inputError{
    public:
        string badFood;
        inputError(){};
        inputError(string input):badFood(input){};
    };
    virtual bool handleInputError(inputError& inpError)=0;
    bool handleInputErrors(queue<inputError> errorList);
public:
    Subtitles * loadSubtitles(string file_path);
    static string itos(int i){
        char buffer[10];
        sprintf(buffer,"%d",i);
        return string(buffer);
    }
    static string dtos(double d){
        char buffer[15];
        sprintf(buffer, "%.3f", d);
        return string(buffer);
    }
    virtual string getInputData(ifstream &file)=0;
    virtual Subtitle * parseInputData(string inputData)=0;
    virtual ~SubtitleIO(){};
    virtual void exportPrep()=0;
    virtual void importPrep()=0;
    virtual string getExportString(Subtitle& sub)=0;
};

class SubRipIO: public SingletonClass<SubRipIO>, public SubtitleIO {
private:
    int exportIndex;
    SubRipIO(){};
    friend class SingletonClass<SubRipIO>;
    virtual bool handleInputError(inputError& inpError) override;
    string mvTimeToString(mvTime t);
    string zeroPadding(string s, int len=2);
public:
    virtual string getInputData(ifstream &file) override;
    virtual Subtitle * parseInputData(string inputData) override;
    ~SubRipIO(){};
    virtual void exportPrep() override;
    virtual void importPrep() override;
    virtual string getExportString(Subtitle& sub) override;
};


//TODO podrska za komentare?
class MplayerIO: public SingletonClass<MplayerIO>, public SubtitleIO{
private:
    int lastTime=0;
    mvTime lastExportTime;
    friend class SingletonClass<MplayerIO>;
    MplayerIO(){};
    virtual bool handleInputError(inputError& inpError);
    mvTime getTime(string extractedTime){
        lastTime+=(stod(extractedTime))*1000;
        return mvTime(0,0,0,lastTime);
    }
public:
    virtual string getInputData(ifstream &file);
    virtual Subtitle * parseInputData(string inputData);
    virtual void exportPrep() override;
    virtual void importPrep() override;
    virtual string getExportString(Subtitle& sub) override;
    ~MplayerIO(){};
};

class MDVDIO: public SingletonClass<MDVDIO>, public SubtitleIO {
private:
    double fps=25;
    double lastTime;
    bool handleInputError(inputError& inpError) override;
    friend class SingletonClass<MDVDIO>;
    MDVDIO(){};
    mvTime convertFromFps(int input);
    int convertToFps(mvTime time);
    string replacePipe(string content);
    string setPipe(string content);
public:
    string getInputData(ifstream &file) override;
    Subtitle * parseInputData(string inputData) override;
    virtual void exportPrep() override;
    virtual void importPrep() override;
    virtual string getExportString(Subtitle& sub) override;
};

template <typename Format> Format * SingletonClass<Format>::instance_=nullptr;

struct OutputSubs{
public:
    SubtitleIO* io;
    Subtitles* subs;
    OutputSubs(SubtitleIO* sio, Subtitles* subts):io(sio),subs(subts){};
    OutputSubs(SubtitleIO* sio, Subtitles& subts):io(sio),subs(&subts){};
};


#endif //POOP_SUBTITLEIO_H