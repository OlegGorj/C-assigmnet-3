#include <stdio.h>
#include <string.h>

#include "defs.h"

/*
  Function:  initBookArray
  Purpose:   Initializes a BookArrayType structure with a specified order.
      out:   The initialized BookArrayType structure.
       in:   The BookArrayType structure and the desired order (ORDER_BY_AUTHOR or ORDER_BY_RATING).
   return:   None.
   side effect: Initializes the size, order, and allocates memory for the book array.
*/
void initBookArray(BookArrayType* arr, OrderType order) {
    // Initialize size, order, and allocate memory for the book array
    arr->size = 0;
    arr->order = order;

    // allocate MAX_CAP structs of type BookType
    // for (int i = 0; i < MAX_CAP; i++){
    //     arr->elements[i] = (BookType*)malloc(sizeof(BookType));
    //     if (arr->elements[i] == NULL) {
    //         fprintf(stderr, "Memory allocation failed for BookArrayType.\n");
    //         exit(EXIT_FAILURE);
    //     }
    // }
}

/*
  Function:  initBook
  Purpose:   Initializes a BookType structure with the provided details.
      out:   The initialized BookType structure.
       in:   The BookType structure and book details (ID, title, author, year, rating).
   return:   None.
   side effect: Sets the fields of the BookType structure based on the provided parameters.
*/
void initBook(BookType* book, int id, char* title, char* author, int year, float rating) {
    // Assumption: input parameter "book" mush be initialized prior

    // Set fields of the BookType structure based on the provided parameters
    book->id = id;
    strncpy(book->title, title, MAX_STR - 1);
    strncpy(book->author, author, MAX_STR - 1);
    book->year = year;
    book->rating = rating;
}

/*
  Function:  findInsPt
  Purpose:   Finds the insertion point for a book in a BookArrayType structure based on its order.
      out:   The insertion point for the book.
       in:   The BookArrayType structure, the book to be inserted, and a pointer to store the insertion point.
   return:   C_OK on success, C_NOK if the array is full.
   side effect: Modifies the insPt parameter to store the insertion point.
*/
int findInsPt(BookArrayType *arr, BookType *b, int *insPt) {
    // Check if the array is full
    if (arr->size >= MAX_CAP) {
        return C_NOK;
    }

    int i = 0;
   
    // Determine insertion point based on the order (by author or by rating)
    if (arr->order == ORDER_BY_AUTHOR) {
        while (i < arr->size && strcmp(arr->elements[i]->author, b->author) < 0) {
            i++;
        }

        while (i < arr->size && strcmp(arr->elements[i]->author, b->author) == 0 && strcmp(arr->elements[i]->title, b->title) < 0) {
            i++;
        }
    } else if (arr->order == ORDER_BY_RATING) {
        while (i < arr->size && arr->elements[i]->rating > b->rating) {
            i++;
        }
    }

    // Store the insertion point
    *insPt = i;
    return C_OK;
}

/*
  Function:  addBookToArray
  Purpose:   Adds a new book to a BookArrayType structure.
      out:   C_OK if the book was successfully added, ERROR_FLAG otherwise.
       in:   The BookArrayType structure and the book to be added.
   return:   C_OK on success, ERROR_FLAG on failure.
   side effect: Dynamically allocates memory for a new book, initializes it, and adds it to the book array.
*/
int addBookToArray(BookArrayType* arr, BookType* b) {
    const int ERROR_FLAG = -1;

    // Check if the array is full
    if (arr->size >= MAX_CAP) {
        printf("Error: can not add any more books - array is full");
        return ERROR_FLAG;
    }

    int insPt;
    // Find the insertion point for the new book
    int result = findInsPt(arr, b, &insPt);

    // Check for errors in finding the insertion point
    if (result == ERROR_FLAG) {
        return ERROR_FLAG;
    }

    // Shift elements to make room for the new book
    for (int i = arr->size; i > insPt; i--) {
        arr->elements[i] = arr->elements[i - 1];
    }

    // Allocate memory for the new book
    arr->elements[insPt] = (BookType*)malloc(sizeof(BookType));
    if (arr->elements[insPt] == NULL) {
        return ERROR_FLAG;
    }

    // Initialize the new book with the provided details
    initBook(arr->elements[insPt], b->id, b->title, b->author, b->year, b->rating);

    // Increment the size of the array
    arr->size++;
    return C_OK;
}

/*
  Function:  printBook
  Purpose:   Prints the details of a book.
      out:   None.
       in:   The BookType structure representing the book.
   return:   None.
   side effect: Displays the book data with aligned formatting.
*/
void printBook(BookType *b) {
    // Print book data with aligned formatting
    printf("%4d  %-30s  %-20s  %4d  %5.2f\n", b->id, b->title, b->author, b->year, b->rating);
}

/*
  Function:  printBookArray
  Purpose:   Prints all books in a BookArrayType structure.
      out:   None.
       in:   The BookArrayType structure containing books.
   return:   None.
   side effect: Displays the book array with column names and details.
*/
void printBookArray(BookArrayType *arr) {
    // Print header with column names
    // printf("%-5s  %-30s  %-20s  %-4s  %-5s\n", "ID", "Title", "Author", "Year", "Rating");
    printf("%-5s\n", "ID");

    for (int i = 0; i < arr->size-1; i++) {
        printBook(arr->elements[i]);
    }
}

/*
  Function:  cleanupBookArray
  Purpose:   Frees the memory allocated for each book in a BookArrayType structure.
      out:   None.
       in:   The BookArrayType structure to be cleaned up.
   return:   None.
   side effect: Frees the memory allocated for each book and resets the size to zero.
*/
void cleanupBookArray(BookArrayType *arr) {
    // Free memory
    for (int i = 0; i < arr->size; i++) {
        free(arr->elements[i]);
        arr->elements[i] = NULL;
    }

    // Reset the size to zero
    arr->size = 0;
}
