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

//#define CREATE_TEST_FILES 1

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
    Parameters params;
    params.setEvalString(" ");
    //set SIRfS parameters. This method replaces PARAMETERS file from Matlab.
    if(!params.setParameters())
    {
        cout<<"[SIRfS]  SIRfS parameters could not be set. The program will exit."<<endl;
        exit(0);
    }

    //load priors on height, light and reflectance: Z, L and R
    cout<<"[SIRfS] Parameters initialized. Loading priors on height, light and reflectance"<<endl;
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

    //test prior data structures
    //cout<<setprecision(21)<<fixed<<prior.getHeight().getMKZ().getMKZ_train()[0]<<endl;
    //cout<<setprecision(15)<<fixed<<prior.getHeight().getMKZ().getGsm().getLut().getF_LL()[2]<<endl;
    //cout<<setprecision(16)<<fixed<<prior.getLights().getLightsColor().getColorNatural().getColorGaussian().getSigma()(1,5)<<endl;
    //cout<<setprecision(16)<<fixed<<prior.getLights().getLightsGray().getGrayNatural().getGrayWhitenParams().getC()(3,5)<<endl;
    //cout<<setprecision(15)<<fixed<<prior.getReflectance().getReflectanceGray().getGrayMA().getGsm().getLut().getF_cost()[3]<<endl;
    //cout<<setprecision(16)<<fixed<<prior.getReflectance().getReflectanceColor().getMA().getGsm_mvn().getSigma_R()(1,2)<<endl;
    //cout<<setprecision(16)<<fixed<<prior.getReflectance().getReflectanceColor().getAw_hist()(2,1, 1)<<endl;

    cout<<"[SIRfS] Priors loaded. Building 'data' class"<<endl;
    //data.true.im
    Data data;
    data.getDataTrue().setInputImage(grayImage);

    //im
    Matrix2D<double> im(grayImage);
    //valid
    Matrix2D<bool>valid(inputMask);

    //build ~valid matrix
    Matrix2D<bool>negated_valid(valid.getRows(), valid.getCols());
    valid.negateMatrixMask(negated_valid);
    //replace 0 with NaN in im
    im.insertNaNValues(negated_valid);

    Matrix2D<double>log_im(im.getRows(), im.getCols());
    log_im.logNatMatrix(im);

    //set some fields of the "data" structure. This class keeps copies of the original data stored on matrixes im, valid and log_im, in case some get modified.
    data.getDataTrue().setIm(im);
    data.getDataTrue().setLogIm(log_im);
    data.getDataTrue().setMask(valid);
    data.setValid(valid);

    cout<<"[SIRfS] Applying median filter"<<endl;
    //the output matrices are written at the address given as input
    medianFilterMatMask(negated_valid,  params.getZMedianHalfwidth(), data.getZMedianFilterMatAddress());
#ifdef CREATE_TEST_FILES
    DataFile<double> dfd;
    dfd.writeKeysValueMatrix2D("validation_files/ZMedianFilterMat.txt", data.getZMedianFilterMatAddress(), 1);
#endif
    //cout<<data.getZMedianFilterMat()->getRows()<<" "<<data.getZMedianFilterMat()->getCols()<<" "<<endl;
    //printing all 3 in the same line (command) blocks the system. Above and below are alternative that seem to work.
    //cout<<data.getZMedianFilterMat()->getMatrixValue(123456, 0).getKeyX()<<" "<<data.getZMedianFilterMat()->getMatrixValue(123456, 0).getKeyY()<<endl;
    //cout<<data.getZMedianFilterMat()->getMatrixValue(123456, 0).getValue()<<endl;
    //cout<<data.getZMedianFilterMat()->getMatrixValue(0, 0).getKeyX()<<" "<<data.getZMedianFilterMat()->getMatrixValue(0, 0).getKeyY()<<endl;
    //cout<<data.getZMedianFilterMat()->getMatrixValue(0, 1).getKeyX()<<" "<<data.getZMedianFilterMat()->getMatrixValue(0, 1).getKeyY()<<endl;
    //cout<<data.getZMedianFilterMat()->getMatrixValue(0, 0).getValue()<<" "<<data.getZMedianFilterMat()->getMatrixValue(0, 1).getValue()<<endl;

    medianFilterMatMask(negated_valid,  params.getAMedianHalfwidth(), data.getAMedianFilterMatAddress());
#ifdef CREATE_TEST_FILES
    dfd.writeKeysValueMatrix2D("validation_files/AMedianFilterMat.txt", data.getAMedianFilterMatAddress(), 1);
#endif

    //compute transposes for the above matrices. Since they store they KeysValue they might not be necessary, as the original can be used, but keep them till determining their usefulness
    data.getZMedianFilterMat()->getTranspose(data.getZMedianFilterMatTAddress());
    data.getAMedianFilterMat()->getTranspose(data.getAMedianFilterMatTAddress());

    cout<<"[SIRfS] Building border normals"<<endl;
    getBorderNormals(data.getDataTrue().getMask(), data.getBorder());

#ifdef CREATE_TEST_FILES
    dfd.writeVector("validation_files/dataBorderIdx.txt", data.getBorder().getIdx(), 0, 1);
    dfd.writeMatrix2D("validation_files/dataBorderNormal.txt", data.getBorder().getNormal(), 15, 0);
    dfd.writeMatrix2D("validation_files/dataBorderTangent.txt", data.getBorder().getTangent(), 15, 0);
    dfd.writeMatrix2D("validation_files/dataBorderPosition.txt", data.getBorder().getPosition(), 0, 1);
#endif // CREATE_TEST_FILES

    data.setPrior(prior);
    cout<<"[SIRfS] Finished setting 'data' class"<<endl;

    cout<<"Time taken "<<(double)(clock() - tStart)/CLOCKS_PER_SEC;

    return 0;
}
