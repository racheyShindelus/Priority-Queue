# Priority Queue (Implemented via Heap Array)

This C++ program implements a priority queue using a binary heap array. It allows the user to create a priority queue of a specified size and choose between a min-heap or a max-heap.

## Priority Queue Implementation

- The priority queue is implemented using a binary heap array.
- The class `PriorityQueueBHA` encapsulates the priority queue functionality.
- The user can specify the size of the priority queue upon creation.
- The user can choose between a min-heap or a max-heap.
- The class provides methods to push elements into the priority queue, pop elements from the priority queue, and sort the priority queue.
- The priority queue is dynamically resized to accommodate new elements.
- The class keeps track of the number of comparisons and swaps performed during operations.

## Main Function

- The `main()` function serves as the program entry point.
- It prompts the user to specify the size of the priority queue and choose between a min-heap or a max-heap.
- It then enters a loop where the user can push positive numbers into the priority queue or pop elements from the priority queue by entering negative numbers.
- The current state of the priority queue is printed after each operation.

## Input Handling

- The program ensures robust input handling, allowing only integers as input.
- If the user enters a non-integer value, the program prompts the user to try again.
- Negative numbers are used to pop elements from the priority queue, while positive numbers are used to push elements into the priority queue.

Feel free to explore and modify the code as needed.
