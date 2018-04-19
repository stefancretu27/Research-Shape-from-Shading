#ifndef GRAYLABORATORY_H_INCLUDED
#define GRAYLABORATORY_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"
#include "../../../prior_struct_node.h"

class GrayLaboratory
{
private:
    GrayGaussian gaussian;
    GrayWhitenParams whiten_params;

public:
    //constructors
    GrayLaboratory(){};
#ifdef U_PTR_CONTAINER
    GrayLaboratory(GrayLaboratory &input)
#else
    GrayLaboratory(const GrayLaboratory &input)
#endif
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
    };

    //operators overloading
#ifdef U_PTR_CONTAINER
    GrayLaboratory& operator=(GrayLaboratory& input)
#else
    GrayLaboratory& operator=(const GrayLaboratory& input)
#endif
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
        return *this;
    };

    //getters
    inline GrayGaussian& getGrayGaussian(){return this->gaussian;};
    inline GrayWhitenParams& getGrayWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeGrayLaboratoryData(StructNode& gray_lab_metadata)
    {
        //create a node instance for each inner fields, that are gaussian and whiten params, which are inner fields of color and laboratory
        vector<StructNode*> nodes4 = gray_lab_metadata.getChildrenNodes();

        for(int iv = 0; iv < nodes4.size(); iv++)
        {
            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
            {
                //initialize whiten parameters
                this->whiten_params.initializeGrayWhitenParamsData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mean "<<\
                        test_vectors("block_A1/prior/lights/gray/laboratory/whiten_params/mean_exp16.txt", this->whiten_params.getMean(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mapp "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/map_exp16.txt", this->whiten_params.getMapp(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->inverse "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/inverse_exp16.txt", this->whiten_params.getInverse(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->C "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/C_exp16.txt", this->whiten_params.getC(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iC "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/iC_exp16.txt", this->whiten_params.getiC(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->D "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/D18.txt", this->whiten_params.getD(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iD "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/iD_exp16.txt", this->whiten_params.getiD(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->V "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/whiten_params/V_exp16.txt", this->whiten_params.getV(), Double)<<endl;
#endif // TEST_PRIOR_LIGHT
            }
            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
            {
                //initialize gaussian
                this->gaussian.initializeGrayGaussianData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"-> mu "<<\
                        test_vectors("block_A1/prior/lights/gray/laboratory/gaussian/mu_exp16.txt", this->gaussian.getMu(), Double)<<endl;
            cout<<"Test reading priors on lights->gray->"<<gray_lab_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->Sigma "<<\
                        test_matrix2D("block_A1/prior/lights/gray/laboratory/gaussian/sigma_exp16.txt", this->gaussian.getSigma(), Double)<<endl<<endl;
#endif // TEST_PRIOR_LIGHT
            }
        }
    }
};

#endif // GRAYLABORATORY_H_INCLUDED
