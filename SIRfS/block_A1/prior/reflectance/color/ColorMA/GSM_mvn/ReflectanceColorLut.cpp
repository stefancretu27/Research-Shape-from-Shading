#include "ReflectanceColorLut.h"

void ReflectanceColorLut::initializeLutReflectanceColorData(StructNode& color_ma_gsm_lut_metadata)
{
    //create a StructNode instance for 5th level fields
    vector<StructNode*> nodes6 = color_ma_gsm_lut_metadata.getChildrenNodes();

    for(unsigned int vi = 0; vi < nodes6.size(); vi++)
    {
        if(strcmp(nodes6[vi]->getStructureP()->name, "bin_range") == 0)
        {
             double *br= (double*)nodes6[vi]->getStructureP()->data;
             this->bin_range.setLow(br[0]);
             this->bin_range.setHigh(br[1]);

#ifdef TEST_PRIOR_REFLECTANCE
            bool result = (fabs(this->bin_range.getHigh() - 3.92954) < pow(10, -5)) &&(fabs(this->bin_range.getLow() - 0.0) < pow(10, -5));
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_lut_metadata.getStructureP()->name<<"->"<<nodes6[vi]->getStructureP()->name<<"  "<<result<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes6[vi]->getStructureP()->name, "bin_width") == 0)
        {
            this->bin_width = *(double*)nodes6[vi]->getStructureP()->data;

#ifdef TEST_PRIOR_REFLECTANCE
            bool result = fabs(this->bin_width - 3.92958e-005) < pow(10, -10);
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_lut_metadata.getStructureP()->name<<"->"<<nodes6[vi]->getStructureP()->name<<"  "<<result<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }

        if(strcmp(nodes6[vi]->getStructureP()->name, "n_bins") == 0)
        {
             this->n_bins = *(double*)nodes6[vi]->getStructureP()->data;
        }

        if(strcmp(nodes6[vi]->getStructureP()->name, "F") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes6[vi]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes6[vi]->getStructureP()->dims[0] * nodes6[vi]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->F.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<color_ma_gsm_lut_metadata.getStructureP()->name<<"->"<<nodes6[vi]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/color/ColorMA/GSM_mvn/F16.txt", this->F, Double)<<endl<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
    }
}
