/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef TEST_ANY_TEST_H
#define TEST_ANY_TEST_H

#include "../src/any.h"
#include "../src/number.h"
#include "../src/safe.h"

#define TYPE_u64 1

the_any_t any_u64 (uint64_t value);
void *any_u64_copy (const void *ctx);
bool any_u64_eq (const void *lhs_ctx, const void *rhs_ctx);
void any_u64_free (void *ctx);
the_str_t any_u64_str (const void *ctx);

the_any_t any_u64 (uint64_t value) {
  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
  *data = value;
  return (the_any_t) {TYPE_u64, data, any_u64_copy, any_u64_eq, any_u64_free, any_u64_str};
}

void *any_u64_copy (const void *ctx) {
  uint64_t *data = the_safe_alloc(sizeof(uint64_t));
  *data = *(const uint64_t *) ctx;
  return data;
}

bool any_u64_eq (const void *lhs_ctx, const void *rhs_ctx) {
  return *(const uint64_t *) lhs_ctx == *(const uint64_t *) rhs_ctx;
}

void any_u64_free (void *ctx) {
  the_safe_free(ctx);
}

the_str_t any_u64_str (const void *ctx) {
  return the_u64_str(*(const uint64_t *) ctx);
}

#endif
