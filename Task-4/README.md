# Task Overview: Slab Allocator in C Language for Postgres
### Task
 - **Learn about memory context in PG**
   - Why, What, When, and How
- **Memory Allocation Based on Size**:
    - Implement memory management where memory is allocated based on the size of the required memory, rather than maintaining a cache of objects.
  
- **Reallocation Feature**:
    - The program must be able to request extra space dynamically, allowing the user to reallocate memory when necessary.
    - This involves:
      - Allocating a new memory block of requested size
      - Copying data from the old memory block to the new one.
      - Deleting the old memory block to free up the resources.