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
    printf("no (was %zu)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("== Test 1 passed == \n\n");

  printf("[2] (reserve) Sanity check\n");
  printf("\tChecking if reserve has no effect on lesser capacity... ");
  if (!int_vector_reserve(testVec, 4) && testVec->cap != 8) {
    printf("no (cap is now %zu)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("\tChecking if reserve increases capacity... ");
  int_vector_reserve(testVec, 16);
  if (testVec->cap != 16) {
    printf("no (capacity was %zu)\n", testVec->cap);
    return 0;
  } else
    printf("yes\n");
  printf("== Test 2 passed == \n\n");

  printf("[3] (resize) Sanity check\n");
  printf("\tChecking if resize to 0 works... ");
  int_vector_resize(testVec, 0);
  if (testVec->size != 0){
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
  
  int_vector_resize(testVec, 8);
  printf("\tChecking if resize increases size... ");
  if (testVec->size != 8) {
    printf("no (size was %zu)\n", testVec->size);
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
	
	printf("\tChecking if resize can extend array capacity... ");
	size_t _newCap = (testVec->cap)+1;
	size_t _oldCap = (testVec->cap);
  int_vector_resize(testVec, _newCap);
  if (testVec->size != testVec->cap || testVec->cap != _newCap) {
    printf("no (old capacity was %zu, new size=capacity is %zu, but now size is %zu and cap is %zu\n", _oldCap, _newCap, testVec->size, testVec->cap);
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
  size_t oldSize = testVec->size;
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
  size_t _size = int_vector_get_size(testVec);
  if (_size != 8) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("\tChecking if get_capacity is satisfactory... ");
  size_t _cap = int_vector_get_capacity(testVec);
  if (_cap != 17) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");

  printf("== Test 4 passed ==\n\n");

  printf("[5] (get_item, set_item) Check getters and setters\n");
  printf("\tChecking if set_item can write to array... ");
  for (size_t i = 0; i < testVec->size; i++)
    int_vector_set_item(testVec, i, (int)i + 90);
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

	printf("[6] (shrink_to_fit) Edge cases \n");
	printf("\tChecking if shrink_to_fit works in non-edge cases... ");
	int_vector_resize(testVec, 6);
	int_vector_shrink_to_fit(testVec);
	if(int_vector_get_capacity(testVec) != 6){
    printf("no\n");
    return 0;
  } else
  printf("yes\n");
  
  printf("\tChecking if shrink_to_fit works in edge cases (size=0)... ");
	int_vector_resize(testVec, 0);
	int_vector_shrink_to_fit(testVec);
  if (testVec->arr != NULL){
    printf("no\n");
    return 0;
  } else
  printf("yes\n");
  printf("== Test 6 passed ==\n\n");

	printf("[7] (pop_back, push_back) Check backrank operations\n");
	int_vector_reserve(testVec, 32);
	int_vector_resize(testVec, 31);
	
	printf("\tChecking if push_back works in non-edge cases... ");
	int_vector_push_back(testVec, 25565);
	if(int_vector_get_item(testVec, 31) != 25565){
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
    
  printf("\tChecking if push_back works in edge case (size=0)... ");
  int_vector_resize(testVec, 0);
	int_vector_push_back(testVec, 1000-7); 
	if(int_vector_get_item(testVec, 0) != 993) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");
    
  printf("\tChecking if push_back increases array capacity to 2n+1... ");
  int_vector_resize(testVec, 32);
	int_vector_push_back(testVec, 11037);
	if(int_vector_get_capacity(testVec) != 65 &&
		int_vector_get_item(testVec, 32) != 11037 &&
		int_vector_get_size(testVec) != 33) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n"); 
    
  printf("\tChecking if pop_back removes elements... ");
	int_vector_pop_back(testVec);
	if(int_vector_get_capacity(testVec) != 65 &&
		int_vector_get_item(testVec, 31) != 25565 &&
		int_vector_get_size(testVec) != 32) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n");  
  printf("== Test 7 passed ==\n\n");

  printf("[8] (copy) Intvector copy test\n");
  IntVector* testVec2;

  printf("\tChecking if copy works... ");
  testVec2 = int_vector_copy(testVec);
  if (testVec2 == NULL){
    printf("no\n");
    return 0;
  } else
    printf("yes\n"); 

  printf("\tChecking if copy is verbatim... ");
  if (testVec2->cap != testVec->cap || testVec2->size != testVec->size || memcmp(testVec->arr, testVec2->arr, testVec->size)) {
    printf("no\n");
    return 0;
  } else
    printf("yes\n"); 
  printf("== Test 8 passed ==\n");
  printf("Freeing test vectors... \n");
  int_vector_free(testVec);
  int_vector_free(testVec2);
  printf("\n===== ALL TESTS PASTED =====\n");
	return 0;
}
