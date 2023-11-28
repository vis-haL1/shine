#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(struct Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        return;
    } else {
        struct Node* curr = *root;
        struct Node* parent = NULL;
        while (curr != NULL) {
            parent = curr;
            if (value <= curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }
        if (value <= parent->data)
            parent->left = createNode(value);
        else
            parent->right = createNode(value);
    }
}


struct StackNode {
    struct Node* data;
    struct StackNode* next;
};

struct StackNode* createStackNode(struct Node* node) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->data = node;
    stackNode->next = NULL;
    return stackNode;
}

void push(struct StackNode** top, struct Node* node) {
    struct StackNode* stackNode = createStackNode(node);
    stackNode->next = *top;
    *top = stackNode;
}

struct Node* pop(struct StackNode** top) {
    if (*top == NULL)
        return NULL;
    struct StackNode* temp = *top;
    *top = (*top)->next;
    struct Node* popped = temp->data;
    free(temp);
    return popped;
}

int isEmpty(struct StackNode* top) {
    return top == NULL;
}


void preOrder(struct Node* root) {
    if (root == NULL)
        return;

    struct StackNode* stack = NULL;
    struct Node* curr = root;

    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            printf("%d ", curr->data);
            push(&stack, curr);
            curr = curr->left;
        }

        curr = pop(&stack);
        curr = curr->right;
    }
}


void inOrder(struct Node* root) {
    if (root == NULL)
        return;

    struct StackNode* stack = NULL;
    struct Node* curr = root;

    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            push(&stack, curr);
            curr = curr->left;
        }

        curr = pop(&stack);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}


void postOrder(struct Node* root) {
    if (root == NULL)
        return;

    struct StackNode* stack1 = NULL;
    struct StackNode* stack2 = NULL;
    struct Node* curr = root;

    push(&stack1, curr);

    while (!isEmpty(stack1)) {
        curr = pop(&stack1);
        push(&stack2, curr);

        if (curr->left)
            push(&stack1, curr->left);
        if (curr->right)
            push(&stack1, curr->right);
    }

    while (!isEmpty(stack2)) {
        curr = pop(&stack2);
        printf("%d ", curr->data);
    }
}

int main() {
    struct Node* root = NULL;
    int value, numNodes;

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < numNodes; i++) {
        scanf("%d", &value);
        insert(&root, value);
    }

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrder(root);
    printf("\n");

    return 0;
}

