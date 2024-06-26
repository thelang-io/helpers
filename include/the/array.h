/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_H
#define THE_ARRAY_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error.h>
#include <the/fn.h>
#include <inttypes.h>
#include <string.h>

/**
 * Macro that can be used to define an array object.
 * @param element_type_name Type name of the element.
 * @param element_type Element type of the array object.
 * @param alloc_element_type Element type of the array object to be used inside variadic argument (cast to int in some cases).
 * @param copy_block Block that is used for copy method of array object.
 * @param eq_block Block that is used for equals method of array object.
 * @param free_block Block that is used for free method of array object.
 * @param str_block Block that is used for str method of array object.
 */
#define THE_ARRAY_DEFINE(element_type_name, element_type, alloc_element_type, copy_block, eq_block, free_block, str_block) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(es, bool, bool, FP3##element_type_name) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(es, void, void, FP3##element_type_name##FP3int) \
  THE_FUNCTION_DEFINE_WITH_PARAMS(es, int, int32_t, FP3##element_type_name##FP3##element_type_name) \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_alloc (size_t length, ...) { \
    element_type *data; \
    va_list args; \
    if (length == 0) return (the_arr_##element_type_name##_t) {NULL, 0}; \
    data = the_safe_alloc(length * sizeof(element_type)); \
    va_start(args, length); \
    for (size_t i = 0; i < length; i++) { \
      const element_type element = va_arg(args, alloc_element_type); \
      data[i] = copy_block; \
    } \
    va_end(args); \
    return (the_arr_##element_type_name##_t) {data, length}; \
  } \
  \
  element_type *the_arr_##element_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, int32_t index) { \
    if ((index >= 0 && (size_t) index >= self.len) || (index < 0 && index < -((int32_t) self.len))) { \
      the_str_t message = the_str_alloc(L"index %" PRId32 L" out of array bounds", index); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return index < 0 ? &self.data[self.len + index] : &self.data[index]; \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_clear (the_arr_##element_type_name##_t *self) { \
    the_arr_##element_type_name##_free(*self); \
    self->data = NULL; \
    self->len = 0; \
    return self; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_concat (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t other) { \
    size_t len = self.len + other.len; \
    element_type *data = the_safe_alloc(len * sizeof(element_type)); \
    size_t k = 0; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[k++] = copy_block; \
    } \
    for (size_t i = 0; i < other.len; i++) { \
      const element_type element = other.data[i]; \
      data[k++] = copy_block; \
    } \
    return (the_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  bool the_arr_##element_type_name##_contains (const the_arr_##element_type_name##_t self, const element_type search) { \
    const element_type rhs_element = search; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type lhs_element = self.data[i]; \
      if (eq_block) return true; \
    } \
    return false; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_copy (const the_arr_##element_type_name##_t self) { \
    element_type *data; \
    if (self.len == 0) return (the_arr_##element_type_name##_t) {NULL, 0}; \
    data = the_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[i] = copy_block; \
    } \
    return (the_arr_##element_type_name##_t) {data, self.len}; \
  } \
  \
  bool the_arr_##element_type_name##_empty (const the_arr_##element_type_name##_t self) { \
    return self.len == 0; \
  } \
  \
  bool the_arr_##element_type_name##_eq (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs) { \
    if (self.len != rhs.len) return false; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type lhs_element = self.data[i]; \
      const element_type rhs_element = rhs.data[i]; \
      if (!(eq_block)) return false; \
    } \
    return true; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_filter (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_esFP3##element_type_name##FRboolFE_t predicate) { \
    size_t len = 0; \
    element_type *data = the_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      if ( \
        predicate.func( \
          predicate.ctx, \
          the_safe_calloc( \
            &(the_fn_esFP3##element_type_name##FRboolFE_params_t) {state, line, col, self.data[i]}, \
            sizeof(the_fn_esFP3##element_type_name##FRboolFE_params_t) \
          ) \
        ) \
      ) { \
        const element_type element = self.data[i]; \
        data[len++] = copy_block; \
      } \
    } \
    return (the_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  element_type *the_arr_##element_type_name##_first (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      the_str_t message = the_str_alloc(L"tried getting first element of empty array"); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[0]; \
  } \
  \
  void the_arr_##element_type_name##_forEach (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_esFP3##element_type_name##FP3intFRvoidFE_t iterator) { \
    for (size_t i = 0; i < self.len; i++) { \
      iterator.func( \
        iterator.ctx, \
        the_safe_calloc( \
          &(the_fn_esFP3##element_type_name##FP3intFRvoidFE_params_t) {state, line, col, self.data[i], i}, \
          sizeof(the_fn_esFP3##element_type_name##FP3intFRvoidFE_params_t) \
        ) \
      ); \
    } \
  } \
  \
  void the_arr_##element_type_name##_free (the_arr_##element_type_name##_t self) { \
    for (size_t i = 0; i < self.len; i++) { \
      element_type element = self.data[i]; \
      free_block; \
    } \
    if (self.data != NULL) the_safe_free(self.data); \
  } \
  \
  the_str_t the_arr_##element_type_name##_join (const the_arr_##element_type_name##_t self, unsigned char o1, const the_str_t separator) { \
    the_str_t x = o1 == 0 ? the_str_alloc(L",") : separator; \
    the_str_t result = (the_str_t) {NULL, 0, false}; \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      if (i != 0) result = the_str_realloc(result, the_str_concat(result, x)); \
      result = the_str_realloc(result, the_str_concat(result, str_block)); \
    } \
    if (o1 == 0) the_str_free(x); \
    return result; \
  } \
  \
  element_type *the_arr_##element_type_name##_last (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self) { \
    if (self->len == 0) { \
      the_str_t message = the_str_alloc(L"tried getting last element of empty array"); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    return &self->data[self->len - 1]; \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_merge (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t other) { \
    size_t k = self->len; \
    self->len += other.len; \
    self->data = the_safe_realloc(self->data, self->len * sizeof(element_type)); \
    for (size_t i = 0; i < other.len; i++) { \
      const element_type element = other.data[i]; \
      self->data[k++] = copy_block; \
    } \
    return self; \
  } \
  \
  element_type the_arr_##element_type_name##_pop (the_arr_##element_type_name##_t *self) { \
    self->len--; \
    return self->data[self->len]; \
  } \
  \
  void the_arr_##element_type_name##_push (the_arr_##element_type_name##_t *self, size_t length, ...) { \
    va_list args; \
    if (length == 0) return; \
    self->len += length; \
    self->data = the_safe_realloc(self->data, self->len * sizeof(element_type)); \
    va_start(args, length); \
    for (size_t i = self->len - length; i < self->len; i++) { \
      const element_type element = va_arg(args, alloc_element_type); \
      self->data[i] = copy_block; \
    } \
    va_end(args); \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_realloc (the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs) { \
    the_arr_##element_type_name##_free(self); \
    return the_arr_##element_type_name##_copy(rhs); \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_remove (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, int32_t index) { \
    size_t i; \
    element_type element; \
    if ((index >= 0 && (size_t) index >= self->len) || (index < 0 && index < -((int32_t) self->len))) { \
      the_str_t message = the_str_alloc(L"index %" PRId32 " out of array bounds", index); \
      the_error_assign_generic(state, line, col, message); \
      the_str_free(message); \
      longjmp(state->buf_last->buf, state->id); \
    } \
    i = index < 0 ? index + self->len : index; \
    element = self->data[i]; \
    free_block; \
    if (i != self->len - 1) { \
      memmove(&self->data[i], &self->data[i + 1], (--self->len - i) * sizeof(element_type)); \
    } else { \
      self->len--; \
    } \
    return self; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_reverse (const the_arr_##element_type_name##_t self) { \
    element_type *data; \
    if (self.len == 0) { \
      return (the_arr_##element_type_name##_t) {NULL, 0}; \
    } \
    data = the_safe_alloc(self.len * sizeof(element_type)); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      data[i] = copy_block; \
    } \
    return (the_arr_##element_type_name##_t) {data, self.len}; \
  } \
  \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_slice (const the_arr_##element_type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end) { \
    int32_t i = 0; \
    int32_t j = 0; \
    element_type *data; \
    size_t len; \
    if (o1 != 0 && start < 0 && start >= -((int32_t) self.len)) { \
      i = (int32_t) ((size_t) start + self.len); \
    } else if (o1 != 0 && start >= 0) { \
      i = (int32_t) ((size_t) start > self.len ? self.len : (size_t) start); \
    } \
    if (o2 == 0 || (end >= 0 && (size_t) end > self.len)) { \
      j = (int32_t) self.len; \
    } else if (end < 0 && end >= -((int32_t) self.len)) { \
      j = (int32_t) ((size_t) end + self.len); \
    } else if (end >= 0) { \
      j = (int32_t) end; \
    } \
    if (i > j || (size_t) i >= self.len) { \
      return (the_arr_##element_type_name##_t) {NULL, 0}; \
    } \
    len = j - i; \
    data = the_safe_alloc(len * sizeof(element_type)); \
    for (size_t k = 0; i < j; i++) { \
      const element_type element = self.data[i]; \
      data[k++] = copy_block; \
    } \
    return (the_arr_##element_type_name##_t) {data, len}; \
  } \
  \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_sort (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, const the_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_t comparator) { \
    if (self->len <= 1) return self; \
    while (1) { \
      unsigned char b = 0; \
      for (size_t i = 1; i < self->len; i++) { \
        int32_t c = comparator.func( \
          comparator.ctx, \
          the_safe_calloc( \
            &(the_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_params_t) {state, line, col, self->data[i - 1], self->data[i]}, \
            sizeof(the_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_params_t) \
          ) \
        ); \
        if (c > 0) { \
          element_type t = self->data[i]; \
          self->data[i] = self->data[i - 1]; \
          self->data[i - 1] = t; \
          b = 1; \
        } \
      } \
      if (b == 0) return self; \
    } \
  } \
  \
  the_str_t the_arr_##element_type_name##_str (const the_arr_##element_type_name##_t self) { \
    the_str_t b = the_str_alloc(L"]"); \
    the_str_t c = the_str_alloc(L", "); \
    the_str_t r = the_str_alloc(L"["); \
    for (size_t i = 0; i < self.len; i++) { \
      const element_type element = self.data[i]; \
      if (i != 0) r = the_str_realloc(r, the_str_concat(r, c)); \
      r = the_str_realloc(r, the_str_concat(r, str_block)); \
    } \
    r = the_str_realloc(r, the_str_concat(r, b)); \
    the_str_free(b); \
    the_str_free(c); \
    return r; \
  }

#endif
