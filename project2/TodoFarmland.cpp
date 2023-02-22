/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoFarmland.h"
#include "Employee.h"
#include <cstdlib>

// Farmland cost 50 upgrade cost 10
// Farmland size 5, 5
// Farmland init max num. of employee is FARMLAND_MAX_NUM_EMPLOYEE_MIN
// Farmland Upgrade:
//      level increases by 1;
//      max num. of employee increases by 1 until FARMLAND_MAX_NUM_EMPLOYEE_MAX
// Farmland Makemoney:
//      getRandInt(0, num. of employees in work x 2 + num. of farmers in work x 6 + level x 3)

const int FARMLAND_COST = 50;
const int FARMLAND_UPGRADE_COST = 10;
const int FARMLAND_SIZE_X = 5; const int FARMLAND_SIZE_Y = 5;
const int FARMLAND_MAX_NUM_EMPLOYEE_MIN = 3;
const int FARMLAND_MAX_NUM_EMPLOYEE_MAX = (FARMLAND_SIZE_X-2) * (FARMLAND_SIZE_Y-2);

#ifdef __HARVEST_MOON_DEBUG__
    inline void debug_getRandInt(string s) {cout << s << endl;};
#else
    inline void debug_getRandInt(string s) {};
#endif

//return random int in [low, high).
int getRandInt(int low, int high) {
    int res = rand() % high + low;
    //debug_getRandInt("getRandInt: low is "+to_string(low));
   // debug_getRandInt("getRandInt: high is "+to_string(high));
  //  debug_getRandInt("getRandInt: res is "+to_string(res));
    return res;
}

string Farmland::getName() const {
	return "Farmland";
}

char Farmland::getSymbol() const {
	return 'R';
}

Farmland::Farmland(int x, int y)
:Property(FARMLAND_COST, FARMLAND_UPGRADE_COST, FARMLAND_MAX_NUM_EMPLOYEE_MIN) {
    setXY(x, y);
    setSize(FARMLAND_SIZE_X, FARMLAND_SIZE_Y);
}

bool Farmland::checkEmployee(Employee* e) const {
    if (e->getName() == "Farmer" || e->getName() == "Employee")
        return true;
    return false;
}

int Farmland::makeMoney() const  {
    int sz_x, sz_y;
    const Employee** employee_list;
    getConstEmployeeList(employee_list);
    int num_employee_in_work=0;
    int num_farmer_in_work=0;
    for(int i = 0; i < getNumEmployee(); i++)
    {
        if (employee_list[i]->getState() == ObjectState::WORK
             && employee_list[i]->getName() == "Employee" )
            num_employee_in_work ++;
        if (employee_list[i]->getState() == ObjectState::WORK
             && employee_list[i]->getName() == "Farmer" )
            num_farmer_in_work ++;
    }
    getSize(sz_x, sz_y);
    delete []employee_list;
    return getRandInt(0, num_employee_in_work*2 + num_farmer_in_work * 6 + getLevel()*3);
}

void Farmland::upgrade() {
    Property::upgrade();
    int new_max_num_employee =
        (getMaxNumEmployee() >= FARMLAND_MAX_NUM_EMPLOYEE_MAX) ?
        FARMLAND_MAX_NUM_EMPLOYEE_MAX : getMaxNumEmployee()+1;
    setMaxNumEmployee(new_max_num_employee);
}






