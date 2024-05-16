#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_USERS 100
#define DATABASE_FILE "users.txt"

// Structure to hold user information
struct User {
   char username[MAX_USERNAME_LENGTH];
   char password[MAX_PASSWORD_LENGTH];
};

// Array to store user data
struct User users[MAX_USERS];
int numUsers = 0;

// Function to load user data from file
void loadUsersFromFile() {
   FILE *file = fopen(DATABASE_FILE, "r");
   if (file != NULL) {
       while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) != EOF) {
           numUsers++;
       }
       fclose(file);
   }
}

// Function to save new user data to file
void saveUserToFile(struct User newUser) {
   FILE *file = fopen(DATABASE_FILE, "a");
   if (file != NULL) {
       fprintf(file, "%s %s\n", newUser.username, newUser.password);
       fclose(file);
   }
}

// Function for user signup
void signup() {
   struct User newUser;
   printf("Enter username: ");
   scanf("%s", newUser.username);
   printf("Enter password: ");
   scanf("%s", newUser.password);

   // Check if username already exists
   for (int i = 0; i < numUsers; i++) {
       if (strcmp(newUser.username, users[i].username) == 0) {
           printf("Username already exists!\n");
           return;
       }
   }

   // Save new user data
   saveUserToFile(newUser);
   printf("Signup successful!\n");
}

// Function for user login
void login() {
   char username[MAX_USERNAME_LENGTH];
   char password[MAX_PASSWORD_LENGTH];
   printf("Enter username: ");
   scanf("%s", username);
   printf("Enter password: ");
   scanf("%s", password);

   // Check if entered username and password match any user data
   for (int i = 0; i < numUsers; i++) {
       if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
           printf("Login successful!\n");
           return;
       }
   }

   printf("Invalid username or password!\n");
}

// Main function
int main() {
   loadUsersFromFile();
   int choice;
   do {
       printf("1. Signup\n");
       printf("2. Login\n");
       printf("3. Exit\n");
       printf("Enter your choice: ");
       scanf("%d", &choice);

       switch (choice) {
           case 1:
               signup();
               break;
           case 2:
               login();
               break;
           case 3:
               printf("Exiting...\n");
               break;
           default:
               printf("Invalid choice!\n");
       }
   } while (choice != 3);

   return 0;
}

