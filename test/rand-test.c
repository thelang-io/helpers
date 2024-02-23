/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <the/rand.h>
#include <assert.h>

static int rand_int (void) {
  unsigned char d[4];
  RAND_bytes(d, 4);
  return (d[0] << 24) | (d[1] << 16) | (d[2] << 8) | d[3];
}

static void test_rand_int (void) {
  int num1 = rand_int();
  int num2 = rand_int();

  assert(num1 != num2);
}

int main (void) {
  test_rand_int();
}
