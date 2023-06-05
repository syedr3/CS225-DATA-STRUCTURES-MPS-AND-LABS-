/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
using namespace std;
class StickerSheet{
    public:
    unsigned int max_;  
    Image base;    
    vector<Image*> layer_image;
    vector<int> x_coordinates;
    vector<int> y_coordinates;
    unsigned int num_stickers;
    void destroy_();
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, int x, int y);
    int setStickerAtLayer(Image &sticker, unsigned layer, int x, int y);
    bool translate(unsigned index, int x, int y);
    void removeSticker(unsigned index);
    Image* getSticker(unsigned index);
    int layers () const;
    Image render () const;
    void copy_(const StickerSheet &other);
    ~StickerSheet();
};