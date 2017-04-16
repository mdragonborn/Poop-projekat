#include <iostream>
#include <regex>
#include "mvtime.h"
#include "SubtitleIO.h"

using namespace std;

int main(){

    //SubtitleApp::main_app();
    //string str="1\n00:00:15,000 --> 00:00:18,000\nA long, long time ago...\n2\n00:00:18,000 --> 00:00:21,000\nin a galaxy far away...\n3\n00:00:21,000 --> 00:00:24,000\nNaboo was under an attack.\n4\n00:00:25,000 --> 00:00:27,500\n";
    SubtitleIO * io=SubRipIO::createObject();
    Subtitles * subt=io->loadSubtitles("C:\\Users\\Milena\\Desktop\\input.txt");
    SubtitleIter begin=subt->begin(), end=subt->end();
    io->exportPrep();
    for(;begin!=end; begin++)
        cout<<io->getExportString(*begin)<<endl;

}