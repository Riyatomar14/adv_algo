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
<img width="546" height="511" alt="image" src="https://github.com/user-attachments/assets/c51e598e-19b9-4e65-9016-89e33aeec125" />

# 📘 Hashing – Collision Handling and Analysis

---

## 1. Collision Handling  

Collisions occur when two keys are mapped to the same index in a hash table.  
To resolve this, we use **collision handling techniques**:

### 🔹 1. Open Addressing (Chaining)  
- Each index in the table stores a **list (linked list / dynamic array)**.  
- If multiple elements map to the same index, they are placed inside that list.  
- **Insertion, Search, Deletion** → Average **O(1)** (if Load Factor is small).  
- Example:
  
<img width="250" height="32" alt="image" src="https://github.com/user-attachments/assets/70873d22-1e72-4b95-9851-ba4ea3454c84" />


✅ Easy insertion/deletion.  
⚠️ Needs extra memory for linked lists.  
---

### 🔹 2. Closed Addressing (Probing Methods)  
Here, all elements are stored **directly inside the table**.  
If a slot is occupied, probing is used to find the next free slot.  

1. **Linear Probing**  
 - Place element in the next empty cell (step = 1).  
 - Problem: Clustering (long chains of occupied cells).  
 - Formula:  
   <img width="370" height="81" alt="image" src="https://github.com/user-attachments/assets/608b78a8-b772-4824-91dc-29f3970356eb" />


2. **Quadratic Probing**  
 - Use quadratic jumps to reduce clustering.  
 - Formula:  
  <img width="293" height="55" alt="image" src="https://github.com/user-attachments/assets/51114793-3f5c-4e7b-92c3-c50243dd755b" />


3. **Double Hashing**  
 - Uses two hash functions to calculate probe sequence.  
 - Formula:  
<img width="397" height="234" alt="image" src="https://github.com/user-attachments/assets/b93a8594-bce3-428b-b47e-86dd25fbc6b4" />
<img width="705" height="392" alt="image" src="https://github.com/user-attachments/assets/9f89049f-41dc-42f1-9c72-e979186dd2cc" />

 - Reduces clustering efficiently.  

---

## 2. Insertion, Deletion & Search  

- **Insertion:**  
- Average Time Complexity: **O(1)**  
- May require **rehashing** if Load Factor exceeds threshold.  

- **Deletion:**  
- In Chaining → remove from linked list.  
- In Probing → mark slot as "deleted" (special marker).  

- **Search:**  
- Average Case: **O(1)**  
- Worst Case: **O(n)** (when collisions are poorly handled).  

---

## 3. Load Factor (LF)  

<img width="472" height="86" alt="image" src="https://github.com/user-attachments/assets/575fc219-de54-4575-b4cd-ed8693ce963a" />


- Ideal: **LF < 0.7** for good performance.  
- If LF grows too high → collisions increase → slower operations.  

---

## 4. Rehashing  

- Triggered when **LF > threshold (e.g., 0.7)**.  
- Steps:  
1. Create a new hash table (usually double the size).  
2. Recompute positions of all existing elements.  
3. Insert them into the new table.  

Keeps performance near **O(1)**.  

---

## 5. Complexity Analysis  

- **Hash Computation (H.C):**  
- Depends on key length `k`.  
- Time Complexity = **O(k)**.  
- If number of elements `n >> k` → treat hashing as **O(1)**.  

- **Insertion / Search / Deletion:**  
- Average Case: **O(1)**  
- Worst Case: **O(n)** (heavy clustering or poor hash function).  

---

## ✅ Summary  

- **Collision Handling:**  
- **Open Addressing (Chaining)** → external lists.  
- **Closed Addressing (Linear, Quadratic, Double Hashing)** → probing inside table.  
- **Load Factor (LF < 0.7)** keeps collisions low.  
- **Rehashing** ensures efficient performance.  
- With a good hash function: **Insertion, Deletion, Search ≈ O(1)** average.  

---




