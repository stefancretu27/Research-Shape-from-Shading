#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <typeinfo>

#include "prior_struct_node.h"

using namespace std;

//Main struct node is prior. It has 3 fields: height, lights and relfectance. For each such node a function is created to get its nodes metadata and data
void getHeight(StructNode& height)
{
    //create a node instance for each inner field and store it in a vector. These nodes are placed on the 2nd level in the structure's tree
     vector<StructNode*>  nodes2 = height.getChildrenNodes();

     //iterate thorugh the nodes which are 2 structures(MKZ and Normal) and one vector (NZ_train)
    for(int ii = 0; ii < nodes2.size(); ii++)
    {
        //get the data for the vector
        if(strcmp(nodes2[ii]->getStructureP()->name, "NZ_train") == 0)
        {
             cout<<"Height > NZ_train "<<nodes2[ii]->getStructureP()->dims[0]<<" "<<nodes2[ii]->getStructureP()->dims[1]<<endl;
             double *NZ_train = (double*)nodes2[ii]->getStructureP()->data;

             //for(int j = 0; j < 10; j++)
                //cout<<NZ_train[j]<<endl;
        }
        //get metadata for inner structures
        else
        {
            //create a StructNode instance for 2nd level fields of type struct
            nodes2[ii]->setNodeFieldsData();
            cout<<"--[Struct level] "<<nodes2[ii]->getNodeLevel()<<" | Struct name:"<<nodes2[ii]->getStructureP()->name<<" | Struct number of fields:"<<nodes2[ii]->getFieldsNo()<<endl;

            //create a StructNode instance for 3rd level fields
            vector<StructNode*> nodes3 = nodes2[ii]->getChildrenNodes();

            for(int iii = 0; iii <  nodes3.size(); iii++)
            {
                //get data for Normal structure directly, as it does not have any inner fields
                if(strcmp(nodes2[ii]->getStructureP()->name, "normal") == 0)
                {
                    if(strcmp(nodes3[iii]->getStructureP()->name, "mult") == 0)
                    {
                        cout<<"Height > Normal >  mult "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                        double mult = *(double*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "power") == 0)
                    {
                        cout<<"Height > Normal >  power "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                        double power = *(double*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "X_train") == 0)
                    {
                        cout<<"Height > Normal > mult "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[ii]->getStructureP()->dims[1]<<endl;
                        double *X_train = (double*)nodes3[iii]->getStructureP()->data;
                    }
                }
                //get data for MKZ_train vector
               else  if(strcmp(nodes2[ii]->getStructureP()->name, "MKZ") == 0 && strcmp(nodes3[iii]->getStructureP()->name, "MKZ_train") == 0)
                {
                        cout<<"Height > MKZ > MKZ_train "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                        double *X_train = (double*)nodes3[iii]->getStructureP()->data;
                }
                //get data for GSM structure
                else
                {
                    nodes3[iii]->setNodeFieldsData();
                    cout<<"---[Struct level] "<<nodes3[iii]->getNodeLevel()<<" | Struct name:"<<nodes3[iii]->getStructureP()->name<<" | Struct number of fields:"<<nodes3[iii]->getFieldsNo()<<endl;

                    //create a node instance for each inner field and store it in a vector
                    vector<StructNode*> nodes4 = nodes3[iii]->getChildrenNodes();

                    for(int iv = 0; iv <  nodes4.size(); iv++)
                    {
                         if(strcmp(nodes4[iv]->getStructureP()->name, "mu") == 0)
                         {
                             cout<<"Heigth > MKZ > MKZ_train > mu "<<nodes4[iv]->getStructureP()->dims[0]<<" "<<nodes4[iv]->getStructureP()->dims[1]<<endl;
                             double  mu = *(double*)nodes4[iv]->getStructureP()->data;
                         }
                        else if(strcmp(nodes4[iv]->getStructureP()->name, "sigs") == 0)
                         {
                             cout<<"Height > MKZ > MKZ_train > sigs "<<nodes4[iv]->getStructureP()->dims[0]<<" "<<nodes4[iv]->getStructureP()->dims[1]<<endl;
                             double *sigs = (double*)nodes4[iv]->getStructureP()->data;
                         }
                        else if(strcmp(nodes4[iv]->getStructureP()->name, "pis") == 0)
                         {
                             cout<<"Height > MKZ > MKZ_train > pis "<<nodes4[iv]->getStructureP()->dims[0]<<" "<<nodes4[iv]->getStructureP()->dims[1]<<endl;
                             double *pis = (double*)nodes4[iv]->getStructureP()->data;
                         }
                         //get data for lut structure
                         else
                         {
                            //create a StructNode instance for 4th level fields
                            nodes4[iv]->setNodeFieldsData();
                            cout<<"----[Struct level] "<<nodes4[iv]->getNodeLevel()<<" | Struct name:"<<nodes4[iv]->getStructureP()->name<<" | Struct number of fields:"<<nodes4[iv]->getFieldsNo()<<endl;

                            //create a node instance for each inner field and store it in a vector
                            vector<StructNode*> nodes5 = nodes4[iv]->getChildrenNodes();

                            for(int v = 0; v < nodes5.size(); v++)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "bin_range") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut > bin_range "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *bin_range = (double*)nodes5[v]->getStructureP()->data;
                                 }
                                 if(strcmp(nodes5[v]->getStructureP()->name, "bin_width") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut > bin_width "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double bin_width = *(double*)nodes5[v]->getStructureP()->data;
                                 }
                                 if(strcmp(nodes5[v]->getStructureP()->name, "n_bins") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut > n_bins "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double n_bins= *(double*)nodes5[v]->getStructureP()->data;
                                 }
                                 if(strcmp(nodes5[v]->getStructureP()->name, "F_LL") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut> F_LL "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *F_LL = (double*)nodes5[v]->getStructureP()->data;
                                 }
                                 if(strcmp(nodes5[v]->getStructureP()->name, "F_cost") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut> F_cost "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *F_cost = (double*)nodes5[v]->getStructureP()->data;
                                 }
                                 if(strcmp(nodes5[v]->getStructureP()->name, "N_train") == 0)
                                 {
                                     cout<<"Height > MKZ > MKZ_train > lut> N_train "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     unsigned int *N_train = (unsigned int*)nodes5[v]->getStructureP()->data;
                                 }
                            }
                         }
                    }
                }
            }
        }
    }
}

