
#include "utils.h"

#include <memory>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "commom.h"
#include "gtest/gtest.h"
#include "testharness.h"

using std::string;
using std::vector;

TEST(LstripTest, UtilsTest) {
    absl::string_view s = "\t 中国人";

    absl::string_view o = nlptools::lstrip(s);
    EXPECT_EQ(o, "中国人");
}