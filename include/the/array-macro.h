/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#ifndef THE_ARRAY_MACRO_H
#define THE_ARRAY_MACRO_H

/* See https://github.com/thelang-io/helpers for reference. */

#include <the/error-type.h>
#include <the/fn-macro.h>
#include <stdarg.h>
#include <stdint.h>

/**
 * Macro that should be used to generate array type.
 * @param element_type_name Name of the element type.
 * @param element_type Element type of the array object.
 */
#define THE_ARRAY_DECLARE(element_type_name, element_type) \
  THE_FUNCTION_DECLARE_WITH_PARAMS(es, bool, bool, FP3##element_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(es, void, void, FP3##element_type_name##FP3int, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
    int32_t n1; \
  }) \
  \
  THE_FUNCTION_DECLARE_WITH_PARAMS(es, int, int32_t, FP3##element_type_name##FP3##element_type_name, { \
    the_err_state_t *state; \
    int line; \
    int col; \
    element_type n0; \
    element_type n1; \
  }) \
  \
  /** Object representation of the array type. */ \
  typedef struct { \
    element_type *data; \
    size_t len; \
  } the_arr_##element_type_name##_t; \
  \
  /**
   * Allocates array object.
   * @param length Amount of elements passed in variadic.
   * @param ... Elements to copy into resulting array.
   * @return Allocated array object.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_alloc (size_t length, ...); \
  \
  /**
   * Accesses element by index and returns its reference.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @param index Index of element inside array.
   * @return Reference to found element.
   */ \
  element_type *the_arr_##element_type_name##_at (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, int32_t index); \
  \
  /**
   * Removes all elements and changes length to zero.
   * @param self Array to perform action on.
   * @return Reference to self.
   */ \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_clear (the_arr_##element_type_name##_t *self); \
  \
  /**
   * Concatenates two arrays into one and returns resulting array.
   * @param self First array to concatenate.
   * @param other First array to concatenate.
   * @return Array created as a result of concatenation.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_concat (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t other); \
  \
  /**
   * Checks whether certain element exists.
   * @param self Array to perform action on.
   * @param search Element to search for.
   * @return Whether certain element exists inside array.
   */ \
  bool the_arr_##element_type_name##_contains (const the_arr_##element_type_name##_t self, const element_type search); \
  \
  /**
   * Copies array object.
   * @param self Array to perform action on.
   * @return Newly copied array object.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_copy (const the_arr_##element_type_name##_t self); \
  \
  /**
   * Checks whether array has elements.
   * @param self Array to perform action on.
   * @return Whether array has elements.
   */ \
  bool the_arr_##element_type_name##_empty (const the_arr_##element_type_name##_t self); \
  \
  /**
   * Compares two array objects.
   * @param self First array object to compare.
   * @param rhs Second array object to compare.
   * @return Whether two array objects are the same.
   */ \
  bool the_arr_##element_type_name##_eq (const the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs); \
  \
  /**
   * Calls `predicate` on every element and constructs array copy out of elements that passed the test.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @param predicate Function to execute on each element of the array. Should return a truthy value to keep the element in the resulting array.
   * @return Array constructed out of elements that passed the test.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_filter (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_esFP3##element_type_name##FRboolFE_t predicate); \
  \
  /**
   * Returns reference to first element.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @return Reference to first element.
   */ \
  element_type *the_arr_##element_type_name##_first (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self); \
  \
  /**
   * Calls `iterator` on every element.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @param iterator Function to execute on each element of the array.
   */ \
  void the_arr_##element_type_name##_forEach (the_err_state_t *state, int line, int col, const the_arr_##element_type_name##_t self, const the_fn_esFP3##element_type_name##FP3intFRvoidFE_t iterator); \
  \
  /**
   * Deallocates array object.
   * @param self Array to perform action on.
   */ \
  void the_arr_##element_type_name##_free (the_arr_##element_type_name##_t self); \
  \
  /**
   * Calls `str` method on every element and joins result with separator.
   * @param self Array to perform action on.
   * @param o1 Whether separator parameter has value passed into it.
   * @param separator Elements separator. The default is comma string.
   * @return String constructed as the result of joining elements with separator.
   */ \
  the_str_t the_arr_##element_type_name##_join (const the_arr_##element_type_name##_t self, unsigned char o1, const the_str_t separator); \
  \
  /**
   * Returns reference to last element.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @return Reference to last element.
   */ \
  element_type *the_arr_##element_type_name##_last (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self); \
  \
  /**
   * Merges other array’s elements into calling array.
   * @param self Array to perform action on.
   * @param other Another array you want to merge.
   * @return Reference to self.
   */ \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_merge (the_arr_##element_type_name##_t *self, const the_arr_##element_type_name##_t other); \
  \
  /**
   * Removes last element from array and returns it.
   * @param self Array to perform action on.
   * @return The element removed.
   */ \
  element_type the_arr_##element_type_name##_pop (the_arr_##element_type_name##_t *self); \
  \
  /**
   * Adds new elements into array.
   * @param self Array to perform action on.
   * @param length Amount of new elements.
   * @param ... New elements to copy into array.
   */ \
  void the_arr_##element_type_name##_push (the_arr_##element_type_name##_t *self, size_t length, ...); \
  \
  /**
   * Reallocates first array object and returns copy of second array object.
   * @param self Array object to reallocate.
   * @param rhs Array object to copy from.
   * @return Second array object copied.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_realloc (the_arr_##element_type_name##_t self, const the_arr_##element_type_name##_t rhs); \
  \
  /**
   * Removes element corresponding to specific index from array.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @param index Element index to remove from array.
   * @return Reference to self.
   */ \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_remove (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, int32_t index); \
  \
  /**
   * Returns reversed copy of the array.
   * @param self Array to perform action on.
   * @return Reversed copy of the array.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_reverse (const the_arr_##element_type_name##_t self); \
  \
  /**
   * Extracts array slice from `start` (inclusive) to `end` (non-inclusive).
   * @param self Array to perform action on.
   * @param o1 Whether start parameter is passed.
   * @param start Index at which to start extraction. The default is zero.
   * @param o2 Whether end parameter is passed.
   * @param end Index at which to end extraction. The default is array length.
   * @return Array constructed as a result of extraction.
   */ \
  the_arr_##element_type_name##_t the_arr_##element_type_name##_slice (const the_arr_##element_type_name##_t self, unsigned int o1, int32_t start, unsigned int o2, int32_t end); \
  \
  /**
   * Sorts elements of the array in place.
   * @param state Error state to perform action on.
   * @param line Line where error appeared.
   * @param col Line column where error appeared.
   * @param self Array to perform action on.
   * @param comparator Function that defines the sort order.
   * @return Reference to self.
   */ \
  the_arr_##element_type_name##_t *the_arr_##element_type_name##_sort (the_err_state_t *state, int line, int col, the_arr_##element_type_name##_t *self, const the_fn_esFP3##element_type_name##FP3##element_type_name##FRintFE_t comparator); \
  \
  /**
   * Generates string representation of the array object.
   * @param self Array object to generate string representation for.
   * @return String representation of the array object.
   */ \
  the_str_t the_arr_##element_type_name##_str (const the_arr_##element_type_name##_t self);

#endif
