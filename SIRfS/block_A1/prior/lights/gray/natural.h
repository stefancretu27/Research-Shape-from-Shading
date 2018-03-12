#ifndef NATURAL_H_INCLUDED
#define NATURAL_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"
#include "../../../prior_struct_node.h"

class GrayNatural
{
private:
    GrayGaussian gaussian;
    GrayWhitenParams whiten_params;

public:
    //constructors
    GrayNatural(){};
    GrayNatural(const GrayNatural &input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
    };

    //operators overloading
    GrayNatural& operator=(const GrayNatural& input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
        return *this;
    };

    //getters
    inline GrayGaussian& getGrayGaussian(){return this->gaussian;};
    inline GrayWhitenParams& getGrayWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeGrayNaturalData(StructNode& gray_nat_metadata)
    {
        //create a node instance for each inner fields, that are gaussian and whiten params, which are inner fields of color and laboratory
        vector<StructNode*> nodes4 = gray_nat_metadata.getChildrenNodes();

        for(int iv = 0; iv < nodes4.size(); iv++)
        {
            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
            {
                //initialize whiten parameters
                this->whiten_params.initializeGrayWhitenParamsData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mean "<<\
                        test_vectors("block_A1/prior/lights/gray/natural/whiten_params/mean20.txt", &this->whiten_params.getMean(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mapp "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/map20.txt", this->whiten_params.getMapp(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->inverse "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/inverse20.txt", this->whiten_params.getInverse(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->C "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/C20.txt", this->whiten_params.getC(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iC "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/iC18.txt", this->whiten_params.getiC(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->D "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/D18.txt", this->whiten_params.getD(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iD "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/iD16.txt", this->whiten_params.getiD(), Double)<<endl;

            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->V "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/whiten_params/V20.txt", this->whiten_params.getV(), Double)<<endl;
#endif // TEST_PRIOR_LIGHT
            }
            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
            {
                //initialize gaussian
                this->gaussian.initializeGrayGaussianData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"-> mu "<<\
                        test_vectors("block_A1/prior/lights/gray/natural/gaussian/mu20.txt", &this->gaussian.getMu(), Double)<<endl;
            cout<<"Test reading priors on lights->gray->"<<gray_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->Sigma "<<\
                        test_matrix2D("block_A1/prior/lights/gray/natural/gaussian/sigma20.txt", this->gaussian.getSigma(), Double)<<endl<<endl;
#endif // TEST_PRIOR_LIGHT
            }
        }
    }
};

#endif // NATURAL_H_INCLUDED
