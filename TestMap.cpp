#include <iostream>

#include "Employee.h"
#include "Map.h"

typedef unsigned int ID;
typedef Map<ID, Employee> Database;

void addEmployees(Database& database) {
  database.add(761028073, Employee("Jan Kowalski", "salesman", 28));
  database.add(510212881, Employee("Adam Nowak", "storekeeper", 54));
  database.add(730505129, Employee("Anna Zaradna", "secretary", 32));
}

void modifyEmployees(Database& database) {
  Employee& pE = database.find(510212881);
  pE.position = "salesman";

  Employee& pE = database.find(761028073);
  pE.age = 29;
}

int main() {
  Database database;
  addEmployees(database);

  Database newDatabase = database;
  newDatabase.add(830505432, Employee("Ewa Nowak", "charwoman", 43));
  modifyEmployees(newDatabase);

  cout << "Original database:" << endl << database << endl;
  cout << "Modified database:" << endl << newDatabase << endl;

  database = newDatabase;

  cout << "Database after the assignment:" << endl << database << endl;
};
