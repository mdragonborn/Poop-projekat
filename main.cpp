#include <iostream>
#include <regex>
#include "mvtime.h"
//#include "SubtitleApp.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    //SubtitleApp::main_app();
    string str="15 3\nA long, long time ago...In a galaxy far far away...";
    SubtitleIO * io=MplayerIO::createObject();
    Subtitle * subt=io->parseInputData(str);
    cout<<subt->getTime().getStart()<<endl<<subt->getTime().getEnd()<<endl<<subt->getContent()<<endl;
    cout<<io->getExportString(*subt)<<endl;
}