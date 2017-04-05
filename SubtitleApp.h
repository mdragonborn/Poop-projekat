//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLEAPP_H
#define POOP_SUBTITLEAPP_H

#include <conio.h>
#include <map>

#define W 119
#define A 97
#define S 115
#define D 100
#define UP 72
#define DOWN 80


using std::map;

class SubtitleApp {
private:
    static map<int, void(*)()> * listingOptions= nullptr;
    SubtitleIter begin, iter, end;
    static void goBack(){
        if(iter!=begin) iter--;
    }
    static void goForward(){
        if(iter!=end) iter++;
    }
    static void shiftAll(){
        cout<< "Uneti za koliko " << io.unit() << " treba pomeriti ovaj i sve titlove posle njega: "<<flush;
        cin>>input;
        io.shiftTitle(begin, end, input);  //dodaj neki exception
        cout<< "Titlovi uspesno pomereni. Pritisnuti bilo sta za nastavak rada."<<endl; getch();
        cin>>input;
    }
    static void printListingHelp(){
        cout<<"Opcije: A - pomeranje svih titlova;"
        <<endl<<"E - razdvajanje jednog titla na dva; "
        <<endl<<"D - spajanje dva titla u jedan;"
        <<endl<<"Navigacija W-S/Strelice"
        <<endl<<"Q - kraj rada"<<endl;
        while(!_kbhit());
        return;
    }
    static void initListingOptions(){
        listingOptions=new map<int, void(*)()>();
        listingOptions->insert(W, &goBack);
        listingOptions->insert(UP, &goBack);
        listingOptions->insert(S, &goForward);
        listingOptions->insert(DOWN, &goForward);
        listingOptions->insert(A, &shiftAll);
        listingOptions->insert(H, &listing_help_print);
        listingOptions->insert(E, &mergeTitles);
        listingOptions->insert(D, &splitTitle);
        return;
    }
    static void printMenu(){
        cout<<"Program za rukovanje DivX titlovima\nMilena Markovic, projektni zadatak za predmet POOP"
        <<endl<<"1. Prolazak kroz titlove"
        <<endl<< "2. Kraj rada sa trenutnim fajlom"
        <<endl<<"0. Kraj programa"
        <<endl;
    }
    static void listSubtitles(SubtitleIO& io){
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
public:
    static int main_app(){

    }
};


#endif //POOP_SUBTITLEAPP_H
