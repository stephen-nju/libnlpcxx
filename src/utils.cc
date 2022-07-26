

#include "utils.h"

#include <string.h>

#include "absl/strings/string_view.h"
#include "absl/strings/strip.h"
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

size_t utf8proc_iterate_reversed(const uint8_t* str, size_t start, int32_t* dst) {
    size_t len = 0;

    const uint8_t* ptr = str + start;

    *dst = -1;

    do {
        if (ptr <= str)
            return 0;
        ptr--;
        len++;
    } while ((*ptr & 0xC0) == 0x80);

    int32_t ch = 0;

    size_t ret_len = utf8proc_iterate(ptr, len, &ch);
    *dst = ch;
    return ret_len;
}

absl::string_view lstrip(absl::string_view& s) {
    const char* text_data = s.data();
    size_t start = 0;
    size_t pos = 0;
    int codepoint;
    char dst[4];
    for (size_t i = 0; i < std::strlen(text_data); i++) {
        int len = utf8proc_iterate((const utf8proc_uint8_t*)text_data + pos, -1, &codepoint);
        if (len < 0) {
            spdlog::info("Decode UTF-8 Error");
            break;
            // 抛出异常
        }
        if (is_whitespace_char(codepoint)) {
            pos += len;
        } else {
            start = pos;
            break;
        }
    }
    return s.substr(start, -1);
};

absl::string_view rstrip(absl::string_view& s) {
    const char* text_data = s.data();
    size_t end = std::strlen(text_data);
    // 先按照utf8切分
    int codepoint;
    char dst[4];
    vector<size_t> start_index;
    size_t start = 0;
    start_index.emplace_back(start);
    while (start < end) {
        int len = utf8proc_iterate((const utf8proc_uint8_t*)text_data + pos, -1, &codepoint);
    }
};

absl::string_view strip(absl::string_view& s){

};
}  // namespace nlptools
