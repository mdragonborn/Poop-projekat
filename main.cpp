#include <iostream>
#include <regex>
#include "mvtime.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    SubtitleIO * io=MplayerIO::createObject();
    io->importPrep();
    Subtitles *subt;
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\input.txt");
    SubtitleIter begin=subt->begin(), end=subt->end();
    io->exportPrep();
        for (; begin != end; begin++)
            cout << io->getExportString(*begin) << endl;
}