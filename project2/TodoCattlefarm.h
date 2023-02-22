/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef CATTLEFARM_H_
#define CATTLEFARM_H_

#include "Property.h"
extern const int CATTLEFARM_SIZE_X;
extern const int CATTLEFARM_SIZE_Y;

class Cattlefarm: public Property {
public:
    Cattlefarm(int x, int y);
    virtual bool checkEmployee(Employee* e) const override;
    virtual void upgrade() override;
    virtual int makeMoney() const override;
    // completely remove the Cow if it is not alive.
    void removeDiedCow();
	string getName() const override;
	char getSymbol() const override;
};

#endif /*CATTLEFARM_H_*/
