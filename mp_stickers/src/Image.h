/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
using namespace cs225;
class Image: public PNG{
public:
Image();
Image(unsigned int width, unsigned int height);
void lighten();
void lighten(double amount);
void darken();
void darken(double amount);
void saturate();
void saturate(double amount);
void desaturate();
void desaturate(double amount);
void grayscale();
void rotateColor(double degrees);
void Illinify();
void scale(double factor);
void scale(unsigned w,unsigned h);
};
