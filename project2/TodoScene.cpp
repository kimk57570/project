/*
 * File Created: Mon Mar 16 2020
 * Author:
 * SID:
*/

#include "Scene.h"
#include "Property.h"
#include "TodoFarmland.h"
#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoFarmer.h"
#include "TodoFeeder.h"
#include "TodoCow.h"

const int SCENE_W = 45;
const int SCENE_H = 10;
const int PROPERTY_X = 35;
const int SCENE_INIT_MONEY = 200;

Scene::Scene()
: m_objects(nullptr), m_num_objects(0), m_money(SCENE_INIT_MONEY) {
    nextRound();
}

Scene::~Scene() {
    //shallowremove employees
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::EMPLOYEE)
            shallowRemoveEmployee(dynamic_cast<Employee*>(m_objects[i]));
    }
    // remove properties
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::PROPERTY)
            delete m_objects[i];
    }
    delete[] m_objects;
}

void Scene::shallowRemoveEmployee(Employee* e) {
    if (m_num_objects <= 0) return;
    if (m_num_objects == 1 && e == m_objects[0]) {
        m_num_objects = 0;
        m_objects = nullptr;
        return;
    }
    int i;
	for (i = 0; i < m_num_objects; i++) {
		if (m_objects[i] == e)
			break;
	}
    Object ** newObjects = new Object*[m_num_objects--];
	for (int j = 0; j < m_num_objects; j++)
		newObjects[j] = m_objects[j];
	if (m_num_objects != i)
		newObjects[i] = m_objects[m_num_objects];
    delete [] m_objects;
    m_objects = newObjects;
}

bool Scene::checkOverlap(const Property* newproperty) {
    int x, y, sz_x, sz_y;
    newproperty->getXY(x, y);
    newproperty->getSize(sz_x, sz_y);
    for(int xx=x; xx<x+sz_x; xx++)
        for(int yy=y; yy<y+sz_y; yy++)
            if(getObjectAt(xx, yy) != nullptr) return true;
    return false;
}


void Scene::addProperty(int property, int x, int y) {
    Property* newProperty = nullptr;
    switch(property) {
    case FARMLAND:
        newProperty = new Farmland(x,y);
        break;
    case CATTLEFARM:
        newProperty = new Cattlefarm(x, y);
        break;
    }
    if (newProperty == nullptr) return;
    if (newProperty->getCost() > m_money || checkOverlap(newProperty)) {
        delete newProperty;
        return;
    }
    addObject(newProperty);
    m_money -= newProperty->getCost();
}


bool Scene::hire(Property* p, int employee) {
    Employee* newEmployee = nullptr;
    switch(employee){
    case EMPLOYEE:
        newEmployee = new Employee();
        break;
    case FARMER:
        newEmployee = new Farmer();
        break;
    case FEEDER:
        newEmployee = new Feeder();
        break;
    case COW:
        newEmployee = new Cow();
        break;
    }
    if (newEmployee == nullptr) return false;
    if (newEmployee->getCost() > m_money || ! p->assignEmployee(newEmployee)) {
        delete newEmployee;
        return false;
    }
    addObject(newEmployee);
    m_money -= newEmployee->getCost();
    return true;
}


Object* Scene::getObjectAt(int s_x, int s_y) const {
	int x, y, sz_x, sz_y;
    // If employee is at s_x, s_y, get employee
    // else, get property
    // otherwise return null
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	return nullptr;
}

//perform shallow copying
void Scene::addObject(Object* newobj) {
	Object** newobjects = new Object*[m_num_objects + 1];
	for (int i = 0; i < m_num_objects; i++)
		newobjects[i] = m_objects[i];
	newobjects[m_num_objects++] = newobj;
	if (m_num_objects != 1)
		delete [] m_objects;
	m_objects = newobjects;
}

void Scene::getConstObjects(const Object**& obj, int& count) const {
	count = m_num_objects;
	if (m_num_objects == 0) {
		obj =nullptr;
		return;
	}
	obj = new const Object*[m_num_objects];
	for (int i = 0; i < m_num_objects; i++)
		obj[i] = m_objects[i];
}

bool Scene::isGameOver() const {
	return m_money < 0;
}

void Scene::removeProperty(Property* p) {
	if (m_num_objects <= 0) return;
    // shallow remove p's employees
    for(int j = 0; j < p->getNumEmployee(); j++) {
        const Employee** employee_list;
        p->getConstEmployeeList(employee_list);
        shallowRemoveEmployee(const_cast<Employee*>(employee_list[j]));
        delete []employee_list;
    }
    if (m_num_objects == 1 && p == m_objects[0]) {
        delete m_objects[0];
        m_num_objects = 0;
        delete [] m_objects;
        m_objects = nullptr;
        return;
    }
    int i;
	for (i = 0; i < m_num_objects; i++) {
		if (m_objects[i] == p)
			break;
	}
	Object ** newObjects = new Object*[--m_num_objects];
	for (int j = 0; j < m_num_objects; j++)
		newObjects[j] = m_objects[j];
	if (m_num_objects != i)
		newObjects[i] = m_objects[m_num_objects];

	delete m_objects[i];
	delete [] m_objects;
	m_objects = newObjects;
}

void Scene::nextRound() {
    //make money
	for (int i = 0; i < m_num_objects; i++) {
		Property* p = dynamic_cast<Property*>(m_objects[i]);
		if (p != nullptr)
            m_money += p->makeMoney();
	}
    //compute Salary, update employee work age, update employee status
	for (int i = 0; i < m_num_objects; i++) {
		Employee* e = dynamic_cast<Employee*>(m_objects[i]);
		if (e != nullptr)
        {
            m_money -= e->getSalary();
            e->updateWorkAge();
            e->updateState();
        }
	}
    //check Cow shallow remove
	for (int i = m_num_objects-1; i >= 0; i--) {
		Cow* c = dynamic_cast<Cow*>(m_objects[i]);
		if (c != nullptr)
        {
            if(!c->isAlive())
                shallowRemoveEmployee(dynamic_cast<Employee*>(m_objects[i]));
        }
	}
    //check CattleFarm
	for (int i = 0; i < m_num_objects; i++) {
		Cattlefarm* cf = dynamic_cast<Cattlefarm*>(m_objects[i]);
		if (cf != nullptr)
            cf->removeDiedCow();
	}
}

bool Scene::upgrade(Property* p) {
	if (p == nullptr || m_money < p->getUpgradeCost())
		return false;
	m_money -= p->getUpgradeCost();
	p->upgrade();
	return true;
}

bool Scene::fire(Employee* e) {
    if (e == nullptr)
        return false;
    // get X, Y of e
    int e_x, e_y;
    e->getXY(e_x, e_y);
    // find the property at (X, Y)
    int x, y, sz_x, sz_y;
    Object* p = nullptr;
    for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( e_x >= x && e_x < x + sz_x && e_y >= y && e_y < y + sz_y)
			p = m_objects[i];
	}
    if (p == nullptr)
        return false;
    else {
        shallowRemoveEmployee(e);
        return dynamic_cast<Property*>(p)->fireEmployee(e);
    }
}
