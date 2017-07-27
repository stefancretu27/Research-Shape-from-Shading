#include <math.h>
#include <iostream>
#include <string>
#include "limits"

#include "params.h"

using namespace std;

Parameters::Parameters()
{
    z_median_halfwidth = 2;
    a_median_halfwidth = 2;

    a_smooth_epsilon = pow( (double)10, (double)-4);
    z_smooth_epsilon = pow( (double)10, (double)-4);

    output_file = string();

    solve_light = true;
    solve_shape = true;

    use_color_images = false;
    //false if the above is false
    natural_illumination = false;

    whiten_light = true;
    //set to maximum value that can be stored in a float memory location
    max_pyr_depth = numeric_limits<float>::max();

    use_init_z = false;
    resize_input = true;

    prior_model_string = string("prior.mat");
    dump_output = string();
    dump_final = false;

    use_numerical = false;

    lbfgs_ncorr = 10;
    n_iters_optimize = 2000;
    f_streak = 5;
    f_percent = 0.005;
    prog_tool = pow((double)10, (double)-9);
    opt_tool = pow((double)10, (double)-5);

    //set to maximum value that can be stored in a float memory location
    max_n_eval = numeric_limits<float>::max();
    n_eval_skip = 0;

    shape_from_shading = false;

    //not sure if needed
   /* global_vars = {"Z_last_global", "Ls_white_global", "global_Ls_dependency", "global_Ls_weights", "global_in_line_search", "global_L_active_idx", "global_greedy_head", \
    "global_loss_best", "global_P", "global_light_fid", "last_display", "num_display", "display_figure", "global_Z_last", "global_L_best", "global_L", "global_state", "global_errors", \
    "num_display", "last_Zprior", "global_losses", "global_losses_history"};*/

    pyr_edges = "repeat";
    pyr_filter = new float[4];
    pyr_filter[0] = 1/sqrt((float) 8);
    pyr_filter[1] = 3/sqrt((float) 8);
    pyr_filter[2] = 3/sqrt((float) 8);
    pyr_filter[3] = 1/sqrt((float) 8);
}

//set parameters for SIRfS. The Matlab PARAMETERS files also contains settings for SFS parameters, which are not converted here.
//Also, for SIRfS, the Matlab code contains firther settings which are not present here, as they are not necessary for executing the code on a color/graysclae image.
bool Parameters::setParameters()
{
    //set parameters only for SIRfS
    if(!this->getShapeFromShading())
    {
        if( (this->getNaturalIllumination() == 0) && (this->getUseColorImages() == 0) )
        {
            this->getHeightData().setContourMult(3.3636);
            this->getHeightData().setContourPower(0.75);
            this->getHeightData().setSmooth(6.7272);
            this->getHeightData().setInit(8);
            this->getHeightData().setInitPower(1.1892);
            this->getHeightData().setSlant(2.3784);

            this->getReflectanceData().setEntropy(1.4142);
            this->getReflectanceData().setEntropySigma(1.6818);
            this->getReflectanceData().setHist(4);
            this->getReflectanceData().setSmooth(6.7272 );

            this->getLightData().setGaussian(4.7568);
        }
        else if( (this->getNaturalIllumination() == 0) && (this->getUseColorImages() == 1) )
        {
            this->getHeightData().setContourMult(4);
            this->getHeightData().setContourPower(0.75);
            this->getHeightData().setSmooth(6.7272);
            this->getHeightData().setInit(6.7272);
            this->getHeightData().setInitPower(1.4142);
            this->getHeightData().setSlant(2.3784);

            this->getReflectanceData().setEntropy(3.3636);
            this->getReflectanceData().setEntropySigma(1.6818);
            this->getReflectanceData().setHist(4.7568);
            this->getReflectanceData().setSmooth(13.4543 );

            this->getLightData().setGaussian(4.7568);
        }
        else if( (this->getNaturalIllumination() == 1) && (this->getUseColorImages() == 1) )
        {
            this->getHeightData().setContourMult(2.8284 );
            this->getHeightData().setContourPower(0.75);
            this->getHeightData().setSmooth(4.7568);
            this->getHeightData().setInit(2);
            this->getHeightData().setInitPower(0.8409 );
            this->getHeightData().setSlant(1);

            this->getReflectanceData().setEntropy(3.3636);
            this->getReflectanceData().setEntropySigma(2.8284);
            this->getReflectanceData().setHist(4.7568);
            this->getReflectanceData().setSmooth(16 );

            this->getLightData().setGaussian(3.3636 );
        }
        else
            return false;
    }
    return true;
}

void Parameters::setEvalString(string new_eval_string)
{
    this->eval_string = new_eval_string;
}
