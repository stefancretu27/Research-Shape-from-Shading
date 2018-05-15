#include "whitenParams.h"
//#include "../../../../templates/matrix2D.cpp"

using namespace std;

void ColorWhitenParams::initializeColorWhitenParamsData(StructNode& color_wp_metadata)
{
    //create a node instance for each inner field and store it in a vector
    vector<StructNode*> nodes5 = color_wp_metadata.getChildrenNodes();

    for(unsigned int v = 0; v <  nodes5.size(); v++)
    {
        if(strcmp(nodes5[v]->getStructureP()->name, "mean") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes5[v]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes5[v]->getStructureP()->dims[0] * nodes5[v]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->mean.assign(raw_data, raw_data + dim);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "map") == 0)
        {
             this->mapp.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "inverse") == 0)
        {
             this->inverse.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "V") == 0)
        {
             this->V.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "iD") == 0)
        {
             this->iD.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "D") == 0)
        {
             this->D.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "C") == 0)
        {
             this->C.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }

        if(strcmp(nodes5[v]->getStructureP()->name, "iC") == 0)
        {
             this->iC.setMatrix2D( (double*)nodes5[v]->getStructureP()->data, nodes5[v]->getStructureP()->dims[0], nodes5[v]->getStructureP()->dims[1], true);
        }
    }
}

