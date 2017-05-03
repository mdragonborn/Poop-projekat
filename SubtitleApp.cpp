//
// Created by Milena on 05/04/2017.
//

#include "SubtitleApp.h"



using namespace std;

void SubtitleApp::shiftAll(){
    string input;
    cout<< "Uneti za koliko sekundi treba pomeriti ovaj i sve titlove posle njega: "<<flush;
    cin>>input;
    //TODO sta je pisac hteo da kaze?
    //io->shiftTitle(begin, end, input);
    cout<< "Titlovi uspesno pomereni. Pritisnuti bilo sta za nastavak rada."<<endl; getch();
    cin>>input;
}
//TODO vidi kako se koristi mapa
void SubtitleApp::initListingOptions(){
    listingOptions=new map<int, void(*)()>();
    listingOptions->emplace(W, &goBack);
    listingOptions->emplace(UP, &goBack);
    listingOptions->emplace(S, &goForward);
    listingOptions->emplace(DOWN, &goForward);
    listingOptions->emplace(A, &shiftAll);
    listingOptions->emplace(H, &printListingHelp);
    listingOptions->emplace(E, &mergeTitles);
    listingOptions->emplace(D, &splitTitle);
    listingOptions->emplace(I, &insertTitle);
    listingOptions->emplace(R, &removeTitle);
    return;
}

void SubtitleApp::initMainOptions(){
    mainOptions=new map<int,void(*)()>();
    mainOptions->emplace(W, &mainGoUp);
    mainOptions->emplace(S, &mainGoDown);
    mainOptions->emplace(UP, &mainGoUp);
    mainOptions->emplace(DOWN, &mainGoDown);
    mainOptions->emplace(KEY_ENTER, &mainSelect);
};


void SubtitleApp::listSubtitles(Subtitles &subs){

    if (listingOptions== nullptr) initListingOptions();
    int input=0;
    begin=iter=subs.begin(), end=subs.end();
    while (1){
        while (1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW) input=_getch();
                break;
            }
        }
            if(input==Q) return;
            try{
                listingOptions->at(input)();
            }catch(out_of_range){continue;};
    //        cout<<io.fileName() << listing_help_print() <<endl;
    //        cout<<*iter<<endl;
        }
    }


void SubtitleApp::insertTitle(){};
void SubtitleApp::removeTitle(){};

void SubtitleApp::printMenu(){
}
void SubtitleApp::printListingHelp(){};

int SubtitleApp::main_app() {
    if (display == nullptr) display = new Display(40, 80);
    if (mainOptions == nullptr) initMainOptions();
    display->generateHomeScr(false);
    int input;
    while (1) {
        while(1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW) input=_getch();
                break;
            }
        }
        if (input == Q) return 0;
        try {
            mainOptions->at(input)();
        } catch (out_of_range) { continue; };
    }
};

void SubtitleApp::callMainOption(){};
void SubtitleApp::splitTitle(){};
void SubtitleApp::mergeTitles(){};

void SubtitleApp::mainGoUp(){
    if(mainCursor>0) {
        mainCursor--;
        display.mainUp();
    }
};
void SubtitleApp::mainGoDown(){
    if(mainCursor<mainCursorMax){
        mainCursor++;
        display.mainDown();
    }
};
void SubtitleApp::mainSelect(){
    if(loaded== nullptr){
        (*mainNotLoaded[mainCursor])();
    } else (*mainLoaded[mainCursor])();
};

void SubtitleApp::export(){

};
void SubtitleApp::edit(){

};
void SubtitleApp::showAbout(){

};
void SubtitleApp::exit(){

};
void SubtitleApp::load(){

};