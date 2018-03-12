#include "height.h"

using namespace std;

void Height::initializeHeightData(StructNode& height_metadata)
{
    //create a node instance for each inner field and store it in a vector. These nodes are placed on the 2nd level in the structure's tree
    vector<StructNode*>  nodes2 = height_metadata.getChildrenNodes();

    //iterate thorugh the nodes which are 2 structures(MKZ and Normal) and one vector (NZ_train)
    for(int ii = 0; ii < nodes2.size(); ii++)
    {
        //get the data for the vector
        if(strcmp(nodes2[ii]->getStructureP()->name, "NZ_train") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes2[ii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes2[ii]->getStructureP()->dims[0] * nodes2[ii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->nz_train.assign(raw_data, raw_data + dim);

            //macro defined in validation.h
#ifdef TEST_PRIOR_HEIGHT
            cout<<"Test for reading priors on height: "<<height_metadata.getStructureP()->name<<"->"<<nodes2[ii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/nz_train17.txt", this->nz_train, Double)<<endl;
#endif // TEST_PRIOR_HEIGHT
        }
        //get metadata for the inner structures
        if(strcmp(nodes2[ii]->getStructureP()->name, "normal") == 0)
        {
            this->normal.initializeNormalData(*nodes2[ii]);
        }
        if(strcmp(nodes2[ii]->getStructureP()->name, "MKZ") == 0)
        {
            this->mkz.initilalizeMKZData(*nodes2[ii]);
        }
    }
}