void getLights(StructNode &lights)
{
    //create a node instance for each inner field and store it in a vector, that are color and gray structures
    vector<StructNode*>  nodes2 = lights.getChildrenNodes();

    for(int ii = 0; ii < nodes2.size(); ii++)
    {
        //for each structure node, set data about its inner nodes
        nodes2[ii]->setNodeFieldsData();
        cout<<"--[Struct level] "<<nodes2[ii]->getNodeLevel()<<" | Struct name:"<<nodes2[ii]->getStructureP()->name<<" | Struct number of fields:"<<nodes2[ii]->getFieldsNo()<<endl;

        //create a StructNode instance for 3rd level fields, that are natural and laboratory structs, which are inner structs for both color and gray
        vector<StructNode*> nodes3 = nodes2[ii]->getChildrenNodes();

        for(int iii = 0; iii <  nodes3.size(); iii++)
        {
            nodes3[iii]->setNodeFieldsData();
            cout<<"---[Struct level] "<<nodes3[iii]->getNodeLevel()<<" | Struct name:"<<nodes3[iii]->getStructureP()->name<<" | Struct number of fields:"<<nodes3[iii]->getFieldsNo()<<endl;

            //create a node instance for each inner fields, that are gaussian and whiten params, which are inner fields of color and laboratory
            vector<StructNode*> nodes4 = nodes3[iii]->getChildrenNodes();

            for(int iv = 0; iv <  nodes4.size(); iv++)
            {
                //create a node instance for each inner field and store it in a vector
                vector<StructNode*> nodes5 = nodes4[iv]->getChildrenNodes();

                for(int v = 0; v <  nodes5.size(); v++)
                {
                    if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
                    {
                        if(strcmp(nodes3[iii]->getStructureP()->name, "laboratory") == 0)
                        {
                            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mean") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > mean "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mean = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "map") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > map "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mapp = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "inverse") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > inverse "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *inverse = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "V") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > V "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *V = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iD") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > iD "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iD = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "D") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > D "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *D = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "C") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > C "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *C = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iC") == 0)
                                {
                                     cout<<"Lights > color > laboratory > whiten_params > iC "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iC = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
                                {
                                     cout<<"Lights > color > laboratory > gaussian > mu "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mu = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
                                {
                                     cout<<"Lights > color > laboratory > gaussian > Sigma "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *Sigma = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                        }
                        if(strcmp(nodes3[iii]->getStructureP()->name, "natural") == 0)
                        {
                            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mean") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > mean "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mean = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "map") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > map "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mapp = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "inverse") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > inverse "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *inverse = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "V") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > V "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *V = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iD") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > iD "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iD = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "D") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > D "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *D = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "C") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > C "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *C = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iC") == 0)
                                {
                                     cout<<"Lights > color > natural > whiten_params > iC "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iC = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
                                {
                                     cout<<"Lights > color > natural > gaussian > mu "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mu = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
                                {
                                     cout<<"Lights > color > natural > gaussian > Sigma "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *Sigma = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                        }
                    }
                    if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
                    {
                        if(strcmp(nodes3[iii]->getStructureP()->name, "laboratory") == 0)
                        {
                            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mean") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > mean "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mean = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "map") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > map "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mapp = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "inverse") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > inverse "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *inverse = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "V") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > V "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *V = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iD") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > iD "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iD = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "D") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > D "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *D = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "C") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > C "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *C = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iC") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > whiten_params > iC "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iC = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > gaussian > mu "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mu = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
                                {
                                     cout<<"Lights > gray > laboratory > gaussian > Sigma "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *Sigma = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                        }
                        if(strcmp(nodes3[iii]->getStructureP()->name, "natural") == 0)
                        {
                            if(strcmp(nodes4[iv]->getStructureP()->name, "whiten_params") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mean") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > mean "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mean = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "map") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > map "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mapp = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "inverse") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > inverse "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *inverse = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "V") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > V "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *V = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iD") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > iD "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iD = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "D") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > D "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *D = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "C") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > C "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *C = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "iC") == 0)
                                {
                                     cout<<"Lights > gray > natural > whiten_params > iC "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *iC = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                            if(strcmp(nodes4[iv]->getStructureP()->name, "gaussian") == 0)
                            {
                                if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
                                {
                                     cout<<"Lights > gray > natural > gaussian > mu "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *mu = (double*)nodes5[v]->getStructureP()->data;
                                }
                                if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
                                {
                                     cout<<"Lights > gray > natural; > gaussian > Sigma "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                     double *Sigma = (double*)nodes5[v]->getStructureP()->data;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void getReflectance(StructNode &reflectance)
{
     //create a node instance for each inner field and store it in a vector
    vector<StructNode*>  nodes2 = reflectance.getChildrenNodes();

    for(int ii = 0; ii < nodes2.size(); ii++)
    {
        //create a StructNode instance for 2nd level fields of type struct, that are gray and color
        nodes2[ii]->setNodeFieldsData();
        cout<<"--[Struct level] "<<nodes2[ii]->getNodeLevel()<<" | Struct name:"<<nodes2[ii]->getStructureP()->name<<" | Struct number of fields:"<<nodes2[ii]->getFieldsNo()<<endl;

        //create a StructNode instance for 3rd level fields, here both gray and color have a inner MA structure alongside some matrices
        vector<StructNode*> nodes3 = nodes2[ii]->getChildrenNodes();

        for(int iii = 0; iii <  nodes3.size(); iii++)
        {
            nodes3[iii]->setNodeFieldsData();

            if(nodes3[iii]->getFieldsNo() == 0)
            {
                if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
                {
                    if(strcmp(nodes3[iii]->getStructureP()->name, "A_whiten") == 0)
                    {
                         cout<<"Reflectance > color > A_whiten "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         double *A_whiten = (double*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "Aw_hist") == 0)
                    {
                         cout<<"Reflectance > color > Aw_hist "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         double *Aw_hist = (double*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "bin_low") == 0)
                    {
                         cout<<"Reflectance > color > bin_low "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         int *bin_low = (int*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "bin_high") == 0)
                    {
                         cout<<"Reflectance > color > bin_high "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         int *bin_high = (int*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "A_train") == 0)
                    {
                         cout<<"Reflectance > color > A_train "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         double *A_train = (double*)nodes3[iii]->getStructureP()->data;
                    }
                }

                if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
                {
                    if(strcmp(nodes3[iii]->getStructureP()->name, "A_train") == 0)
                    {
                         cout<<"Reflectance > gray > A_train "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         double *A_train = (double*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "A_range") == 0)
                    {
                         cout<<"Reflectance > gray > A_range "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         int *A_range = (int*)nodes3[iii]->getStructureP()->data;
                    }
                    if(strcmp(nodes3[iii]->getStructureP()->name, "A_spline") == 0)
                    {
                         cout<<"Reflectance > gray > A_spline "<<nodes3[iii]->getStructureP()->dims[0]<<" "<<nodes3[iii]->getStructureP()->dims[1]<<endl;
                         double *A_spline= (double*)nodes3[iii]->getStructureP()->data;
                    }
                }
            }
            //get inner structs
            else
            {
                //create a StructNode instance for 4th level fields, that is GSM for gray.MA and GSM_mvn for color.MA + a matrix for gray.MA
                vector<StructNode*> nodes4 = nodes3[iii]->getChildrenNodes();

                for(int iv = 0; iv <  nodes4.size(); iv++)
                {
                    nodes4[iv]->setNodeFieldsData();

                    if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0 && strcmp(nodes4[iv]->getStructureP()->name, "MA_train") == 0)
                    {
                        cout<<"Reflectance > gray > MA > MA_train "<<nodes4[iv]->getStructureP()->dims[0]<<" "<<nodes4[iv]->getStructureP()->dims[1]<<endl;
                        double *MA_train= (double*)nodes4[iv]->getStructureP()->data;
                    }
                    else
                    {
                        //create a StructNode instance for 5th level fields
                        vector<StructNode*> nodes5 = nodes4[iv]->getChildrenNodes();

                        for(int v = 0; v <  nodes5.size(); v++)
                        {
                            nodes5[v]->setNodeFieldsData();

                            if(nodes5[v]->getFieldsNo() == 0)
                            {
                                if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
                                {
                                    if(strcmp(nodes5[v]->getStructureP()->name, "pis") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > pis "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *pis = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "Sigma") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > Sigma "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *Sigma = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "vars") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > vars "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *vars = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_inv") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > Sigma_inv "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *Sigma_inv = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_R") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > Sigma_R "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *Sigma_R = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "logmults") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > logmults "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *logmults = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "Sigma_whiten") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > Sigma_whiten "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *Sigma_whiten = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "LL_zero") == 0)
                                    {
                                         cout<<"Reflectance > color > MA > GSM_mvn > LL_zero "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *LL_zero = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                }
                                if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
                                {
                                    if(strcmp(nodes5[v]->getStructureP()->name, "mu") == 0)
                                    {
                                         cout<<"Reflectance > gray > MA > GSM > mu "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         int mu = *(int*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "sigs") == 0)
                                    {
                                         cout<<"Reflectance > gray > MA > GSM> sigs "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *sigs = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                    if(strcmp(nodes5[v]->getStructureP()->name, "pis") == 0)
                                    {
                                         cout<<"Reflectance > gray > MA > GSM> pis "<<nodes5[v]->getStructureP()->dims[0]<<" "<<nodes5[v]->getStructureP()->dims[1]<<endl;
                                         double *pis = (double*)nodes5[v]->getStructureP()->data;
                                    }
                                }
                            }
                            else
                            {
                                //create a StructNode instance for 5th level fields
                                vector<StructNode*> nodes6 = nodes5[v]->getChildrenNodes();

                                for(int vi = 0; vi <  nodes6.size(); vi++)
                                {
                                    nodes6[vi]->setNodeFieldsData();
                                    if(strcmp(nodes2[ii]->getStructureP()->name, "color") == 0)
                                    {
                                        if(strcmp(nodes6[vi]->getStructureP()->name, "bin_range") == 0)
                                        {
                                             cout<<"Reflectance > color > MA > GSM_mvn > lut> bin_range "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double *pis = (double*)nodes6[vi]->getStructureP()->data;
                                        }
                                        if(strcmp(nodes6[vi]->getStructureP()->name, "Sigma") == 0)
                                        {
                                             cout<<"Reflectance > color > MA > GSM_mvn > lut > bin_width "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double bin_width = *(double*)nodes6[vi]->getStructureP()->data;
                                        }
                                        if(strcmp(nodes6[vi]->getStructureP()->name, "n_bins") == 0)
                                        {
                                             cout<<"Reflectance > color > MA > GSM_mvn > lut > n_bins "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             int n_bins = *(int*)nodes6[vi]->getStructureP()->data;
                                        }
                                        if(strcmp(nodes6[vi]->getStructureP()->name, "F") == 0)
                                        {
                                             cout<<"Reflectance > color > MA > GSM_mvn > lut > F "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double *F = (double*)nodes6[vi]->getStructureP()->data;
                                        }
                                    }
                                    if(strcmp(nodes2[ii]->getStructureP()->name, "gray") == 0)
                                    {
                                        if(strcmp(nodes6[vi]->getStructureP()->name, "bin_range") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut > bin_range "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double *bin_range = (double*)nodes6[vi]->getStructureP()->data;
                                         }
                                         if(strcmp(nodes6[vi]->getStructureP()->name, "bin_width") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut > bin_width "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double bin_width = *(double*)nodes6[vi]->getStructureP()->data;
                                         }
                                         if(strcmp(nodes6[vi]->getStructureP()->name, "n_bins") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut > n_bins "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double n_bins= *(double*)nodes6[vi]->getStructureP()->data;
                                         }
                                         if(strcmp(nodes6[vi]->getStructureP()->name, "F_LL") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut> F_LL "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double *F_LL = (double*)nodes6[vi]->getStructureP()->data;
                                         }
                                         if(strcmp(nodes6[vi]->getStructureP()->name, "F_cost") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut> F_cost "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             double *F_cost = (double*)nodes6[vi]->getStructureP()->data;
                                         }
                                         if(strcmp(nodes6[vi]->getStructureP()->name, "N_train") == 0)
                                         {
                                             cout<<"Reflectance > gray > Ma >GSM > lut> N_train "<<nodes6[vi]->getStructureP()->dims[0]<<" "<<nodes6[vi]->getStructureP()->dims[1]<<endl;
                                             unsigned int *N_train = (unsigned int*)nodes6[vi]->getStructureP()->data;
                                         }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    mat_t    *matfp;
    //create root node of the structure hierarchy and set its level to 0 (root node)
    StructNode prior(0);
    string filename = "prior.mat";

    //open the .mat file and get pointer to it
    matfp = Mat_Open(filename.c_str(), MAT_ACC_RDONLY);
    if ( NULL == matfp )
    {
        cout<<"Error opening MAT file: "<<filename<<endl;
        return EXIT_FAILURE;
    }

    //get pointer to main structure from the .mat file, that is prior
    prior.setStructureP(Mat_VarReadNext(matfp));
    if( prior.getStructureP() != NULL )
    {
        //Once the pointer to the struct is known, its fields data can be retrieved
        prior.setNodeFieldsData();
        //print some info about the parent node
        cout<<"[Struct level] "<<prior.getNodeLevel()<<" | Struct name:"<<prior.getStructureP()->name<<" | Struct number of fields:"<<prior.getFieldsNo()<<endl;

        vector<StructNode*>  nodes1 = prior.getChildrenNodes();

        for(int i = 0; i < nodes1.size(); i++)
        {
            nodes1[i]->setNodeFieldsData();
            cout<<"-[Struct level] "<<nodes1[i]->getNodeLevel()<<" | Struct name:"<<nodes1[i]->getStructureP()->name<<" | Struct number of fields:"<<nodes1[i]->getFieldsNo()<<endl;

             //Check if height, lights and reflectance structs have been corectly set, it should have 3 fields. For safety, check if it has been set
            if(nodes1[i]->getFieldsNo() > 0)
            {
                if(strcmp(nodes1[i]->getStructureP()->name, "height") == 0)
                {
                    getHeight(*nodes1[i]);
                }
                if(strcmp(nodes1[i]->getStructureP()->name, "lights") == 0)
                {
                    getLights(*nodes1[i]);
                }
                if(strcmp(nodes1[i]->getStructureP()->name, "reflectance") == 0)
                {
                    getReflectance(*nodes1[i]);
                }

            }
            cout<<endl;
        }
    }

    Mat_Close(matfp);

    return EXIT_SUCCESS;
}

