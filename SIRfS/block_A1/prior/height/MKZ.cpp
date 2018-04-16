#include "MKZ.h"

using namespace std;

void MKZ::initilalizeMKZData(StructNode& MKZ_metadata)
{
    //create a StructNode instance for 3rd level fields
    vector<StructNode*> nodes3 = MKZ_metadata.getChildrenNodes();

    for(int iii = 0; iii <  nodes3.size(); iii++)
    {
        if(strcmp(nodes3[iii]->getStructureP()->name, "MKZ_train") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes3[iii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->MKZ_train.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_HEIGHT
            cout<<"Test for reading priors on height: "<<MKZ_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/height/mkz_train21.txt", this->MKZ_train, Double)<<endl;
#endif // TEST_PRIOR_HEIGHT
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "GSM") == 0)
        {
            this->gsm.initializeGSMHeightData(*nodes3[iii]);
        }
    }
}
