#pragma once

#include <cstddef>
#include <iostream>
#include <new>     // for placement new
#include <utility> // for forward

template <size_t SIZE, typename... Types>
constexpr void
allocate(void *memory,
         Types &&...args) requires(... && std::is_copy_constructible_v<Types>) {
  size_t requiredSize = (0 + ... + sizeof(std::decay_t<Types>));

  if (requiredSize > SIZE) {
    throw std::bad_alloc();
  }

  auto construct = [memory, offset = size_t{0}](auto &&arg) mutable {
    using T = std::decay_t<decltype(arg)>;
    void *ptr = static_cast<char *>(memory) + offset;
    new (ptr) T(std::forward<decltype(arg)>(arg)); // placement new
    offset += sizeof(T);
  };

  (..., construct(std::forward<Types>(args)));
}