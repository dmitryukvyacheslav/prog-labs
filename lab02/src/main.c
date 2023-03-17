#include "IntVector.h"

static void testCase(int test) {
  if (test) {
    printf("no\n");
    exit(0);
  } else
    printf("yes\n");
}

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
  testCase(!testVec);
  printf("\tChecking if integer array is allocated... ");
  testCase(!testVec->arr);
  printf("\tChecking if size of new IntVector is 0... ");
  testCase(testVec->size != 0);
  printf("\tChecking if IntVector has desired capacity... ");
  testCase(testVec->cap != (size_t)8);
  printf("== Test 1 passed == \n\n");

  printf("[2] (reserve) Sanity check\n");
  printf("\tChecking if reserve has no effect on lesser capacity... ");
  testCase(!int_vector_reserve(testVec, 4) && testVec->cap != 8);
  printf("\tChecking if reserve increases capacity... ");
  int_vector_reserve(testVec, 16);
  testCase(testVec->cap != 16);
  printf("== Test 2 passed == \n\n");

  printf("[3] (resize) Sanity check\n");
  printf("\tChecking if resize to 0 works... ");
  int_vector_resize(testVec, 0);
  testCase(testVec->size != 0);
  int_vector_resize(testVec, 8);
  printf("\tChecking if resize increases size... ");
  testCase(testVec->size != 8);
  printf("\tChecking if resize can shrink the array... ");
  int_vector_resize(testVec, 4);
  testCase(testVec->size != 4);
  printf("\tChecking if resize can extend array capacity... ");
  size_t _newCap = (testVec->cap) + 1;
  // size_t _oldCap = (testVec->cap);
  int_vector_resize(testVec, _newCap);
  testCase(testVec->size != testVec->cap || testVec->cap != _newCap);
  printf("\tChecking if no memory reallocation occurs on lesser size... ");
  int *old_addr = testVec->arr;
  int_vector_resize(testVec, 2);
  testCase(old_addr != testVec->arr);
  printf("\tChecking if no memory reallocation occurs on equal size... ");
  old_addr = testVec->arr;
  int_vector_resize(testVec, 2);
  testCase(old_addr != testVec->arr);
  printf("\tChecking if resize reinits elements that were previously "
         "out of bounds... ");
  size_t oldSize = testVec->size;
  int_vector_resize(testVec, 8);
  int flag = 0;
  for (size_t i = oldSize; i < testVec->size; i++)
    if (testVec->arr[i] != 0)
      flag = 1;
  testCase(flag == 1);
  printf("== Test 3 passed ==\n\n");

  printf("[4] (get_size, get_capacity) Verify the values after prior"
         "intvector manipulations\n");
  printf("\tChecking if get_size is satisfactory... ");
  size_t _size = int_vector_get_size(testVec);
  testCase(_size != 8);
  printf("\tChecking if get_capacity is satisfactory... ");
  size_t _cap = int_vector_get_capacity(testVec);
  testCase(_cap != 17);
  printf("== Test 4 passed ==\n\n");

  printf("[5] (get_item, set_item) Check getters and setters\n");
  printf("\tChecking if set_item can write to array... ");
  for (size_t i = 0; i < testVec->size; i++)
    int_vector_set_item(testVec, i, (int)i + 90);
  flag = 0;
  for (size_t i = 0; i < testVec->size; i++)
    if (testVec->arr[i] != (int)(i + 90))
      flag = 1;
  testCase(flag);
  printf("\tChecking if set_item can read from array... ");
  flag = 0;
  for (size_t i = 0; i < testVec->size; i++)
    if (int_vector_get_item(testVec, i) != (int)(i + 90))
      flag = 1;
  testCase(flag);
  printf("== Test 5 passed ==\n\n");

  printf("[6] (shrink_to_fit) Edge cases \n");
  printf("\tChecking if shrink_to_fit works in non-edge cases... ");
  int_vector_resize(testVec, 6);
  int_vector_shrink_to_fit(testVec);
  testCase(int_vector_get_capacity(testVec) != 6);
  printf("\tChecking if shrink_to_fit works in edge cases (size=0)... ");
  int_vector_resize(testVec, 0);
  int_vector_shrink_to_fit(testVec);
  testCase(testVec->arr != NULL);
  printf("== Test 6 passed ==\n\n");

  printf("[7] (pop_back, push_back) Check backrank operations\n");
  int_vector_reserve(testVec, 32);
  int_vector_resize(testVec, 31);
  printf("\tChecking if push_back works in non-edge cases... ");
  int_vector_push_back(testVec, 25565);
  testCase(int_vector_get_item(testVec, 31) != 25565);
  printf("\tChecking if push_back works in edge case (size=0)... ");
  int_vector_resize(testVec, 0);
  int_vector_push_back(testVec, 1000 - 7);
  testCase(int_vector_get_item(testVec, 0) != 993);
  printf("\tChecking if push_back increases array capacity to 2n+1... ");
  int_vector_resize(testVec, 32);
  int_vector_push_back(testVec, 11037);
  testCase(int_vector_get_capacity(testVec) != 65 &&
           int_vector_get_item(testVec, 32) != 11037 &&
           int_vector_get_size(testVec) != 33);

  printf("\tChecking if pop_back removes elements... ");
  int_vector_pop_back(testVec);
  testCase(int_vector_get_capacity(testVec) != 65 &&
           int_vector_get_item(testVec, 31) != 25565 &&
           int_vector_get_size(testVec) != 32);
  printf("== Test 7 passed ==\n\n");

  printf("[8] (copy) Intvector copy test\n");
  IntVector *testVec2;
  printf("\tChecking if copy works... ");
  testVec2 = int_vector_copy(testVec);
  testCase(testVec2 == NULL);
  printf("\tChecking if copy is verbatim... ");
  testCase(testVec2->cap != testVec->cap || testVec2->size != testVec->size ||
           memcmp(testVec->arr, testVec2->arr, testVec->size));
  printf("== Test 8 passed ==\n");

  printf("Freeing test vectors... \n");
  int_vector_free(testVec);
  int_vector_free(testVec2);

  printf("\n===== ALL TESTS PASTED =====\n");
  return 0;
}
