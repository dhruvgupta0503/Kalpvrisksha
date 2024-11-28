#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.txt"

typedef struct {
    int userID;
    char userName[50];
    int userAge;
} User;

void create();
void read();
void update();
void delete();
void initializeFile();

int main() {
    int choice;
    initializeFile();

    do {
        printf("\n--- User Management System ---\n");
        printf("1. Create New User\n");
        printf("2. Read All Users\n");
        printf("3. Update User Details\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                read();
                break;
            case 3:
                update();
                break;
            case 4:
                delete();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void initializeFile() {
    FILE *filePtr = fopen(FILE_NAME, "a");
    if (filePtr == NULL) {
        printf("Error initializing file.\n");
        exit(1);
    }
    fclose(filePtr);
}

void create() {
    FILE *filePtr = fopen(FILE_NAME, "a");
    if (filePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User newUser;
    printf("Enter User ID: ");
    scanf("%d", &newUser.userID);
    printf("Enter Name: ");
    scanf(" %[^\n]", newUser.userName);
    printf("Enter Age: ");
    scanf("%d", &newUser.userAge);

    fprintf(filePtr, "%d,%s,%d\n", newUser.userID, newUser.userName, newUser.userAge);
    fclose(filePtr);
    printf("User created successfully!\n");
}

void read() {
    FILE *filePtr = fopen(FILE_NAME, "r");
    if (filePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User currentUser;
    printf("\n--- User Records ---\n");
    while (fscanf(filePtr, "%d,%49[^,],%d\n", &currentUser.userID, currentUser.userName, &currentUser.userAge) == 3) {
        printf("ID: %d | Name: %s | Age: %d\n", currentUser.userID, currentUser.userName, currentUser.userAge);
    }
    fclose(filePtr);
}

void update() {
    int searchID, isFound = 0;
    printf("Enter the User ID to update: ");
    scanf("%d", &searchID);

    FILE *filePtr = fopen(FILE_NAME, "r");
    FILE *tempFilePtr = fopen("temp.txt", "w");
    if (filePtr == NULL || tempFilePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User currentUser;
    while (fscanf(filePtr, "%d,%49[^,],%d\n", &currentUser.userID, currentUser.userName, &currentUser.userAge) == 3) {
        if (currentUser.userID == searchID) {
            isFound = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", currentUser.userName);
            printf("Enter new Age: ");
            scanf("%d", &currentUser.userAge);
        }
        fprintf(tempFilePtr, "%d,%s,%d\n", currentUser.userID, currentUser.userName, currentUser.userAge);
    }

    fclose(filePtr);
    fclose(tempFilePtr);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (isFound) {
        printf("User updated successfully!\n");
    } else {
        printf("User ID not found.\n");
    }
}

void delete() {
    int searchID, isFound = 0;
    printf("Enter the User ID to delete: ");
    scanf("%d", &searchID);

    FILE *filePtr = fopen(FILE_NAME, "r");
    FILE *tempFilePtr = fopen("temp.txt", "w");
    if (filePtr == NULL || tempFilePtr == NULL) {
        printf("Error opening file.\n");
        return;
    }

    User currentUser;
    while (fscanf(filePtr, "%d,%49[^,],%d\n", &currentUser.userID, currentUser.userName, &currentUser.userAge) == 3) {
        if (currentUser.userID != searchID) {
            fprintf(tempFilePtr, "%d,%s,%d\n", currentUser.userID, currentUser.userName, currentUser.userAge);
        } else {
            isFound = 1;
        }
    }

    fclose(filePtr);
    fclose(tempFilePtr);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (isFound) {
        printf("User deleted successfully!\n");
    } else {
        printf("User ID not found.\n");
    }
}
