#include <iostream>
#include "Display.h"


using namespace std;
/*
int main(){
    SubtitleIO * io=MplayerIO::createObject();
    Subtitles *subt;
    clock_t b=clock();
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");
    clock_t e=clock();
    io->exportPrep();
    for (auto& begin: *subt)
        cout << io->getExportString(begin)<<endl;
    cout<<(double)(e-b)/CLOCKS_PER_SEC;
}*/

int main(){
    Display disp(30,100);
    disp.initScrolling();
    refresh();
}