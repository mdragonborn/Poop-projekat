#include <iostream>
#include <regex>
#include "mvtime.h"
#include "SubtitleIO.h"
#include <ctime>

using namespace std;

int main(){
    SubtitleIO * io=MplayerIO::createObject();
    io->importPrep();
    Subtitles *subt;
    clock_t b=clock();
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");
    clock_t e=clock();
    SubtitleIter begin=subt->begin(), end=subt->end();
    io->exportPrep();
        for (; begin != end; begin++)
            cout << io->getExportString(*begin)<<endl;
    cout<<(double)(e-b)/CLOCKS_PER_SEC;
}