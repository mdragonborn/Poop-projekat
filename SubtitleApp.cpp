//
// Created by Milena on 05/04/2017.
//

#include "SubtitleApp.h"
#include "Display.h"


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
    int input;

    if (display == nullptr) display = new Display(40, 80);
    if (mainOptions == nullptr) initMainOptions();
    mainCursor=0;
    if (!loaded) {
        mainCursorMax=3;
//  TODO      display->setNewMenu(&mainNotLoadedStr,3);
    }
    else {
        mainCursorMax = 4;
  // TODO     display->setNewMenu(&mainLoadedStr,3);
    }

    display->generateHomeScr(false);
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
            if (!loaded) mainCursorMax=3;
            else mainCursorMax=4;
        } catch (out_of_range) { continue; };
    }
};

void SubtitleApp::callMainOption(){};
void SubtitleApp::splitTitle(){};
void SubtitleApp::mergeTitles(){};

void SubtitleApp::mainGoUp(){
    if(mainCursor>0) {
        mainCursor--;
        display->mainUp();
    }
};
void SubtitleApp::mainGoDown(){
    if(mainCursor<mainCursorMax){
        mainCursor++;
        display->mainDown();
    }
};
void SubtitleApp::mainSelect(){
    if(loaded== nullptr){
        (*mainNotLoaded[mainCursor])();
    } else (*mainLoaded[mainCursor])();
    display->displayMain(); mainCursor=0;
};

void SubtitleApp::subExport() {
    int input, expCursor;
    SubtitleIO *IO;
    string extension;
    string options[] = {"SubRip", "MicroDVD", "Mplayer"};
    //display->setNewMenu(&options, 3);
    display->displayMain();
    while (1) {
        while (1) {
            if (_kbhit()) {
                input = _getch();
                if (input == ARROW) input = _getch();
                break;
            }
        }
        if (input == DOWN || input == S && expCursor < 2) {
            expCursor++;
            display->mainDown();
        }
        else if (input == UP || input == W && expCursor != 0) {
            expCursor--;
            display->mainUp();
        }
        else if (input == ENTER) {
            switch (expCursor) {
                case 0:
                    IO = SubRipIO::instance_;
                    extension = ".srt";
                    break;
                case 1:
                    IO = MDVDIO::instance_;
                    extension = ".sub";
                    break;
                case 2:
                    IO = MplayerIO::instance_;
                    extension = ".sub";
                    break;
            }

            string path = display->stringInput(Coord(0, 0), "Folder path:"); //TODO zavrsi ovo
            string fname = display->stringInput(Coord(0, 0), "File name:");
            //save(path+"\\"+fname+extension);
        }
    }
};


void SubtitleApp::edit(){
    if(!loaded) return;
    if(!editOptions) initEditOptions();
    int input=0;
    display->initScrolling(loaded);
    while (1) {
        while(1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW) input=_getch();
                break;
            }
        }
        if (input == Q) {display->displayMain(); mainCursor=0; return;}
        try{
            editOptions->at(input)();
        }catch(out_of_range){continue;}
    }
};

void SubtitleApp::initEditOptions(){
    editOptions=new map<int, fun_ptr>;
    editOptions->emplace(A, &shiftAll);
/*    editOptions->emplace(R, &removeCurrent);
    editOptions->emplace(I, &insertNew);
    editOptions->emplace(D, &merge);
    editOptions->emplace(Q, &exit);
    editOptions->emplace(W, &scrollUp);
    editOptions->emplace(UP, &scrollUp);
    editOptions->emplace(S, &scrollDown);
    editOptions->emplace(DOWN, &scrollDown);
    editOptions->emplace(F,&find);*/
};


void SubtitleApp::showAbout(){
    display->displayText("Projektni zadatak iz praktikuma iz objektno orjentisanog programiranja\nMilena Markovic 2015/436\nApril 2017.");
    while(!_kbhit());
    display->displayMain(); mainCursor=0;
    return;
};

void SubtitleApp::quitApp(){
    if(!loaded) exit(1);
    display->quitSavePrompt();
    int optionToggle=0, input;
    while (1) {
        while(1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW) input=_getch();
                break;
            }
        }
        if (input == Q) {display->displayMain(); mainCursor=0; return;}
        if(input==LEFT || input==A || input==RIGHT || input==D) {
            optionToggle=(optionToggle+1)%2; display->savePromptShift();
        }
        if(input==ENTER) if(optionToggle) exit(1);
        else {
            subExport(); exit(1);
        }
    }
};
void SubtitleApp::load(){
  //TODO ovde mora da odradi prepoznavanje formata tj biranej IO objekta, ucitavanje i smestanje u loaded. vraca se u main
};

void SubtitleApp::removeCurrent(){
    SubtitleIter next=iter+1;
    if(iter==end) next=iter-1;
    loaded->remove(iter);
    find(next);
};
void SubtitleApp::insertNew(){};

void SubtitleApp::scrollUp(){
    if((iter-2)>=begin)
        display->scrollUp(&*(iter - 2));
    else
        display->scrollUp(nullptr);
    iter--;
};
void SubtitleApp::scrollDown(){
    if(iter+2<=end)
        display->scrollDown(&*(iter+2));
    else
        display->scrollDown(nullptr);
    iter++;
};

void SubtitleApp::find(SubtitleIter s){
};
