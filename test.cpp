#include <gtest/gtest.h>
#include "pch.h"
#include "C:\Users\pavli\OneDrive - lnu.edu.ua\Робочий стіл\Лну файлс\Гошко\Markov_Pavlo_Yavorivskyi.h"

TEST(MarkovTest, Program1) {
    Markov markov;
    String word("|*||");
    markov.add_rule({ "|b", "ba|",0 });
    markov.add_rule({ "ab", "ba",0 });
    markov.add_rule({ "b", "",0 });
    markov.add_rule({ "*|", "b*",0 });
    markov.add_rule({ "*", "c",0 });
    markov.add_rule({ "|c", "c" ,0});
    markov.add_rule({ "ac", "c|" ,0});
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "c||");
}
TEST(MarkovTest, Program2) {
    Markov markov;
    String word("101");
    markov.add_rule({ "1", "0|",0 });
    markov.add_rule({ "|0", "0||",0 });
    markov.add_rule({ "0", "" ,0 });
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "|||||");
}
TEST(MarkovTest, Program3) {
    Markov markov;
    String word("bbbbaabb");
    markov.add_rule({ "aa", "a",0 });
    markov.add_rule({ "bb", "b",0 });
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "bab");
}
TEST(MarkovTest, Program4) {
    Markov markov;
    String word("***abc");
    markov.add_rule({ "*a", "a*",0 });
    markov.add_rule({ "*b", "b*",0 });
    markov.add_rule({ "*c", "c*" ,0 });
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "abc***");
}
TEST(MarkovTest, Program5) {
    Markov markov;
    String word("ababccba");
    markov.add_rule({ "ba", "ab",0 });
    markov.add_rule({ "ca", "ac",0 });
    markov.add_rule({ "cb", "bc",0 });
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "aaabbbcc");
}
TEST(MarkovTest, Program6) {
    Markov markov;
    String word("1000000");
    markov.add_rule({ "1", "t",1 });
    markov.add_rule({ "0", "nt",0 });
    markov.add_ryadok(word);
    markov.program();
    EXPECT_EQ(markov.getRyadok(), "t000000");
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}