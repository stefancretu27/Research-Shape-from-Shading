#include "GSM_mvn.h"

void GSM_mvn::initializeGSM_mvnData(StructNode& color_ma_gsm_metadata)
{
    //create a StructNode instance for 5th level fields
    vector<StructNode*> nodes5 = color_ma_gsm_metadata.getChildrenNodes();

    for(int v = 0; v <  nodes5.size(); v++)
    {
        if(strcmp(nodes5[v]->getStructureP()->name, "pis") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->pis.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/color/ColorMA/pis21.txt", this->pis, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
        {
             this->Sigma.setMatrix2D((double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_matrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma16.txt", this->Sigma, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "vars") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->vars.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/color/ColorMA/vars_exp15.txt", this->vars, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_inv") == 0)
        {
             this->Sigma_inv.setMatrix2D((double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_matrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_inv16.txt", this->Sigma_inv, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_R") == 0)
        {
             this->Sigma_R.setMatrix2D((double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
             //this->Sigma_R.Transp();

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_matrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_R16.txt", this->Sigma_R, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "logmults") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->logmults.assign(raw_data, raw_data + dim);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test for reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/reflectance/color/ColorMA/logmults16.txt", this->logmults, Double)<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_whiten") == 0)
        {
             this->Sigma_whiten.setMatrix2D((double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);

#ifdef TEST_PRIOR_REFLECTANCE
            cout<<"Test reading priors on reflectance: "<<color_ma_gsm_metadata.getStructureP()->name<<"->"<<nodes5[v]->getStructureP()->name<<"  "<<\
                        test_matrix2D("block_A1/prior/reflectance/color/ColorMA/Sigma_whiten16.txt", this->Sigma_whiten, Double)<<endl<<endl;
#endif // TEST_PRIOR_REFLECTANCE
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "LL_zero") == 0)
        {
             this->LL_zero = *(double*)nodes5[v]->getStructureP()->data;
        }
        if(strcmp(nodes5[v]->getStructureP()->name, "lut") == 0)
        {
             this->lut.initializeLutReflectanceColorData(*nodes5[v]);
        }
    }
}
