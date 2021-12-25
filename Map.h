#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#define LOG true
#define SMALL_PRIME 1289
#define MID_PRIME 100003
#define BIG_PRIME 10000019

class KeyExistsError {};
class NoSuchKeyError {};
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

    V& get(K key) {
      Node* val = find(key);
      if (!val) throw NoSuchKeyError();
      return val->value;
    };

    bool exists(const K& key) const { return find(key) != NULL; };
    void add(K key, V value) {
      if (exists(key)) throw KeyExistsError();
      data = new Node{data, key, value};
    };

    void del(const K& key) {
      if (!exists(key)) return;
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
      Node* itr = data;
      while (itr != NULL) {
        count++;
        itr = itr->next;
      }
      return count;
    }
  };

 public:
  Map(unsigned size = SMALL_PRIME) : size(size) {
    data = new LinkedList[size];
  };
  ~Map() { delete[] data; };
  V& find(const K& key) { return data[hash(key)].get(key); }
  void add(K key, V value) { data[hash(key)].add(key, value); };
  void del(const K& key) { data[hash(key)].del(key); };
  bool exists(K key) const { return data[hash(key)].exists(key); };
  void printStats() {
    int elements = 0;
    int hashes = 0;
    for (int id = 0; id < (int)size; id++) {
      int howMany = data[id].length();
      if (howMany) {
        elements += howMany;
        hashes++;
      }
    }
    cout << "Computed " << elements << " elements into " << hashes << " hashes."
         << endl;
  }

  void testRotate() {
    unsigned toRotate = 0xff0000fe;
    const size_t s = sizeof(unsigned) * 8;
    bitset<s> org = toRotate;
    bitset<s> rot0 = rotate(toRotate, 0);
    bitset<s> rot2 = rotate(toRotate, 2);
    bitset<s> rot3 = rotate(toRotate, 3);
    bitset<s> rot9 = rotate(toRotate, 9);
    bitset<s> rot13 = rotate(toRotate, 13);

    cout << " (x): " << org << endl;
    cout << " (0): " << rot0 << endl;
    cout << " (2): " << rot2 << endl;
    cout << " (3): " << rot3 << endl;
    cout << " (9): " << rot9 << endl;
    cout << "(13): " << rot13 << endl;
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

  static string toString(K data) {
    ostringstream stream;
    stream << data;
    return stream.str();
  }

  unsigned strHash(K key) const {
    string data = toString(key);
    unsigned hash = 0;
    for (long unsigned id = 0; id < data.length(); id++) {
      hash += data[id] * 3 * (id + 1);
    }
    return hash % size;
  }

  static unsigned rotate(unsigned num, int bits) {
    unsigned msb = num << bits;
    unsigned lsb = num >> (sizeof(unsigned) * 8 - bits);
    return msb | lsb;
  }

  unsigned xorHash(K key) const {
    unsigned hash = 0;
    string data = toString(key);
    for (char c : data) {
      hash = rotate(hash, 3);
      hash = hash ^ c;
    }
    return hash % size;
  }

  unsigned hash(K key) const { return xorHash(key); };
  LinkedList* data;
};

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
}

void testStringKeys() {
  Map<string, double> test;
  test.add("A test", 1.1);
  test.add("Another test", 1.1);
  test.add("Just a dumb test", 1.1);
  test.add("Test", 1.1);
  test.add("Testt", 1.1);
  test.printStats();
}

void testRotate() {
  Map<int, int> m;
  m.testRotate();
}
