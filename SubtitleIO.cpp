//
// Created by Milena on 07/04/2017.
//
#include "SubtitleIO.h"

using namespace std;

Subtitles * SubtitleIO::loadSubtitles(string file_path){
    ifstream inputStream;
    try{
        inputStream.open(file_path);
    }catch(ios_base::failure){ throw new FailedToOpenFile();} //ili samo throw; ?

    string inputBuffer;
    int i=0;
    Subtitle * newSub; Subtitles * newTitles= new Subtitles();
    queue<inputError> inpErrors;
    while (!inputStream.eof()){
        try{ inputBuffer=getInputData(inputStream); }
        catch(TooBadFile) { throw; }
        try { newSub = parseInputData(inputBuffer); }
        catch(ParsingError){
            inpErrors.push(inputError(inputBuffer));   //pozicija
            /*if(inpErrors.size()>5) {
                delete newTitles; inputStream.close();
                throw new TooBadFile();
            }*/
            continue;
        }
        newTitles->insert(*newSub);
    }
    inputStream.close();
    if(handleInputErrors(inpErrors)) return newTitles;
    //else { delete newTitles; throw new TooBadFile(); }
}

bool SubtitleIO::handleInputErrors(queue<inputError> errorList){
    inputError currentError;
    return true;
    while(!errorList.empty()){
        currentError=errorList.front();
        errorList.pop();
        if (!handleInputError(currentError)) return false;
    }
    return true;
};

//SubRipIO implementation

string SubRipIO::getInputData(ifstream &file) {
    string buffer;
    string rtValue = "";
    std::getline(file, buffer);
    while (!regex_match(buffer, regex("^\\s*$"))) {
        rtValue += buffer + "\n";
        getline(file, buffer);
    }
        return rtValue;
}


Subtitle * SubRipIO::parseInputData(string inputData){
    if (!regex_match(inputData, regex("\\d+\n\\d{2}:\\d{2}:\\d{2},\\d{3} --> \\d{2}:\\d{2}:\\d{2},\\d{3}\n(.|\n)+"))) throw ParsingError();
    regex format("\\d+\n(\\d{2}):(\\d{2}):(\\d{2}),(\\d{3}) --> (\\d{2}):(\\d{2}):(\\d{2}),(\\d{3})\n((.|\n)+)");
    sregex_iterator iter(inputData.begin(), inputData.end(),format);
    mvTime begin(stoi((*iter)[1]), stoi((*iter)[2]), stoi((*iter)[3]),stoi((*iter)[4]));
    mvTime end(stoi((*iter)[5]), stoi((*iter)[6]), stoi((*iter)[7]),stoi((*iter)[8]));
    return new Subtitle(mvTimeRange(begin,end),(*iter)[9]);  //TODO multiline?
}

string SubRipIO::getExportString(Subtitle& sub){
    string buffer="";
    buffer.append(itos(exportIndex++)).append("\n");
    buffer.append(mvTimeToString(sub.getTime().getStart())).append(" --> ").append(mvTimeToString(sub.getTime().getEnd())).append("\n");
    buffer.append(sub.getContent()).append("\n\n");
    return buffer;
}

string SubRipIO::mvTimeToString(mvTime t){
    string buffer;
    buffer.append(zeroPadding(itos(t.getHour()))).append(":");
    buffer.append(zeroPadding(itos(t.getMinute()))).append(":");
    buffer.append(zeroPadding(itos(t.getSecond()))).append(",");
    buffer.append(zeroPadding(itos(t.getMilli()),3));
    return buffer;
};

string SubRipIO::zeroPadding(string s, int len){
    if (s.length()<len) {
        while(s.length()<len) s="0"+s;
    }
    return s;
};

void SubRipIO::exportPrep(){
    exportIndex=1;
};
void SubRipIO::importPrep(){
    return;
}

//TODO handle error SubRipIO
bool SubRipIO::handleInputError(inputError& inpError){
    return false;
};

//MplayerIO implementation

string MplayerIO::getInputData(ifstream &file){
    string buffer, rtValue="";
    getline(file,buffer);   // kod ispravnog fajla
    while(!regex_match(buffer, regex("^\\s*$")) && !file.eof()){
        if(buffer[0]!='#') rtValue+=buffer+"\n";
        getline(file,buffer);
        if (regex_match(buffer, regex("^\\d+\\.?\\d*?\\s\\d+\\.?\\d*?$"))) throw new TooBadFile();
    }
    return rtValue;
}

Subtitle * MplayerIO::parseInputData(string inputData){
    if (!regex_match(inputData, regex("\\d+\\.?\\d*?\\s\\d+\\.?\\d*?\n(.|\n)+"))) throw ParsingError();
    // regex za multiline captione?
    regex format("(\\d+\\.?\\d*)\\s(\\d+\\.?\\d*)\n((.|\n)+)");   //ovde kod regexa treba grupisai decimalu
    sregex_iterator iter(inputData.begin(), inputData.end(), format);
    mvTime begin=getTime((*iter)[1]);
    mvTime endt=getTime((*iter)[2]);
    return new Subtitle(mvTimeRange(begin,endt),(*iter)[3]);

}

string MplayerIO::getExportString(Subtitle& sub){
    string buffer="";
    double start = ((sub.getTime().getStart() - lastExportTime).toMillisec()) / 1000.;
    double end = (sub.getTime().getEnd() - sub.getTime().getStart()).toMillisec() / 1000.;
    lastExportTime=sub.getTime().getEnd();
    buffer.append(dtos(start)).append(" ");  //TODO sklanjanje uvisnih decimala kod dtos
    buffer.append(dtos(end)).append("\n").append(sub.getContent());
    return buffer;
}

//TODO handle eror MplayerIO
bool MplayerIO::handleInputError(inputError& inpError){
    return false;
};

void MplayerIO::exportPrep(){
    lastExportTime={0,0,0,0};
};

void MplayerIO::importPrep(){
    lastTime=0;
}

//MDVDIO implementation

string MDVDIO::getInputData(ifstream &file){
    string buffer;
    getline(file,buffer);
    return buffer;
}

Subtitle * MDVDIO::parseInputData(string inputData){
    if (!regex_match(inputData, regex("\\{\\d+\\}\\{\\d+\\}.*$"))) throw ParsingError();
    regex format("\\{(\\d+)\\}\\{(\\d+)\\}(.*)$");
    sregex_iterator iter(inputData.begin(), inputData.end(), format);
    return new Subtitle(mvTimeRange( convertFromFps(stoi((*iter)[1])), convertFromFps(stoi((*iter)[2])) ), replacePipe((*iter)[3]) );

    //return new Subtitle (mvTimeRange(convertToFps(mvTime()),convertToFps(mvTime())),"ok");
};

string MDVDIO::getExportString(Subtitle& sub){
    string rtVal;
    rtVal.append("{").append(itos(convertToFps(sub.getTime().getStart()))).append("}{");
    rtVal.append(itos(convertToFps(sub.getTime().getEnd()))).append("}").append(setPipe(sub.getContent()));
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

void MDVDIO::exportPrep(){
    return;
};

void MDVDIO::importPrep(){
    lastTime=0;
};

