#ifndef PRIOR_H_INCLUDED
#define PRIOR_H_INCLUDED

#include "prior/height.h"
#include "prior/lights.h"
#include "prior/reflectance.h"

class Prior
{
private:
    //data
    Height height;
    Lights light;
    Reflectance reflectance;
    //metadata
    StructNode prior_metadata;

public:
    //constructors: Since the copy constructor is overridden as it is needed for = operator, the default constructor needs to be defined as the implicit constructor cannot be called anymore (once any kind of constructor is defined)
    Prior(){};
    Prior(const Prior& new_prior)
    {
        this->height = new_prior.height;
        this->light = new_prior.light;
        this->reflectance = new_prior.reflectance;
    }
    //operators overloading
    Prior& operator=(const Prior& new_prior)
    {
        this->height = new_prior.height;
        this->light = new_prior.light;
        this->reflectance = new_prior.reflectance;
        return *this;
    };

    //getters
    Height& getHeight(){return this->height;};
    Lights& getLights(){return this->light;};
    Reflectance& getReflectance(){return this->reflectance;};

    //setter: initialize data
    void initializePriorData(mat_t *matfp)
    {
        //create root node of the structure hierarchy and set its level to 0 (root node)
        this->prior_metadata.setNodeLevel(0);

        //get pointer to main structure from the .mat file, that is prior
        this->prior_metadata.setStructureP(Mat_VarReadNext(matfp));
        if( this->prior_metadata.getStructureP() == NULL )
        {
            cout<<"Could not get pointer to prior structure"<<endl;
            return;
        }
        else
        {
             //Once the pointer to the struct is known, its fields data can be retrieved
            this->prior_metadata.setNodeFieldsData();
            //store in a vector childern nodes' metadata, such as names, number of inner fields and pointers to these inner fields
            vector<StructNode*> nodes1 = this->prior_metadata.getChildrenNodes();

            for(int i = 0; i < nodes1.size(); i++)
            {
                if(nodes1[i]->getFieldsNo() > 0)
                {
                    if(strcmp(nodes1[i]->getStructureP()->name, "height") == 0)
                    {
                        this->height.initializeHeightData(*nodes1[i]);
                    }
                    if(strcmp(nodes1[i]->getStructureP()->name, "lights") == 0)
                    {
                        this->light.initializeLightsData(*nodes1[i]);
                    }
                    if(strcmp(nodes1[i]->getStructureP()->name, "reflectance") == 0)
                    {
                        this->reflectance.initializeReflectanceData(*nodes1[i]);
                    }
                }
                else
                {
                    cout<<"Could not load data for prior children nodes"<<endl;
                }
            }
        }
    }
};

#endif // PRIOR_H_INCLUDED
