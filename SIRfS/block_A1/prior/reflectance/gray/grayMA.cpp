#include "grayMA.h"

using namespace std;

void GrayMA::initializeGrayMAdata(StructNode& gray_ma_metadata)
{
    //create a StructNode instance for 4th level fields, that is GSM for gray.MA and GSM_mvn for color.MA + a matrix for gray.MA
    vector<StructNode*> nodes4 = gray_ma_metadata.getChildrenNodes();

    for(int iv = 0; iv <  nodes4.size(); iv++)
    {
        if(strcmp(nodes4[iv]->getStructureP()->name, "MA_train") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes4[iv]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes4[iv]->getStructureP()->dims[0] * nodes4[iv]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->MA_train.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<gray_ma_metadata.getStructureP()->name<<"->"<<nodes4[iv]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/gray/MA_train20.txt", this->MA_train, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes4[iv]->getStructureP()->name, "GSM") == 0)
        {
            this->gsm.initializeGSMReflectanceGrayData(*nodes4[iv]);
        }
    }
}
