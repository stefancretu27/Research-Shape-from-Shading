#ifndef COLORNATURAL_H_INCLUDED
#define COLORNATURAL_H_INCLUDED

#include "gaussian.h"
#include "whitenParams.h"
#include "../../../prior_struct_node.h"

class ColorNatural
{
private:
    ColorGaussian gaussian;
    ColorWhitenParams whiten_params;

public:
    //constructors
    ColorNatural(){};
    ColorNatural(const ColorNatural &input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
    };

    //operators overloading
    ColorNatural& operator=(const ColorNatural& input)
    {
        this->gaussian = input.gaussian;
        this->whiten_params = input.whiten_params;
        return *this;
    };

    //getters
    inline ColorGaussian& getColorGaussian(){return this->gaussian;};
    inline ColorWhitenParams& getColorWhitenParams(){return this->whiten_params;};

    //initialize data
    void initializeColorNaturalData(StructNode& color_nat_metadata)
    {
        //create a node instance for each inner fields, that are gaussian and whiten params, which are inner fields of color and laboratory
        vector<StructNode*> nodes4 = color_nat_metadata.getChildrenNodes();

        for(int iv = 0; iv < nodes4.size(); iv++)
        {
            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
            {
                //initialize whiten parameters
                this->whiten_params.initializeColorWhitenParamsData(*nodes4[iv]);
#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mean "<<\
                        test_vectors("block_A1/prior/lights/color/natural/whiten_params/mean20.txt", &this->whiten_params.getMean(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->mapp "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/mapp20.txt", this->whiten_params.getMapp(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->inverse "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/inverse21.txt", this->whiten_params.getInverse(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->C "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/C21.txt", this->whiten_params.getC(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iC "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/iC15.txt", this->whiten_params.getiC(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->D "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/D20.txt", this->whiten_params.getD(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->iD "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/iD16.txt", this->whiten_params.getiD(), Double)<<endl;

            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->V "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/whiten_params/V19.txt", this->whiten_params.getV(), Double)<<endl;
#endif // TEST_PRIOR_LIGHT
            }
            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
            {
                //initialize gaussian
                this->gaussian.initializeColorGaussianData(*nodes4[iv]);

#ifdef TEST_PRIOR_LIGHT
            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"-> mu "<<\
                        test_vectors("block_A1/prior/lights/color/natural/gaussian/mu20.txt", &this->gaussian.getMu(), Double)<<endl;
            cout<<"Test reading priors on lights->color->"<<color_nat_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->Sigma "<<\
                        test_matrix2D("block_A1/prior/lights/color/natural/gaussian/sigma20.txt", this->gaussian.getSigma(), Double)<<endl<<endl;
#endif // TEST_PRIOR_LIGHT
            }
        }
    }
};

#endif // COLORNATURAL_H_INCLUDED
