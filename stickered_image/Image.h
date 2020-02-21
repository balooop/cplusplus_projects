/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using std::string;
using namespace cs225;

class Image : public PNG 
{
    public:
        //increases luminance by 0.1 or amount
        void lighten();
        void lighten(double amount);

        //decreases luminance by 0.1 or amount
        void darken();
        void darken(double amount);

        //increases saturation by 0.1 or amount
        void saturate();
        void saturate(double amount);

        //decreases saturation by 0.1 or amount
        void desaturate();
        void desaturate(double amount);
        
        //turns image grayscale
        void grayscale();

        //rotates the color wheel by degrees
        void rotateColor(double degrees);

        //illinifies the image
        void illinify();

        //scales image by a factor, or to fit within w x h
        void scale(double factor);
        void scale(unsigned w, unsigned h);
};
