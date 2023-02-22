/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoCow.h"
#include <cstdlib>

// Cattlefarm cost 80 upgrade cost 16
// Cattlefarm size 6, 6
// Cattlefarm init max num. of employee is CATTLEFARM_MAX_NUM_EMPLOYEE_MIN
// Cattlefarm Upgrade:
//      level increases by 1;
//      max num. of employees increases by 1 until CATTLEFARM_MAX_NUM_EMPLOYEE_MAX
// Cattlefarm Makemoney:
//      min(num. of cows, num. of feeders in work) x level x 10;

const int CATTLEFARM_COST = 80;
const int CATTLEFARM_UPGRADE_COST = 16;
const int CATTLEFARM_SIZE_X = 6; const int CATTLEFARM_SIZE_Y = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MIN = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MAX = (CATTLEFARM_SIZE_X-2) * (CATTLEFARM_SIZE_Y-2);

// TODO: Start to implement your code.

string Cattlefarm::getName() const {
	return "Cattlefarm";
}

char Cattlefarm::getSymbol() const {
	return 'C';
}

Cattlefarm::Cattlefarm(int x, int y)
:Property(CATTLEFARM_COST, CATTLEFARM_UPGRADE_COST, CATTLEFARM_MAX_NUM_EMPLOYEE_MIN) {
    setXY(x, y);
    setSize(CATTLEFARM_SIZE_X, CATTLEFARM_SIZE_Y);
}

bool Cattlefarm::checkEmployee(Employee* e) const {
    if (e->getName() == "Feeder" || e->getName() == "Cow")
        return true;
    return false;
}

// #farmer x Area
int Cattlefarm::makeMoney() const {
    int sz_x, sz_y;
    // Employee** employee_list = getEmployeeList();
    const Employee** employee_list;
    getConstEmployeeList(employee_list);
    int num_cow=0;
    int num_feeder_in_work=0;
    for(int i = 0; i < getNumEmployee(); i++)
    {
        if (employee_list[i]->getState() == ObjectState::WORK
             && employee_list[i]->getName() == "Feeder" )
            num_feeder_in_work ++;
        if (employee_list[i]->getName() == "Cow" )
            num_cow ++;
    }
    getSize(sz_x, sz_y);
    delete []employee_list;
    return min(num_cow, num_feeder_in_work) * getLevel() * 10;
}

void Cattlefarm::removeDiedCow() {
    for(int i = getNumEmployee()-1; i >= 0; i--) {
        // Employee** employee_list = getEmployeeList();
        const Employee** employee_list;
        getConstEmployeeList(employee_list);
        Cow* c = dynamic_cast<Cow*>(const_cast<Employee*>(employee_list[i]));
        if (c != nullptr)
            if(!c->isAlive())
                fireEmployee(c);
        delete []employee_list;
    }
}

void Cattlefarm::upgrade() {
    Property::upgrade();
    int new_max_num_employee =
        (getMaxNumEmployee() >= CATTLEFARM_MAX_NUM_EMPLOYEE_MAX) ?
        CATTLEFARM_MAX_NUM_EMPLOYEE_MAX : getMaxNumEmployee()+1;
    setMaxNumEmployee(new_max_num_employee);
}
