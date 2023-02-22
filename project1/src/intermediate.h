#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <string>

using namespace std;

class Table;

// String comparison mode
// Equals, Contains
enum compare {EQ, CONTAINS};

// Sorting order
enum order {ASCENDING, DESCENDING};

// Doubly linked list node pointing to an entry
// The entry is not owned by this node
struct EntryNode {
	string *entry;

	EntryNode *prev;
	EntryNode *next;
};

// This class represents the "intermediate objects" of a query
class Intermediate {
public:
	// No default constructor
	Intermediate() = delete;

	
	Intermediate(const Table &table);

	
	~Intermediate();

	
	Intermediate& where(const string &attr, enum compare mode, const string &value);

	
	Intermediate& orderBy(const string &attr, enum order order);

	
	Intermediate& limit(unsigned int limit);

	
	void update(const string &attr, const string &new_value) const;

	
	void select(const string *attrs = nullptr, int numAttrs = 0) const;

private:
	// Pointer to the 1D array of attributes
	// Not owned by intermediate
	const string *attrs;
	int numAttrs;

	// Doubly linked list
	EntryNode *head;
	EntryNode *tail;
};


// Returns a string left-padded with space to length
static string
_left_pad_until(const string &s, int length)
{
	int padding = length - s.length();

	if (padding > 0)
		return string(padding, ' ') + s;
	else
		return s;
}

#endif
