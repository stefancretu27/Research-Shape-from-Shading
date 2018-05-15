#include "gray.h"

using namespace std;

void ReflectanceGray::initializeReflectanceGrayData(StructNode& gray_metadata)
{
    vector<StructNode*> nodes3 = gray_metadata.getChildrenNodes();

    for(unsigned int iii = 0; iii <  nodes3.size(); iii++)
    {
        if(strcmp(nodes3[iii]->getStructureP()->name, "A_train") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes3[iii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->A_train.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<gray_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/A_train15.txt", this->A_train, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "A_range") == 0)
        {
            //set directly the data observed in Matlab
             this->A_range.setLow(4);
             this->A_range.setHigh(-7);
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "A_spline") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes3[iii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->A_spline.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<gray_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/A_spline15.txt", this->A_spline, Double)<<endl<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "MA") == 0)
        {
            this->MA.initializeGrayMAdata(*nodes3[iii]);
        }
    }
}
