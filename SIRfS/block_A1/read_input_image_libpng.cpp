#include "read_input_image_libpng.h"

using namespace std;

void libs_version_info()
{
    cout<<"[Reading input image] Reading input image using libpng and zlib"<<endl;
    //Upper case are macros defined in both libs which show the compile time versions.
    //The lower case are globals which show versions at the time when they run.
    cout<<"[Reading input image] Libpng compile time version: "<<PNG_LIBPNG_VER_STRING<<" running version: "<<png_libpng_ver<<endl;
    cout<<"[Reading input image] Zlib compile time version: "<<ZLIB_VERSION<<" running version: "<<zlibVersion<<endl;
}

Matrix2D<double> read_png_file()
{
    //read filename into a string from cin
    string filename = "images/Peets.png";
    //used for checking the png signature = first 8 bits
    png_byte sig[8];
    //gather data from image header
    int width, height;
    png_byte color_type;
    png_byte bit_depth;
    //pointer to png byte pointer used for storing image values.
    png_bytep *row_pointers;
    //number of channels
    png_uint_32  rowbytes, channels;
    //store the image data as 'double'
    double **grayscaled_values;
    //used for gamma component
    double  scaled_sum= 0.0;

    //cout<<"[Reading input image] Insert file's name"<<endl;
    //cin>>filename;

    libs_version_info();

    /* Open and check the input file */
    //Open the file. If it cannot be done, exit
    FILE *fp = fopen(filename.c_str(), "rb");
    if(!fp)
    {
        cout<<"[Reading input image] Could not open the input file!"<<endl;
        abort();
    }
    //Check if the input file's format is PNG. If not, exit.
    //png_check_sig, like png_sig_cmp do not require information from any png structure, unlike the other libpng functions
    fread(sig, 1, 8, fp);
    if (!png_check_sig(sig, 8))
    {
        cout<<"[Reading input image] The input file's format is not PNG!"<<endl;
        abort();
    }

    /*Load information into png structs*/
    //png_struct_pointer points to a structure that is used by libpng internally to keep track of the PNG image state at any given moment
    png_structp png_struct_pointer = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png_struct_pointer)
    {
        cout<<"[Reading input image] Could not load data in png_structp!"<<endl;
        abort();
    }
    //info_struct_pointer will indicate the state of the image after all user transformations are performed
    png_infop info_struct_pointer = png_create_info_struct(png_struct_pointer);
    if(!info_struct_pointer)
    {
        cout<<"[Reading input image] Could not load data in png_infop!"<<endl;
        //destroy the previously allocated pointer
        png_destroy_read_struct(&png_struct_pointer, NULL, NULL);
        abort();
    }

    //set libpng error handling code by saving the state of the program (registers, stack etc.) If it cannot be done, destroy the pointers to structures
    if(setjmp(png_jmpbuf(png_struct_pointer)))
    {
        cout<<"[Reading input image] Could not save program's state for error handling!"<<endl;
        png_destroy_read_struct(&png_struct_pointer, &info_struct_pointer, NULL);
        abort();
    }

    //png_init_io takes the file pointer and stores it in png_struct_pointer for later use
    png_init_io(png_struct_pointer, fp);
    //the first 8 bytes were checked, so tell png_struct_pointer that hese bytes cannot be fund at the known pointer location
    png_set_sig_bytes(png_struct_pointer, 8);
    //read info about the input image and store this data in the previously allocated structs. The png_read_info processes all headers/chunks until it meets the image data.
    png_read_info(png_struct_pointer, info_struct_pointer);

    //get some info about the image, such as diemnsions, bit depth and color type
    width = png_get_image_width(png_struct_pointer, info_struct_pointer);
    height = png_get_image_height(png_struct_pointer, info_struct_pointer);
    color_type = png_get_color_type(png_struct_pointer, info_struct_pointer);
    bit_depth  = png_get_bit_depth(png_struct_pointer, info_struct_pointer);
    channels = png_get_channels(png_struct_pointer, info_struct_pointer);

    //allocate memory for grayscaled image, which will have input's image dimensions
    Matrix2D<double> grayImage(height, width);

    /*Apply transformations*/
    //if color image, then expand to 24-bit RGB
    if(color_type == PNG_COLOR_TYPE_PALETTE)
    {
        //png_set_expand(png_struct_pointer);
        png_set_palette_to_rgb(png_struct_pointer);
    }
    // if grayscale image, expand it to 8-bit
    //PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
    {
        //png_set_expand(png_struct_pointer);
        png_set_expand_gray_1_2_4_to_8(png_struct_pointer);
    }
    //expand tRNS to full alpha channel. It can apply to any of the above cases (either RGB or grayscale)
    if(png_get_valid(png_struct_pointer, info_struct_pointer, PNG_INFO_tRNS))
    {
        //png_set_expand(png_struct_pointer);
        png_set_tRNS_to_alpha(png_struct_pointer);
    }
    //reduce the images with 16-bit sampling (48-bit RGB) to 8-bit per sample (24-bit RGB)
    if(bit_depth == 16)
    {
        png_set_strip_16(png_struct_pointer);
    }
    //expand grayscale images to RGB
    if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        png_set_gray_to_rgb(png_struct_pointer);
    }
    // Fill the alpha channel with 0xff. Extends rowbytes from 600 to 800 => introduces alpha values and it is not needed
    if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
    {
        //png_set_filler(png_struct_pointer, 0xFF, PNG_FILLER_AFTER);
    }

    //update the structs with all the above transformations
    png_read_update_info(png_struct_pointer, info_struct_pointer);

    //get # of channels
    rowbytes = png_get_rowbytes(png_struct_pointer, info_struct_pointer);

    //allocate memory for rows
    row_pointers = (png_bytep*)calloc(height, sizeof(png_bytep));
    for(int y = 0; y < height; y++)
    {
        //for each row, allocate memory for R,G,B (get row bytes = gets the # of channels) for each column
        row_pointers[y] = (png_byte*)calloc(rowbytes, sizeof(png_byte));
    }

    //read the image into the allocated array
    png_read_image(png_struct_pointer, row_pointers);

    //check the remiander of the image for correctness (remaining chunks)
    png_read_end(png_struct_pointer, NULL);

    //RGB => rowbytes/width = 3
    for(int height_id = 0; height_id < height; height_id++)
        for(int width_id = 0; width_id < rowbytes; width_id+=3)
        {
            scaled_sum =  ((double)row_pointers[height_id][width_id])/255+  ((double)row_pointers[height_id][width_id+1])/255+  ((double)row_pointers[height_id][width_id+2])/255;
            grayImage.setMatrixValue(height_id, width_id/3, scaled_sum/3);
        }

    /*Check data validity*/
    /*ifstream test_file;
    test_file.open("input_image.txt", ios::in);

    double test_matrix[height][width];
    for(int height_id = 0; height_id < height; height_id++)
    {
        for(int width_id = 0; width_id < width; width_id++)
        {
            test_file>>test_matrix[height_id][width_id];
        }
    }

    unsigned int counter = 0;
    for(int width_id = 0; width_id < width; width_id++)
        for(int height_id = 0; height_id < height; height_id++)
        {
            if(fabs(test_matrix[height_id][width_id] - grayImage.getMatrixValue(height_id, width_id)) < pow(10, -15))
            {
                //how many correct values
                counter++;
            }
        }
    cout<<"Testing correctness of  the input image reading process"<<endl;
    cout<<"Number of correct elements: "<<counter<<" Matrix linear size: "<<width*height<<endl;
    test_file.close();
    */

    //cleanup
    //add cleanup for row_pointers after storing data in Matrix2D and convert it to grayscale
    if (png_struct_pointer && info_struct_pointer)
    {
        png_destroy_read_struct(&png_struct_pointer, &info_struct_pointer, NULL);
        png_struct_pointer = NULL;
        info_struct_pointer = NULL;
    }
    for(int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);

    return grayImage;
}
