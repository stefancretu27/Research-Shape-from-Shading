//c/c++ libraries
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iomanip>
#include <time.h>
#include "limits"
#include "Matlab_include/engine.h"
//own defined headers
#include "block_A1/data_class.h"
#include "block_A1/params.h"
#include "block_A1/prior.h"
#include "block_A2/SIRfS_Functions.h"
#include "helpers/validation.h"

using namespace std;

int main()
{
    Engine *ep;
    int img_rows, img_cols;

    string image_path;
    //get image's path
    cout<<"[SIRfS] Insert the path to the image:"<<endl;
    getline (cin, image_path);

    cout<<"[SIRfS] Insert image height (number of rows):"<<endl;
    cin>>img_rows;
    cout<<"[SIRfS] Insert image width (number of cols):"<<endl;
    cin>>img_cols;
    //allocate memory for input image
    Matrix2D<double> grayImage(img_rows, img_cols);

    //if Matlab engine can be accessed, used it for reading input image
    if ((ep = engOpen("")))
    {
        cout<<"[SIRfS] Reading input image using Matlab engine"<<endl;
        //mxArray that is passed to Matlab engine for storing the values output by imread
        mxArray  *matlab_matrix = NULL;
        //it stores the pointer to  mxArray, that is converted to double, after it is retrieved from Matlab space
        double *d_input_image = NULL;
        //build Matlab command
        const char* cmd = ("input_image = mean(double(imread('" + image_path + "'))/255,3);").c_str();
        //Create a matrix for storing input
        matlab_matrix = mxCreateDoubleMatrix(img_rows, img_cols, mxREAL);

        //Place the variable T into the MATLAB workspace
        engPutVariable(ep, "input_image", matlab_matrix);
        //read the image in grayscale: C:\Users\stefa_000\Documents\GitHubLocalRepos\Research-Shape-from-Shading\SIRfS\images\Peets.png
        engEvalString(ep, cmd);
        //get the values from Matlab engine
        matlab_matrix = engGetVariable(ep, "input_image");
        //get the pointer tot he 1st element
        d_input_image = (double*) mxGetPr(matlab_matrix);

        Matrix2D<double> input_image(img_rows, img_cols);

        for(int x = 0; x < img_rows; x++)
         {
             for(int y = 0; y < img_cols; y++)
             {
                 grayImage.setMatrixValue(x, y, d_input_image[y*img_rows + x]);
             }
         }

        //destroy the mxArray and close Matlab routine
        mxDestroyArray(matlab_matrix);
        engEvalString(ep, "exit");
        engClose(ep);
	}
	else
    {
        cout<<"The MATLAB engine could not be open. Thus, the input image cannot be read. The program will exit"<<endl;
        exit(0);
    }

    clock_t tStart = clock();

    //create mask for the input image
    Matrix2D<bool> inputMask(img_rows, img_cols);
    grayImage.compareValuesToTreshold(inputMask, 0, GreaterThan);

    //Initialize SIRfS parameters. Replaces CONSTANTS file from Matlab.
    cout<<"[SIRfS] Finished reading input. Matlab engine is now closed. Initializing parameters"<<endl;
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
    prior.initializePriorData();

    //test prior data structures
    /*
    cout<<setprecision(21)<<fixed<<prior.getHeight().getMKZ().getMKZ_train()[0]<<endl;
    cout<<setprecision(15)<<fixed<<prior.getHeight().getMKZ().getGsm().getLut().getF_LL()[2]<<endl;
    cout<<setprecision(16)<<fixed<<prior.getLights().getLightsColor().getColorNatural().getColorGaussian().getSigma()(1,5)<<endl;
    cout<<setprecision(16)<<fixed<<prior.getLights().getLightsGray().getGrayNatural().getGrayWhitenParams().getC()(3,5)<<endl;
    cout<<setprecision(15)<<fixed<<prior.getReflectance().getReflectanceGray().getGrayMA().getGsm().getLut().getF_cost()[3]<<endl;
    cout<<setprecision(16)<<fixed<<prior.getReflectance().getReflectanceColor().getMA().getGsm_mvn().getSigma_R()(1,2)<<endl;
    cout<<setprecision(16)<<fixed<<prior.getReflectance().getReflectanceColor().getAw_hist()(2,1, 1)<<endl;
    */

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
