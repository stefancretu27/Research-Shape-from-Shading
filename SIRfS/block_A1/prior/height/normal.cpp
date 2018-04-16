#include "normal.h"

using namespace std;

void Normal::initializeNormalData(StructNode& normal_metadata)
{
    //create a StructNode instance for 3rd level fields
    vector<StructNode*> nodes3 = normal_metadata.getChildrenNodes();

    for(int iii = 0; iii <  nodes3.size(); iii++)
    {
        //get data for Normal structure directly, as it does not have any inner fields
        if(strcmp(nodes3[iii]->getStructureP()->name, "mult") == 0)
        {
            this->mult = *(double*)nodes3[iii]->getStructureP()->data;

#ifdef TEST_PRIOR_HEIGHT
            bool result = fabs(this->mult - 2.95) < 0.000001;
            cout<<"-->Test for reading priors on height: "<<normal_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<result<<endl;
#endif // TEST_PRIOR_HEIGHT
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "power") == 0)
        {
            this->power = *(double*)nodes3[iii]->getStructureP()->data;

#ifdef TEST_PRIOR_HEIGHT
            bool result = this->power == 0.75;
            cout<<"-->Test for reading priors on height: "<<normal_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<result<<endl;
#endif // TEST_PRIOR_HEIGHT
        }

        if(strcmp(nodes3[iii]->getStructureP()->name, "X_train") == 0)
        {
            //get pointer to raw data from .mat file
            double *raw_data = (double*)nodes3[iii]->getStructureP()->data;
            //get dimension of the vector
            int dim  = nodes3[iii]->getStructureP()->dims[0] * nodes3[iii]->getStructureP()->dims[1];
            //use pointer to the first and the last element in the array as iterators
            this->X_train.assign(raw_data, raw_data + dim);

            //macro defined in validation.h
#ifdef TEST_PRIOR_HEIGHT
            cout<<"Test for reading priors on height: "<<normal_metadata.getStructureP()->name<<"->"<<nodes3[iii]->getStructureP()->name<<"  "<<\
                        test_vectors("block_A1/prior/height/x_train17.txt", this->X_train, Double)<<endl;
#endif // TEST_PRIOR_HEIGHT
        }
    }
}
