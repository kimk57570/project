#include "table.h"
#include <string>
#include <iostream>

using namespace std;

Table::Table() : attrs(nullptr), entries(nullptr), numAttrs(0), numEntries(0) {};

Table::Table(const Table &another) {
	numEntries = another.numEntries;
	numAttrs = another.numAttrs;
	attrs = new string [numAttrs];
		for(int i = 0; i < numAttrs; i++) {
			attrs[i] = another.attrs[i];
		}
	entries = new string* [numEntries];
		for(int i = 0; i < numEntries; i++) {
			entries[i] = new string [numAttrs];
				for(int j = 0; j < numAttrs; j++) {
					entries[i][j] = another.entries[i][j];
				}
		}
}

Table::~Table() {
	delete [] attrs;

	for (int i = 0; i < numEntries; i++) {
		delete [] entries[i];
	}
	delete [] entries;
}


bool Table::addAttribute(const string &attr, int index, const string &default_value) {

	if (index < -1 || index > numAttrs) {
		return false;
	}
	else {
		string* attrs2 = new string [numAttrs+1];
		if (index == -1) {
			for(int i = 0; i < numAttrs; i++) {
				attrs2[i] = attrs[i];
			}
			attrs2[numAttrs] = attr;
		}
		else {
			for(int i = 0; i < numAttrs+1; i++) {
				if (i < index) {
					attrs2[i] = attrs[i];
				}
				else if (i == index) {
					attrs2[index] = attr;
				}
				else {
					attrs2[i] = attrs[i-1];
				}
			}
		}
		delete [] attrs;
		attrs = attrs2;


		if(numEntries == 0) {
			numAttrs += 1;
			return true;
		}
		else {
			for(int i=0; i < numEntries; i++) {
				string* entries2 = new string [numAttrs+1];
				if (index == -1) {
					for (int j = 0; j < numAttrs; j++) {
						entries2[j] = entries[i][j];
					}
					entries2[numAttrs] = default_value;
				}
				else {
					for(int j = 0; j < numAttrs+1; j++) {
						if (j < index) {
							entries2[j] = entries[i][j];
						}
						else if (j == index) {
							entries2[index] = default_value;
						}
						else {
							entries2[j] = entries[i][j-1];
						}
					}
				}
				delete [] entries[i];
				entries[i] = entries2;
			}
			numAttrs += 1;
			return true;
		}
	}
return false;
}

bool Table::addEntry(const string *entry, int index) {

	if (index < -1 || index > numEntries) {
		return false;
	}
	else {
		string *newEntry = new string [numAttrs];
		for (int i = 0; i < numAttrs; i++) {
			newEntry[i] = entry[i];
		}
		string** newEntries = new string *[numEntries+1];
		if(index == -1) {
			for (int i = 0; i < numEntries; i++) {
				newEntries[i] = entries[i];
			}
			newEntries[numEntries] = newEntry;
		}
		else {
			for (int i = 0; i < numEntries+1; i++) {
				if (i < index) {
					newEntries[i] = entries[i];
				}
				else if (i == index) {
					newEntries[index] = newEntry;
				}
				else {
					newEntries[i] = entries[i-1];
				}
			}
		}
		numEntries += 1;
		entries = newEntries;
		return true;
	}
	return false;
}

bool Table::deleteAttribute(int index) {
	if (index < 0 || index > numAttrs-1) {
			return false;
	}
	else {
		string* attrs2 = new string [numAttrs-1];
		for(int i = 0; i < numAttrs; i++) {
			if (i < index) {
				attrs2[i] = attrs[i];
			}
			else if (i == index) {
				continue;
			}
			else {
				attrs2[i-1] = attrs[i];
			}
		}
		delete [] attrs;
		attrs = attrs2;

		if(numAttrs == 1) {
			for (int i = 0; i < numEntries; i++) {
				delete [] entries[i];
			}
			delete [] entries;
			numAttrs = 0;
			numEntries = 0;
			return true;
		}
		else if(numAttrs >= 2) {
			if (numEntries == 0) {
				numAttrs -= 1;
				return true;
			}
			else {
				for(int i=0; i < numEntries; i++) {
					string* entries2 = new string [numAttrs-1];
					for(int j = 0; j < numAttrs; j++) {
						if (j < index) {
							entries2[j] = entries[i][j];
						}
						else if (j == index) {
							continue;
						}
						else {
							entries2[j-1] = entries[i][j];
						}
					}
					delete [] entries[i];
					entries[i] = entries2;
				}
				numAttrs -= 1;
				return true;
			}
		}
	}
return false;
}

bool Table::deleteEntry(int index) {
	if (index < 0 || index > numEntries-1	) {
		return false;
	}
	else {
		string** newEntries = new string *[numEntries-1];
		for (int i = 0; i < numEntries; i++) {
			if (i < index) {
				newEntries[i] = entries[i];
			}
			else if (i == index) {
				continue;
			}
			else {
				newEntries[i-1] = entries[i];
			}
		}
		numEntries -= 1;
		delete [] entries[index];
		delete [] entries;
		entries = newEntries;
		return true;
	}
	return false;
}

bool Table::append(const Table &another) {
	if(this->numAttrs == another.numAttrs) {
		for(int i = 0; i < this->numAttrs; i++) {
			if(this->attrs[i] == another.attrs[i]) {
				continue;
			}
			else {
				return false;
			}
		}
		string** newTable = new string* [this->numEntries+another.numEntries];
		for (int i = 0; i < this->numEntries+another.numEntries; i++) {
			if(i < this->numEntries) {
				newTable[i] = entries[i];
			}
			else {
				newTable[i] = another.entries[i-this->numEntries];
			}
		}
		this->numEntries = this->numEntries + another.numEntries;
		delete [] this->entries;
		entries = newTable;
		return true;
	}
	else {
		return false;
	}

	return false;
}

void Table::print() const {

}






