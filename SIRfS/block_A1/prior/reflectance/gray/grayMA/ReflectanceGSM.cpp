//#include "../../../height/MKZ/GSM.h"
#include "ReflectanceGSM.h"

void ReflectanceGSM::initializeGSMReflectanceGrayData(StructNode& gray_ma_gsm_metadata)
{
    //create a StructNode instance for 5th level fields
    vector<StructNode*> nodes5 = gray_ma_gsm_metadata.getChildrenNodes();

    for(int v = 0; v <  nodes5.size(); v++)
    {
        if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
        {
             this->mu = *(int*)nodes5[v]->getStructureP()->data;
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "sigs") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->sigs.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/gray/grayMA/sigs21.txt",  this->sigs, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "pis") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->pis.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/gray/grayMA/pis_exp16.txt", this->pis, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "lut") == 0)
        {
            this->lutObj.initializeLutData(*nodes5[v]);

#ifdef TEST_PRIOR_REFLECTANCE
            bool result;

            result = (fabs(this->getLut().getBin_range().getLow() + 3.9254) < 0.0001) && (fabs(this->getLut().getBin_range().getHigh() - 3.9254) < 0.0001);
            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->bin_range: "<<result<<endl;

            result = fabs(this->getLut().getBin_width() - 3.9256e-04) < pow(10, -8);
            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->bin_width: "<<result<<endl;

            result = this->getLut().getN_bins() == 20000;
            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->n_bins: "<<result<<endl;

            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->F_LL  "<<\
                    test_vectors("block_A1/prior/reflectance/gray/grayMA/GSM/F_LL15.txt", this->getLut().getF_LL(), Double)<<endl;

            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->F_cost: "<<\
                    test_vectors("block_A1/prior/reflectance/gray/grayMA/GSM/F_cost15.txt", this->getLut().getF_cost(), Double)<<endl;

            cout<<"Test for reading priors on reflectance: "<<gray_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"->N_train:  "<<\
                        test_vectors("block_A1/prior/reflectance/gray/grayMA/GSM/N_train.txt", this->getLut().getN_train(), Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
    }
}
