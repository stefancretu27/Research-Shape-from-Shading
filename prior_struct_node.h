#ifndef PRIOR_STRUCT_NODE_H_INCLUDED
#define PRIOR_STRUCT_NODE_H_INCLUDED

#include <iostream>
#include <vector>

extern "C"
{
    #include "C:\Users\stefa_000\Downloads\matio-1.5.11\matio-1.5.11\src\matio.h"
}

class StructNode
{
private:
    /*info about the node */
    //depth level of the structure, in the hierarchy
    unsigned int node_level;
    //pointer to Matlab structure
    matvar_t* structure_p;

    /* info about fields*/
    //structure's # of fields
    unsigned int fields_no;
    //array that contains the node's fields' names
    char* const *fields_names;
    //array of pointers to fields
    matvar_t **struct_fields_p;

public:
    //setters
    void setNodeLevel(unsigned int nl);
    //internally set
    void setFieldsNo();
    void setStructureP(matvar_t* strctr);
    void setFieldsNames(char* const *sfn);
    void setFieldsNames();
    //it needs structure_p to initialize the other fields
    void setNodeFieldsData();

    //getters
    unsigned int getNodeLevel() const;
    unsigned int getFieldsNo() const;
    matvar_t* getStructureP() const;
    char* const * getFieldsNames() const;
    matvar_t* getFieldP(int index);
    matvar_t ** getFields_P();
    std::vector<StructNode*>  getChildrenNodes();

    //constructors
    StructNode(){};
    StructNode(unsigned int nl,  matvar_t* strctr);
    StructNode(unsigned int nl);
    StructNode(unsigned int nl, unsigned int fn, matvar_t* strctr);
    StructNode(const StructNode &sn);
    ~StructNode();

    //operators overloading
    StructNode& operator=(const StructNode &sn);
};

#endif // PRIOR_STRUCT_NODE_H_INCLUDED
