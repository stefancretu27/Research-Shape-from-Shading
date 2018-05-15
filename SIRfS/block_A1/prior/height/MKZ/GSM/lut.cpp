#include "lut.h"

using namespace std;

void Lut::initializeLutData(StructNode& lut_metadata)
{
    //create a node instance for each inner field and store it in a vector
    vector<StructNode*> nodes5 = lut_metadata.getChildrenNodes();

    for(unsigned int v = 0; v < nodes5.size(); v++)
    {
        if(strcmp(nodes5[v]->getStructureP()->name, "bin_range") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //use pointer to the first and the last element in the array as iterators
            this->bin_range.setLow(raw_data[0]);
            this->bin_range.setHigh(raw_data[1]);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "bin_width") == 0)
        {
            this->bin_width = *(double*)nodes5[v]->getStructureP()->data;
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "n_bins") == 0)
        {
            this->n_bins= *(double*)nodes5[v]->getStructureP()->data;
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "F_LL") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->F_LL.assign(raw_data, raw_data + dim);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "F_cost") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->F_cost.assign(raw_data, raw_data + dim);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "N_train") == 0)
        {
            //get pointer to raw data from .mat file
            unsigned int *raw_data = (unsigned int*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->N_train.assign(raw_data, raw_data + dim);
        }
    }
}
