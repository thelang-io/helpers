/*!
 * Copyright (c) Aaron Delasy
 * Licensed under the MIT License
 */

#include "number.h"
#include <d4/string.h>
#include <inttypes.h>

static d4_str_t str_float_truncate (d4_str_t s) {
  for (size_t i = s.len - 1; i >= 1; i--) {
    if (s.data[i] == '0' && s.data[i - 1] != '.') {
      s.data[i] = '\0';
      s.len--;
      continue;
    }

    break;
  }

  return s;
}

d4_str_t d4_f32_str (float self) {
  return str_float_truncate(d4_str_alloc(L"%f", (double) self));
}

d4_str_t d4_f64_str (double self) {
  return str_float_truncate(d4_str_alloc(L"%f", self));
}

d4_str_t d4_float_str (double self) {
  return str_float_truncate(d4_str_alloc(L"%f", self));
}

d4_str_t d4_i8_str (int8_t self) {
  return d4_str_alloc(L"%" PRId8, self);
}

d4_str_t d4_i16_str (int16_t self) {
  return d4_str_alloc(L"%" PRId16, self);
}

d4_str_t d4_i32_str (int32_t self) {
  return d4_str_alloc(L"%" PRId32, self);
}

d4_str_t d4_i64_str (int64_t self) {
  return d4_str_alloc(L"%" PRId64, self);
}

d4_str_t d4_int_str (int32_t self) {
  return d4_str_alloc(L"%" PRId32, self);
}

d4_str_t d4_isize_str (ptrdiff_t self) {
  return d4_str_alloc(L"%zd", self);
}

d4_str_t d4_u8_str (uint8_t self) {
  return d4_str_alloc(L"%" PRIu8, self);
}

d4_str_t d4_u16_str (uint16_t self) {
  return d4_str_alloc(L"%" PRIu16, self);
}

d4_str_t d4_u32_str (uint32_t self) {
  return d4_str_alloc(L"%" PRIu32, self);
}

d4_str_t d4_u64_str (uint64_t self) {
  return d4_str_alloc(L"%" PRIu64, self);
}

d4_str_t d4_usize_str (size_t self) {
  return d4_str_alloc(L"%zu", self);
}
