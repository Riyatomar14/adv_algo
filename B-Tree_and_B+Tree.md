# 🌳 B-Tree and B+ Tree Notes

## 📘 B-Tree

### 🔹 Definition
A **B-Tree** is a balanced multi-way search tree in which:  
- All leaves appear at the same level.  
- Data can be stored in **both internal nodes and leaf nodes**.  

---

### 🔹 Node Structure

- **Block Pointer (BP)** → Points to the **child node**.  
- **Key** → Actual key value stored.  
- **Data Pointer (DP)** → Points to the **record in secondary memory (disk)**.  

**Format**:  
[BP | Key | DP | BP | Key | DP ... | BP]

---

### 🔹 Order & Capacity
- **Block Pointers** = Order of the tree = `p`  
- **Keys** = `p - 1`  
- **Data Pointers** = Equal to number of keys  

---

### 🔹 Children & Keys Rules

| Node Type        | Children (Min–Max)        | Keys (Min–Max)           |
|------------------|----------------------------|---------------------------|
| **Root**         | 2 to `p` (if not leaf)    | 1 to `p - 1`              |
| **Intermediate** | ⌈p/2⌉ to `p`              | ⌈p/2⌉ - 1 to `p - 1`     |
| **Leaf**         | 0 children                | Same as Intermediate Node |

✅ Example (Order = 5 → `p = 5`):  
- **Root** → Children = 2–5, Keys = 1–4  
- **Intermediate** → Children = 3–5, Keys = 2–4  
- **Leaf** → Keys = 2–4  

---

### 🔹 Rules
1. Root has at least **2 children** if it is not a leaf.  
2. Every node has at most **p children**.  
3. Every intermediate node has at least **⌈p/2⌉ children**.  
4. Keys inside a node are always **sorted**.  
5. Search may occur in **internal or leaf nodes**.  

---

### 🔹 Numerical Example (Order = 23, Block size = 512B)

- Key size = 10B  
- DP size = 8B  
- BP size = 5B  

Formula:  
\[
n × BP + (n-1)×(Key + DP) <= 512
\]

Substitute:  
\[
n × 5 + (n-1)(10+8) <= 512
\]

\[
23n <= 530
\]

✅ **Order of B-Tree = 23**

---

## 📘 B+ Tree

### 🔹 Definition
A **B+ Tree** is an extension of B-Tree where:  
- Data is stored **only in leaf nodes**.  
- Internal nodes act as **index nodes**.  
- Leaf nodes are **linked for range queries**.  

---

### 🔹 Node Structure

- **Block Pointer (BP)** → Points to the **child node**.  
- **Key** → Used for **indexing/searching**.  
- **Data Pointer (DP)** → Appears **only in leaf nodes**, points to **records in secondary memory (disk)**.  

**Internal Node Format**:  
[BP | Key | BP | Key ... | BP]

**Leaf Node Format**:  

---

### 🔹 Order & Capacity
- **Block Pointers (internal)** = Order of tree = `p`  
- **Keys (internal)** = `p - 1`  
- **Data Pointers (leaf)** = Equal to number of keys  

---

### 🔹 Children & Keys Rules

| Node Type        | Children (Min–Max)        | Keys (Min–Max)           |
|------------------|----------------------------|---------------------------|
| **Root**         | 2 to `p` (if not leaf)    | 1 to `p - 1`              |
| **Intermediate** | ⌈p/2⌉ to `p`              | ⌈p/2⌉ - 1 to `p - 1`     |
| **Leaf**         | 0 children (linked)       | ⌈p/2⌉ - 1 to `p - 1`     |

---

### 🔹 Rules
1. Root has at least **2 children** if it is not a leaf.  
2. Internal nodes contain **only keys and block pointers**.  
3. Leaf nodes contain **all data pointers**.  
4. Leaf nodes are **linked together**.  
5. Range queries are efficient because of **linked leaves**.  

---

### 🔹 Numerical Example (Block size = 512B)

- Key size = 10B  
- DP size = 8B  
- BP size = 5B  

**For Internal Node**:  
\[
n × BP + (n-1) × Key <= 512
\]

\[
n×5+(n-1) ×10<=512
\]

\[
15n<=502
\]

✅ **Order of Internal Node = 34**

---

**For Leaf Node**:  
\[
n × (Key + DP) + BP <= 512
\]

\[
18n +5 <=512
\]

✅ **Leaf Node capacity = 28 keys**

---

## 🔑 Differences between B-Tree and B+ Tree

| Feature              | B-Tree                               | B+ Tree                                  |
|----------------------|---------------------------------------|-------------------------------------------|
| **Data storage**     | Internal + leaf nodes                | Only in leaf nodes                        |
| **Search speed**     | Slower                               | Faster (index + linked leaves)            |
| **Redundant keys**   | No redundancy                        | Keys may repeat (for indexing)            |
| **Leaf linkage**     | Not linked                           | Linked (efficient range queries)          |
| **Use cases**        | Older DB, file systems               | Modern DB & file systems (MySQL, NTFS)    |
