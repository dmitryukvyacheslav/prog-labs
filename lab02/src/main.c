#include "IntVector.h"

int main(void) {
  printf(
      "\n /$$$$$$             /$$   /$$    /$$                      /$$       "
      "                 \n");
  printf("|_  $$_/            | $$  | $$   | $$                     | $$       "
         "                 \n");
  printf("  | $$   /$$$$$$$  /$$$$$$| $$   | $$ /$$$$$$   /$$$$$$$ /$$$$$$    "
         "/$$$$$$   /$$$$$$ \n");
  printf("  | $$  | $$__  $$|_  $$_/|  $$ / $$//$$__  $$ /$$_____/|_  $$_/   "
         "/$$__  $$ /$$__  $$\n");
  printf("  | $$  | $$  \\ $$  | $$   \\  $$ $$/| $$$$$$$$| $$        | $$    "
         "| $$  \\ $$| $$  \\__/\n");
  printf("  | $$  | $$  | $$  | $$ /$$\\  $$$/ | $$_____/| $$        | $$ /$$| "
         "$$  | $$| $$      \n");
  printf(" /$$$$$$| $$  | $$  |  $$$$/ \\  $/  |  $$$$$$$|  $$$$$$$  |  $$$$/| "
         " $$$$$$/| $$      \n");
  printf("|______/|__/  |__/   \\___/    \\_/    \\_______/ \\_______/   "
         "\\___/   \\______/ |__/      \n");
  printf("MOTD: For all last-minute changes and notes, please visit "
         "admomsk.ru.\n");

  printf("\n[1] (new) Sanity check\n");
  IntVector *testVec = int_vector_new(8);

  printf("\tChecking if structure is allocated... ");
  if (!testVec) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  printf("\tChecking if integer array is allocated... ");
  if (!testVec->arr) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if size of new IntVector is 0... ");
  if (testVec->size != 0) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if IntVector has desired capacity... ");
  if (testVec->cap != (size_t)8) {
    printf("no (was %llu)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("== Test 1 passed == \n\n");

  printf("[2] (reserve) Sanity check\n");
  printf("\tChecking if reserve has no effect on lesser capacity... ");
  if (!int_vector_reserve(testVec, 4) && testVec->cap != 8) {
    printf("no (cap is now %llu)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("\tChecking if reserve increases capacity... ");
  int_vector_reserve(testVec, 16);
  if (testVec->cap != 16) {
    printf("no (capacity was %lld)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("== Test 2 passed == \n\n");

  printf("[3] (resize) Sanity check\n");
  int_vector_resize(testVec, 8);

  printf("\tChecking if resize increases size... ");
  if (testVec->size != 8) {
    printf("no (size was %lld)\n", testVec->size);
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if resize can shrink the array... ");
  int_vector_resize(testVec, 4);
  if (testVec->size != 4) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if no memory reallocation occurs on lesser size... ");
  int *old_addr = testVec->arr;
  int_vector_resize(testVec, 2);
  if (old_addr != testVec->arr) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if no memory reallocation occurs on equal size... ");
  old_addr = testVec->arr;
  int_vector_resize(testVec, 2);
  if (old_addr != testVec->arr) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if resize reinits elements that were previously out of "
         "bounds... ");
  int oldSize = testVec->size;
  int_vector_resize(testVec, 8);
  int flag = 0;
  for (size_t i = oldSize; i < testVec->size; i++)
    if (testVec->arr[i] != 0)
      flag = 1;
  if (flag == 1) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  printf("== Test 3 passed ==\n\n");

  printf("[4] (get_size, get_capacity) Verify the values after prior intvector "
         "manipulations\n");
  printf("\tChecking if get_size is satisfactory... ");
  int _size = int_vector_get_size(testVec);
  if (_size != 8) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if get_capacity is satisfactory... ");
  int _cap = int_vector_get_capacity(testVec);
  if (_cap != 16) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("== Test 4 passed ==\n\n");

  printf("[5] (get_item, set_item) Check getters and setters\n");
  printf("\tChecking if set_item can write to array... ");
  for (size_t i = 0; i < testVec->size; i++)
    int_vector_set_item(testVec, i, i + 90);
  flag = 0;
  for (size_t i = 0; i < testVec->size; i++)
    if (testVec->arr[i] != (int)(i + 90))
      flag = 1;
  if (flag) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  printf("\tChecking if set_item can read from array... ");
  flag = 0;
  for (size_t i = 0; i < testVec->size; i++)
    if (int_vector_get_item(testVec, i) != (int)(i + 90))
      flag = 1;
  if (flag) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  printf("== Test 5 passed ==\n\n");

  printf("[6] (push_back) Edge case check\n");

  printf("\tChecking if push works in non-edgecases... ");

  int_vector_resize(testVec,14);
  printf("size: %lld cap: %lld", testVec->size, testVec->cap);
  int_vector_push_back(testVec, 1337);
  if (int_vector_get_item(testVec, testVec->size-1) != 1337) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if push can extend the array... ");
  printf("ok");
  int_vector_push_back(testVec, 1338);
  printf("ok2");
  if (int_vector_get_item(testVec, testVec->size-1) != 1338 && testVec->size == 32) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  
  printf("\tChecking if push works in edgecase (size=0)... ");
  int_vector_resize(testVec, 0);
  int_vector_push_back(testVec, 1339);
   if (int_vector_get_item(testVec, 0) != 1339) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if push works in edgecase (size=0, cap=0)... ");
  int_vector_resize(testVec, 0);
  int_vector_shrink_to_fit(testVec);
  
  int_vector_push_back(testVec, 1339);
  if (int_vector_get_item(testVec, 0) != 1339) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  return 0;
}