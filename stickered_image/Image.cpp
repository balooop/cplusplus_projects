#include "Image.h"
using namespace cs225;
#include <string>
using std::string;
#include<cmath>

//parameter-less lighten function
void Image::lighten()
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //increases the luminance, ensuring it stays within the bounds
            if(thisPixel.l + .1 > 1)
                thisPixel.l = 1;
            else
                thisPixel.l += .1;    
        }
    }
}

//parameterized lighten function
void Image::lighten(double amount)
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //increases the luminance, ensuring it stays within the bounds
            if(thisPixel.l + amount > 1)
                thisPixel.l = 1;
            else
                thisPixel.l += amount;    
        }
    }
}

//parameter-less darken function
void Image::darken()
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //decreases the luminance, ensuring it stays within the bounds
            if(thisPixel.l - .1 < 0)
                thisPixel.l = 0;
            else
                thisPixel.l -= .1;    
        }
    }
}

//parameterized darken function
void Image::darken(double amount)
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //decreases the luminance, ensuring it stays within the bounds
            if(thisPixel.l - amount < 0)
                thisPixel.l = 0;
            else
                thisPixel.l -= amount;    
        }
    }
}


//parameter-less saturate function
void Image::saturate()
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //increases the saturation, ensuring it stays within the bounds
            if(thisPixel.s + .1 > 1)
                thisPixel.s = 1;
            else
                thisPixel.s += .1;    
        }
    }
}


//parameterized saturate function
void Image::saturate(double amount)
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //increases the saturation, ensuring it stays within the bounds
            if(thisPixel.s + amount > 1)
                thisPixel.s = 1;
            else
                thisPixel.s += amount;    
        }
    }
}

//parameter-less desaturate function
void Image::desaturate()
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //decreases the saturation, ensuring it stays within the bounds
            if(thisPixel.s - .1 < 0)
                thisPixel.s = 1;
            else
                thisPixel.s -= .1;    
        }
    }
}

//parameterized saturate function
void Image::desaturate(double amount)
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++)
    {
        for (unsigned y = 0; y < this->height(); y++)
        {
            //creates a reference to the pixel at (x,y) for modificatiton
            HSLAPixel & thisPixel = this->getPixel(x,y);

            //decreases the saturation, ensuring it stays within the bounds
            if(thisPixel.s - amount < 0)
                thisPixel.s = 0;
            else
                thisPixel.s -= amount;    
        }
    }
}

void Image::grayscale()
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++) 
    {
        for (unsigned y = 0; y < this->height(); y++) 
        {
            //creates a reference to the pixel at (x,y) for modification
            HSLAPixel & pixel = this->getPixel(x, y);
            //grayscales pixel by setting saturation to 0
            pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees)
{
    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++) 
    {
        for (unsigned y = 0; y < this->height(); y++) 
        {
            //creates a reference to the pixel at (x,y) for modification
            HSLAPixel & pixel = this->getPixel(x, y);
            //rotates the color
            if(pixel.h + degrees < 360 && pixel.h + degrees > 0)
                pixel.h += degrees;
            if(pixel.h + degrees < 0)
                pixel.h = pixel.h + degrees + 360;
            if(pixel.h + degrees > 360)
                pixel.h = pixel.h + degrees - 360;
    }
  }
}

void Image::illinify()
{
    double dhOrange, dhBlue;
    double blueHue = 216;
    double orangeHue = 11;

    //loops through rows and cols of pixels
    for (unsigned x = 0; x < this->width(); x++) 
    {
        for (unsigned y = 0; y < this->height(); y++) 
        {
            HSLAPixel & pixel = this->getPixel(x, y);     //get pixel at each location

            // calculates difference in hue from illini orange
            // compares pixels hue to orange and orange + 360 to account for circular natuer of HSL color space
            if (std::abs(orangeHue - pixel.h) > std::abs((orangeHue+360) - pixel.h))
                dhOrange = std::abs((orangeHue+360) - pixel.h);
            else
                dhOrange = std::abs(orangeHue - pixel.h);

            // calculates difference from illini blue
            // compares pixels hue to blue and blue + 360 to account for circular natuer of HSL color space
            if (std::abs(blueHue - pixel.h) > std::abs((blueHue+360) - pixel.h))
                dhBlue = std::abs((blueHue+360) - pixel.h);
            else
                dhBlue = std::abs(blueHue - pixel.h);

            // appropriately changes the hue fo the pixel based on if it is coser to orange than blue
            if (dhOrange > dhBlue)  //if its more orange than blue
                pixel.h = blueHue;
            else
                pixel.h = orangeHue;
        }
    }
}

void Image::scale(double factor)
{
    //creates an image that is identical to the image calling this method
    //needed becasue we resize the image
    Image* original = new Image(*this);

    //calculates new width and height of scaled image
    unsigned int newW, newH;
    newW = factor*this->width();
    newH = factor*this->height();
    
    //resizes imaage according to new width and height
    resize(newW, newH);

    if(factor != 1.0)
    {
        //loops through rows and cols of picture
        for(unsigned int i = 0; i < this->width(); i++)
        {
            for(unsigned int j = 0; j < this->height(); j ++)
            {
            //general algorithm: pixel in orig image at (i/factor, j/factor) maps to (i,j)
            
            //define coordinates to grab pixel from original image
            double origX = ((double)i)/factor;
            double origY = ((double)j)/factor;

            //create reference pixels for original pixel and pixel on scaled image
            HSLAPixel & origPixel = original->getPixel(origX, origY);
            HSLAPixel & newPixel = this->getPixel(i, j);

            //assigns new pixels properties of original pixel
            newPixel.h = origPixel.h;
            newPixel.s = origPixel.s;
            newPixel.l = origPixel.l;
            newPixel.a = origPixel.a;
            }
        }
    }

    //frees heap memory created for scaling
    delete original;
    original = NULL;
}

void Image::scale(unsigned w, unsigned h)
{
    double factored_w = ((double)w)/(this->width());
    double factored_h = ((double)h)/(this->height());
    (factored_w > factored_h) ? scale(factored_h) : scale(factored_w);
}