/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "Property.h"
#include "Employee.h"

void Property::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Cost:" << getCost() << endl;
    os << "Upgrade Cost:" << getUpgradeCost() << endl;
    os << "Level:" << getLevel() << endl;
    os << "# of Employee:" << getNumEmployee() << " / " << getMaxNumEmployee() << endl;
}

void Property::upgrade() {
    m_level++;
}

void Property::getConstEmployeeList(const Employee**& employee) const {
	if (m_num_employee == 0) {
		employee =nullptr;
		return;
	}
	employee = new const Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; i++)
		employee[i] = m_employee_list[i];
}

Property::Property(int cost, int upgrade_cost, int max_num_employee):
m_cost(cost), m_upgrade_cost(upgrade_cost), m_max_num_employee(max_num_employee) {
}

Property::~Property() {
    for(int i=0; i < m_num_employee; i++)
        delete m_employee_list[i];
    delete[] m_employee_list;
}

int Property::getCost() const {
    return m_cost;
}

int Property::getUpgradeCost() const {
    return m_upgrade_cost;
}

int Property::getLevel() const {
    return m_level;
}

int Property::getMaxNumEmployee() const {
    return m_max_num_employee;
}

void Property::setMaxNumEmployee(int max_num_employee) {
    m_max_num_employee = max_num_employee;
}
int Property::getNumEmployee() const {
    return m_num_employee;
}

// Helper function
void setEmployeeXY(Employee* employee, Property* property, int idx) {
    //set employee x, y
    int e_x, e_y, p_x, p_y, p_sz_x, p_sz_y;
    property->getXY(p_x, p_y);
    property->getSize(p_sz_x, p_sz_y);
    p_sz_x --; p_sz_x --;
    p_sz_y --; p_sz_y --;
    e_x = idx / p_sz_y + p_x + 1;
    e_y = idx % p_sz_y + p_y + 1;
    employee->setXY(e_x, e_y);
    return;
}

//perform shallow copying
bool Property::assignEmployee(Employee* employee) {
    // if full, return false
    if (m_num_employee == m_max_num_employee)
        return false;
    // if already exist, return false
    for(int i = 0; i < m_num_employee; i++)
        if (m_employee_list[i] == employee)
            return false;
    // if unsuitable, return false
    if (!checkEmployee(employee))
        return false;
    // copy the original employee list
    Employee** employee_list = new Employee*[m_num_employee + 1];
    for(int i = 0; i < m_num_employee; i++)
        employee_list[i] = m_employee_list[i];
    // Set employee xy and state
    setEmployeeXY(employee, this, m_num_employee);
    employee->setState(ObjectState::WORK);
    // update employee list
    employee_list[m_num_employee++] = employee;
    if (m_num_employee != 1)
        delete [] m_employee_list;
    m_employee_list = employee_list;
    return true;
}

bool Property::fireEmployee(Employee* employee) {
    if (employee == nullptr) return false;
    //No employee to fire
    if (m_num_employee <= 0) return false;
    //If only one employee
    if (m_num_employee == 1 && employee == m_employee_list[0]) {
        delete m_employee_list[0];
        m_num_employee = 0;
        delete [] m_employee_list;
        m_employee_list = nullptr;
        return true;
    }
    // It requires the assumption that employee has to be in the list.
    int i;
    for (i = 0; i < m_num_employee; i++)
        if (m_employee_list[i] == employee)
            break;
    //remove the i-th element from the list, remember to delete the employee and the old Employee list
    Employee** employee_list = new Employee* [--m_num_employee];
    for (int j = 0; j < m_num_employee; j++)
        employee_list[j] = m_employee_list[j];
    if (m_num_employee != i)
        employee_list[i] = m_employee_list[m_num_employee];
    delete m_employee_list[i];
    delete[] m_employee_list;
    m_employee_list = employee_list;

    // update x, y for all employee in the list
    for (int i=0; i<m_num_employee; i++)
        setEmployeeXY(m_employee_list[i], this, i);
    return true;
}
