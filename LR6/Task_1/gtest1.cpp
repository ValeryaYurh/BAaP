#include <gtest/gtest.h>
#include "find.h"

TEST(FindTests, OneGroupOfFive) {
    char arr[] = "11111";
    EXPECT_EQ(find(arr, 5), 1);
}


TEST(FindTests, TwoGroupsSeparatedBySpace) {
    char arr[] = "11111 00000";
    EXPECT_EQ(find(arr, 11), 2);
}

TEST(FindTests, OneGroupOfFour) {
    char arr[] = "1111";
    EXPECT_EQ(find(arr, 4), 0);
}


TEST(FindTests, MixedGroups) {
    char arr[] = "1 11 111 1111 11111 111111";
    EXPECT_EQ(find(arr, 29), 1);
}


TEST(FindTests, MultipleSpaces) {
    char arr[] = "11111   00000";
    EXPECT_EQ(find(arr, 13), 2);
}


TEST(FindTests, FiveAtEnd) {
    char arr[] = "1 11 111 11111";
    EXPECT_EQ(find(arr, 17), 1);
}


TEST(FindTests, FiveAtStart) {
    char arr[] = "11111 1 11";
    EXPECT_EQ(find(arr, 11), 1);
}

TEST(FindTests, NoGroups) {
    char arr[] = "0 01 010 0101";
    EXPECT_EQ(find(arr, 14), 0);
}

TEST(FindTests, EmptyString) {
    char arr[] = "";
    EXPECT_EQ(find(arr, 0), 0);
}

TEST(FindTests, MaxLengthInput) {
    char arr[81];
    for (int i = 0; i < 80; i++) arr[i] = '1';
    arr[80] = '\0';
    EXPECT_EQ(find(arr, 80), 0); 
}