
#include "utils.h"

#include <cstring>
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

namespace nlptools {
bool is_whitespace_char(int c) {
    const char* cat = utf8proc_category_string(c);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        return true;
    }
    // Unicode中，每个字符都有Category的属性
    return cat[0] == 'Z' && cat[1] == 's';
}

ssize_t utf8proc_iterate_reversed(const uint8_t* str, ssize_t start, int32_t* dst) {
    ssize_t len = 0;

    const uint8_t* ptr = str + start;

    *dst = -1;

    do {
        if (ptr <= str)
            return 0;
        ptr--;
        len++;
    } while ((*ptr & 0xC0) == 0x80);

    int32_t ch = 0;

    ssize_t ret_len = utf8proc_iterate(ptr, len, &ch);
    *dst = ch;
    return ret_len;
}

// char* lstrip(char* s) {
//     size_t pos = 0;
//     int codepoint;
//     char dst[4];
//     while (pos < std::strlen(s)) {
//         int len = utf8proc_iterate((const utf8proc_uint8_t*)s + pos, -1, &codepoint);
//         assert(len > 0);
//         if (!is_whitespace_char(codepoint)) {
//             break;
//         }
//         pos += len;
//     }

//     return ;
// };

// char* rstrip(char* s) {
//     size_t spaces = 0;
//     uint8_t* ptr = (uint8_t*)s;
//     int32_t ch = 0;
//     ssize_t pos = std::strlen(s);

//     while (pos > 0) {
//         ssize_t char_len = utf8proc_iterate_reversed(ptr, pos, &ch);

//         if (char_len <= 0) {
//             spdlog::info("Decode UTF-8 Error");
//             break;
//         }
//         if (!is_whitespace_char(ch)) {
//             break;
//         }
//         pos -= char_len;
//     }

//     return;
// };

// char* strip(char* s) {
//     absl::string_view s1 = lstrip(s);
//     absl::string_view s2 = rstrip(s1);
//     return s2;
// };
}  // namespace nlptools
