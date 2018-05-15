#include "GSM.h"
#include <fstream>
#include <iomanip>

using namespace std;

void GSM::initializeGSMHeightData(StructNode& GSMHeight_metadata)
{
     //create a node instance for each inner field and store it in a vector
    vector<StructNode*> nodes4 = GSMHeight_metadata.getChildrenNodes();

    for(unsigned int iv = 0; iv <  nodes4.size(); iv++)
    {
         if(strcmp(nodes4[iv]->getStructureP()->name, "mu") == 0)
         {
             this->mu = *(double*)nodes4[iv]->getStructureP()->data;

#ifdef TEST_PRIOR_HEIGHT
            bool result = fabs(this->mu - 0) < 0.000001;
            cout<<"Test for reading  priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<\
                        nodes4[iv]->getStructureP()->name<<"  "<<result<<endl;
#endif // TEST_PRIOR_HEIGHT
         }

        if(strcmp(nodes4[iv]->getStructureP()->name, "sigs") == 0)
         {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes4[iv]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes4[iv]->getStructureP()->dims[0] * nodes4[iv]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->sigs.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_HEIGHT
            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/height/MKZ/sigs21.txt", this->sigs, Double)<<endl;
#endif // TEST_PRIOR_HEIGHT
         }

        if(strcmp(nodes4[iv]->getStructureP()->name, "pis") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes4[iv]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes4[iv]->getStructureP()->dims[0] * nodes4[iv]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->pis.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_HEIGHT
            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/height/MKZ/pis31.txt", this->pis, Double)<<endl;
#endif // TEST_PRIOR_HEIGHT
         }

         //get data for lut structure
         if(strcmp(nodes4[iv]->getStructureP()->name, "lut") == 0)
         {
             this->lutObj.initializeLutData(*nodes4[iv]);

#ifdef TEST_PRIOR_HEIGHT
            bool result;

            result = (fabs(this->getLut().getBin_range().getLow() + 2.193261791481005) < 0.000001) && (fabs(this->getLut().getBin_range().getHigh() - 2.193261791481005) < 0.000001);
            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->bin_range: "<<result<<endl;

            result = fabs(this->getLut().getBin_width() - 2.193371460054008e-04) < pow(10, -15);
            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->bin_width: "<<result<<endl;

            result = this->getLut().getN_bins() == 20000;
            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->n_bins: "<<result<<endl;

            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->F_LL  "<<\
                    test_vectors("block_A1/prior/height/MKZ/GSM/F_LL15.txt", this->getLut().getF_LL(), Double)<<endl;

            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->F_cost: "<<\
                    test_vectors("block_A1/prior/height/MKZ/GSM/F_cost15.txt", this->getLut().getF_cost(), Double)<<endl;

            cout<<"Test for reading priors on height: "<<GSMHeight_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"->N_train: "<<\
                    test_vectors("block_A1/prior/height/MKZ/GSM/N_train.txt", this->getLut().getN_train(), Int)<<endl;
#endif // TEST_PRIOR_HEIGHT
         }
    }
}
