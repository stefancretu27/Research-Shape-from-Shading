#include "prior_struct_node.h"

using namespace std;

//setters
void StructNode::setNodeLevel(unsigned int nl)
{
    this->node_level = nl;
}
void StructNode::setFieldsNo()
{
    this->fields_no = Mat_VarGetNumberOfFields(this->getStructureP());
    struct_fields_p = new matvar_t*[this->getFieldsNo()];
}
void StructNode::setStructureP(matvar_t* strctr)
{
    this->structure_p = strctr;
}
void StructNode::setFieldsNames(char* const *sfn)
{
    this->fields_names  = sfn;
}
void StructNode::setFieldsNames()
{
   this->fields_names = Mat_VarGetStructFieldnames(this->getStructureP());
}

//getters
unsigned int StructNode::getNodeLevel() const
{
    return this->node_level;
}
unsigned int StructNode::getFieldsNo() const
{
    return this->fields_no;
}
matvar_t* StructNode::getStructureP() const
{
    return this->structure_p;
}
char* const * StructNode::getFieldsNames() const
{
    return this->fields_names;
}
matvar_t* StructNode::getFieldP(int index)
{
    return this->struct_fields_p[index];
}
matvar_t** StructNode::getFields_P()
{
    return this->struct_fields_p;
}

//it needs structure_p to initialize the other fields
void StructNode::setNodeFieldsData()
{
    //Firstly, get fields names and fields_no
    this->fields_no = Mat_VarGetNumberOfFields(this->structure_p);
    this->fields_names = Mat_VarGetStructFieldnames(this->structure_p);
    //this->setFieldsNames(Mat_VarGetStructFieldnames(this->getStructureP()));

    //Secondly, for each inner structure, store its pointer in an array of pointers
    this->struct_fields_p = new matvar_t*[this->fields_no];

     for(int i = 0; i < this->getFieldsNo(); i++)
    {
        //get pointer to inner structs, by names
       this->struct_fields_p[i] = Mat_VarGetStructFieldByName(this->structure_p, this->fields_names[i], 0);
    }
}

//Function for getting the metadata of inner nodes of a parent node, returning a vector of pointers to them. It sets the pointer to each node and the dats for inner nodes of each child node
vector<StructNode*>  StructNode::getChildrenNodes()
{
    vector<StructNode*> children_nodes;
    children_nodes.reserve(this->getFieldsNo());

     for(int i = 0; i < this->getFieldsNo(); i++)
    {
        //create a StructNode instance for 1st level fields
        children_nodes.push_back(new StructNode(this->getNodeLevel()+1, this->getFieldP(i)));

        //for each node, get inner nodes info: number of nodes, name of nodes, pointer to each node
        children_nodes[i]->setNodeFieldsData();
    }

    return children_nodes;
}

//constructors
StructNode::StructNode(unsigned int nl,  matvar_t* strctr)
{
    this->node_level = nl;
    this->structure_p = strctr;
}
StructNode::StructNode(unsigned int nl)
{
    this->node_level = nl;
}
StructNode::StructNode(unsigned int nl, unsigned int fn, matvar_t* strctr)
{
    this->node_level = nl;
    this->fields_no = fn;
    this->structure_p = strctr;
    struct_fields_p = new matvar_t*[this->getFieldsNo()];
}
StructNode::StructNode(const StructNode &sn)
{
    this->node_level = sn.getNodeLevel();
    this->fields_no = sn.getFieldsNo();
    this->structure_p = sn.getStructureP();
    this->struct_fields_p = new matvar_t*[this->getFieldsNo()];
}
StructNode::~StructNode()
{
    Mat_VarFree(this->structure_p);
    this->structure_p = NULL;
}

//operators overloading
StructNode& StructNode::operator=(const StructNode &sn)
{
    this->node_level = sn.getNodeLevel();
    this->fields_no = sn.getFieldsNo();
    this->structure_p = sn.getStructureP();
    this->struct_fields_p = new matvar_t*[this->getFieldsNo()];

    return *this;
}


