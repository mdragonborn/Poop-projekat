#include <iostream>
#include <conio.h>
#include "Display.h"
#include "SubtitleIO.h"

using namespace std;

int main(){
    SubtitleIO * io=MplayerIO::createObject();
    Subtitles *subt;
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");

    Display display(40,80);
    display.initScrolling(subt);
    SubtitleIter iter=subt->begin();
    display.scrollDown(&(*++iter));
    display.scrollDown(&(*++iter));
    display.scrollDown(&(*++iter));
    display.scrollUp(&(*--iter));
    display.scrollUp(&(*--iter));
    display.scrollUp(&(*--iter));
    display.scrollUp(&(*--iter));
    refresh();
    //SubtitleApp::main_app();
}