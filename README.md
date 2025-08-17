# C-ToDo: Console To-Do List Manager

A simple yet comprehensive console-based to-do list manager written in C that demonstrates the implementation of multiple data structures.

## Features

- **Task Management**: Add, view, delete, and mark tasks as completed
- **Pending Queue**: Queue tasks for later activation using FIFO principle
- **Undo Functionality**: Restore accidentally deleted tasks using a stack
- **Priority Organization**: View tasks organized by priority levels using Binary Search Tree
- **Search Capability**: Find tasks by name using linear search
- **Progress Tracking**: Visual progress display with completion percentage

## Data Structures Implemented

1. **Linked List** - Stores active tasks with dynamic insertion/deletion
2. **Queue (FIFO)** - Manages pending tasks in First-In-First-Out order
3. **Stack (LIFO)** - Handles undo functionality for deleted tasks
4. **Binary Search Tree** - Organizes tasks by priority for efficient searching
5. **Linear Search** - Searches tasks by name through the linked list
6. **BFS Traversal** - Level-order traversal of the priority tree

## Getting Started

### Prerequisites

- GCC compiler or any C compiler
- Windows/Linux/macOS

### Compilation

```bash
gcc -o todo to-do.c
```

### Running the Program

```bash
./todo
```

## How to Use

### Main Menu Options

1. **Add Active Task** - Create a new task and add it to your active list
2. **Show Active Tasks** - Display all current tasks with progress tracking
3. **Delete Task** - Remove a task (saved for undo)
4. **Mark Task as Done** - Mark a task as completed
5. **Add Pending Task** - Add a task to the pending queue
6. **Show Pending Tasks** - View all queued tasks
7. **Move Pending to Active** - Transfer the next pending task to active list
8. **Undo Last Delete** - Restore the most recently deleted task
9. **Search Task by Name** - Find a specific task by its name
10. **Show Tasks by Priority** - View tasks organized in priority tree (BFS)
11. **Exit** - Close the application

### Priority Levels

- **1** - High Priority (Urgent tasks)
- **2** - Medium Priority (Important tasks)
- **3** - Low Priority (When time permits)

## Code Structure

### Core Data Types

```c
struct Task {
    char name[MAX_LENGTH];    // Task name (max 30 characters)
    int priority;             // Priority level (1-3)
    int isDone;              // Completion status (0/1)
};
```

### Global Pointers

- `activeHead` - Head of active tasks linked list
- `pendingFront/pendingRear` - Front and rear of pending queue
- `undoTop` - Top of undo stack
- `bstRoot` - Root of priority Binary Search Tree

### Key Functions

- **Task Management**: `addTask()`, `showTasks()`, `deleteTask()`, `markAsDone()`
- **Queue Operations**: `addPendingTask()`, `showPendingTasks()`, `movePendingToActive()`
- **Undo System**: `undoDelete()`, `pushUndo()`, `popUndo()`
- **Search & Display**: `searchTaskByName()`, `displayBST_BFS()`
- **Data Structure Helpers**: `enqueuePending()`, `dequeuePending()`, `insertBST()`

## Example Usage

```
=== Welcome to To-Do List Manager ===

--- TO-DO LIST MENU ---
1. Add Active Task
2. Show Active Tasks
...

Enter your choice: 1

--- Adding New Task ---
Enter task name: Complete project documentation
Enter priority (1=High, 2=Medium, 3=Low): 1
Task added successfully!
```

## Educational Value

This project demonstrates:

- **Memory Management**: Dynamic allocation and deallocation
- **Data Structure Implementation**: Practical use of fundamental data structures
- **Algorithm Implementation**: Search algorithms and tree traversal
- **Input Validation**: Handling user input safely
- **Modular Programming**: Clean function organization

## Technical Details

- **Language**: C (C99 standard)
- **Memory Management**: Manual allocation/deallocation using malloc/free
- **Input Handling**: Uses `fgets()` for safe string input and `scanf()` for numbers
- **Cross-Platform**: Compatible with Windows, Linux, and macOS

## Limitations

- Task names limited to 30 characters
- No persistent storage (data lost on exit)
- BST not rebalanced on deletions (simplified for educational purposes)
- Fixed-size array for BFS queue (100 nodes maximum)

## Future Enhancements

- File-based data persistence
- Task categories and tags
- Due date management
- Task priority modification
- Search by priority range
- Export functionality

## Contributing

This is an educational project. Feel free to fork and enhance it for learning purposes.

## License

Open source - feel free to use for educational purposes.

---

**Author**: Developed as a demonstration of data structures in C programming.
