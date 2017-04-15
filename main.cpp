#include <iostream>
#include <regex>
#include "mvtime.h"
//#include "SubtitleApp.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    //SubtitleApp::main_app();
    string str="1\n00:00:15,000 --> 00:00:18,000\nA long, long time ago...";
    SubtitleIO * io=SubRipIO::createObject();
    Subtitle * subt=io->parseInputData(str);
    cout<<subt->getTime().getStart()<<endl<<subt->getTime().getEnd()<<endl<<subt->getContent()<<endl;
    cout<<io->getExportString(*subt)<<endl;
}