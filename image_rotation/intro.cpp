#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
    //reads PNG file
    cs225::PNG prerotated_;
    prerotated_.readFromFile(inputFile);

    //constructs a new PNG of the same size as the original. this will hold the rotated image
    cs225::PNG rotated_ = cs225::PNG(prerotated_.width(), prerotated_.height());

    //loops through rows of the original PNG image
    for (unsigned x = 0; x < prerotated_.width(); x++)
    {
        //loops through columns of the original png image
        for (unsigned y = 0; y < prerotated_.height(); y++)
        {
            cs225::HSLAPixel & tempPixel_ = prerotated_.getPixel(x, y);
            cs225::HSLAPixel & rotatedPixel_ = rotated_.getPixel(rotated_.width() - (x + 1), rotated_.height() - (y + 1));
            rotatedPixel_ = tempPixel_;
        }

    }

    //writes outputfile
    rotated_.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
    cs225::PNG png(width, height);
  // TODO: Part 3

    //generates random starting sue (# between 0 anad 360)
    double myHue_ = (std::rand() % 360)+ 1;
    //generates random starting saturation (# between 0 and 1)
    double mySaturation_ = ((double)(rand() % 10) + 1) / 10;
    //generates random starting luminance (# between 0 and 1)
    double myLuminance_ = ((double)(rand() % 10) + 1) / 10;
    //generates random starting alpha value (# between 0 and 1)
    double myAlpha_ = ((double)(rand() % 10) + 1) / 10;

    //loops through rows of the image
    for (unsigned x = 0; x < png.width(); x++)
    {
        //creates the pixel that will be placed in each column fo the row

        //loops through columns of the original png image
        for (unsigned y = 0; y < png.height(); y++)
        {
            cs225::HSLAPixel pixel_ = cs225::HSLAPixel(myHue_, mySaturation_, myLuminance_, myAlpha_);
            cs225::HSLAPixel & tempPixel_ = png.getPixel(x,y);
            tempPixel_ = pixel_;
        }

        //increments ue
        myHue_++;
        //resets hue upon passing 360
        if(myHue_ > 360)
            myHue_ = 0;

        //increments saturation
        mySaturation_ += 0.1;
        //resets saturation upon exceeding 1
        if(mySaturation_ > 1)
            mySaturation_ = 0;

        //increments luminance
        myLuminance_ += 0.1;
        //resets luminance upon exceeding 1
        if(myLuminance_ > 1)
            myLuminance_ = 0;

        //increments alpha
        myAlpha_ += 0.1;
        //resets luminance upon exceeding 1
        if(myAlpha_ > 1)
            myAlpha_ = 0;
    }

    return png;
}
