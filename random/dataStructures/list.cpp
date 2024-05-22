#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <optional>

struct List {
  int value;
  struct List *next;
};

void listPush(struct List *xs, int x) {
  // find the end of the list
  List *current = xs;
  while (current->next != NULL) {
    current = current->next;
  }
  // add to the end
  current->next = (List *)malloc(sizeof(List));
  current->next->value = x;
  current->next->next = NULL;
}

void listAppend(List **xs, int x) {
  // init the head of the new list
  List *xs_new;
  xs_new = (List *)malloc(sizeof(List));
  // push the new value to the new list
  xs_new->value = x;
  // add the old list to the new list
  xs_new->next = *xs;
  // reasign the old list to the new list
  *xs = xs_new;
}

void listPrint(List *xs) {

  if (xs == NULL) {
    printf("[]\n");
    return;
  }

  List *current = xs;
  printf("[ ");
  while (current != NULL) {
    printf("%d, ", current->value);
    current = current->next;
  }
  printf("\b\b ]\n");
}

void listFromArray(int *arr, size_t size, List **xs) {
  while (size > 0) {
    listAppend(xs, arr[size - 1]);
    --size;
  }
}

std::optional<int> listPop(List **xs) {
  if (*xs == NULL) {
    return std::nullopt;
  }
  List *xs_new = (*xs)->next;
  int x = (*xs)->value;
  free(*xs);
  *xs = xs_new;

  return x;
}

std::optional<int> listPopAt(List **xs, size_t idx) {
  if (*xs == NULL) {
    return std::nullopt; // Indicate failure due to empty list
  }

  List *current = *xs;
  List *previous = NULL;
  std::optional<int> result = std::nullopt;

  // If the index is 0, we need to pop the head
  if (idx == 0) {
    *xs = current->next; // Update head to the next element
    result = std::optional(current->value);
    free(current);                // Free the old head
    return std::optional(result); // Indicate success
  }

  // Traverse the list to find the node at index idx
  while (current != NULL && idx > 0) {
    previous = current;
    current = current->next;
    --idx;
  }

  // If current is NULL, the index was out of bounds
  if (current == NULL) {
    return result; // Indicate failure due to out of bounds index
  }

  // Pop the element at the given index
  *result = current->value;
  previous->next = current->next;
  free(current); // Free the node

  return std::optional(*result); // Indicate success
}

// Same as popAt but does not pop, only returns the element
std::optional<int> listGetElem(List *xs, size_t idx) {
  List *current = xs;
  while (idx > 0 && current != NULL) {
    current = current->next;
    --idx;
  }
  if (current == NULL) {
    return std::nullopt;
  } else if (idx > 0) {
    return std::nullopt;
  } else {
    return std::optional(current->value);
  }
}

// 1 -> 2 -> 3 -> x
// x <- 1 2 -> 3 -> x
// x <- 1 <- 2 3 -> x
// x <- 1 <- 2 <- 3 x
void listReverse(List **xs) {
  if (*xs == NULL || (*xs)->next == NULL) {
    return;
  }

  List *previous = NULL;
  List *current = *xs;
  List *next = NULL;

  while (current != NULL) {
    next = current->next;     // Save the next node
    current->next = previous; // Reverse the current node's pointer
    previous = current;       // Move previous to this node
    current = next;           // Move to the next node
  }

  // Update the head pointer to the new head (last node processed)
  *xs = previous;
}

// bubble sort
void listSort(List **xs) {
  if (*xs == NULL || (*xs)->next == NULL) {
    return;
  }

  for (List *inner = *xs; inner != NULL; inner = inner->next) {
    for (List *outer = inner; outer != NULL; outer = outer->next) {
      if (inner->value > outer->value) {
        int keeper = inner->value;
        inner->value = outer->value;
        outer->value = keeper;
      }
    }
  }
}

bool listQueryFor(List *xs, int x) {
  while (xs != NULL) {
    if (xs->value == x) {
      return true;
    }
    xs = xs->next;
  }
  return false;
}

bool listDelete(List *xs) {
  while (xs != NULL) {
    List *keeper = xs->next;
    free(xs);
    xs = keeper;
  }
  return false;
}

int main() {
  int arr[10] = {5, 2, -8, 4, 7};
  // int arr[10] = {5};
  List *xs = NULL;

  listFromArray(arr, 5, &xs);
  listPrint(xs);

  // printf("%d\n", listPop(&xs).value());
  // listPrint(xs);
  //
  // printf("%d\n", listPopAt(&xs, 1).value());
  // listPrint(xs);

  listReverse(&xs);
  listPrint(xs);

  listSort(&xs);
  listPrint(xs);

  std::cout << listGetElem(xs, 1).value() << std::endl;
  std::cout << listQueryFor(xs, -8) << std::endl;
  listPrint(xs);

  listDelete(xs);
  // listPrint(xs);

  return 0;
}
