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
    grayImage.compareValuesToTreshold(inputMask, 0, GreaterThan);
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

    //build ~valid matrix
    Matrix2D<bool>negated_valid(valid.getRows(), valid.getCols());
    valid.negateMatrixMask(negated_valid);
    //replace 0 with NaN in im
    im.insertNaNValues(negated_valid);

    Matrix2D<double>log_im(im.getRows(), im.getCols());
    log_im.logNatMatrix(im);

    //set some fields of the "data" structure
    data.getDataTrue().getIm() = im;
    data.getDataTrue().getLogIm() = log_im;
    data.getValid() = valid;
    data.getDataTrue().getMask() = valid;

    //the output matrices are written at the address given as input
    medianFilterMatMask(negated_valid,  params.getZMedianHalfwidth(), data.getZMedianFilterMatAddress());
    //cout<<data.getZMedianFilterMat()->getRows()<<" "<<data.getZMedianFilterMat()->getCols()<<" "<<endl;
    //cout<<data.getZMedianFilterMat()->getMatrixValue(210000,0).getKeyX()<<" "<<data.getZMedianFilterMat()->getMatrixValue(210000,0).getKeyY()<<" "<<data.getZMedianFilterMat()->getMatrixValue(210000,0).getValue()<<endl;
    medianFilterMatMask(negated_valid,  params.getAMedianHalfwidth(), data.getAMedianFilterMatAddress());

    //compute transposes for the above matrices. Since they store they KeysValue they might not be necessary, as the original can be used, but keep them till determining their usefulness
    data.getZMedianFilterMat()->getTranspose(data.getZMedianFilterMatTAddress());
    //cout<<data.getZMedianFilterMatT()->getRows()<<" "<<data.getZMedianFilterMatT()->getCols()<<" "<<endl;
    //cout<<data.getZMedianFilterMatT()->getMatrixValue(0, 210000).getKeyX()<<" "<<data.getZMedianFilterMatT()->getMatrixValue(0, 210000).getKeyY()<<" "<<data.getZMedianFilterMatT()->getMatrixValue(0, 210000).getValue()<<endl;
    data.getAMedianFilterMat()->getTranspose(data.getAMedianFilterMatTAddress());

    getBorderNormals(data.getDataTrue().getMask(), data.getBorder());

    std::sort(data.getBorder().getIdx().begin(), data.getBorder().getIdx().end());
    for(int idx =0; idx < data.getBorder().getIdx().size(); idx++)
        cout<<data.getBorder().getIdx()[idx]<<endl;

    return 0;
}
