

#include "infectionAnalyzer.h"
#include <fstream> //for reading file
#include <queue> //you may use STL queue
#include <algorithm> //you may use STL algorithm
using namespace std;



InfectionAnalyzer::~InfectionAnalyzer() {
	for(unsigned int i = 0; i < trees.size(); i++) {
		delete trees[i];
		trees[i] = nullptr;
	}
	trees.clear();
}


bool InfectionAnalyzer::loadInfectionFile(const string filename) {
	ifstream ifs;
	ifs.open(filename);
	if(!ifs) {
		return false;
	}

	string parent;
	string child;
	while(ifs >> parent >> child) {
		if(trees.size() == 0) {
			Tree<string>* x = new Tree<string>;
			x->addRoot(parent);
			x->addChild(parent,child);
			trees.push_back(x);
		}

		else {
			Tree<string>* b;
			unsigned int i = 0;
			for(i = 0; i < trees.size(); i++) {
				b = trees[i]->find(parent);
				if (b != nullptr) {
					break;
				}
			}
			Tree<string>* a;
			unsigned int j = 0;
			for(j=0; j < trees.size(); j++) {
				a = trees[j]->find(child);
				if (a != nullptr) {
					break;
				}
			}


			if(b == nullptr && a == nullptr) {
				Tree<string>* y = new Tree<string>;
				y->addRoot(parent);
				y->addChild(parent,child);
				trees.push_back(y);
			}
			else if (b == nullptr && a != nullptr) {
				trees[j]->addRoot(parent);

			}
			else if (b != nullptr && a== nullptr){
				trees[i]->addChild(parent,child);
			}
			else if (b != nullptr && a != nullptr) {
				trees[i]->addChild(parent, child);
				trees[i]->find(child)->root = a->root;
				trees.erase(trees.begin()+j);
			}
		}
	}
	ifs.close();
	return true;
}


bool InfectionAnalyzer::isInfected(const string name) const {
	for(unsigned int i = 0; i < trees.size(); i++) {
		const Tree<string>* infected = trees[i]->find(name);
		if (infected != nullptr) {
			return true;
		}
		else if (infected == nullptr) {
			continue;
		}
	}
	return false;
}


string InfectionAnalyzer::getInfectionSource(const string name) const {
	for(unsigned int i = 0; i < trees.size(); i++) {
		queue<Node<string>*> source;
		source.push(trees[i]->root); //pointer to very first node
		if(trees[i]->find(name) != nullptr) {
			if (trees[i]->root->data == name) {
				return "ZERO";
			}
			else {
				while(!source.empty()) {
					Node<string>* first = source.front();
					if(first->children != nullptr) {
						for (int i = 0; i < first->childCount; i++) {
							source.push(first->children[i].root);
							if (first->children[i].root->data == name) {
								return first->data;
							}
							else {
								continue;
							}
						}
						source.pop();
					}
					else {
						source.pop();
					}
				}
			}
		}
		else if (trees[i]->find(name) == nullptr) {
			source.pop();
			continue;
		}
	}
	return "NA";
}


int InfectionAnalyzer::getInfectionGeneration(const string name) const {
	if(isInfected(name) == false) {
		return -1;
	}
	else {
		unsigned int i = 0;
		for(i = 0; i < trees.size(); i++) {
			const Tree<string>* gen = trees[i]->find(name);
			if (gen != nullptr) {
				break;
			}
			else if (gen == nullptr) {
				continue;
			}
		}
		return trees[i]->getDepth(name);
	}
}



bool compare(pair<string, int> p1, pair<string, int> p2){
	if (p1.second > p2.second) {
		return true;
	}
	else if (p1.second == p2.second) {
		if (p1.first < p2.first) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (p1.second < p2.second) {
		return false;
	}
	return true;
}



const vector<pair<string, int>>& InfectionAnalyzer::getInfectionPowerVector() {
	infectionPowerVector.clear();

	for (unsigned int i = 0; i < trees.size(); i++) {
		if(trees[i]->isEmpty()) {
			continue;
		}
		queue<Node<string>*> pVector;
		pVector.push(trees[i]->root);
		while (!pVector.empty()) {
			Node<string>* first = pVector.front();
			if (first->children != nullptr) {
				for (int i = 0; i < first->childCount; i++) {
					pVector.push(first->children[i].root);
				}
			}
			infectionPowerVector.push_back(make_pair(first->data, trees[i]->getDescendantCount(first->data)));
			pVector.pop();
		}
	}
	sort(infectionPowerVector.begin(), infectionPowerVector.end(), compare);
	return infectionPowerVector;
}
