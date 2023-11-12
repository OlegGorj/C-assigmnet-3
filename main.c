#include <stdio.h>
#include <string.h>

#include "defs.h"


int main() {
    // Declare a local BookClubType variable
    BookClubType myBookClub;

    // Initialize the book club structure
    initBookClub(&myBookClub, "My Book Club");

    // Load book data into the book club
    loadBookData(&myBookClub);

    // Variable to store the user's menu choice
    int choice;

    // Main control flow
    do {
        // Print the main menu
        printMenu(&choice);

        // Process user selection
        switch (choice) {
            case 1:
                // Print all books
                printBooks(&myBookClub);
                break;

            case 2:
                // Print top-rated books
                printTopRatedBooks(&myBookClub);
                break;

            case 3:
                // Add a new book
                {
                    int id, year;
                    float rating;
                    char title[MAX_STR], authorFirst[MAX_STR], authorLast[MAX_STR];

                    // Prompt user to enter new book data
                    printf("Enter Book ID: ");
                    scanf("%d", &id);

                    printf("Enter Book Title: ");
                    scanf(" %[^\n]", title);

                    printf("Enter Author First Name: ");
                    scanf(" %[^\n]", authorFirst);

                    printf("Enter Author Last Name: ");
                    scanf(" %[^\n]", authorLast);

                    printf("Enter Publication Year: ");
                    scanf("%d", &year);

                    printf("Enter Rating: ");
                    scanf("%f", &rating);

                    // Add the new book to the book club
                    int result = addBookToClub(&myBookClub, id, title, authorFirst, authorLast, year, rating);

                    // Check for errors and notify the user
                    if (result == C_NOK) {
                        printf("Error: Unable to add the book. Please check your input.\n");
                    } else {
                        printf("Book added successfully!\n");
                    }
                }
                break;

            case 0:
                // Exit the program
                printf("Exiting the program. Cleaning up...\n");
                break;

            default:
                // Invalid choice, prompt for a new selection
                printf("Invalid option. Please choose a valid menu option.\n");
                break;
        }

        // Check if the user chose to exit
    } while (choice != 0);

    // Clean up the book collection
    cleanupBookArray(&(myBookClub.books));

    return 0;
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print all books\n");
  printf("  (2) Print top rated books\n");
  printf("  (3) Add a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}
