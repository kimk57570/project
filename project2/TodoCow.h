/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef COW_H_
#define COW_H_

#include "Employee.h"

class Cow: public Employee {
public:
    Cow();
    virtual ~Cow() = default;
	string getName() const override;
	char getSymbol() const override;
    // Return true if workage < lifespan.
    bool isAlive() const;
    // Get lifespan.
    int getLifespan() const;
private:
    const int m_lifespan;
    virtual void writeToStream(ostream& os) const override;
};

#endif /*COW_H_*/
