#ifndef TABLE_H
#define TABLE_H

#include <string>

#include "intermediate.h"

using namespace std;


class Table {
public:
	
	Table();

	
	Table(const Table &another);

	
	~Table();

	
	bool addAttribute(const string &attr, int index = -1, const string &default_value = "");

	
	bool addEntry(const string *entry, int index = -1);

	
	bool deleteAttribute(int index);

	
	bool deleteEntry(int index);

	
	bool append(const Table &another);

	
	Intermediate query() const { return Intermediate {*this}; }

	
	void print() const;

	
	friend class Intermediate;
	int getNumAttrs() const { return numAttrs; }

	int getNumEntries() const { return numEntries; }

	const string& getAttribute(int index) const { return attrs[index]; }

	const string& getEntry(int entryIndex, int attrIndex) const { return entries[entryIndex][attrIndex]; }

private:
	// 1D array of attributes
	string *attrs;

	// 2D array of entries
	string **entries;

	
	int numAttrs;

	
	int numEntries;
};

#endif
