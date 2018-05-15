#ifndef COLORLABORATORY_H_INCLUDED
#define COLORLABORATORY_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"
//#include "../../../../helpers/prior_struct_node.h"

class ColorLaboratory
{
private:
    ColorGaussian gaussian;
    ColorWhitenParams whiten_params;

public:
    //constructors
    ColorLaboratory(){};
    ColorLaboratory(const ColorLaboratory &input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
    };

    //operators overloading
    ColorLaboratory& operator=(const ColorLaboratory& input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
        return *this;
    };

    //getters
    inline ColorGaussian& getColorGaussian(){return this->gaussian;};
    inline ColorWhitenParams& getColorWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeColorLaboratoryData(StructNode& color_lab_metadata)
    {
        //create a node instance for each inner fields, that are gaussian and whiten params, which are inner fields of color and laboratory
        vector<StructNode*> nodes4 = color_lab_metadata.getChildrenNodes();

        for(unsigned int iv = 0; iv <  nodes4.size(); iv++)
        {
            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
            {
                //initialize whiten parameters
                this->whiten_params.initializeColorWhitenParamsData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mean "<<\
                        test_vectors("block_A1/prior/lights/color/laboratory/whiten_params/mean_exp16.txt", this->whiten_params.getMean(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mapp "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/mapp20.txt", this->whiten_params.getMapp(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->inverse "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/inverse_exp16.txt", this->whiten_params.getInverse(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->C "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/C_exp16.txt", this->whiten_params.getC(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iC "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/iC_exp16.txt", this->whiten_params.getiC(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->D "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/D20.txt", this->whiten_params.getD(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iD "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/iD16.txt", this->whiten_params.getiD(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->V "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/whiten_params/V_exp16.txt", this->whiten_params.getV(), Double)<<endl;
#endif // TEST_PRIOR_LIGHT
            }
            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
            {
                //initialize gaussian
                this->gaussian.initializeColorGaussianData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mu "<<\
                        test_vectors("block_A1/prior/lights/color/laboratory/gaussian/mu_exp17.txt", this->gaussian.getMu(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->Sigma "<<\
                        test_matrix2D("block_A1/prior/lights/color/laboratory/gaussian/Sigma_exp17.txt", this->gaussian.getSigma(), Double)<<endl<<endl;
#endif // TEST_PRIOR_LIGHT
            }
        }
    }
};

#endif // COLORLABORATORY_H_INCLUDED
