#include <gtest/gtest.h>

#include <cstdlib>

#include "hash_table.hpp"
#include "self_balancing_binary_search_tree.hpp"
#include "student_record.hpp"

TEST(hash, set) {
  HashTable<int, double> A;
  ASSERT_TRUE(A.SET(1, 2.3));
  ASSERT_FALSE(A.SET(1, 4.5));
  ASSERT_TRUE(A.SET(6, 7.8, 9));
}

TEST(hash, get) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  A.SET(1, 8.9);
  ASSERT_DOUBLE_EQ(A.GET(1), 2.3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
}

TEST(hash, exist) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  A.SET(1, 8.9);
  ASSERT_TRUE(A.EXIST(1));
  ASSERT_FALSE(A.EXIST(2));
  ASSERT_TRUE(A.EXIST(4));
}

TEST(hash, del) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_TRUE(A.EXIST(1));
  A.DEL(1);
  ASSERT_FALSE(A.EXIST(1));
  ASSERT_TRUE(A.EXIST(4));
  A.DEL(4);
  ASSERT_FALSE(A.EXIST(4));
}

TEST(hash, update) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_DOUBLE_EQ(A.GET(1), 2.3);
  A.UPDATE(1, 4.5);
  ASSERT_DOUBLE_EQ(A.GET(1), 4.5);
  ASSERT_FALSE(A.UPDATE(2, 6.7));
  ASSERT_FALSE(A.EXIST(2));
  A.UPDATE(4, 8.9);
  ASSERT_DOUBLE_EQ(A.GET(4), 8.9);
}

TEST(hash, keys) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  std::vector<int> reply = A.KEYS();
  ASSERT_EQ(reply.size(), 2);
  ASSERT_TRUE(reply[0] == 1 || reply[1] == 1);
  ASSERT_TRUE(reply[0] == 4 || reply[1] == 4);
}

TEST(hash, rename) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6);
  A.SET(9, 10, 11);
  ASSERT_FALSE(A.RENAME(1, 4));
  ASSERT_TRUE(A.RENAME(1, 7));
  ASSERT_FALSE(A.RENAME(1, 8));
  ASSERT_TRUE(A.RENAME(9, 12));
  ASSERT_DOUBLE_EQ(A.GET(7), 2.3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
  ASSERT_TRUE(A.EXIST(12));
  ASSERT_GT(A.TTL(12), 0);
}

TEST(hash, ttl) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_EQ(A.TTL(4), 7);
}

TEST(hash, find) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);

  auto reply1 = A.FIND(2.3);
  auto reply2 = A.FIND(5.6);
  auto reply3 = A.FIND(1);

  ASSERT_EQ(reply1.size(), 1);
  ASSERT_EQ(reply2.size(), 2);
  ASSERT_EQ(reply3.size(), 0);
  ASSERT_EQ(reply1[0], 1);
}

TEST(hash, showall) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);

  auto reply = A.SHOWALL();

  ASSERT_EQ(reply.size(), 3);
  ASSERT_TRUE(reply[0] == 2.3 || reply[0] == 5.6);
  ASSERT_TRUE(reply[1] == 2.3 || reply[1] == 5.6);
  ASSERT_TRUE(reply[2] == 2.3 || reply[2] == 5.6);
  ASSERT_TRUE(reply[0] == 2.3 || reply[1] == 2.3 || reply[2] == 2.3);
}

TEST(hash, export) {
  HashTable<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);
  ASSERT_EQ(A.EXPORT("foo.dat"), 3);
}

TEST(hash, upload) {
  HashTable<int, double> A;
  ASSERT_EQ(A.UPLOAD("foo.dat"), 3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
  ASSERT_DOUBLE_EQ(A.GET(7), 5.6);
  system("rm foo.dat");
}

TEST(hash, more_del) {
  unsigned seed = time(0), num{10000};
  HashTable<int, int> A;
  std::vector<int> deck;
  for (unsigned i{}; i < num; i++) {
    A.SET(i, i, (i % 2) ? 10 : 0);
    deck.push_back(i);
  }
  for (unsigned i{}; i < num - 1; i++) {
    unsigned pos = rand_r(&seed) % (num - 1 - i);
    std::swap(deck[i], deck[i + pos]);
  }
  for (auto &each : deck) {
    A.DEL(each);
  }
}

// ================================

TEST(tree, set) {
  SelfBalancingBinarySearchTree<int, double> A;
  ASSERT_TRUE(A.SET(1, 2.3));
  ASSERT_FALSE(A.SET(1, 4.5));
  ASSERT_TRUE(A.SET(6, 7.8, 9));
}

TEST(tree, get) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  A.SET(1, 8.9);
  ASSERT_DOUBLE_EQ(A.GET(1), 2.3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
}

TEST(tree, exist) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  A.SET(1, 8.9);
  ASSERT_TRUE(A.EXIST(1));
  ASSERT_FALSE(A.EXIST(2));
  ASSERT_TRUE(A.EXIST(4));
}

