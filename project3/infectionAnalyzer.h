
#ifndef INFECTIONANALYZER_H
#define INFECTIONANALYZER_H

#include "tree.h"
#include <string>
#include <iostream>
#include <vector> //you may use STL vector
#include <queue> //you may use STL queue
using std::string;

//The Infection Analyzer
class InfectionAnalyzer {
private:
    vector<Tree<string>*> trees; //the vector of all infection trees
    // in a vector array named tree, there are element of type tree pointer (data type is string)

    vector<pair<string, int>> infectionPowerVector; //the sorted vector of name-power pairs that tell the infection powers of all the people in all the trees

public:
    
    ~InfectionAnalyzer();

    //load the infection file of the specified filename, and construct the infection trees, return true at the end
    //for the file format and examples of the resulting trees, see webpage and sample output
    //if the file cannot be loaded, do nothing and return false
    bool loadInfectionFile(const string filename);

    //return true if the specified name can be found in any of the infection trees
    //return false otherwise
    bool isInfected(const string name) const;

    //check all trees, and find the node with the specified name, and return the name of its parent
    //if the node with the specified name is a root node of a tree (i.e. no parent), then return "ZERO" to indicate that the person might be a patient-zero
    //if the specified name is not found at all in all trees, return "NA"
    string getInfectionSource(const string name) const;

    //return the depth of the node with the specified name
    //if the specified name is not found at all in all trees, return -1
    int getInfectionGeneration(const string name) const;

    //generate the infectionPowerVector and return it
    //the infection power of a person is defined as the number of descendants it has in a tree
    //the name-power pairs should be ordered by the infection power in descending order
    //if two pairs have the the same power, then they are ordered by their names in ascending order 

    const vector<pair<string, int>>& getInfectionPowerVector();

    //print all the infection trees to the ostream
    void printInfectionTrees(std::ostream& os)
    {
        if (trees.size() == 0)
            return;

        os << "----------------------------" << endl;
        for (size_t i=0; i<trees.size(); i++)
        {
            os << "Infection Tree " << i << endl << endl;
            trees[i]->print(os);
            os << endl << "----------------------------" << endl;
        }
    }
};

#endif
