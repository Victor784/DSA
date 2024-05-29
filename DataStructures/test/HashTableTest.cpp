#include "HashTable.hpp"
#include "gtest/gtest.h"

using namespace vics_data_structures;

namespace tests {

TEST(HashTableTest, HashTable_creates_an_empty_table_with_initial_capacity) {
  HashTable<std::string, int> table(8);
  ASSERT_EQ(table.getSize(), 0); // Test that initial size is 0
  EXPECT_EQ(table.getNumBuckets(),
            8); // Test that initial number of buckets is 8
}

TEST(HashTableTest, HashTable_insert_and_search_elements) {
  HashTable<std::string, int> table(8);

  table.insert("one", 1);
  table.insert("two", 2);
  table.insert("three", 3);

  EXPECT_NE(table.search("one"), nullptr);
  EXPECT_EQ(*table.search("one"), 1);

  EXPECT_NE(table.search("two"), nullptr);
  EXPECT_EQ(*table.search("two"), 2);

  EXPECT_NE(table.search("three"), nullptr);
  EXPECT_EQ(*table.search("three"), 3);

  EXPECT_EQ(table.search("four"), nullptr); // This should return nullptr
}

TEST(HashTableTest, HashTable_remove_elements) {
  HashTable<std::string, int> table(8);

  table.insert("one", 1);
  table.insert("two", 2);
  table.insert("three", 3);

  EXPECT_TRUE(table.remove("two"));
  EXPECT_EQ(table.search("two"), nullptr);
  EXPECT_EQ(table.getSize(), 2);

  EXPECT_FALSE(table.remove("four")); // Non-existing key
  EXPECT_EQ(table.getSize(), 2);
}

TEST(HashTableTest, HashTable_rehash) {
  HashTable<std::string, int> table(8);

  for (int i = 0; i < 10; ++i) {
    table.insert("key" + std::to_string(i), i);
  }
  EXPECT_EQ(table.getSize(), 10);
  for (int i = 0; i < 10; ++i) {
    EXPECT_NE(table.search("key" + std::to_string(i)), nullptr);
    EXPECT_EQ(*table.search("key" + std::to_string(i)), i);
  }
}

TEST(HashTableTest, HashTable_handle_collisions) {
  HashTable<int, int> table(8);

  table.insert(1, 10);
  table.insert(9, 90); // Assuming a small table and a poor hash function, these
                       // might collide
  table.insert(17, 170); // These might also collide

  EXPECT_EQ(*table.search(1), 10);
  EXPECT_EQ(*table.search(9), 90);
  EXPECT_EQ(*table.search(17), 170);
}

} // namespace tests

int main(int nArgs, char **vArgs) {
  ::testing::InitGoogleTest(&nArgs, vArgs);
  return RUN_ALL_TESTS();
}