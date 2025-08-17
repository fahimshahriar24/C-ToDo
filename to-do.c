/*
 ===============================================
                    C-ToDo
                TO-DO LIST MANAGER
        Using Multiple Data Structures
 ===============================================
 
 Data Structures Used:
 1. Linked List - Active Tasks
 2. Queue - Pending Tasks  
 3. Stack - Deleted Tasks (for undo)
 4. Binary Search Tree - Priority search
 5. Linear Search - Search by name
 6. BFS - Tree traversal
 
 ===============================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 30

// Structure for Task
struct Task {
    char name[MAX_LENGTH];
    int priority;
    int isDone;
};

// Linked List Node for Active Tasks
struct Node {
    struct Task task;
    struct Node *next;
};

// Queue Node for Pending Tasks
struct QueueNode {
    struct Task task;
    struct QueueNode *next;
};

// Stack Node for Deleted Tasks (Undo)
struct StackNode {
    struct Task task;
    struct StackNode *next;
};

// BST Node for searching by priority
struct BSTNode {
    struct Task task;
    struct BSTNode *left, *right;
};

// Global Pointers
struct Node *activeHead = NULL;           // Linked List Head
struct QueueNode *pendingFront = NULL;    // Queue Front
struct QueueNode *pendingRear = NULL;     // Queue Rear
struct StackNode *undoTop = NULL;         // Stack Top
struct BSTNode *bstRoot = NULL;           // BST Root

// Function Declarations
void addTask();
void showTasks();
void deleteTask();
void markAsDone();
void addPendingTask();
void showPendingTasks();
void movePendingToActive();
void undoDelete();
void searchTaskByName();
void insertBST(struct Task task);
void displayBST_BFS();
void clearScreen();

// Data Structure Helpers
void pushUndo(struct Task task);
struct Task popUndo();
void enqueuePending(struct Task task);
struct Task dequeuePending();
struct BSTNode* createBSTNode(struct Task task);

// ----------------- MAIN -----------------
int main() {
    int choice;
    
    printf("\n=== Welcome to To-Do List Manager ===\n");
    while(1) {
        printf("\n--- TO-DO LIST MENU ---\n");
        printf("1. Add Active Task\n");
        printf("2. Show Active Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Mark Task as Done\n");
        printf("5. Add Pending Task\n");
        printf("6. Show Pending Tasks\n");
        printf("7. Move Pending to Active\n");
        printf("8. Undo Last Delete\n");
        printf("9. Search Task by Name\n");
        printf("10. Show Tasks by Priority\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addTask(); break;
            case 2: showTasks(); break;
            case 3: deleteTask(); break;
            case 4: markAsDone(); break;
            case 5: addPendingTask(); break;
            case 6: showPendingTasks(); break;
            case 7: movePendingToActive(); break;
            case 8: undoDelete(); break;
            case 9: searchTaskByName(); break;
            case 10: displayBST_BFS(); break;
            case 11: 
                printf("\nThank you for using the To-Do Manager!\n");
                printf("Goodbye!\n");
                exit(0);
            default: 
                printf("Invalid choice! Please enter 1-11.\n");
        }
        printf("\nPress Enter to continue...");
        getchar();
        clearScreen();
    }
    return 0;
}

// ----------------- CORE FUNCTIONS -----------------

void addTask() {
    struct Task newTask;
    
    printf("\n--- Adding New Task ---\n");
    printf("Enter task name: ");
    fgets(newTask.name, MAX_LENGTH, stdin);
    newTask.name[strlen(newTask.name)-1] = '\0';
    
    printf("Enter priority (1=High, 2=Medium, 3=Low): ");
    scanf("%d", &newTask.priority);
    getchar();
    newTask.isDone = 0;

    // Validate priority
    if(newTask.priority < 1 || newTask.priority > 3) {
        printf("Invalid priority! Setting to Medium (2).\n");
        newTask.priority = 2;
    }

    // Insert into linked list
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->task = newTask;
    newNode->next = activeHead;
    activeHead = newNode;

    // Insert into BST
    insertBST(newTask);

    printf("Task added successfully!\n");
}

void showTasks() {
    if(activeHead == NULL) {
        printf("\n--- Active Tasks ---\n");
        printf("No active tasks found.\n");
        printf("Add some tasks to get started!\n");
        return;
    }
    
    printf("\n--- Active Tasks ---\n");
    struct Node *temp = activeHead;
    int i = 1;
    int totalTasks = 0, completedTasks = 0;
    
    while(temp) {
        printf("%d. %s", i++, temp->task.name);
        printf(" [Priority: %d]", temp->task.priority);
        if(temp->task.isDone) {
            printf(" [DONE]");
            completedTasks++;
        }
        printf("\n");
        
        totalTasks++;
        temp = temp->next;
    }
    
    printf("\nProgress: %d/%d tasks completed", completedTasks, totalTasks);
    if(totalTasks > 0) {
        int percentage = (completedTasks * 100) / totalTasks;
        printf(" (%d%%)", percentage);
    }
    printf("\n");
}

void deleteTask() {
    if(activeHead == NULL) {
        printf("\n--- Delete Task ---\n");
        printf("No tasks to delete.\n");
        return;
    }
    
    printf("\n--- Delete Task ---\n");
    showTasks();
    printf("Enter task number to delete: ");
    int pos;
    scanf("%d", &pos);
    getchar();

    struct Node *temp = activeHead, *prev = NULL;
    int i = 1;
    while(temp && i < pos) {
        prev = temp;
        temp = temp->next;
        i++;
    }
    if(!temp) {
        printf("Invalid task number.\n");
        return;
    }
    
    printf("Deleting: %s\n", temp->task.name);
    
    if(prev == NULL) activeHead = temp->next;
    else prev->next = temp->next;

    pushUndo(temp->task);
    free(temp);
    printf("Task deleted! (You can undo with option 8)\n");
}

void markAsDone() {
    if(activeHead == NULL) {
        printf("\n--- Mark Task as Done ---\n");
        printf("No tasks to mark as done.\n");
        return;
    }
    
    printf("\n--- Mark Task as Done ---\n");
    showTasks();
    printf("Enter task number to mark as done: ");
    int pos;
    scanf("%d", &pos);
    getchar();
    
    struct Node *temp = activeHead;
    int i = 1;
    while(temp && i < pos) {
        temp = temp->next;
        i++;
    }
    if(!temp) {
        printf("Invalid task number.\n");
        return;
    }
    
    if(temp->task.isDone) {
        printf("Task is already marked as done!\n");
        return;
    }
    
    temp->task.isDone = 1;
    printf("Task \"%s\" marked as completed!\n", temp->task.name);
}

void addPendingTask() {
    struct Task newTask;
    
    printf("\n--- Add Pending Task ---\n");
    printf("Enter pending task name: ");
    fgets(newTask.name, MAX_LENGTH, stdin);
    newTask.name[strlen(newTask.name)-1] = '\0';
    
    printf("Enter priority (1=High, 2=Medium, 3=Low): ");
    scanf("%d", &newTask.priority);
    getchar();
    newTask.isDone = 0;
    
    // Validate priority
    if(newTask.priority < 1 || newTask.priority > 3) {
        printf("Invalid priority! Setting to Medium (2).\n");
        newTask.priority = 2;
    }
    
    enqueuePending(newTask);
    printf("Task added to pending queue!\n");
}

void showPendingTasks() {
    if(!pendingFront) {
        printf("\n--- Pending Tasks ---\n");
        printf("No pending tasks in queue.\n");
        return;
    }
    
    printf("\n--- Pending Tasks (Queue) ---\n");
    struct QueueNode *temp = pendingFront;
    int i = 1;
    
    while(temp) {
        printf("%d. %s [Priority: %d]", i++, temp->task.name, temp->task.priority);
        if(i == 2) printf(" <- Next to be moved");
        printf("\n");
        temp = temp->next;
    }
    
    printf("Total pending: %d tasks\n", i-1);
}

void movePendingToActive() {
    if(!pendingFront) {
        printf("\n--- Move Pending to Active ---\n");
        printf("No pending tasks to move.\n");
        return;
    }
    
    printf("\n--- Move Pending to Active ---\n");
    struct Task t = dequeuePending();
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->task = t;
    newNode->next = activeHead;
    activeHead = newNode;
    insertBST(t);
    
    printf("Task \"%s\" moved to active list!\n", t.name);
}

void undoDelete() {
    if(!undoTop) {
        printf("\n--- Undo Delete ---\n");
        printf("No deleted tasks to restore.\n");
        return;
    }
    
    printf("\n--- Undo Delete ---\n");
    struct Task t = popUndo();
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->task = t;
    newNode->next = activeHead;
    activeHead = newNode;
    insertBST(t);
    
    printf("Task \"%s\" restored!\n", t.name);
}

void searchTaskByName() {
    char name[MAX_LENGTH];
    
    printf("\n--- Search Task by Name ---\n");
    printf("Enter task name to search: ");
    fgets(name, MAX_LENGTH, stdin);
    name[strlen(name)-1] = '\0';

    printf("Searching...\n");

    struct Node *temp = activeHead;
    int found = 0;
    int position = 1;
    
    while(temp) {
        if(strcmp(temp->task.name, name) == 0) {
            printf("Task found!\n");
            printf("Position: %d\n", position);
            printf("Task: %s\n", temp->task.name);
            printf("Priority: %d\n", temp->task.priority);
            printf("Status: %s\n", temp->task.isDone ? "DONE" : "PENDING");
            found = 1;
            break;
        }
        temp = temp->next;
        position++;
    }
    
    if(!found) {
        printf("Task \"%s\" not found.\n", name);
    }
}

// ----------------- BST FUNCTIONS -----------------
struct BSTNode* createBSTNode(struct Task task) {
    struct BSTNode *node = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    node->task = task;
    node->left = node->right = NULL;
    return node;
}

void insertBST(struct Task task) {
    struct BSTNode **current = &bstRoot;
    while(*current) {
        if(task.priority < (*current)->task.priority)
            current = &(*current)->left;
        else
            current = &(*current)->right;
    }
    *current = createBSTNode(task);
}

void displayBST_BFS() {
    if(!bstRoot) {
        printf("\n--- Tasks by Priority (BST) ---\n");
        printf("No tasks in priority tree.\n");
        return;
    }
    
    printf("\n--- Tasks by Priority (BFS Traversal) ---\n");
    printf("Binary Search Tree - Level Order:\n");
    
    struct BSTNode *queue[100];
    int front = 0, rear = 0;
    int level = 1;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;
    
    queue[rear++] = bstRoot;
    
    printf("Level %d: ", level);
    
    while(front < rear) {
        struct BSTNode *node = queue[front++];
        nodesInCurrentLevel--;
        
        printf("%s(P:%d) ", node->task.name, node->task.priority);
        
        if(node->left) {
            queue[rear++] = node->left;
            nodesInNextLevel++;
        }
        if(node->right) {
            queue[rear++] = node->right;
            nodesInNextLevel++;
        }
        
        if(nodesInCurrentLevel == 0 && nodesInNextLevel > 0) {
            printf("\nLevel %d: ", ++level);
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
    
    printf("\n\nPriority: 1=High, 2=Medium, 3=Low\n");
}

// ----------------- STACK & QUEUE HELPERS -----------------
void pushUndo(struct Task task) {
    struct StackNode *node = (struct StackNode*)malloc(sizeof(struct StackNode));
    node->task = task;
    node->next = undoTop;
    undoTop = node;
}

struct Task popUndo() {
    struct Task t = undoTop->task;
    struct StackNode *temp = undoTop;
    undoTop = undoTop->next;
    free(temp);
    return t;
}

void enqueuePending(struct Task task) {
    struct QueueNode *node = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    node->task = task;
    node->next = NULL;
    if(pendingRear) pendingRear->next = node;
    else pendingFront = node;
    pendingRear = node;
}

struct Task dequeuePending() {
    struct QueueNode *temp = pendingFront;
    struct Task t = temp->task;
    pendingFront = pendingFront->next;
    if(!pendingFront) pendingRear = NULL;
    free(temp);
    return t;
}

// Clear Screen (Windows)
void clearScreen() {
    system("cls");
}
