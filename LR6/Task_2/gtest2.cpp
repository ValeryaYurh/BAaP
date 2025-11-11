#include <gtest/gtest.h>
#include "receipt_calc.h"

// Краевые случаи
TEST(ReceiptTest, EmptyString) {
    char telegram[] = "";
    EXPECT_EQ(calcWords(telegram), 0);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.0);
}

TEST(ReceiptTest, OnlySpaces) {
    char telegram[] = "     ";
    EXPECT_EQ(calcWords(telegram), 0);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.0);
}

// Обычные случаи
TEST(ReceiptTest, TwoWords) {
    char telegram[] = "Привет мир";
    EXPECT_EQ(calcWords(telegram), 2);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.13);
}

TEST(ReceiptTest, FourWords) {
    char telegram[] = "Это тестовая телеграмма";
    EXPECT_EQ(calcWords(telegram), 3);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.195);
}

TEST(ReceiptTest, OneWord) {
    char telegram[] = "Один";
    EXPECT_EQ(calcWords(telegram), 1);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.065);
}

TEST(ReceiptTest, ThreeWords) {
    char telegram[] = "Слово1 Слово2 Слово3";
    EXPECT_EQ(calcWords(telegram), 3);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.195);
}

TEST(ReceiptTest, MultipleSpaces) {
    char telegram[] = "Слово1  Слово2   Слово3";
    EXPECT_EQ(calcWords(telegram), 3);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.195);
}

TEST(ReceiptTest, SixWords) {
    char telegram[] = "Много слов в телеграмме без проблем";
    EXPECT_EQ(calcWords(telegram), 6);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.39);
}

TEST(ReceiptTest, OneLongWord) {
    char telegram[] = "ОдноДлинноеСлово";
    EXPECT_EQ(calcWords(telegram), 1);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.065);
}

TEST(ReceiptTest, FiveWords) {
    char telegram[] = "Слово1 Слово2 Слово3 Слово4 Слово5";
    EXPECT_EQ(calcWords(telegram), 5);
    EXPECT_DOUBLE_EQ(costReceipt(telegram), 0.325);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
