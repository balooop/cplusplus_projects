This project implements the "Image" class, and the "Stickersheet" class, and creates a creative image with stickers on it. The files I contributed to were image.h, image.cpp, stickersheet.h, stickersheet.cpp, and main.cpp
The image class represents an image - it implements the following methods for image modification:
Functions implemented: 
    1) lighten(): increases the luminance of each pixel in the image by a certain amount
    2) darken(): decreases the luminance of each pixel in the image by a certain amount
    3) saturate(): saturates the image by a certain amount
    4) desaturate(): desaturates the image by a certain amount
    5) grayscale(): transforms the image into a grayscale image
    6) rotateColor(): rotates the color of each pixel on the HSL color wheel by an inputted amount fo degrees
    7) illinify(): makes the image illini blue and orange
    8) scale(): scales the image by a multiplicative factor or to fit a new set of dimensions (overloaded function)
The StickerSheet class implements a way to place various sticker images on top of a main image. It utilizes the image class to do so. It utilizes an array of pointers for the stickers, with an arrays for their x and y coordinates 
Functions implemented:
    1) constructor: creates a new stickersheet based on an image and a max number of stickers to be put on it, allocating memory for its members
    2) destructor: destroys the stickersheet object, freeing all memory associated with it.
    3) copy constructor: creates a deep copy of a StickerSheet object
    4) = operator: assings one stickersheet object to the contents of another, does a deep copy
    5) changemaxStickers(): changes the max number of stickers allowed on the stickersheet, potentially removing stickers if it is resized smalelr
    6) addSticker(): adds a sticker to the base image on the stickersheet
    7) translate(): changes the x and y coordinates of a sticker
    8) removeSticker(): removes a sticker from the stickersheet
    9) getSticker(): returns a pointer to the sticker at an input index
    10) render(): renders the stickersheet object as a PNG image
The creative portion of this project creates a stickersheet image that makes a meme out of U of I's alma mater statue. This was written in main.cpp
This project was completed for CS225. All materials not mentioned were provided by course staff.
