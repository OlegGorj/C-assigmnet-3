#include <stdio.h>
#include <string.h>

#include "defs.h"

// This will have initBookClub(), addBookToClub(), printBooks(), printTopRatedBooks()

void initBookClub(BookClubType *club, char *n) {
    // Initialize the club's name by copying the provided string
    strncpy(club->name, n, MAX_STR - 1);
    club->name[MAX_STR - 1] = '\0';

    // Initialize the book array using the existing function initBookArray
    initBookArray(&(club->books), ORDER_BY_AUTHOR); // You can choose the desired order
}


void printBooks(BookClubType *club) {
    // Print the book club's name
    printf("Book Club: %s\n", club->name);

    // Print all the books in the book club's collection using an existing function
    printBookArray(&(club->books));
}

void printTopRatedBooks(BookClubType *club) {
    // Declare temporary book collections
    BookArrayType allBooks, topRatedBooks;

    // Initialize both temporary book collections
    initBookArray(&allBooks, ORDER_BY_RATING);
    initBookArray(&topRatedBooks, ORDER_BY_RATING);

    // Loop over the given club’s book collection and add each book to the temporary all books collection
    for (int i = 0; i < club->books.size; i++) {
        addBookToArray(&allBooks, club->books.elements[i]);
    }

    // Compute the number that represents 20% of the total number of books in the club
    int topRatedCount = (int)(0.2 * allBooks.size);

    // Loop over the temporary all books collection to add only the top-rated books to the temporary top-rated collection
    for (int i = 0; i < topRatedCount; i++) {
        addBookToArray(&topRatedBooks, allBooks.elements[i]);
    }

    // Print out the club’s name and the top-rated books collection
    printf("Book Club: %s\n", club->name);
    printf("Top Rated Books (20%%):\n");
    printBookArray(&topRatedBooks);

    // Cleanup temporary book collections
    cleanupBookArray(&allBooks);
    cleanupBookArray(&topRatedBooks);
}



int addBookToClub(BookClubType *club, int id, char *t, char *af, char *al, int y, float r) {
    // (a) Validate id and year as positive numbers
    if (id <= 0 || y <= 0) {
        return C_NOK; // Invalid id or year
    }

    // (b) Validate rating to be in the range between 0 and 5, inclusively
    if (r < 0 || r > 5) {
        return C_NOK; // Invalid rating
    }

    // (d) Create a single string for the author’s name
    char author[MAX_STR * 2];  // Assuming MAX_STR is the maximum length for both first and last names
    sprintf(author, "%s, %s", al, af);

    // (e) Dynamically allocate memory for a new book and initialize it
    BookType *newBook = (BookType *)calloc(1, sizeof(BookType));
    if (newBook == NULL) {
        fprintf(stderr, "Memory allocation failed for BookType.\n");
        return C_NOK; // Memory allocation failed
    }

    // Initialize the new book using the existing function
    initBook(newBook, id, t, author, y, r);

    // (f) Add the new book to the book club’s collection using an existing function
    int result = addBookToArray(&(club->books), newBook);

    // (g) Return an error flag if the book could not be added to the collection
    if (result == C_NOK) {
        free(newBook); // Cleanup allocated memory in case of failure
        return C_NOK;  // Unable to add the book to the collection
    }


    free(newBook);
    return C_OK; // Success
}

