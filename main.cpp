#include <iostream>
#include <conio.h>
#include "Display.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    SubtitleIO * io=MplayerIO::createObject();
    Subtitles *subt;
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");

    Display display(50,60);
    display.initScrolling(subt);
    refresh();
    //SubtitleApp::main_app();

}