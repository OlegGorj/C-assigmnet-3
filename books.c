#include <stdio.h>
#include <string.h>

#include "defs.h"

//This will have initBook(), initBookArray(), addBookToArray(), findInsPt(), printBook(), printBookArray(), cleanupBookArray()

void initBookArray(BookArrayType* arr, OrderType o) {
    // Initialize the size of the collection to zero
    arr->size = 0;

    // Initialize the ordering of books in the array to the given parameter
    arr->order = o;

    // Use calloc to initialize the elements (book pointers) in the array to NULL
    arr->elements[0] = (BookType*)calloc(MAX_CAP, sizeof(BookType*));
    if (arr->elements[0] == NULL) {
      fprintf(stderr, "Memory allocation failed for BookArrayType.\n");
      exit(EXIT_FAILURE);
    }
}

void initBook(BookType* b, int id, char* t, char* a, int y, float r) {
    // Set the fields of the BookType structure based on the provided parameters
    b->id = id;

    // Use calloc to ensure that the title and author fields are null-terminated
    b->title[0] = '\0';
    b->author[0] = '\0';

    // Copy the title to the title field, ensuring it doesn't exceed the maximum length
    strncpy(b->title, t, MAX_STR - 1);

    // Copy the author to the author field, ensuring it doesn't exceed the maximum length
    strncpy(b->author, a, MAX_STR - 1);

    b->year = y;
    b->rating = r;
}


int findInsPt(BookArrayType *arr, BookType *b, int *insPt) {
    

    // Check if the array is full
    if (arr->size >= MAX_CAP) {
        return C_NOK; // Array is full, cannot insert more books
    }

    int i = 0;
    
    if (arr->order == ORDER_BY_AUTHOR) {
        // Find the insertion point in ascending alphabetical order by author
        while (i < arr->size && strcmp(arr->elements[i]->author, b->author) < 0) {
            i++;
        }

        // Handle books by the same author ordered by title, making sure stays at same author and only compares titles
        while (i < arr->size && strcmp(arr->elements[i]->author, b->author) == 0 && strcmp(arr->elements[i]->title, b->title) < 0) {
            i++;
        }

    } else if (arr->order == ORDER_BY_RATING) {
        // Find the insertion point in descending numerical order by rating
        while (i < arr->size && arr->elements[i]->rating > b->rating) {
            i++;
        }
    }

    *insPt = i; // Set the insertion point
    return C_OK; // Success
}

int addBookToArray(BookArrayType* arr, BookType* b) {
    // Error flag constant
    const int ERROR_FLAG = -1;

    // Check if there is room in the array for the new book
    if (arr->size >= MAX_CAP) {
        return ERROR_FLAG; // Array is full, cannot add more books
    }

    int insPt;

    // Find the insertion point using the existing function
    int result = findInsPt(arr, b, &insPt);

    // Check for errors in finding the insertion point
    if (result == ERROR_FLAG) {
        return ERROR_FLAG; // Unable to find insertion point, return error flag
    }

    // Move each element one position towards the back of the array
    for (int i = arr->size; i > insPt; i--) {
        arr->elements[i] = arr->elements[i - 1];
    }

    // Allocate memory for the new book and copy the data
    arr->elements[insPt] = (BookType*)calloc(1, sizeof(BookType));
    if (arr->elements[insPt] == NULL) {
        return ERROR_FLAG; // Memory allocation failed, return error flag
    }

    // Copy the book data into the newly allocated memory
    initBook(arr->elements[insPt], b->id, b->title, b->author, b->year, b->rating);

    // Increase the size of the array
    arr->size++;

    return C_OK; // Success
}

void printBook(BookType *b) {
    // Print book data with aligned formatting
    printf("%4d  %-30s  %-20s  %4d  %5.2f\n", b->id, b->title, b->author, b->year, b->rating);
}

void printBookArray(BookArrayType *arr) {
    // Print header with column names
    printf("%-5s  %-30s  %-20s  %-4s  %-5s\n", "ID", "Title", "Author", "Year", "Rating");

    // Print each book in the array using printBook function
    for (int i = 0; i < arr->size; i++) {
        printBook(arr->elements[i]);
    }
}


void cleanupBookArray(BookArrayType *arr) {
    // Free the memory allocated for each book
    for (int i = 0; i < arr->size; i++) {
        free(arr->elements[i]);
    }

    // Reset the size to zero
    arr->size = 0;
}