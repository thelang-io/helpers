/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include <assert.h>
#include "../src/rune.h"
#include "../src/string.h"

static void test_rune_byte (void) {
  assert(((void) "Generates byte of 'a'", the_rune_byte(L'a') == 0x61));
  assert(((void) "Generates byte of '0'", the_rune_byte(L'0') == 0x30));
}

static void test_rune_isDigit (void) {
  assert(((void) "Checks 'A'", !the_rune_isDigit(L'A')));
  assert(((void) "Checks 'a'", !the_rune_isDigit(L'a')));
  assert(((void) "Checks '@'", !the_rune_isDigit(L'@')));
  assert(((void) "Checks '0'", the_rune_isDigit(L'0')));
  assert(((void) "Checks '9'", the_rune_isDigit(L'9')));
}

static void test_rune_isLetter (void) {
  assert(((void) "Checks 'A'", the_rune_isLetter(L'A')));
  assert(((void) "Checks 'a'", the_rune_isLetter(L'a')));
  assert(((void) "Checks '@'", !the_rune_isLetter(L'@')));
  assert(((void) "Checks '0'", !the_rune_isLetter(L'0')));
  assert(((void) "Checks '9'", !the_rune_isLetter(L'9')));
}

static void test_rune_isLetterOrDigit (void) {
  assert(((void) "Checks 'A'", the_rune_isLetterOrDigit(L'A')));
  assert(((void) "Checks 'a'", the_rune_isLetterOrDigit(L'a')));
  assert(((void) "Checks '@'", !the_rune_isLetterOrDigit(L'@')));
  assert(((void) "Checks '0'", the_rune_isLetterOrDigit(L'0')));
  assert(((void) "Checks '9'", the_rune_isLetterOrDigit(L'9')));
}

static void test_rune_isLower (void) {
  assert(((void) "Checks 'A'", !the_rune_isLower(L'A')));
  assert(((void) "Checks 'a'", the_rune_isLower(L'a')));
  assert(((void) "Checks '@'", !the_rune_isLower(L'@')));
  assert(((void) "Checks '0'", !the_rune_isLower(L'0')));
  assert(((void) "Checks '9'", !the_rune_isLower(L'9')));
}

static void test_rune_isUpper (void) {
  assert(((void) "Checks 'A'", the_rune_isUpper(L'A')));
  assert(((void) "Checks 'a'", !the_rune_isUpper(L'a')));
  assert(((void) "Checks '@'", !the_rune_isUpper(L'@')));
  assert(((void) "Checks '0'", !the_rune_isUpper(L'0')));
  assert(((void) "Checks '9'", !the_rune_isUpper(L'9')));
}

static void test_rune_isWhitespace (void) {
  assert(((void) "Checks 'A'", !the_rune_isWhitespace(L'A')));
  assert(((void) "Checks 'a'", !the_rune_isWhitespace(L'a')));
  assert(((void) "Checks '@'", !the_rune_isWhitespace(L'@')));
  assert(((void) "Checks '0'", !the_rune_isWhitespace(L'0')));
  assert(((void) "Checks '9'", !the_rune_isWhitespace(L'9')));
}

static void test_rune_lower (void) {
  assert(((void) "Transforms into lowercase 'A'", the_rune_lower(L'A') == L'a'));
  assert(((void) "Transforms into lowercase 'a'", the_rune_lower(L'a') == L'a'));
  assert(((void) "Transforms into lowercase '@'", the_rune_lower(L'@') == L'@'));
  assert(((void) "Transforms into lowercase '0'", the_rune_lower(L'0') == L'0'));
  assert(((void) "Transforms into lowercase '9'", the_rune_lower(L'9') == L'9'));
}

static void test_rune_repeat (void) {
  the_str_t a1 = the_rune_repeat(L'a', 0);
  the_str_t a2 = the_rune_repeat(L'a', 1);
  the_str_t a3 = the_rune_repeat(L'a', 2);
  the_str_t a4 = the_rune_repeat(L'a', 10);

  the_str_t s1_cmp = the_str_alloc(L"");
  the_str_t s2_cmp = the_str_alloc(L"a");
  the_str_t s3_cmp = the_str_alloc(L"aa");
  the_str_t s4_cmp = the_str_alloc(L"aaaaaaaaaa");

  assert(((void) "Repeat 'a' times 0", the_str_eq(a1, s1_cmp)));
  assert(((void) "Repeat 'a' times 1", the_str_eq(a2, s2_cmp)));
  assert(((void) "Repeat 'a' times 2", the_str_eq(a3, s3_cmp)));
  assert(((void) "Repeat 'a' times 10", the_str_eq(a4, s4_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);
  the_str_free(s3_cmp);
  the_str_free(s4_cmp);

  the_str_free(a1);
  the_str_free(a2);
  the_str_free(a3);
  the_str_free(a4);
}

static void test_rune_str (void) {
  the_str_t a1 = the_rune_str(L'A');
  the_str_t a2 = the_rune_str(L'9');

  the_str_t s1_cmp = the_str_alloc(L"A");
  the_str_t s2_cmp = the_str_alloc(L"9");

  assert(((void) "Stringifies 'A'", the_str_eq(a1, s1_cmp)));
  assert(((void) "Stringifies '9'", the_str_eq(a2, s2_cmp)));

  the_str_free(s1_cmp);
  the_str_free(s2_cmp);

  the_str_free(a1);
  the_str_free(a2);
}

static void test_rune_upper (void) {
  assert(((void) "Transforms into uppercase 'A'", the_rune_upper(L'A') == L'A'));
  assert(((void) "Transforms into uppercase 'a'", the_rune_upper(L'a') == L'A'));
  assert(((void) "Transforms into uppercase '@'", the_rune_upper(L'@') == L'@'));
  assert(((void) "Transforms into uppercase '0'", the_rune_upper(L'0') == L'0'));
  assert(((void) "Transforms into uppercase '9'", the_rune_upper(L'9') == L'9'));
}

int main (void) {
  test_rune_byte();
  test_rune_isDigit();
  test_rune_isLetter();
  test_rune_isLetterOrDigit();
  test_rune_isLower();
  test_rune_isUpper();
  test_rune_isWhitespace();
  test_rune_lower();
  test_rune_repeat();
  test_rune_str();
  test_rune_upper();
}
