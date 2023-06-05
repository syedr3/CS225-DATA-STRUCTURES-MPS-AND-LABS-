
#include "StickerSheet.h"
using namespace cs225;
StickerSheet::StickerSheet(const Image &picture, unsigned max){
    max_ = max;
    base = picture;
    num_stickers = 0;
    layer_image.resize(max_);
    x_coordinates.resize(max_);
    y_coordinates.resize(max_);
}
void StickerSheet::copy_(const StickerSheet &other){
    base = other.base;
    max_ = other.max_;
    num_stickers = other.num_stickers;
    layer_image.resize(max_);
    x_coordinates.resize(max_);
    y_coordinates.resize(max_);
    for (unsigned int i = 0; i < num_stickers; i++){
        layer_image[i] = other.layer_image[i];
        x_coordinates[i] = other.x_coordinates[i];
        y_coordinates[i] = other.y_coordinates[i];        
    }
}

StickerSheet::StickerSheet(const StickerSheet &other){
    copy_(other);
}

int StickerSheet::addSticker(Image &sticker, int x, int y){
    num_stickers++;
    while(max_ < num_stickers){
        max_++;
    }
    layer_image.insert(layer_image.begin()+num_stickers-1, &sticker);
    x_coordinates.insert(x_coordinates.begin()+num_stickers-1, x);
    y_coordinates.insert(y_coordinates.begin()+num_stickers-1, y);
    return num_stickers-1;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max < num_stickers){
        layer_image.erase(layer_image.begin()+max,layer_image.begin()+num_stickers-1);
        x_coordinates.erase(x_coordinates.begin()+max,x_coordinates.begin()+num_stickers-1);
        y_coordinates.erase(y_coordinates.begin()+max,y_coordinates.begin()+num_stickers-1);
        num_stickers = max;
    }
    max_ = max;
}

Image* StickerSheet::getSticker(unsigned index){
    if(index<num_stickers){
        return layer_image[index];
    }
    return NULL;
}

int StickerSheet::layers () const{
    return max_;
}

 const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
        destroy_();
        copy_(other);
        return *this;
}

 void StickerSheet::destroy_(){
}

StickerSheet::~StickerSheet(){
    destroy_();
}

void StickerSheet::removeSticker(unsigned index){
layer_image.erase(layer_image.begin()+index);
x_coordinates.erase(x_coordinates.begin()+index);
y_coordinates.erase(y_coordinates.begin()+index);
num_stickers--;
}

Image StickerSheet::render () const{
    int max_w = base.width();
    int max_h = base.height();
    int hey_x = 0;
    int hey_y = 0;
    for (unsigned int i = 0; i<num_stickers; i++){
        if(layer_image[i] != NULL){
            int plz = layer_image[i]->width();
            int work = layer_image[i]->height();
        if(plz+x_coordinates[i] > max_w) {max_w = plz+x_coordinates[i];}
        if(work+y_coordinates[i] > max_h) {max_h = work+y_coordinates[i];}
        if (x_coordinates[i] < hey_x){
            hey_x = x_coordinates[i];
        }
        if (y_coordinates[i] < hey_y){
            hey_y = y_coordinates[i];
        }
    }}
    int w = max_w-hey_x;
    int h = max_h-hey_y;
    Image product(w,h);

    for (unsigned int i = 0; i<base.width(); i++){
        for (unsigned int j = 0; j<base.height(); j++){
            HSLAPixel sticker_pixel = base.getPixel(i,j);
            HSLAPixel &base_pixel = product.getPixel(-hey_x+i,-hey_y+j);
            base_pixel = sticker_pixel;
        }
    }
    for (unsigned int i = 0; i<num_stickers; i++){
        if (layer_image[i] != NULL){
            unsigned int cw = layer_image[i]->width();
            unsigned int ch = layer_image[i]->height();
            for (unsigned int x = 0; x<cw; x++){
                for (unsigned int y = 0; y<ch; y++){
                    HSLAPixel sticker_pixel = layer_image[i]->getPixel(x,y);
                    HSLAPixel &base_pixel = product.getPixel(x_coordinates[i]+x-hey_x,y_coordinates[i]+y-hey_y);
                    if (sticker_pixel.a != 0){
                        base_pixel = sticker_pixel;
                    }
                }
            }
        }
    }
    return product;
}

int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (layer < num_stickers){
        *layer_image[layer] = sticker;
        x_coordinates[layer] = x;
        y_coordinates[layer] = y;
        return layer;
    }
    return -1;
}

bool StickerSheet::translate(unsigned index, int x, int y){
    if (index < num_stickers){
        x_coordinates[index] = x;
        y_coordinates[index] = y;
        return true;
    }
    return false;
}
