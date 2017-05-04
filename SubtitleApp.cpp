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
    listingOptions=new map<int, fun_ptr>();
    listingOptions->emplace(W, &SubtitleApp::goBack);
    listingOptions->emplace(UP_KEY, &SubtitleApp::goBack);
    listingOptions->emplace(S, &SubtitleApp::goForward);
    listingOptions->emplace(DOWN_KEY, &SubtitleApp::goForward);
    listingOptions->emplace(A, &SubtitleApp::shiftAll);
    listingOptions->emplace(H, &SubtitleApp::printListingHelp);
    listingOptions->emplace(E, &SubtitleApp::mergeTitles);
    listingOptions->emplace(D, &SubtitleApp::splitTitle);
    listingOptions->emplace(I, &SubtitleApp::insertTitle);
    listingOptions->emplace(R, &SubtitleApp::removeTitle);
    return;
}

void SubtitleApp::initMainOptions(){
    mainOptions=new map<int,fun_ptr>();
    mainOptions->emplace(W, &SubtitleApp::mainGoUp);
    mainOptions->emplace(S, &SubtitleApp::mainGoDown);
    mainOptions->emplace(UP_KEY, &SubtitleApp::mainGoUp);
    mainOptions->emplace(DOWN_KEY, &SubtitleApp::mainGoDown);
    mainOptions->emplace(KEY_ENTER, &SubtitleApp::mainSelect);
};


void SubtitleApp::listSubtitles(Subtitles &subs){

    if (listingOptions== nullptr) initListingOptions();
    int input=0;
    begin=iter=subs.begin(), end=subs.end();
    while (1){
        while (1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW_KEY) input=_getch();
                break;
            }
        }
            if(input==Q) return;
            try{
                (this->*listingOptions->at(input))();
            }catch(out_of_range){continue;};
    //        cout<<io.fileName() << listing_help_print() <<endl;
    //        cout<<*iter<<endl;
        }
    }


void SubtitleApp::insertTitle(){};
void SubtitleApp::removeTitle(){};

void SubtitleApp::printListingHelp(){};

int SubtitleApp::main_app() {
    int input;
    SubtitleIO * io=MplayerIO::createObject();
    loaded = io->loadSubtitles("C:\\Users\\Milena\\Desktop\\Primer.sub");
    if (display == nullptr) display = new Display(35, 100);
    if (mainOptions == nullptr) initMainOptions();
    mainCursor=0;
    if (!loaded) {
        mainCursorMax=3;
        display->setNewMenu(&mainNotLoadedStr,3);
    }
    else {
        mainCursorMax = 4;
        display->setNewMenu(&mainLoadedStr,3);
    }
    display->generateHomeScr(false);
    while (1) {
        while(1) {
            if (_kbhit()) {
                input = _getch();
                if(input==ARROW_KEY) input=_getch();
                break;
            }
        }
        if (input == Q) return 0;
        try {
            (this->*mainOptions->at(input))();
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
        display->menuUp();
    }
};
void SubtitleApp::mainGoDown(){
    if(mainCursor<mainCursorMax){
        mainCursor++;
        display->menu();
    }
};
void SubtitleApp::mainSelect(){
    if(loaded== nullptr){
        (this->*mainNotLoaded[mainCursor])();
    } else (this->*mainLoaded[mainCursor])();
    if (!loaded) {
        mainCursorMax=3;
        display->setNewMenu(&mainNotLoadedStr,3);
    }
    else {
        mainCursorMax = 4;
        display->setNewMenu(&mainLoadedStr,3);
    }
    display->generateHomeScr((bool)loaded); mainCursor=0;
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
                if (input == ARROW_KEY) input = _getch();
                break;
            }
        }
        if (input == DOWN_KEY || input == S && expCursor < 2) {
            expCursor++;
            display->mainDown();
        }
        else if (input == UP_KEY || input == W && expCursor != 0) {
            expCursor--;
            display->mainUp();
        }
        else if (input == ENTER_KEY) {
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
                if(input==ARROW_KEY) input=_getch();
                break;
            }
        }
        if (input == Q) {display->displayMain(); mainCursor=0; return;}
        try{
            (this->*editOptions->at(input))();
        }catch(out_of_range){continue;}
    }
};

void SubtitleApp::initEditOptions(){
    editOptions=new map<int, fun_ptr>;
    editOptions->emplace(A, &shiftAll);
    editOptions->emplace(E,&editContent);
    editOptions->emplace(R, &removeCurrent);
    editOptions->emplace(I, &insertNew);
    editOptions->emplace(D, &mergeTitles);
    editOptions->emplace(W, &scrollUp);
    editOptions->emplace(UP_KEY, &scrollUp);
    editOptions->emplace(S, &scrollDown);
    editOptions->emplace(DOWN_KEY, &scrollDown);
    editOptions->emplace();
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
                if(input==ARROW_KEY) input=_getch();
                break;
            }
        }
        if (input == Q) {display->displayMain(); mainCursor=0; return;}
        if(input==LEFT || input==A || input==RIGHT || input==D) {
            optionToggle=(optionToggle+1)%2; display->savePromptShift();
        }
        if(input==ENTER_KEY) if(optionToggle) exit(1);
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
    find();
};
void SubtitleApp::insertNew(){};

void SubtitleApp::scrollUp(){
    if(iter==begin) return;
    if((iter-2)>=begin)
        display->scrollUp(&*(iter - 2));
    else
        display->scrollUp(nullptr);
    iter--;
};
void SubtitleApp::scrollDown(){
    if(iter==back) return;
    if(iter+2<=end)
        display->scrollDown(&*(iter + 2));
    else
        display->scrollDown(nullptr);
    iter++;
};

void SubtitleApp::find(){
};

void SubtitleApp::editContent(){
    (*iter).changeContent(display->contentEditCurrent());
    display->refreshScrolled();
};
