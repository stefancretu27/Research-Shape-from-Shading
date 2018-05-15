#ifndef PARAMS_H_INCLUDED
#define PARAMS_H_INCLUDED

#include <string>
#include <vector>
#include "params/height_data.h"
#include "params/light_data.h"
#include "params/reflectance_data.h"

class Parameters
{
    private:
        int z_median_halfwidth, a_median_halfwidth, n_eval_skip, lbfgs_ncorr, n_iters_optimize;
        float max_pyr_depth, f_streak, f_percent, max_n_eval;
        double z_smooth_epsilon, a_smooth_epsilon, prog_tool, opt_tool;
        bool solve_light, solve_shape, natural_illumination, use_color_images, whiten_light, use_init_z, resize_input, dump_final, shape_from_shading, use_numerical;
        std::string output_file, prior_model_string, dump_output, pyr_edges, *global_vars, eval_string;
        HeightData hd;
        LightData ld;
        ReflectanceData rd;
    public:
        float *pyr_filter;

    public:
        //constructor: initializes data members. Replaces CONSTANTS file in Matlab code
        Parameters();
        ~Parameters(){delete [] pyr_filter;};
        //set parameters: replace PARAMETERS file in Matlab code
        bool setParameters();
        void setEvalString(std::string new_eval_string);
        //getters
        int getZMedianHalfwidth(){return this->z_median_halfwidth;};
        int getAMedianHalfwidth(){return this->a_median_halfwidth;};
        int getNEvalSkip(){return n_eval_skip;};
        float getMaxPyrDepth(){return max_pyr_depth;};
        int getLbfgsNcorr(){return lbfgs_ncorr;};
        int getNItersOptimize(){return n_iters_optimize;};
        float getFStreak(){return f_streak;};
        float getFPercent(){return f_percent;};
        float getMaxNEval(){return max_n_eval;};
        std::string getOuputFile(){return output_file;};
        std::string getPriorModelString(){return prior_model_string;};
        std::string getDumpOuput(){return dump_output;};
        std::string getPyrEdges(){return pyr_edges;};
        std::string getGlobalVars(unsigned int index){return global_vars[index];};
        std::string getEvalString(){return eval_string;};
        bool getSolveLight(){return solve_light;};
        bool getSolveShape(){return solve_shape;};
        bool getNaturalIllumination(){return natural_illumination;};
        bool getUseColorImages(){return use_color_images;};
        bool getWhitenLight(){return whiten_light;};
        bool getUseInitZ(){return use_init_z;};
        bool getResizeInput(){return resize_input;};
        bool getDumpFinal(){return dump_final;};
        bool getShapeFromShading(){return shape_from_shading;};
        bool getUseNumerical(){return use_numerical;};
        HeightData getHeightData(){ return hd;};
        ReflectanceData getReflectanceData(){return rd;};
        LightData getLightData(){return ld;};
};

#endif // PARAMS_H_INCLUDED
