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

void add_abonent(abonent** abonents, int* size) {
  realloc_memory(abonents, ++(*size));
  if (*abonents == NULL)
    return;

  printf("Введите имя: ");
  scanf("%9s", (*abonents)[*size - 1].name);
  printf("Введите фамилию: ");
  scanf("%9s", (*abonents)[*size - 1].second_name);
  printf("Введите номер телефона: ");
  scanf("%9s", (*abonents)[*size - 1].tel);

  printf("Абонент добавлен.\n");
}

void delete_abonent(abonent** abonents, int* size) {
  char name[10];
  printf("Введите имя абонента для удаления: ");
  scanf("%9s", name);

  for (int i = 0; i < *size; i++) {
    if (strcmp((*abonents)[i].name, name) == 0) {
      for (int j = i; j < *size - 1; j++) {
        (*abonents)[j] = (*abonents)[j + 1];
      }
      realloc_memory(abonents, --(*size));
      if (*abonents == NULL)
        return;

      printf("Абонент удален.\n");
      return;
    }
  }
  printf("Абонент с таким именем не найден.\n");
}

void find_abonent(abonent* abonents, const int size) {
  char name[10];
  printf("Введите имя для поиска: ");
  scanf("%9s", name);

  int found = 0;
  for (int i = 0; i < size; i++) {
    if (strcmp(abonents[i].name, name) == 0) {
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
