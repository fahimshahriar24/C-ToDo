# C-ToDo — Simple Project Report

## 1) Introduction
This is a console-based To-Do list program written in C. The goal is to practice basic data structures and make a small working app to manage tasks. It uses simple structs and pointers to store tasks in memory while the app is running.

## 2) What the program does
- Add a new active task (name + priority)
- Show active tasks and progress (done/total)
- Delete a task (can undo the last delete)
- Mark a task as done
- Add a pending task (queue)
- Show pending tasks
- Move one pending task to active
- Search a task by name (linear search)
- Show tasks by priority using a tree (BST with BFS)

## 3) Data structures used
- Linked List: active tasks (easy add/remove at head)
- Queue (FIFO): pending tasks (first in, first out)
- Stack (LIFO): deleted tasks (for undo)
- Binary Search Tree (BST): tasks organized by priority (1 high, 2 medium, 3 low)
- Linear Search: search tasks by name
- BFS (level-order): print BST level by level

Task data (what a task stores):
- name (max 30 chars)
- priority (1–3, where 1 is High)
- done flag (0 = not done, 1 = done)

## 4) How it works (short flow)
1. The program shows a simple menu in a loop.
2. You choose an option (1–11).
3. It runs the matching function.
4. After finishing, it waits for Enter and clears the screen.
5. In memory it keeps: an active list, a pending queue, an undo stack, and a priority BST (the BST isn’t updated on delete to keep it simple).

## 5) Important functions (one line each)
- `addTask()`: read task and add to linked list; also insert into BST.
- `showTasks()`: print all active tasks and progress.
- `deleteTask()`: remove a task from list; push to undo stack.
- `markAsDone()`: set a task done.
- `addPendingTask()`: enqueue a pending task.
- `showPendingTasks()`: list pending tasks (front is next).
- `movePendingToActive()`: dequeue and add to active; insert into BST.
- `undoDelete()`: pop from stack and restore to active; insert into BST.
- `searchTaskByName()`: find by name using linear search.
- `insertBST()`: insert by priority (smaller left, else right).
- `displayBST_BFS()`: print the BST by levels.
- `pushUndo()` / `popUndo()`: manage the undo stack of deleted tasks.
- `clearScreen()`: clear the console between actions.

## 6) How to build and run
You need a C compiler (GCC/MinGW, Clang, or similar).

Windows (PowerShell):
```powershell
# compile
gcc -o todo to-do.c
# run
.\todo.exe
```

Linux/macOS:
```bash
# compile
gcc -o todo to-do.c
# run
./todo
```

Note: If `gcc` isn’t found on Windows, install “MinGW-w64” and add its `bin` folder to PATH.

## 7) Example run
```
=== Welcome to To-Do List Manager ===
--- TO-DO LIST MENU ---
1. Add Active Task
...
Enter your choice: 1

--- Adding New Task ---
Enter task name: Study DS project
Enter priority (1=High, 2=Medium, 3=Low): 1
Task added successfully!
```

## 8) Limitations (simple)
- Task names are max 30 characters.
- If priority is not 1–3, it becomes 2 by default.
- Deleting from active list does not remove it from the BST (kept simple).
- No saving to a file; data resets on exit.

## 9) What I would add next
- Save/load tasks from a file.
- Edit task name/priority.
- Balance the BST or use a map for faster search.
- Search by part of the name or by priority range.
- Better-looking console UI.

## 10) Conclusion
This project shows how linked lists, queues, stacks, and trees can work together in one small C program. It is simple and good for learning the basics. It helped me practice pointers, structs, and basic algorithms step by step.


