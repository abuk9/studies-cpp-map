#include <iostream>
using namespace std;

class KeyError {};

template <class K, class V>
class Map {
  class LinkedList {
   private:
    struct Node {
      Node* next{NULL};
      K key;
      V value;
    };
    Node* data{NULL};
    Node* find(const K& key) const {
      Node* itr = data;
      while (itr) {
        if (itr->key == key) return itr;
        itr = itr->next;
      }
      return NULL;
    };

   public:
    LinkedList(){};
    ~LinkedList() {
      while (data != NULL) {
        Node* next = data->next;
        delete data;
        data = next;
      }
    };

    V& get(K key) { return find(key)->value; };
    bool exists(const K& key) const { return find(key) != NULL; };
    void add(K key, V value) { data = new Node{data, key, value}; };
    void del(const K& key) {
      Node* found = find(key);
      if (!found) throw KeyError();
      if (!(found->next)) {
        delete found;
        return;
      }

      Node* next = found->next;
      found->next = next->next;
      found->key = next->key;
      found->value = next->value;
      delete next;
    };
    int length() {
      int count = 0;
      while (data != NULL) {
        Node* next = data->next;
        count++;
        data = next;
      }
      return count;
    }
  };

 public:
  Map(unsigned size = 1000) : size(size) { data = new LinkedList[size]; };
  ~Map() { delete[] data; };
  V& find(const K& key) const { return data[0].get(key); }
  void add(K key, V value) { data[0].add(key, value); };
  void del(const K& key) { data[0].del(key); };
  bool exists(K key) const { return data[0].exists(key); };
  int lengthOf(int id) const { return data[id].length(); }

 private:
  unsigned size;
  unsigned hash(K key) const;
  LinkedList* data;
};

int main() {
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
  cout << test.lengthOf(0) << endl;
  return 0;
}