//**********************************************************************************
// Employee class definition
// Author: Erick Ramos
// Date: December 11, 2017
//***********************************************************************************
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee {
  string name;
  int salary, seniority;
  
  public:
  
  Employee(string n, double dollars, int level){
      name = n;
      salary = dollars;
      seniority = level;
  }
  
  const string & getName() const{
      return name;
  }
  
  bool operator == (const Employee & rhs) const{
      return getName() == rhs.getName();
  }
  
  bool operator != (const Employee & rhs) const{
      return !(*this == rhs);
  }
  
  string toString() {
      return name + ": $" + to_string(salary) + ".00, level: " + to_string(seniority);
  }
};

#endif
