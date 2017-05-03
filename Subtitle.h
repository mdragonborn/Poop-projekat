//
// Created by Milena on 05/04/2017.
//

#ifndef POOP_SUBTITLE_H
#define POOP_SUBTITLE_H


#include "mvtime.h"
#include <string.h>

using std::string;

class Color{
private:
    int r=0, g=0, b=0;
public:
    Color(int red, int green, int blue):r(red%256),g(green%256),b(blue%256){};
    Color(){};
    Color(Color& copy):r(copy.r),g(copy.g),b(copy.b){};
    int getRed(){return r;}
    int getGreen(){return g;}
    int getBlue(){return b;}
};

class Subtitle {
private:
  /*  struct Formatting{
    private:
        Color * color= nullptr;
        bool italic=false, bold=false, underline=false;
        string * font=nullptr;

    public:
        Formatting(Color*c):color(c){};
        Formatting(string*f):font(font){};
        Formatting(bool i, bool b, bool u):italic(i),bold(b),underline(u){};
        Formatting(Formatting& f){
            if(f.color) color=new Color(*f.color);
            if(f.font) font=new string(*f.font);
            italic=f.italic;
            bold=f.bold;
            underline=f.underline;
        }

        Color getColor() const {
            return *color;
        }

        bool isItalic() const {
            return italic;
        }

        bool isBold() const {
            return bold;
        }

        bool isUnderline() const {
            return underline;
        }

        string getFont() const {
            return *font;
        }
    };
*/
    mvTimeRange time_;
    string content_;
    //Formatting * format_;
public:
    Subtitle(const Subtitle& copy):time_(copy.time_), content_(copy.content_)//, format_(new Formatting(*copy.format_))
    {};
    Subtitle(Subtitle& copy):time_(copy.time_), content_(copy.content_)//, format_(new Formatting(*copy.format_))
    {};
    Subtitle(Subtitle&& copy):time_(copy.time_), content_(copy.content_)//,  format_(new Formatting(*copy.format_))
     {};
    Subtitle(mvTimeRange time, string content//, Formatting* formatting= nullptr
    ):content_(content), time_(time)//, format_(formatting)
    {};

    Subtitle& shiftTime(mvTime disp, mvTimeRange::dir direction){
        time_.shift(disp, direction);
        return *this;
    }
    Subtitle& extendFront(mvTime disp, mvTimeRange::dir direction){
        time_.shiftStart(disp, direction);
        return *this;
    }
    Subtitle& extendBack(mvTime disp, mvTimeRange::dir direction){
        time_.shiftEnd(disp,direction);
        return *this;
    }
    Subtitle& setTime(mvTimeRange time){
        time_=time;
        return *this;
    }
    Subtitle& changeContent(string newContent){
        content_=newContent;
        return *this;
    }
    string getContent(){
        return content_;
    }
    mvTimeRange getTime(){
        return time_;
    };
    /*Formatting *getFormat_(){
        return format_;
    }*/
    string* splitInLines(int n, int len);

    Subtitle& operator=(const Subtitle& s);
    Subtitle& operator=(Subtitle& s);
    operator string();
};


#endif //POOP_SUBTITLE_H
