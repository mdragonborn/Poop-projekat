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
    if (!regex_match(inputData, regex("\\d\n\\d{2}:\\d{2}:\\d{2}\\.\\d{3} --> \\d{2}:\\d{2}:\\d{2}\\.\\d{3}\n(.*\n?)+"))) throw ParsingError();
    
}

string SubRipIO::getExportString(Subtitle& sub){

}


//MplayerIO implementation

string MplayerIO::getInputData(ifstream& file){
    string buffer, rtValue="";
    getline(file,buffer);   // kod ispravnog fajla
    while(!regex_match(buffer, regex("^\\s*$"))){
        if(buffer[0]!='#') rtValue+=buffer+"\n";
        getline(file,buffer);
        if (regex_match(buffer, regex("^\\d+\\.?\\d*?\\s\\d+\\.?\\d*?$"))) throw new TooBadFile();
    }
    return rtValue;
}

Subtitle * MplayerIO::parseInputData(string inputData){
    if (!regex_match(inputData, regex("\\d+\\.?\\d*?\\s\\d+\\.?\\d*?\n(.*\n?)+"))) throw ParsingError();
    // regex za multiline captione?
    regex format("(\\d+\\.?\\d*)\\s(\\d+\\.?\\d*)\n(.*\n?)");   //ovde kod regexa treba grupisai decimalu
    std::sregex_iterator iter(inputData.begin(), inputData.end(), format);
    std::sregex_iterator end;
    mvTime begin=getTime((*iter)[1]);
    mvTime endt=getTime((*iter)[2]);
    return new Subtitle(mvTimeRange(begin,endt),(*iter)[3]);

}

string MplayerIO::getExportString(Subtitle& sub){
    string buffer=""; char temp[10];
    double start=((sub.getTime().getStart()-lastExportTime).toMillisec())/1000.;
    double end=(sub.getTime().getEnd()-sub.getTime().getStart()).toMillisec()/1000.;
    lastExportTime=sub.getTime().getEnd();
    sprintf(temp, "%f",start);   //double to string, sklanjanje suvisnih decimala
    buffer.append(temp).append(" ");
    sprintf(temp, "%f",end);
    buffer.append(temp).append("\n").append(sub.getContent());
    return buffer;
}



//MDVDIO implementation


string MDVDIO::getInputData(ifstream& file){
    string buffer;
    getline(file,buffer);
    return buffer;
}

Subtitle * MDVDIO::parseInputData(string inputData){
    if (!regex_match(inputData, regex("\\{\\d+\\}\\{\\d+\\}.*$"))) throw ParsingError();
    regex format("\\{(\\d+)\\}\\{(\\d+)\\}(.*)$");
    std::sregex_iterator iter(inputData.begin(), inputData.end(), format);
    return new Subtitle(mvTimeRange( convertFromFps(stoi((*iter)[1])), convertFromFps(stoi((*iter)[2])) ), replacePipe((*iter)[3]) );

    //return new Subtitle (mvTimeRange(convertToFps(mvTime()),convertToFps(mvTime())),"ok");
};

string MDVDIO::getExportString(Subtitle& sub){
    string rtVal; char buffer[20];
    sprintf(buffer,"%d",convertToFps(sub.getTime().getStart()));
    rtVal.append("{").append(buffer).append("}{");
    sprintf(buffer,"%d",convertToFps(sub.getTime().getEnd()));
    rtVal.append(buffer).append("}").append(setPipe(sub.getContent()));
    return rtVal;
}

//TODO handle error MDVDIO

bool MDVDIO::handleInputError(inputError& inpError){
    return false;
}

mvTime MDVDIO::convertFromFps(int input){
    lastTime=(double)input*1000/(fps);
    return mvTime(0,0,0,(int)lastTime);
}

int MDVDIO::convertToFps(mvTime time){
    return (int)(time.toMillisec()*fps/1000);
}

string MDVDIO::replacePipe(string content){
    for(int i=0; i<content.length();i++)
        if (content[i]=='|') content[i]='\n';
    return content;
}

string MDVDIO::setPipe(string content){
    for(int i=0; i<content.length();i++)
        if (content[i]=='\n') content[i]='|';
    return content;
}


