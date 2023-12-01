#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char employee_name[50];
    int emp_id;
    int emp_salary;
    struct Employee *left;
    struct Employee *right;
};

typedef struct Employee Employee;

Employee* createEmployeeNode(int emp_id, char* emp_name, int emp_salary) {
    Employee* newNode = (Employee*)malloc(sizeof(Employee));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->emp_id = emp_id;
    newNode->emp_salary = emp_salary;
    strcpy(newNode->employee_name, emp_name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Employee* insertEmployee(Employee* root, int emp_id, char* emp_name, int emp_salary) {
    if (root == NULL) {
        return createEmployeeNode(emp_id, emp_name, emp_salary);
    }

    if (emp_id < root->emp_id) {
        root->left = insertEmployee(root->left, emp_id, emp_name, emp_salary);
    } else if (emp_id > root->emp_id) {
        root->right = insertEmployee(root->right, emp_id, emp_name, emp_salary);
    }

    return root;
}

Employee* searchEmployeeById(Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id) {
        return root;
    }

    if (emp_id < root->emp_id) {
        return searchEmployeeById(root->left, emp_id);
    } else {
        return searchEmployeeById(root->right, emp_id);
    }
}

void inorderTraversal(Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Employee ID: %d, Name: %s, Salary: %d\n", root->emp_id, root->employee_name, root->emp_salary);
        inorderTraversal(root->right);
    }
}

int main() {
    Employee* root = NULL;
    int numEmployees, emp_id, emp_salary;
    char emp_name[50];

    printf("Enter the number of employees: ");
    scanf("%d", &numEmployees);

    for (int i = 0; i < numEmployees; ++i) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("Employee ID: ");
        scanf("%d", &emp_id);

        printf("Employee Name: ");
        scanf("%s", emp_name);

        printf("Employee Salary: ");
        scanf("%d", &emp_salary);

        root = insertEmployee(root, emp_id, emp_name, emp_salary);
    }

    printf("\nEmployee records sorted by emp_id in ascending order:\n");
    inorderTraversal(root);

    int search_id;
    printf("\nEnter the Employee ID to search: ");
    scanf("%d", &search_id);
    
    Employee* foundEmployee = searchEmployeeById(root, search_id);
    if (foundEmployee != NULL) {
        printf("\nEmployee found with ID %d: Name: %s, Salary: %d\n", search_id, foundEmployee->employee_name, foundEmployee->emp_salary);
    } else {
        printf("\nEmployee with ID %d not found\n", search_id);
    }

    return 0;
}
