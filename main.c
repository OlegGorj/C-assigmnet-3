#include <stdio.h>
#include <string.h>

#include "defs.h"


int main() {
  /*
  Purpose:   Keep a book club, add books to it and get top rated books.
    Usage:   Run program, enter value 1, 2, 3 or 0 depending on use, if adding, enter information on book
  Commands:   Only run program command
   author:   Nicolas Gorodnitchi
  */
    BookClubType myBookClub;

    initBookClub(&myBookClub, "My Book Club");
    loadBookData(&myBookClub);
    
    int choice;

    do {
        printMenu(&choice);

        // Process user selection
        switch (choice) {
          
            case 1:
                //all books
                printBooks(&myBookClub);
                break;

            case 2: 
                //top rated
                printTopRatedBooks(&myBookClub);
                break;

            case 3:
                {
                  // Case for adding a new book
                    int id, year;
                    float rating;
                    char title[MAX_STR], authorFirst[MAX_STR], authorLast[MAX_STR];
                  //Prompt for entering new book data
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
                printf("Exiting the program. Cleaning up...\n");
                
                break;

            default:
                printf("Invalid option. Please choose a valid menu option.\n");
                break;
        }

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
