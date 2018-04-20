//c/c++ libraries
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <time.h>
#include "limits"

//own defined headers
#include "block_A1/data_class.h"
#include "block_A1/params.h"
#include "block_A1/prior.h"
#include "block_A1/read_input_image_libpng.h"
#include "block_A2/SIRfS_Functions.h"
#include "helpers/validation.h"

using namespace std;

int main()
{
    //declare object to refer the input image
    Matrix2D<double> grayImage;
    //read input image
    grayImage = read_png_file();

    //start measuring the execution time
    clock_t tStart = clock();

    //create mask for the input image
    Matrix2D<bool> inputMask(grayImage.getRows(), grayImage.getCols());
    grayImage.compareValuesToTreshold(inputMask, 0, GreaterThan);

    //Initialize SIRfS parameters. Replaces CONSTANTS file from Matlab.
    cout<<"[SIRfS] Finished reading input. Initializing parameters"<<endl;
    clock_t initialize_params = clock();
    Parameters params;
    params.setEvalString(" ");
    //set SIRfS parameters. This method replaces PARAMETERS file from Matlab.
    if(!params.setParameters())
    {
        cout<<"[SIRfS]  SIRfS parameters could not be set. The program will exit."<<endl;
        exit(0);
    }
    cout<<"Time taken for initialize params: "<<(double)(clock() - initialize_params)/CLOCKS_PER_SEC<<endl<<endl;

    //load priors on height, light and reflectance: Z, L and R
    cout<<"[SIRfS] Parameters initialized. Loading priors on height, light and reflectance"<<endl;
    clock_t load_priors= clock();
    Prior prior;

    mat_t *matfp;
    matfp = Mat_Open("prior.mat", MAT_ACC_RDONLY);
    if ( NULL == matfp )
    {
        cout<<"Error opening MAT file: "<<"prior.mat"<<endl;
    }
    else
    {
        prior.initializePriorData(matfp);
    }
    cout<<"Time taken for loading priors: "<<(double)(clock() - load_priors)/CLOCKS_PER_SEC<<endl<<endl;

    cout<<"[SIRfS] Priors loaded. Building 'data' class"<<endl;
    //data.true.im
    clock_t build_data = clock();
    Data data;
    data.getDataTrue().setInputImage(grayImage);

    //im
    Matrix2D<double> im(grayImage);
    //valid
    Matrix2D<bool>valid(inputMask);

    //build ~valid matrix
    Matrix2D<bool>negated_valid(valid.getRows(), valid.getCols());
    negated_valid.negateMatrixMask(valid);
    //replace 0 with NaN in im
    im.insertNaNValues(negated_valid);

    Matrix2D<double>log_im(im.getRows(), im.getCols());
    log_im.logNatMatrix(im);

    //set some fields of the "data" structure. This class keeps copies of the original data stored on matrixes im, valid and log_im, in case some get modified.
    data.getDataTrue().setIm(im);
    data.getDataTrue().setLogIm(log_im);
    data.getDataTrue().setMask(valid);
    data.setValid(valid);
    cout<<"Time taken for building data class: "<<(double)(clock() - build_data)/CLOCKS_PER_SEC<<endl<<endl;

    cout<<"[SIRfS] Applying median filter"<<endl;
    //the output matrices are written at the address given as input
    clock_t clock_median_filter = clock();
    medianFilterMatMask(negated_valid,  params.getZMedianHalfwidth(), data.getZMedianFilterMatAddress());
    medianFilterMatMask(negated_valid,  params.getAMedianHalfwidth(), data.getAMedianFilterMatAddress());

    //compute transposes for the above matrices. Since they store they KeysValue they might not be necessary, as the original can be used, but keep them till determining their usefulness
    data.getZMedianFilterMat()->getTranspose(data.getZMedianFilterMatTAddress());
    data.getAMedianFilterMat()->getTranspose(data.getAMedianFilterMatTAddress());
    cout<<"Time taken for median filter: "<<(double)(clock() - clock_median_filter)/CLOCKS_PER_SEC<<endl;

#ifdef TEST_BLOCK_A2
    //first 2 values represent indexes and need to be incremented by 1 as MATLAB indexing is 1-based
    cout<<"Test ZMedianFilterMatMask: "<<test_matrix2D("block_A2/ZM.txt", *data.getZMedianFilterMat(), Double)<<endl;
    cout<<"Test AMedianFilterMatMask: "<<test_matrix2D("block_A2/AM.txt", *data.getAMedianFilterMat(), Double)<<endl;
#endif

    cout<<"[SIRfS] Building border normals"<<endl;
    clock_t clock_border_normals = clock();
    getBorderNormals(data.getDataTrue().getMask(), data.getBorder());
    cout<<"Time taken for  border normals: "<<(double)(clock() - clock_border_normals)/CLOCKS_PER_SEC<<endl<<endl;

#ifdef TEST_BLOCK_A2
    cout<<"Test Border.idx: "<<test_vectors("block_A2/IdxM.txt", data.getBorder().getIdx(), Double)<<endl;
    cout<<"Test Border.position: "<<test_matrix2D("block_A2/PositionM.txt", data.getBorder().getPosition(), Double)<<endl;
    cout<<"Test Border.normal: "<<test_matrix2D("block_A2/NormalM.txt", data.getBorder().getNormal(), Double)<<endl;
    cout<<"Test Border.tangent: "<<test_matrix2D("block_A2/TangentM.txt", data.getBorder().getTangent(), Double)<<endl;

#endif

    data.setPrior(prior);
    cout<<"[SIRfS] Finished setting 'data' class"<<endl;

    cout<<"Time taken "<<(double)(clock() - tStart)/CLOCKS_PER_SEC;
    return 0;
}
