#ifndef PHONEBOOK_H
#define PHONEBOOK_H

#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char name[10];
  char second_name[10];
  char tel[10];
} abonent;

void run();
void print_menu();

void realloc_memory(abonent** abonents, const int new_size);
void free_memory(abonent** abonents);

void safe_input(char* input, size_t size, const char* prompt);
void clear_input_buffer();
void add_abonent(abonent** abonents, int* size);
void delete_abonent(abonent** abonents, int* size);
void find_abonent(abonent* abonents, const int size);
void print_abonents(abonent* abonents, const int size);

#endif  // PHONEBOOK_H
