#include "intermediate.h"
#include "table.h"
#include <string>
#include <iostream>

using namespace std;



Intermediate::Intermediate(const Table &table) {
	numAttrs = table.numAttrs;
	attrs = table.attrs;
	if (table.numEntries == 0) {
		head = nullptr;
		tail = nullptr;
	}
	else if (table.numEntries == 1) {
		head = new EntryNode;
		head->entry = table.entries[0];
		head->prev = nullptr;
		head->next = nullptr;
		tail = head;

	}
	else if (table.numEntries == 2) {
		head = new EntryNode;
		tail = new EntryNode;
		head->entry = table.entries[0];
		head->prev = nullptr;
		head->next = tail;
		tail->entry = table.entries[1];
		tail->prev = head;
		tail->next = nullptr;
	}
	else if (table.numEntries > 2) {
		head = new EntryNode;
		tail = new EntryNode;
		head->entry = table.entries[0];
		tail->entry = table.entries[table.numEntries-1];
		head->next = tail;
		head->prev = nullptr;
		tail->prev = head;
		tail->next = nullptr;


		for(int i = 1; i < table.numEntries-1; i++) {
			EntryNode* newNode = new EntryNode;
			EntryNode* temp = head;
			for (int j = 1; j < i; j++) {
				temp = temp->next;
			}
			newNode->next = temp->next;
			temp->next = newNode;
			newNode->prev = temp;
			temp->next->prev = temp;
			newNode->entry = table.entries[i];
		}
	}
}

Intermediate::~Intermediate() {
	int b = 1;
	for (EntryNode* temp = head; temp->next!= nullptr; temp=temp->next) {
		b++;
	}

	for (int i = 1; i < b+1; i++) {
		EntryNode* temp = head;
		head = head->next;
		delete temp;
	}
	delete head;
	delete tail;



}


int isSubstring(string s1, string s2) {
	 int x = s1.length();
	 int y = s2.length();
	 for (int i = 0; i <= y - x; i++) {
		 int j;
		 for (j = 0; j < x; j++) {
			if (s2[i + j] != s1[j]) {
				break;
			}

			if (j == x) {
				return i;
			}
		 }
	}
	return -1;
}

Intermediate& Intermediate::where(const string &attr, enum compare mode, const string &value) {
	int a = 0;
	for (int i = 0; i < numAttrs; i++) {
		if(attrs[i] != attr) {
			a += 1;
			continue;
		}
		else if(attrs[i] == attr) {
			break;
		}
	}


	if (a >= numAttrs) {
		return *this;
	}
	else {
		if(mode == 0) {
			for(EntryNode* temp = head; temp->next != nullptr; temp=temp->next) {
				if(temp->entry[a] != value) {
					if (temp == head) {
						head = head->next;
						head->prev = nullptr;
						delete [] temp->entry;
						delete temp;
					}
					else if (temp == tail) {
						tail = tail->prev;
						tail->next = nullptr;
						delete [] temp->entry;
						delete temp;
					}
					else {
						temp->prev->next = temp->next;
						temp->next->prev = temp->prev;
						delete [] temp->entry;
						delete temp;
					}
				}
				else {
					continue;
				}
			}
			return *this;
		}
		else if (mode == 1) {
			for(EntryNode* temp = head; temp->next != nullptr; temp=temp->next) {
				int x = isSubstring(temp->entry[a], value);
				if(x == -1) {
					if (temp == head) {
						head = head->next;
						head->prev = nullptr;
						delete [] temp->entry;
						delete temp;
					}
					else if (temp == tail) {
						tail = tail->prev;
						tail->next = nullptr;
						delete [] temp->entry;
						delete temp;
					}
					else {
						temp->prev->next = temp->next;
						temp->next->prev = temp->prev;
						delete [] temp->entry;
						delete temp;
					}
				}
				else {
					continue;
				}
			}
			return *this;
		}
	}
	return *this;
}



Intermediate& Intermediate::orderBy(const string &attr, enum order order) {
	int a = 0;
	for (int i = 0; i < numAttrs; i++) {
		if(attrs[i] != attr) {
			a += 1;
			continue;
		}
		else if(attrs[i] == attr) {
			break;
		}
	}

	int b = 1;
	for (EntryNode* temp = head; temp->next!= nullptr; temp=temp->next) {
		b++;
	}

	if (a >= numAttrs) {
		return *this;
	}
	else {
		//accending
		if(order == 0) {
			for(int i = 0; i < b; i++) {
				for(EntryNode* temp = head; temp->next != nullptr; temp=temp->next) {
					//current attribute is smaller or equal than next
					if(temp->entry[a].compare(temp->next->entry[a])<=0) {
						continue;
					}
					//currrent attribute is larger than next
					else {
						string* tempEntry = temp->entry;
						temp->entry = temp->next->entry;
						temp->next->entry = tempEntry;
					}
				}
			}
		}
		//decending
		else if (order == 1) {
			for(int i = 0; i < b; i++) {
				for(EntryNode* temp = tail; temp->prev != nullptr; temp=temp->prev) {
					//current attribute is smaller or equal than next
					if(temp->entry[a].compare(temp->prev->entry[a])<=0) {
						continue;
					}
					//currrent attribute is larger than next
					else {
						string* tempEntry = temp->entry;
						temp->entry = temp->prev->entry;
						temp->prev->entry = tempEntry;
					}
				}
			}
		}
	}
}

Intermediate& Intermediate::limit(unsigned int limit) {
	int b = 1;
	for (EntryNode* temp = head; temp->next!= nullptr; temp=temp->next) {
		b++;
	}

	if (limit == 0) {
		delete attrs;
		attrs = nullptr;
		numAttrs = 0;
		for (int i = 1; i < b+1; i++) {
			EntryNode* temp = head;
			head = head->next;
			delete [] temp->entry;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
	}

	else {
		EntryNode* temp = head;
		for (int i = 0; i < (int)limit; i++) {
			temp= temp->next;
		}
		if ((int)limit < b+1) {
			tail = temp->prev;
		}
		for (int i = limit; i < b; i++) {
			EntryNode* temp2 = temp->next;
			delete [] temp->entry;
			delete temp;
			temp = temp2;
		}
	}
	return *this;
}

void Intermediate::update(const string &attr, const string &new_value) const {
	int a = 0;
	for (int i = 0; i < numAttrs; i++) {
		if(attrs[i] != attr) {
			a += 1;
			continue;
		}
		else if(attrs[i] == attr) {
			break;
		}
	}

	if (a >= numAttrs) {
		return;
	}
	else {
		for(EntryNode* temp = head; temp->next!=nullptr; temp = temp->next) {
			temp->entry[a] = new_value;
		}
	}

}

void Intermediate::select(const string *attrs, int numAttrs) const {
	if(this->attrs == nullptr) {
		return;
	}
	if(attrs == nullptr) {
		numAttrs = this->numAttrs;
	}
	int selected[numAttrs];

	if (attrs == nullptr) {
		for(int i = 0; i <this->numAttrs; i++) {
			selected[i] = i;
		}
	}
	else {
		for (int i = 0; i < numAttrs; i++) {
			for (int j = 0; j < this->numAttrs; j++) {
				if(attrs[i] == this->attrs[j]){
					selected[i] = j;
				}
			}
		}
	}

	string result = "";
	for (EntryNode* temp = head; temp->next != nullptr; temp = temp->next) {
		for (int i = 0; i < numAttrs; i++) {
			result = result + temp->entry[selected[i]] + " | ";
		}
		result = result + "\n";
	}
	cout << result << endl;




}
