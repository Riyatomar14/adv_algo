# 📌 HashMap (Hash Table) in Development

## 🔹 What is a HashMap?
A **HashMap** (also called **Hash Table** or **Dictionary**) is a data structure that stores **key–value pairs**.  
It uses a **hashing function** to map keys to memory locations, making insertion, deletion, and search **average O(1)** time.

---

## 🔎 Why Do We Need HashMap?  

Let’s compare with other data structures for **searching an element**:

---

### 1. Using **Linked List**  
- Suppose we store elements `[10, 20, 30, 40, 50]`.  
- To search `40`, we may need to traverse each element one by one.  

⏱️ **Time Complexity:**  
- Insertion: **O(1)** (at head)  
- Search: **O(n)**  
- Deletion: **O(n)**  

✅ Simple but **too slow** for large data.  

---

### 2. Using **Binary Search Tree (BST)**  
- If we insert elements into a **Balanced BST**, searching becomes faster.  

Example: 

<img width="187" height="132" alt="image" src="https://github.com/user-attachments/assets/a277acdc-a2b3-4116-8ef9-81b48b76377e" />


- To search `40`, we follow: `30 → 40`.  

⏱️ **Time Complexity:**  
- Insertion: **O(log n)** (balanced BST)  
- Search: **O(log n)**  
- Deletion: **O(log n)**  

✅ Faster, but still not the best.  

---

### 3. Using **Hash Table (HashMap)**  
- Idea: Use a **hash function** to compute an index from the key.  
- Example: `key % table_size`.  

If we insert:
<img width="158" height="151" alt="image" src="https://github.com/user-attachments/assets/5057b646-a296-467e-8ea3-ff51344150bd" />

- To search `40`, we directly compute index → O(1).  

⏱️ **Time Complexity (Average):**  
- Insertion: **O(1)**  
- Search: **O(1)**  
- Deletion: **O(1)**  

✅ Best choice for large datasets.  

---

## ⚡ Inbuilt C++ Implementations  

### 1. **`map`**
- Implemented using **Balanced BST (Red-Black Tree)**.  
- Keys stored in **sorted order**.  

⏱️ Time Complexity:  
- Insertion: **O(log n)**  
- Search: **O(log n)**  
- Deletion: **O(log n)**  

---

### 2. **`unordered_map`**
- Implemented using **Hash Table**.  
- Keys stored in **random order** (not sorted).  

⏱️ Time Complexity (Average Case):  
- Insertion: **O(1)**  
- Search: **O(1)**  
- Deletion: **O(1)**  

---

## ✅ Summary Table  

| Data Structure    | Insertion | Search   | Deletion | Order Maintained |
|-------------------|-----------|----------|----------|------------------|
| **Linked List**   | O(1)      | O(n)     | O(n)     | Insertion order  |
| **BST**           | O(log n)  | O(log n) | O(log n) | Sorted order     |
| **Hash Table**    | O(1)      | O(1)     | O(1)     | No order         |
| **map**           | O(log n)  | O(log n) | O(log n) | Sorted by key    |
| **unordered_map** | O(1)      | O(1)     | O(1)     | No order         |

---

## 🚀 Practical Examples with `unordered_map`

### 1. Basic Insertion
```cpp
#include <iostream>
#include <unordered_map>
#include <map>
using namespace std;

int main() {
    unordered_map<string, int> m;

    // Method 1: insert pair
    pair<string, int> p = make_pair("riya", 3);
    m.insert(p);

    // Method 2: direct pair
    pair<string, int> p2("apple", 2);
    m.insert(p2);

    // Method 3: using []
    m["my"] = 1;

    // Update Value
    m["my"] = 2;   // updates existing value
    cout << m["my"] << endl;      // ✅ returns 2
    cout << m.at("riya") << endl; // ✅ returns 3

    // Difference between [] and at()
    cout << m["unknownKey"] << endl;    // inserts {"unknownKey", 0}
    cout << m.at("unknownKey") << endl; // ✅ now works (prints 0)

    // If we do only at() without []:
    // cout << m.at("newKey") << endl; // ❌ throws out_of_range if key not present

    // Check Presence (count)
    cout << m.count("apple") << endl;   // 1 (present)
    cout << m.count("absent") << endl;  // 0 (absent)

    // Size of Map
    cout << m.size() << endl;

    // Erase Key
    m.erase("riya");
    cout << m.size() << endl;

    // Iterators with map vs unordered_map
    // * map       → elements printed in sorted order by key
    // * unordered → elements printed in random order
    cout << "\nIterating over unordered_map (unsorted order):\n";
    for (auto i:m){
        cout << i.first << " " << i.second << endl;
    }
    map<string, int> mp;
    mp["apple"] = 1;
    mp["banana"] = 2;
    mp["cherry"] = 3;

    cout << "\nIterating over map (sorted order):\n";
    map<string, int>::iterator it = mp.begin();
    while (it != mp.end()) {
        cout << it->first << " " << it->second << endl;
        it++;
    }

    return 0;
}
```
<img width="525" height="404" alt="image" src="https://github.com/user-attachments/assets/655fc27d-c679-463f-9c68-18f6dea126b2" />
