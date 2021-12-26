#include <cassert>
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
  {
    Employee& E = database.find(510212881);
    E.position = "salesman";
  }
  {
    Employee& E = database.find(761028073);
    E.age = 29;
  }
}

void defaultTest() {
  Database database;
  addEmployees(database);
  cout << "Original database:" << endl << database << endl;

  // Database newDatabase = database;
  // Employee e("Ewa Nowak", "charwoman", 42);
  // newDatabase.add(830505432, e);
  // modifyEmployees(newDatabase);
  // cout << "Modified database:" << endl << newDatabase << endl;

  // database = newDatabase;
  // cout << "Database after the assignment:" << endl << database << endl;
}

void testIntKeys() {
  Map<int, double> test;
  test.add(1, 1.1);
  test.add(2, 2.2);
  test.add(3, 3.3);
  test.add(4, 4.4);

  cout << test.find(1) << endl;
  cout << test.find(2) << endl;
  cout << test.find(3) << endl;
  cout << test.find(4) << endl;

  cout << test.exists(2) << endl;
  test.del(2);
  cout << test.exists(2) << endl;
  test.printStats();
  cout << test << endl;
}

void testStringKeys() {
  Map<string, double> test;
  test.add("A test", 1.1);
  test.add("Another test", 1.1);
  test.add("Just a dumb test", 1.1);
  test.add("Test", 1.1);
  test.add("Testt", 1.1);
  test.printStats();
  cout << test << endl;
}

void testRotate() {
  Map<int, int> m;
  m.testRotate();
}

void testEdgeCases() {
  Map<int, double> m;
  m.add(3, 3.1);
  m.add(4, 4.1);
  m.add(5, 5.1);

  assert(m.exists(5));
  try {
    m.add(5, 5.2);
    assert(false);
  } catch (KeyExistsError e) {
    cout << "KeyExistsError works" << endl;
  }

  assert(m.exists(3));
  m.del(3);
  assert(!m.exists(3));
  m.del(3);  // Testing if this is indeed a no-op
  assert(!m.exists(3));

  try {
    m.find(3);
    assert(false);
  } catch (NoSuchKeyError e) {
    cout << "NoSuchKeyError works" << endl;
  }
  cout << endl;
}

int main() {
  testIntKeys();
  testStringKeys();
  testEdgeCases();
  defaultTest();
}
