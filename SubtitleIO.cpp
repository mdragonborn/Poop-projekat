//
// Created by Milena on 07/04/2017.
//

#include "SubtitleIO.h"
#include "mvtime.h"
#include <regex>

using namespace std;

Subtitles * SubtitleIO::loadSubtitles(string file_path){
    ifstream inputStream;
    try{
        inputStream.open(file_path);
    }catch(std::ios_base::failure){ throw new FailedToOpenFile();} //ili samo throw; ?

    string inputBuffer;
    int i;
    Subtitle * newSub; Subtitles * newTitles= new Subtitles();
    queue<inputError> inpErrors;
    while (!inputStream.eof()){
        try{ inputBuffer=getInputData(inputStream); }
        catch(TooBadFile) { throw; }
        try { newSub = parseInputData(inputBuffer); }
        catch(ParsingError){
            inpErrors.push(inputError(inputBuffer,i));   //pozicija
            if(inpErrors.size()>5) {
                delete newTitles; inputStream.close();
                throw new TooBadFile();
            }
            newSub=new Subtitle(mvTimeRange(0,0),"");
        }
        newTitles->insertNew(*newSub);
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
/*
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

}

string MicroDVDIO::getExportString(Subtitle& sub){

}

//TODO handle error MicroDVDIO
bool MicroDVDIO::handleInputError(inputError& inpError){

}

*/
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

//TODO parse Mplayer

Subtitle * MplayerIO::parseInputData(string inputData){
    /*
    if (!regex_match(string, regex("\\{\\d+\\}\\{\\d+\\}.*$"))) throw ParsingError();
    regex format("\\{(\\d+)\\}\\{(\\d+)\\}(.*)$");
    std::sregex_iterator iter(inputData.begin(), inputData.end(), format);
    return new Subtitle(mvTimeRange( convertFps(atoi((*iter)[1])), convertFps(atoi((*iter)[2])) ), replacePipe((*iter)[3]) );
     */
    return new Subtitle (mvTimeRange(convertToFps(mvTime()),convertToFps(mvTime())),"ok");
};

//TODO exportString MplayerIO
string MplayerIO::getExportString(Subtitle& sub){
    return "e";
}

//TODO handle error MplayerIO

bool MplayerIO::handleInputError(inputError& inpError){
    return false;
}
mvTime MplayerIO::convertFromFps(int input){
    lastTime=input/(fps*1000);
    return mvTime(0,0,0,(int)lastTime);
}

int MplayerIO::convertToFps(mvTime time){
    return (int)(time.toMillisec()*1000*fps);
}

string MplayerIO::replacePipe(string content){
    for(int i=0; i<content.length();i++)
        if (content[i]=='|') content[i]='\n';
    return content;
}
