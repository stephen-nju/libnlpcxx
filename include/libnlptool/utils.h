
#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
#include "commom.h"
#include "spdlog/spdlog.h"
#include "utf8proc.h"

#ifdef _MSC_VER
#    define _CRT_SECURE_NO_WARNINGS 1
#endif

using namespace std;
namespace nlptools {

inline size_t readline(char** __restrict line, size_t* __restrict len, FILE* __restrict fp) {
    // Check if either line, len or fp are NULL pointers
    if (line == NULL || len == NULL || fp == NULL) {
        errno = EINVAL;
        return -1;
    }

    // Use a chunk array of 512 bytes as parameter for fgets
    char chunk[512];

    // Allocate a block of memory for *line if it is NULL or smaller than the chunk array
    if (*line == NULL || *len < sizeof(chunk)) {
        *len = sizeof(chunk);
        if ((*line = (char*)malloc(*len)) == NULL) {
            errno = ENOMEM;
            return -1;
        }
    }

    // "Empty" the string
    (*line)[0] = '\0';

    while (fgets(chunk, sizeof(chunk), fp) != NULL) {
        // Resize the line buffer if necessary
        size_t len_used = strlen(*line);
        size_t chunk_used = strlen(chunk);

        if (*len - len_used < chunk_used) {
            // Check for overflow
            if (*len > SIZE_MAX / 2) {
                errno = EOVERFLOW;
                return -1;
            } else {
                *len *= 2;
            }

            if ((*line = (char*)realloc(*line, *len)) == NULL) {
                errno = ENOMEM;
                return -1;
            }
        }

        // Copy the chunk to the end of the line buffer
        memcpy(*line + len_used, chunk, chunk_used);
        len_used += chunk_used;
        (*line)[len_used] = '\0';
        // Check if *line contains '\n', if yes, return the *line length
        if ((*line)[len_used - 1] == '\n') {
            return len_used;
        }
    }
    return -1;
}
ssize_t utf8proc_iterate_reversed(const uint8_t* str, ssize_t start, int32_t* dst);
absl::string_view rstrip(absl::string_view& s);
absl::string_view lstrip(absl::string_view& s);
absl::string_view strip(absl::string_view& s);

}  // namespace nlptools

#endif  // UTIL_H_
