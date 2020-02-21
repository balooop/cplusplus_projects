#include "StickerSheet.h"
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

//constructor
StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    //creates the base image in heap memory
    base = new Image(picture);
    //assigns max and sets count to 0
    max_ = max;
    count_ = 0;
    
    //creates x and y position arrays
    x = new unsigned[max_];
    y = new unsigned[max_];

    //creates scene arrays to hold images
    Scene = new Image*[max_];
    
}

//destructor
StickerSheet::~StickerSheet()
{
    //calls destroy helper function (also used in =)
    destroy();
}

//copy constructor
StickerSheet::StickerSheet(const StickerSheet & other)
{
    //calls copy helper function (also used in =)
    copy(other);
}

//copy helper function, used in copy ctor and = operator
void StickerSheet::copy(const StickerSheet &other)
{
    //sets max and count according to other
    max_ = other.max_;
    count_ = other.count_;
    
    //allocates base image, scene array, x/y coord arrays
    base = new Image(*(other.base));
    Scene = new Image*[max_];
    x = new unsigned[max_];
    y = new unsigned[max_];

    //loops from 0 to max
    for(unsigned i = 0; i < count_; i++)
    {
        //deep copy image from other array
        this->Scene[i] = new Image(*(other.Scene[i]));
        //copy x and  y coordinate
        x[i] = other.x[i];
        y[i] = other.y[i];
    }
}

//destroy helper function, used in dtor and = operattor
void StickerSheet::destroy(){
    //loops 0 to max

    for(unsigned i = 0; i < count_; i ++)
    {
    
        //deallocate the sticker, set ptr to null, set x/y coord to 0
        delete Scene[i];
        Scene[i] = NULL;
        x[i] = 0;
        y[i] = 0;
    
    }
    //deletes all member variables
    delete base;    
    delete[] Scene; 
    delete[] x;
    delete[] y;
}

//= operator overload
const StickerSheet& StickerSheet::operator=(const StickerSheet &other)
{
    //destroys/deallocates current image
    destroy();
    //deep copies other
    copy(other);
    //returns sheet that is calling =
    return *this;
}

//changes # max stickers
void StickerSheet::changeMaxStickers(unsigned max)
{
    if(max == max_)
        return;
    //algorithm:
    //create a temp array of size max for scene x and y
    //if max > max_, copy all pointers from original array from 0 to count 
    //if max < max_, cop yeverything from either 0 to new max or 0 to count, based on which is smaller
    //then delete all images after max
    //increment count if it was more than max, otherwise leave it the same

    //allocate a new scene, x, and y array
    Image ** newScene = new Image*[max];
    unsigned * newX = new unsigned[max];
    unsigned * newY = new unsigned[max];

    //case where we increase max
    if(max > max_)
    {
        for(unsigned i = 0; i < count_; i++)

        {
            //copy all image ptrs, x and y coordinates
            newScene[i] = Scene[i];
            newX[i] = x[i];
            newY[i] = y[i];
        }
    }
    //case where we decrease max
   if(max < max_)
    {
        //calculate what our bound should be (the smaller of count and max)
        unsigned bound = ((count_ > max) ? max : count_);
        for(unsigned i = 0; i < bound; i++)
        {
            //copy all image ptrs, x and y coordinates
            newScene[i] = Scene[i];
            newX[i] = x[i];
            newY[i] = y[i];
        }
        //delete all images past new max
        for(unsigned j = max; j < count_; j++)
        {
            delete Scene[j];
        }
    //either increments or decrements count
    (count_ > max) ? (count_ = max) : (count_ += 0);
    }

    //deletes scene, x, and y from original stickersheet
    delete[] Scene;
    delete[] x;
    delete[] y;

    //assigns callee scene, x, y, and max to point to or hold the values of newScene, newX, newY, and new max
    Scene = newScene;
    x = newX;
    y = newY;
    max_ = max;

    
}

//adds a sticker to the array
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{   
    //algorithm:
    //if array is full, return -1
    //else, assign sticker, x, and y, to respective arrays at [count_]
    //increment count
    if(count_ == max_)
        return -1;
    else
    {   
        //creates a new sticker to get added on heap
        Image * newSticker = new Image(sticker); 
        //scene at count (next available slot) points to the new sticker
        Scene[count_] = newSticker;
        //assigns x and y
        this->x[count_] = x;
        this->y[count_] = y;
        //increments count
        count_++;
        //returns index
        return count_ - 1;
    }
}

//changes x and y positions
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    //index should be for a sticker that exists
    if(index < count_)
    {
        //assigns x and y and returns true
        this->x[index] = x;
        this->y[index] = y;
        return true;
    }
    else
    {
        //else you can't translate shit
        return false;
    }
}

//removes a sticker from the array
void StickerSheet::removeSticker(unsigned index)
{
    //algorithm:
    //if index is greater than or equal to count, return
    //else, delete scene at index, set its pointer to null, set (x,y) to (0,0)
    //slide stickers over: loop from index to count, for x, y, and scene, set [i] to [i+1]
    
    //decrement count
    if(index >= count_)
    {
        //if index >= count_ we can't remove a sticker
        return;
    }
    else
    {
        //removes the image that needs to be removed
        delete Scene[index];
        Scene[index] = NULL;
        //slides all the images after index ahead
        for(unsigned i = index; i < count_ - 1; i ++)    
        {
            x[i] = x[i+1];
            y[i] = y[i+1];
            Scene[i] = Scene[i+1];
        }
        count_--;
    }
}

//gets a sticker from the array
Image * StickerSheet::getSticker(unsigned index)
{
    //algorithm:
    //if index >= count, return null
    //else, return the pointer to the sticker at index within scene
    if(index >= count_)
    {
        return NULL;
    }
    else
    {
        return Scene[index];
    }
}

//renders the image 
Image StickerSheet::render() const
{
    //algorithm:
    //create a new image 
    //look through all stickers, if a sticker will go out of bounds or is larger than the sticker, we resize the image
    //after resized, we look through each sticker, and within that, loop through each image of the stickers
    //for each sticker, we loop through the pixels it overwrites, and overwrite them
    Image rendered(*base);    
    unsigned int maxW = rendered.width();
    unsigned int maxH = rendered.height();

    for(unsigned i = 0; i < count_; i++)
    {
        if(maxW < (x[i] + Scene[i]->width())) 
            { 
                maxW = x[i] + Scene[i]->width();
            }
        if(maxH < (y[i] + Scene[i]->height())) 
            {
                maxH = y[i] + Scene[i]->height();
            }
        
    }

    rendered.resize(maxW, maxH);
    
    //loops through stickers
    for(unsigned i = 0; i < count_; i++ )
    {   
        //makes sure there is a sticker to add
    
        //loops through rows and columns of sticker, starts at x/y coordinate and ends at x/y coordinate + width/height of sticker
        for(unsigned j = x[i]; j < (x[i] + Scene[i]->width()); j++)
        {
            for(unsigned k = y[i]; k < (y[i] + Scene[i]->height()); k++)
            {
                //creates pixel references from base and sticker
                HSLAPixel & stickerPixel = Scene[i]->getPixel(j - x[i], k - y[i]);
                HSLAPixel & basePixel = rendered.getPixel(j, k);
                //overwrites HSLA of base image 
                if(stickerPixel.a != 0)
                {
                    basePixel.h = stickerPixel.h; 
                    basePixel.s = stickerPixel.s;
                    basePixel.l = stickerPixel.l;
                    basePixel.a = stickerPixel.a;
                }
            }
        }
    
    }
    return rendered;
}

