#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int roll_number;
    float cgpa;
};

void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(struct Student arr[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left].roll_number > arr[largest].roll_number)
        largest = left;

    if (right < n && arr[right].roll_number > arr[largest].roll_number)
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void maxHeapSort(struct Student arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student students[n];

    for (int i = 0; i < n; i++) {
        printf("Enter name for student %d: ", i + 1);
        scanf(" %49[^\n]", students[i].name); // Use %[^\n] to read full names with spaces
        printf("Enter roll number for student %d: ", i + 1);
        scanf("%d", &students[i].roll_number);
        printf("Enter CGPA for student %d: ", i + 1);
        scanf("%f", &students[i].cgpa);
    }

    printf("\nStudent data before sorting by roll number:\n");
    printf("Name\t\tRollNumber\tCGPA\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%.2f\n", students[i].name, students[i].roll_number, students[i].cgpa);
    }

    maxHeapSort(students, n);

    printf("\nStudent data after sorting by roll number:\n");
    printf("Name\t\tRollNumber\tCGPA\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%.2f\n", students[i].name, students[i].roll_number, students[i].cgpa);
    }

    return 0;
}