TEST(tree, del) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_TRUE(A.EXIST(1));
  A.DEL(1);
  ASSERT_FALSE(A.EXIST(1));
  ASSERT_TRUE(A.EXIST(4));
  A.DEL(4);
  ASSERT_FALSE(A.EXIST(4));
}

TEST(tree, update) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_DOUBLE_EQ(A.GET(1), 2.3);
  A.UPDATE(1, 4.5);
  ASSERT_DOUBLE_EQ(A.GET(1), 4.5);
  ASSERT_FALSE(A.UPDATE(2, 6.7));
  ASSERT_FALSE(A.EXIST(2));
  A.UPDATE(4, 8.9);
  ASSERT_DOUBLE_EQ(A.GET(4), 8.9);
}

TEST(tree, keys) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  std::vector<int> reply = A.KEYS();
  ASSERT_EQ(reply.size(), 2);
  ASSERT_TRUE(reply[0] == 1 || reply[1] == 1);
  ASSERT_TRUE(reply[0] == 4 || reply[1] == 4);
}

TEST(tree, rename) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6);
  A.SET(9, 10, 11);
  ASSERT_FALSE(A.RENAME(1, 4));
  ASSERT_TRUE(A.RENAME(1, 7));
  ASSERT_FALSE(A.RENAME(1, 8));
  ASSERT_TRUE(A.RENAME(9, 12));
  ASSERT_DOUBLE_EQ(A.GET(7), 2.3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
  ASSERT_TRUE(A.EXIST(12));
  ASSERT_GT(A.TTL(12), 0);
}

TEST(tree, ttl) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 7);
  ASSERT_EQ(A.TTL(4), 7);
}

TEST(tree, find) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);

  auto reply1 = A.FIND(2.3);
  auto reply2 = A.FIND(5.6);
  auto reply3 = A.FIND(1);

  ASSERT_EQ(reply1.size(), 1);
  ASSERT_EQ(reply2.size(), 2);
  ASSERT_EQ(reply3.size(), 0);
  ASSERT_EQ(reply1[0], 1);
}

TEST(tree, showall) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);

  auto reply = A.SHOWALL();

  ASSERT_EQ(reply.size(), 3);
  ASSERT_TRUE(reply[0] == 2.3 || reply[0] == 5.6);
  ASSERT_TRUE(reply[1] == 2.3 || reply[1] == 5.6);
  ASSERT_TRUE(reply[2] == 2.3 || reply[2] == 5.6);
  ASSERT_TRUE(reply[0] == 2.3 || reply[1] == 2.3 || reply[2] == 2.3);
}

TEST(tree, export) {
  SelfBalancingBinarySearchTree<int, double> A;
  A.SET(1, 2.3);
  A.SET(4, 5.6, 10);
  A.SET(7, 5.6);
  ASSERT_EQ(A.EXPORT("foo.dat"), 3);
}

TEST(tree, upload) {
  SelfBalancingBinarySearchTree<int, double> A;
  ASSERT_EQ(A.UPLOAD("foo.dat"), 3);
  ASSERT_DOUBLE_EQ(A.GET(4), 5.6);
  ASSERT_DOUBLE_EQ(A.GET(7), 5.6);
  system("rm foo.dat");
}

TEST(tree, more_del) {
  unsigned seed = time(0), num{10000};
  SelfBalancingBinarySearchTree<int, int> A;
  std::vector<int> deck;
  for (unsigned i{}; i < num; i++) {
    A.SET(i, i, (i % 2) ? 10 : 0);
    deck.push_back(i);
  }
  for (unsigned i{}; i < num - 1; i++) {
    unsigned pos = rand_r(&seed) % (num - 1 - i);
    std::swap(deck[i], deck[i + pos]);
  }
  for (auto &each : deck) {
    A.DEL(each);
  }
}

// // =============================================

// TEST(record, assign) {
//   StudentRecord A, B;
//   A.last_name_ = "a";
//   A.first_name_ = "b";
//   A.year_of_birth_ = 1;
//   A.city_ = "c";
//   A.coins_ = 2;
//   B.last_name_ = "d";
//   B.first_name_ = "-";
//   B.year_of_birth_ = 3;
//   B.city_ = "c";
//   B.coins_ = -1;
//   A = B;
//   ASSERT_EQ(A.last_name_, "d");
//   ASSERT_EQ(A.first_name_, "b");
//   ASSERT_EQ(A.year_of_birth_, 3);
//   ASSERT_EQ(A.city_, "c");
//   ASSERT_EQ(A.coins_, 2);
// }

// TEST(record, compare) {
//   StudentRecord A, B, C;
//   A.last_name_ = "a";
//   A.first_name_ = "b";
//   A.year_of_birth_ = 1;
//   A.city_ = "c";
//   A.coins_ = 2;
//   B.last_name_ = "d";
//   B.first_name_ = "-";
//   B.year_of_birth_ = 3;
//   B.city_ = "c";
//   B.coins_ = -1;
//   C.last_name_ = "a";
//   C.first_name_ = "-";
//   C.year_of_birth_ = 1;
//   C.city_ = "c";
//   C.coins_ = -1;
//   ASSERT_FALSE(A == B);
//   ASSERT_TRUE(A == C);
// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
