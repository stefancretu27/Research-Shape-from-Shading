#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iomanip>
#include "limits"

#include "params.h"
#include "prior.h"
#include "data.h"
#include "SIRfS_Functions.h"

using namespace std;

int main()
{
    //allocate memory for input image
    Matrix2D<double> grayImage(250, 200);

    //read the image data from file. It was read, grayscaled in Matlab and its values outputed to the file used below.
    DataFile<double> dFileReader;
    dFileReader.readMatrix2D("input_image.txt", grayImage, 250, 200, 17);

    //create mask for the input image
    Matrix2D<bool> inputMask(250, 200);
    computeMatrixMask(grayImage, inputMask, 0);
    //cout<<inputMask.getMatrixValue(74,23)<<endl;

    //Initialize SIRfS parameters. Replaces CONSTANTS file from Matlab.
    Parameters params;
    params.setEvalString(" ");
    //set SIRfS parameters. This replaces PARAMETERS file from Matlab.
    if(!params.setParameters())
    {
        cout<<"SIRfS parameters could not be set. The program will exit."<<endl;
        exit(0);
    }

    //load priors on height, light and reflectance: Z, L and R
    //Prior priorObject;
    //priorObject.initializePriorData();

    //test prior data structures
    //cout<<scientific;
    //cout<<setprecision(31)<<fixed<<priorObject.getHeight().getMKZ().getGsm().getLut().getF_LL()[2]<<endl;
    //cout<<setprecision(16)<<fixed<<priorObject.getLights().getLightsColor().getColorNatural().getColorGaussian().getSigma()(1,5)<<endl;
    //cout<<setprecision(16)<<fixed<<priorObject.getLights().getLightsGray().getGrayNatural().getGrayWhitenParams().getC()(3,5)<<endl;
    //cout<<setprecision(15)<<fixed<<priorObject.getReflectance().getReflectanceGray().getGrayMA().getGsm().getLut().getF_cost()[3]<<endl;
    //cout<<setprecision(16)<<fixed<<priorObject.getReflectance().getReflectanceColor().getMA().getGsm_mvn().getSigma_R()(1,2)<<endl;
    //cout<<setprecision(16)<<fixed<<priorObject.getReflectance().getReflectanceColor().getAw_hist()(2,1, 1)<<endl;

    //data.true.im
    Data data;
    data.getDataTrue().getInputImage() = grayImage;

    //im
    Matrix2D<double> im(grayImage);
    //valid
    Matrix2D<bool>valid(inputMask);

    //construct ~valid
    Matrix2D<bool>negated_valid(valid.getRows(), valid.getCols());
    negated_valid.negateMatrixMask(valid);
    //insert replace 0 with NaN in im
    insertNaNValues(im, negated_valid);
    //cout<<setprecision(15)<<fixed<<im.getMatrixValue(74,23)<<endl;

    Matrix2D<double>log_im(im.getRows(), im.getCols());
    log_im.logNatMatrix(im);
   //cout<<setprecision(15)<<fixed<<log_im.getMatrixValue(74,23)<<endl;

    data.getDataTrue().getIm() = im;
    data.getDataTrue().getLogIm() = log_im;
    //cout<<setprecision(15)<<fixed<<data.getDataTrue().getLogIm().getMatrixValue(74,23)<<endl;
    data.getValid() = valid;
    data.getDataTrue().getMask() = valid;
    //cout<<setprecision(15)<<fixed<<data.getDataTrue().getMask().getMatrixValue(74,23)<<endl;

    medianFilterMatMask(negated_valid,  params.getZMedianHalfwidth(), data.getZMedianFilterMatrix());
    //medianFilterMatMask(negated_valid,  params.getAMedianHalfwidth(), data.getAMedianFilterMatrix());

    return 0;
}
