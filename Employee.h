#include <iostream>

class Employee {
 public:
  string name;
  string position;
  int age;

  Employee(string name, string position, int age)
      : name(name), position(position), age(age) {}
};

ostream& operator<<(ostream& out, const Employee& e) {
  out << e.name << ", age " << e.age << " - " << e.position << endl;
};