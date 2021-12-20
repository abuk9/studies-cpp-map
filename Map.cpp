#include <iostream>
using namespace std;
#define LOG false
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
    Node* findParent(const K& key) const {
      if (!data) return NULL;
      Node* parent = data;
      while (parent->next) {
        if (parent->next->key == key) return parent;
        parent = parent->next;
      }
      return NULL;
    }

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
    // TODO: protect against inserting a key twice
    void add(K key, V value) { data = new Node{data, key, value}; };
    void del(const K& key) {
      if (data->key == key) {
        Node* temp = data->next;
        delete data;
        data = temp;
      } else {
        Node* parent = findParent(key);
        Node* grandChild = parent->next->next;
        delete parent->next;
        parent->next = grandChild;
      }
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
  V& find(const K& key) { return data[hash(key)].get(key); }
  void add(K key, V value) { data[hash(key)].add(key, value); };
  void del(const K& key) { data[hash(key)].del(key); };
  bool exists(K key) const { return data[hash(key)].exists(key); };
  void printStats() {
    int elements = 0;
    int hashes = 0;
    for (int id = 0; id < size; id++) {
      int howMany = data[id].length();
      if (howMany) {
        elements += howMany;
        hashes++;
      }
    }
    cout << "Computed " << elements << " elements into " << hashes << " hashes."
         << endl;
  }

 private:
  unsigned size;
  unsigned noHash(K key) const { return 0; }
  unsigned modHash(K key) const {
    unsigned long long* bits = (unsigned long long*)&key;
    unsigned out = *bits % size;
    if (LOG) cout << "Hash for " << key << ": " << out << endl;
    return out;
  };

  unsigned hash(K key) const { return modHash(key); };
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
  test.printStats();
  return 0;
}