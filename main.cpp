#include <iostream>
#include <conio.h>
#include <windows.h>
#include <curses.h>

using namespace std;

int main(){
    /*SubtitleIO * io=MplayerIO::createObject();
    Subtitles *subt;
    subt = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");

    Display display(40,80);
    display.initScrolling(subt);
    SubtitleIter iter=subt->begin();
    display.scrollDown(&(*(++iter+1)));
    display.scrollDown(&(*(++iter+1)));
    display.scrollDown(&(*(++iter+1)));
    display.scrollUp(&(*(--iter-1)));
    display.scrollUp(&(*(--iter-1)));
    display.scrollUp(nullptr);
    refresh();*/
    //SubtitleApp::main_app();
    while(1) {
        short shiftKeyState=GetAsyncKeyState(VK_SHIFT);
        if(shiftKeyState&(1<<15)) cout<<"held";
        if (_kbhit()) {
            int input = _getch();
            if(input==KEY_SHIFT_L || input==KEY_SHIFT_R) {
                cout<<"shift"<<endl;
                continue;
            }
            break;
        }
    }
}