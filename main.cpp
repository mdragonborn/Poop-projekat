#include <iostream>
#include "mvtime.h"
//#include "SubtitleApp.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    //SubtitleApp::main_app();
    string str="{375}{450}A long, long time ago...";
    MplayerIO * mpio=MplayerIO::createObject();
    Subtitle * subt=mpio->parseInputData(str);
    cout<<subt->getContent()<<subt->getTime().getStart()<<endl<<subt->getTime().getEnd()<<endl;
}