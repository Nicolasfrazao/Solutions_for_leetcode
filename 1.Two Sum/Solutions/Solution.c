//Here is the solutions in c from the code 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 *  bruteforce
 *
 *  Description:
 *  
 *  This function uses a brute force approach to find two elements in an array
 *  that add up to a given target value. It iterates through the array and checks
 *  every pair of elements to see if they add up to the target value. If they do,
 *  it returns the indices of the two elements. If not, it returns -1.
 *
 *  Parameters:
 *  
 *  nums (int*): The array to search for the two elements.
 *  numsSize (int): The size of the array.
 *  target (int): The target value to search for.
 *  returnSize (int*): The number of elements in the returned array.
 *
 *  Returns:
 *  
 *  int*: An array containing the indices of the two elements that add up to the target value. If no such elements are found, returns NULL.
 */
int bruteforce(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    result[0] = 0;
    result[1] = 1;
    return result;
}

//---------------------------------------------------------------------------------//

/*
 *  EMPTY_SLOT
 *
 *  Description:
 *  
 *  This constant is used to initialize the hash table. It is used to indicate that
 *  a slot in the hash table is empty.
 */
#define EMPTY_SLOT -1000000

/*
 *  HashEntry
 *
 *  Description:
 *  
 *  This structure represents an entry in the hash table. It contains the key
 *  (the value from the array) and the value (the index of that value in the array).
 */
typedef struct {
    int key;   // The value from the array
    int value; // The index of that value
} HashEntry;

/*
 *  HashTable
 *
 *  Description:
 *  
 *  This structure represents the hash table. It contains a pointer to an array of
 *  HashEntries and the size of the array.
 */
typedef struct {
    HashEntry* entries;
    int size;
} HashTable;

/*
 *  hash
 *
 *  Description:
 *  
 *  This function is used to map the keys to valid indices in the hash table. It
 *  takes into account negative values and ensures that the result is always positive.
 *
 *  Parameters:
 *  
 *  key (int): The key to map to an index.
 *  size (int): The size of the hash table.
 *
 *  Returns:
 *  
 *  int: The mapped index.
 */
int hash(int key, int size) {
    return (abs(key) % size);  // Ensures that the result is always positive
}

/*
 *  createHashTable
 *
 *  Description:
 *  
 *  This function initializes the hash table. It allocates memory for the hash
 *  table and initializes all entries as empty (using the EMPTY_SLOT constant).
 *
 *  Parameters:
 *  
 *  size (int): The size of the hash table.
 *
 *  Returns:
 *  
 *  HashTable*: A pointer to the initialized hash table.
 */
HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->entries = (HashEntry*)malloc(size * sizeof(HashEntry));
    table->size = size;
    
    // Initialize all entries as empty (use sentinel value)
    for (int i = 0; i < size; i++) {
        table->entries[i].key = EMPTY_SLOT;
    }

    return table;
}

/*
 *  insert
 *
 *  Description:
 *  
 *  This function inserts a key-value pair into the hash table. It uses linear
 *  probing to handle collisions.
 *
 *  Parameters:
 *  
 *  table (HashTable*): The hash table to insert the key-value pair into.
 *  key (int): The key to insert.
 *  value (int): The value associated with the key.
 */
void insert(HashTable* table, int key, int value) {
    int index = hash(key, table->size);
    // Handle collisions using linear probing
    while (table->entries[index].key != EMPTY_SLOT && table->entries[index].key != key) {
        index = (index + 1) % table->size; // Linear probing
    }
    table->entries[index].key = key;
    table->entries[index].value = value;
}

/*
 *  find
 *
 *  Description:
 *  
 *  This function finds a value (index) by key in the hash table.
 *
 *  Parameters:
 *  
 *  table (HashTable*): The hash table to search in.
 *  key (int): The key to search for.
 *
 *  Returns:
 *  
 *  int: The index associated with the key, or -1 if the key is not found.
 */
int find(HashTable* table, int key) {
    int index = hash(key, table->size);
    while (table->entries[index].key != EMPTY_SLOT) {
        if (table->entries[index].key == key) {
            return table->entries[index].value;
        }
        index = (index + 1) % table->size;
    }
    return -1; // Key not found
}

/*
 *  freeHashTable
 *
 *  Description:
 *  
 *  This function frees the memory allocated for the hash table.
 *
 *  Parameters:
 *  
 *  table (HashTable*): The hash table to free.
 */
void freeHashTable(HashTable* table) {
    free(table->entries);
    free(table);
}

/*
 *  opitmalSolution
 *
 *  Description:
 *  
 *  This function uses a hash table to find two elements in an array that add up
 *  to a given target value. It iterates through the array and checks every element
 *  against the hash table to see if it has a complement that adds up to the
 *  target value. If it does, it returns the indices of the two elements. If not,
 *  it returns -1.
 *
 *  Parameters:
 *  
 *  nums (int*): The array to search for the two elements.
 *  numsSize (int): The size of the array.
 *  target (int): The target value to search for.
 *  returnSize (int*): The number of elements in the returned array.
 *
 *  Returns:
 *  
 *  int*: An array containing the indices of the two elements that add up to the target value. If no such elements are found, returns NULL.
 */
int opitmalSolution(int* nums, int numsSize, int target, int* returnSize){
     HashTable* table = createHashTable(numsSize * 2);

    // Allocate memory for the result
    int* result = (int*)malloc(2 * sizeof(int));

    // Iterate through the array
    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        
        // Check if the complement exists in the hash table
        int complementIndex = find(table, complement);
        if (complementIndex != -1) {
            // If found, return the indices
            result[0] = complementIndex;
            result[1] = i;
            *returnSize = 2;
            freeHashTable(table);
            return result;
        }

        // Otherwise, insert the current number and its index into the hash table
        insert(table, nums[i], i);
    }

    // If no solution is found
    *returnSize = 0;
    free(result);
    freeHashTable(table);
    return NULL;
}
