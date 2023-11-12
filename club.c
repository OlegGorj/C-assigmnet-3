#include <stdio.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initBookClub
  Purpose:   Initializes a BookClubType structure with the provided name.
      out:   The initialized BookClubType structure.
       in:   The name for the book club and the club.
   return:   None.
   side effect: Copies the provided name to the BookClubType structure and initializes the associated book array.
*/
void initBookClub(BookClubType *club, char *name) {
    // Copy the provided name to the BookClubType structure, ensuring null-termination
    int _len = strlen(name) + 1;
    if (_len > MAX_STR) {
        _len = MAX_STR;
    }
    strncpy(club->name, name, _len - 1);  club->name[_len] = '\0';

    // Initialize the book array, ordering books by author
    initBookArray(&(club->books), ORDER_BY_AUTHOR);
}


/*
  Function:  printBooks
  Purpose:   Prints all books in a BookClubType structure.
      out:   Displaying book club info.
       in:   The BookClubType structure containing books.
   return:   None.
   side effect: Displays the book club's name and all the books in the collection.
*/
void printBooks(BookClubType *club) {
    // Display the name of the book club
    printf("Book Club: %s\n", club->name);

    printBookArray(&(club->books));
}


#if !defined(ARRAY_SIZE)
    #define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

/*
  Function:  printTopRatedBooks
  Purpose:   Prints the top-rated books (20%) from a BookClubType structure.
      out:   Displays the book club's name and the top-rated books.
       in:   The BookClubType structure containing books.
   return:   None.
   side effect: Displays the book club's name and the top-rated books.
*/
void printTopRatedBooks(BookClubType *club) {
    BookArrayType allBooks, topRatedBooks;
    initBookArray(&allBooks, ORDER_BY_RATING);
    initBookArray(&topRatedBooks, ORDER_BY_RATING);

    // Copy all books from the book club's collection to the 'allBooks' array
    for (int i = 0; i < club->books.size-1; i++) {
        addBookToArray(&allBooks, club->books.elements[i]);
    }

    // Determine the number of top-rated books, 20%
    int topRatedCount = (int)(0.2 * allBooks.size);

    for (int i = 0; i < topRatedCount-1; i++) {
        addBookToArray(&topRatedBooks, allBooks.elements[i]);
    }

    // Display the name of the book club and the top-rated books
    printf("Book Club: %s\n", club->name);
    printf("Top Rated Books (20%%):\n");
    printBookArray(&topRatedBooks);

    // Clean up
    cleanupBookArray(&topRatedBooks);
    cleanupBookArray(&allBooks);
}


/*
  Function:  addBookToClub
  Purpose:   Adds a new book to a BookClubType structure.
      out:   C_OK if the book was successfully added, C_NOK otherwise.
       in:   The BookClubType structure, book details (ID, title, author, year, rating).
   return:   C_OK on success, C_NOK on failure.
   side effect: Dynamically allocates memory for a new book, initializes it, and adds it to the book club's collection.
*/
int addBookToClub(BookClubType *club, int id, char *t, char *af, char *al, int y, float r) {
    if (id <= 0 || y <= 0) {
        return C_NOK;
    }

    if (r < 0 || r > 5) {
        return C_NOK;
    }

    // Concatenate author's name
    char author[MAX_STR * 2];
    sprintf(author, "%s, %s", al, af);

    BookType *newBook = (BookType *)malloc(sizeof(BookType));
    if (newBook == NULL) {
        fprintf(stderr, "Memory allocation failed for BookType.\n");
        return C_NOK;
    }

    initBook(newBook, id, t, author, y, r);
    // Check for errors in adding
    if (addBookToArray(&(club->books), newBook) == C_NOK) {
        free(newBook);
        return C_NOK;
    }

    free(newBook);
    return C_OK;
}
