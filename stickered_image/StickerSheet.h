/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class StickerSheet{
    private:
        //private members vars of Scene
        Image ** Scene;
        unsigned max_;
        Image * base;
        unsigned count_;
        unsigned * x;
        unsigned * y;

        //private helper functions for Scene
        void copy(const StickerSheet &other);
        void destroy();

    public:
        //stickersheet constructor, copy constructor, destructor
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);

        //= operator
        const StickerSheet& operator=(const StickerSheet &other);
    
        //public methods for StickerSheet
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        Image render() const;
};

