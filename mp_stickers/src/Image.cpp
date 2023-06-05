#include "Image.h"
using namespace cs225;
Image::Image(){
this->resize(0,0);
}
Image::Image(unsigned int width, unsigned int height){
this->resize(width,height);
}
void Image::lighten(){

    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.l = x.l+0.1;
            if (x.l>1) {x.l = 1;}
            if (x.l<0) {x.l = 0;}
            }
    }
}
void Image::lighten(double amount){

    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.l = x.l+amount;
            if (x.l>1) {x.l = 1;}
            if (x.l<0) {x.l = 0;}
            }
    }
}
void Image::darken(){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.l = x.l-0.1;
            if (x.l<0) {x.l = 0;}
            if (x.l>1) {x.l = 1;}
            }
    }
}
void Image::darken(double amount){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.l = x.l-amount;
            if (x.l<0) {x.l = 0;}
            if (x.l>1) {x.l = 1;}
            }
    }
}
void Image::saturate(){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.s = x.s+0.1;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::saturate(double amount){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.s = x.s+amount;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::desaturate(){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.s = x.s-0.1;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::desaturate(double amount){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.s = x.s-amount;
            if (x.s<0) {x.s = 0;}
            if (x.s>1) {x.s = 1;}
            }
    }
}
void Image::grayscale(){
    for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.s = 0;
            }
    }
}
void Image::rotateColor(double degrees){
        for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            x.h = x.h+degrees;
            while(x.h>360){
                x.h = x.h-360;
            }
            while(x.h<0){
                x.h = x.h+360;
            }
            }
    }
}
void Image::Illinify(){
        for(unsigned int i = 0; i<this->width(); i++){
        for (unsigned int j = 0; j<this->height(); j++){
            HSLAPixel &x = this->getPixel(i,j);
            int o = std::abs(x.h-11);
            int b = std::abs(x.h-216);
            if (o<b){x.h = 11;}
            if (b<o){x.h = 216;}
            }
    }
}
void Image::scale(double factor){
unsigned int w = factor*this->width();
unsigned int h = factor*this->height();
Image* newone = new Image;
*newone = *this;
this->resize(w,h);
for(unsigned int i = 0; i<w; i++){
        for (unsigned int j = 0; j<h; j++){
            HSLAPixel &x = this->getPixel(i,j);
            HSLAPixel &y = newone->getPixel(i/factor,j/factor);
            x = y;
        }
    }
    delete newone;
}
void Image::scale(unsigned w,unsigned h){
    double factor;
    double width = this->width();
    double height = this->height();
    double wi = w/width;
    double hi = h/height;
    if (wi<hi) {factor  = wi;}
    else {factor = hi;}
    unsigned int ww = factor*this->width();
    unsigned int hh = factor*this->height();
    Image* newone = new Image;
    *newone = *this;
    this->resize(ww,hh);
    for (unsigned int i = 0; i<ww; i++){
        for (unsigned int j = 0; j<hh; j++){
            HSLAPixel &x = this->getPixel(i,j);
            HSLAPixel &y = newone->getPixel(i/factor,j/factor);
            x = y;
        }
    }
    delete newone;
}