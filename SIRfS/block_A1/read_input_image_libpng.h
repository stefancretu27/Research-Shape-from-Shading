#ifndef READ_INPUT_IMAGE_LIBPNG_H_INCLUDED
#define READ_INPUT_IMAGE_LIBPNG_H_INCLUDED

#include <iostream>
#include <stdlib.h>

//library used for reading input image
extern "C"
{
    #include "../libpng/include/png.h"
}
//temporary
#include <fstream>

#include "../helpers/validation.h"

//This function prints the versions of libpng and zlib used for this program
void libs_version_info();
//read input image
Matrix2D<double> read_png_file();

#endif // READ_INPUT_IMAGE_LIBPNG_H_INCLUDED
