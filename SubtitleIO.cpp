//
// Created by Milena on 07/04/2017.
//

#include "SubtitleIO.h"
#include <regex>

SingletonClass<SubRipIO>::instance_=nullptr;
SingletonClass<MicroDVDIO>::instance_= nullptr;
SingletonClass<MplayerIO>::instance_=nullptr;


Subtitles * SubtitleIO::loadSubtitles(string file_path){
    ifstream inputStream;
    try{
        inputStream.open(file_path);
    }catch(std::ios_base::failure){return new FailedToOpenFile();} //ili samo throw; ?

    string inputBuffer;     int i;
    Subtitle * newSub; Subtitles * newTitles= new Subtitles(file_path);
    queue<inputError> inpErrors;

    while (!inputStream.eof()){
        try{ inputBuffer=getInputData(inputStream); }
        catch(TooBadFile) { throw; }
        try { newSub = parseInputData(inputBuffer); }
        catch(ParsingError){
            inpError.push(new inputErrors(*inputBuffer,i));   //pozicija
            if(inpErrors.size()>5) {
                delete newTitles; inputStream.close();
                throw new TooBadFile();
            }
            newSub=new Subtitle(mvTimeRange(0,0),"");
        }
        newTitles->insertNew(&newSub);
    }
    inputStream.close();
    if(handleInputErrors(inpErrors)) return newTitles;
    else { delete newTitles; throw new TooBadFile(); }
}

bool SubtitleIO::handleInputErrors(queue<inputError> errorList){
    inputError currentError;
    while(!errorList.empty()){
        currentError=errorList.front();
        errorList.pop();
        if (!handleInputError(currentError)) return false;
    }
    return true;
};

//SubRipIO implementation

string SubRipIO::getInputData(ifstream& file){
    string buffer, rtValue="";
    getline(file,buffer);
    while(!regex_match(buffer, regex("^\\s*$"))){
        rtValue+=buffer+"\n";
        getline(file,buffer);
    }
    return rtValue;
}

Subtitle * SubRipIO::parseInputData(string inputData){
    //regex za parsianje
}

string SubRipIO::getExportString(Subtitle& sub){

}

//MicroDVDIO implementation

string MicroDVDIO::getInputData(ifstream& file){
    string buffer;
    getline(file,buffer);
    return buffer;
}

Subtitle * MicroDVDIO::parseInputData(string inputData){
    if (!regex_match(string, regex("{\\d+}{\\d+}.*$"))) throw ParsingError();

}

string MicroDVDIO::getExportString(Subtitle& sub){

}

//MplayerIO implementation

string MplayerIO::getInputData(ifstream& file){
    string buffer, rtValue="";
    getline(file,buffer);
    while(!regex_match(buffer, regex("^\\s*$"))){
        if(buffer[0]!='#') rtValue+=buffer+"\n";
        if (regex_match(buffer, regex("^\\d+\\s\\d+$"))) throw new TooBadFile();
        getline(file,buffer);
    }
    return rtValue;
}

Subtitle * MplayerIO::parseInputData(string inputData);

string MplayerIO::getExportString(Subtitle& sub);