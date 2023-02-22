/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef FARMER_H_
#define FARMER_H_

#include "Employee.h"


class Farmer : public Employee
{
public:
	Farmer();

	virtual ~Farmer() = default;

	string getName() const override;

	char getSymbol() const override;


};


#endif /*FARMER_H_*/
