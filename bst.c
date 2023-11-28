#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//  INSERTION

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

struct Node* findMin(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// DELETION

struct Node* delete(struct Node* root, int data) {
    if (root == NULL) {
        return root;
    }

    if (data < root->data) {
        root->left = delete(root->left, data);
    } else if (data > root->data) {
        root->right = delete(root->right, data);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = delete(root->right, temp->data);
    }

    return root;
}

// MIRROR IMAGE

struct Node* mirrorImage(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    struct Node* temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);

    return root;
}

// LEVEL ORDER DISPLAY
void levelOrderDisplay(struct Node* root) {
    if (root == NULL) {
        return;
    }

    struct Node** queue = (struct Node**)malloc(100 * sizeof(struct Node*));
    int front = -1, rear = -1;
    queue[++rear] = root;

    while (front != rear) {
        struct Node* current = queue[++front];
        printf("%d ", current->data);

        if (current->left != NULL) {
            queue[++rear] = current->left;
        }
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }

    free(queue);
}

// HEIGHT

int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// DISPLAY LEAF NODE
void displayLeafNodes(struct Node* root) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
    }

    displayLeafNodes(root->left);
    displayLeafNodes(root->right);
}

void displayMenu() {
    printf("\nBinary Search Tree Operations");
    printf("\n1. Create");
    printf("\n2. Insert");
    printf("\n3. Delete");
    printf("\n4. Mirror Image");
    printf("\n5. Level wise Display");
    printf("\n6. Height of the tree");
    printf("\n7. Display Leaf Nodes");
    printf("\n8. Exit");
    printf("\nEnter your choice: ");
}

struct Node* createBST() {
    struct Node* root = NULL;
    int numElements, value;

    printf("Enter the total number of elements to create BST: ");
    scanf("%d", &numElements);

    printf("Enter %d elements to create BST:\n", numElements);
    for (int i = 0; i < numElements; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &value);
        root = insert(root, value);
    }

    return root;
}

int main() {
    struct Node* root = NULL;
    int choice, value;

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                root = createBST();
                printf("BST created successfully.\n");
                break;
            case 2:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 3:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            case 4:
                root = mirrorImage(root);
                printf("Mirror Image of the BST.\n");
                break;
            case 5:
                printf("Level order display: ");
                levelOrderDisplay(root);
                printf("\n");
                break;
            case 6:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 7:
                printf("Leaf Nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);
    return 0;
}

