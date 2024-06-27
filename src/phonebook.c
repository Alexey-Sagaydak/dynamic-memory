#include "../include/phonebook.h"

void print_menu() {
  printf(
      "1) Добавить абонента\n"
      "2) Удалить абонента\n"
      "3) Поиск абонентов по имени\n"
      "4) Вывод всех записей\n"
      "5) Выход\n");
}

void run() {
  abonent* abonents = NULL;
  int choice, size = 0;

  do {
    print_menu();
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        add_abonent(&abonents, &size);
        break;
      case 2:
        delete_abonent(&abonents, &size);
        break;
      case 3:
        find_abonent(abonents, size);
        break;
      case 4:
        print_abonents(abonents, size);
        break;
      case 5:
        printf("Выходим...\n");
        free_memory(&abonents);
        break;

      default:
        printf("Ошибка! Неверное значение пункта меню.\n");
        break;
    }
  } while (choice != 5);
}

void realloc_memory(abonent** abonents, const int new_size) {
  abonent* temp = (abonent*)realloc(*abonents, new_size * sizeof(abonent));
  if (temp != NULL || (temp == NULL && new_size == 0)) {
    *abonents = temp;
  } else {
    printf("Ошибка при выделении памяти\n");
    free_memory(abonents);
  }
}

void free_memory(abonent** abonents) {
  free(*abonents);
  *abonents = NULL;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void safe_input(char* input, size_t size, const char* prompt) {
  while (1) {
    printf("%s", prompt);
    if (scanf("%9s", input) == 1) {
      if (strlen(input) == size - 1) {
        int c = getchar();
        if (c != '\n' && c != EOF) {
          clear_input_buffer();
          printf("Введено слишком много символов. Попробуйте снова.\n");
          continue;
        }
      }
      break;
    } else {
      printf("Ошибка ввода. Попробуйте снова.\n");
      clear_input_buffer();
    }
  }
}

void add_abonent(abonent** abonents, int* size) {
  realloc_memory(abonents, ++(*size));
  if (*abonents == NULL)
    return;

  safe_input((*abonents)[*size - 1].name, 10, "Введите имя: ");
  safe_input((*abonents)[*size - 1].second_name, 10, "Введите фамилию: ");
  safe_input((*abonents)[*size - 1].tel, 10, "Введите номер телефона: ");

  printf("Абонент добавлен.\n");
}

void delete_abonent(abonent** abonents, int* size) {
  char name[10], second_name[10];
  safe_input(name, 10, "Введите имя: ");
  safe_input(second_name, 10, "Введите фамилию: ");

  int found = 0;
  for (int i = 0; i < *size; i++) {
    if (strcmp((*abonents)[i].name, name) == 0 &&
        strcmp((*abonents)[i].second_name, second_name) == 0) {
      for (int j = i; j < *size - 1; j++) {
        (*abonents)[j] = (*abonents)[j + 1];
      }
      realloc_memory(abonents, --(*size));
      if (*abonents == NULL)
        return;

      printf("Абонент удален.\n");
      found = 1;
    }
  }
  if (!found) {
    printf("Абоненты с таким именем не найдены.\n");
  }
}

void find_abonent(abonent* abonents, const int size) {
  char name[10], second_name[10];
  safe_input(name, 10, "Введите имя: ");
  safe_input(second_name, 10, "Введите фамилию: ");

  int found = 0;
  for (int i = 0; i < size; i++) {
    if (strcmp(abonents[i].name, name) == 0 &&
        strcmp(abonents[i].second_name, second_name) == 0) {
      printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name,
             abonents[i].second_name, abonents[i].tel);
      found = 1;
    }
  }
  if (!found) {
    printf("Абоненты с таким именем не найдены.\n");
  }
}

void print_abonents(abonent* abonents, const int size) {
  for (int i = 0; i < size; i++) {
    printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name,
           abonents[i].second_name, abonents[i].tel);
  }
}
