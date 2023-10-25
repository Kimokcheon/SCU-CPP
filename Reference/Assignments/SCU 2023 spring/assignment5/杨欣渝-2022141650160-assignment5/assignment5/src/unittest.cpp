#include <limits.h>
#include "assignment5.h"
#include "gtest/gtest.h" //google test
namespace
{
    TEST(assignment5Test,ReadData)
    {
        auto table = read_csv("dataset.csv");
        EXPECT_EQ(211, table.size());
        EXPECT_EQ("Data Smart",table.at(1).at(0));
        EXPECT_EQ("Goswami, Jaideva", table[0][1]);  
    }

    TEST(assignment5Test,authors)
    {
        auto table = read_csv("dataset.csv");
        auto books = defineBooks(&table);
        
        EXPECT_EQ("Said, Edward",books[4].getAuthorName());
        EXPECT_EQ("Vonnegut, Kurt",books[11].getAuthorName()); 
    }

    TEST(assignment5Test,publisher)
    {
        auto table = read_csv("dataset.csv");
        auto books = defineBooks(&table);
        
        EXPECT_EQ("Dell",books[210].getPublisherName());
        EXPECT_EQ("Penguin",books[177].getPublisherName());
    }

    TEST(assignment5Test,printTable)
    {
        auto table = read_csv("dataset.csv");
        showTable(&table,10,14);
    }
}
