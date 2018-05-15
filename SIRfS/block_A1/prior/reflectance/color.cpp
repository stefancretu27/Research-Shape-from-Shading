#include "color.h"

using namespace std;

void ReflectanceColor::initializeReflectanceColorData(StructNode& color_metadata)
{
    vector<StructNode*> nodes3 = color_metadata.getChildrenNodes();

    for(unsigned int iii = 0; iii <  nodes3.size(); iii++)
    {
        if(strcmp(nodes3[iii]->getStructureP()->name, "A_whiten") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes3[iii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->A_whiten.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<color_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/color/A_whiten16.txt", this->A_whiten, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "Aw_hist") == 0)
        {
             this->Aw_hist.setMatrix3D((double*) nodes3[iii]->getStructureP()->data, nodes3[iii]->getStructureP()->dims[0], nodes3[iii]->getStructureP()->dims[1], nodes3[iii]->getStructureP()->dims[2], true);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_matrix3D("block_A1/prior/reflectance/color/Aw_histM16.txt", this->Aw_hist, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "bin_low") == 0)
        {
            this->bin_low.reserve(nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1]);
            this->bin_low[0] = this->bin_low[1] = this->bin_low[2] = -7;
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "bin_high") == 0)
        {
            this->bin_high.reserve(nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1]);
            this->bin_high[0] = this->bin_high[1] = this->bin_high[2] = 4;
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "A_train") == 0)
        {
             this->A_train.setMatrix2D((double*)nodes3[iii]->getStructureP()->data, nodes3[iii]->getStructureP()->dims[0], nodes3[iii]->getStructureP()->dims[1], true);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_matrix2D("block_A1/prior/reflectance/color/A_train16.txt", this->A_train, Double)<<endl<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "MA") == 0)
        {
            this->ma.initializeColorMAData(*nodes3[iii]);
        }
    }
}
