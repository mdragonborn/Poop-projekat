//
// Created by Milena on 05/04/2017.
//

#include "SubtitleApp.h"


static void SubtitleApp::shiftAll(){
    cout<< "Uneti za koliko " << io.unit() << " treba pomeriti ovaj i sve titlove posle njega: "<<flush;
    cin>>input;
    io.shiftTitle(begin, end, input);  //dodaj neki exception
    cout<< "Titlovi uspesno pomereni. Pritisnuti bilo sta za nastavak rada."<<endl; getch();
    cin>>input;
}

static void SubtitleApp::initListingOptions(){
    listingOptions=new map<int, void(*)()>();
    listingOptions->insert(W, &goBack);
    listingOptions->insert(UP, &goBack);
    listingOptions->insert(S, &goForward);
    listingOptions->insert(DOWN, &goForward);
    listingOptions->insert(A, &shiftAll);
    listingOptions->insert(H, &listing_help_print);
    listingOptions->insert(E, &mergeTitles);
    listingOptions->insert(D, &splitTitle);
    listingOptions->insert(I, &insertTitle);
    listingOptions->insert(R, &removeTitle);
    return;
}

static void SubtitleApp::listSubtitles(SubtitleIO& io){
    if (listingOptions= nullptr) initListingOptions();
    int input=0;
    begin=iter=io.begin(), end=io.end();
    while (1){
        while (1){
            if (_kbhit()){
                input=_getch();
                break;
            }
            if(input==Q) return;
            try{
                listingOptions->at(input)();
            }catch(out_of_range){continue;};
            system("cls");
            cout<<io.fileName() << listing_help_print() <<endl;
            cout<<*iter<<endl;
        }
    }
}