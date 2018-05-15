#include "gaussian.h"
//#include "../../../../templates/matrix2D.cpp"

using namespace std;

void GrayGaussian::initializeGrayGaussianData(StructNode& gray_g_metadata)
{
    //create a node instance for each inner field and store it in a vector
    vector<StructNode*> nodes5 = gray_g_metadata.getChildrenNodes();

    for(int v = 0; v <  nodes5.size(); v++)
    {
        if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->mu.assign(raw_data, raw_data + dim);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
        {
             this->Sigma.setMatrix2D((double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }
    };
}
