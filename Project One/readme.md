# Project One Data Structure Analysis

In Project One, we implemented three different data structures: a dynamic array (vector), a hash table, and a binary search tree (BST). Below is an analysis of their runtime and memory characteristics:

## Dynamic Array (Vector)

**Runtime Complexity:**

1. **Insertion at the End (Amortized):** Inserting an element at the end of a dynamic array (vector) is an amortized constant-time operation, O(1). It's fast on average but may occasionally become O(n) when resizing is required.

2. **Access (Random):** Accessing an element by index in a dynamic array is a constant-time operation, O(1). You can directly access elements using their indices.

3. **Deletion (at End):** Removing an element from the end of a dynamic array is an amortized constant-time operation, O(1), like insertion. In some cases, when resizing is needed, it becomes O(n).

4. **Search (Linear):** Searching for an element in an unsorted dynamic array is a linear-time operation, O(n), as you may need to traverse the entire array.

**Memory Complexity:**

Dynamic arrays (vectors) consume memory based on the number of elements they hold. Memory consumption is proportional to the number of elements, with additional memory allocated for potential resizing.

## Hash Table

**Runtime Complexity:**

1. **Insertion:** Inserting an element into a hash table has an average-case constant-time complexity, O(1), for most operations. In rare cases, when hash collisions occur, the time complexity can degrade to O(n), where 'n' is the number of elements in the table. Properly designed hash functions and collision resolution strategies minimize the likelihood of collisions.

2. **Access (Average):** Accessing an element by key in a hash table has an average-case constant-time complexity, O(1), assuming a well-distributed set of keys and a good hash function.

3. **Deletion:** Deleting an element from a hash table has a similar average-case constant-time complexity, O(1), for the same reasons as insertion.

4. **Search (Average):** Searching for an element in a hash table, given its key, also has an average-case constant-time complexity, O(1), assuming an evenly distributed set of keys.

**Memory Complexity:**

Hash tables consume memory based on the number of key-value pairs they store. Memory consumption is proportional to the number of elements, and extra memory may be allocated to handle collisions.

## Binary Search Tree (BST)

**Runtime Complexity:**

1. **Insertion (Average):** Inserting an element into a balanced binary search tree (BST) has an average-case time complexity of O(log n), where 'n' is the number of elements in the tree. In the worst case, when the tree becomes unbalanced, the complexity can degrade to O(n), making it important to maintain balance.

2. **Access (Average):** Accessing an element in a balanced BST has an average-case time complexity of O(log n), which is efficient due to the logarithmic nature of the tree.

3. **Deletion (Average):** Deleting an element from a balanced BST also has an average-case time complexity of O(log n).

4. **Search (Average):** Searching for an element in a balanced BST, given the key, has an average-case time complexity of O(log n).

**Memory Complexity:**

Binary search trees consume memory based on the number of elements they store. Memory consumption is proportional to the number of elements. In the worst case, if the tree is completely unbalanced, it can consume memory similar to that of a linked list, leading to a memory overhead of O(n).

## Summary

- **Dynamic Array (Vector):**
  - Efficient for random access and insertion at the end.
  - Linear time for searching (unsorted) and occasional resizing.

- **Hash Table:**
  - Efficient for average-case insertion, access, and deletion (O(1)).
  - May degrade to linear time in rare cases due to collisions.

- **Binary Search Tree:**
  - Efficient for average-case access, insertion, and deletion (O(log n)).
  - May degrade to linear time (O(n)) in the worst case if unbalanced.

The choice of data structure depends on the specific use case and the types of operations you need to perform. Vectors are great for random access and dynamic resizing, hash tables are efficient for fast average-case access and operations, and balanced binary search trees are suitable for maintaining order and efficient search operations.