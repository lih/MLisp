#include "AVLTree.test.hh"
#include "AVLTree.hh"

#include "TestMacros.hh"

using namespace Utils;

namespace {
  void test_Iterator() {
    ENTER_TEST("iterator");

    AVLTree<int> tree;

    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    AVLTree<int>::Iterator it=tree.begin();
    
    for(int i=3;i<=5;++i) {
      TEST(it!=tree.end());
      TEST(*it==i);
      ++it;
    }
  }
  void test_Erase() {
    ENTER_TEST("deletion");
    
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    { // erase arbitrary
      ENTER_TEST("deletion of element in the middle");

      TEST(tree.erase(4));

      AVLTree<int>::Iterator i=tree.begin();

      TEST(*i==1); ++i;
      TEST(*i==2); ++i;
      TEST(*i==3); ++i;
      TEST(*i==5); ++i;
      TEST(i==tree.end());

      tree.insert(4);
    }
    { // erase last
      ENTER_TEST("deletion of last element");

      TEST(tree.erase(5));

      AVLTree<int>::Iterator i=tree.begin();

      TEST(*i==1); ++i;
      TEST(*i==2); ++i;
      TEST(*i==3); ++i;
      TEST(*i==4); ++i;
      TEST(i==tree.end());

      tree.insert(5);
    }
    { // erase first
      ENTER_TEST("deletion of first element");

      TEST(tree.erase(1));

      AVLTree<int>::Iterator i=tree.begin();

      TEST(*i==2); ++i;
      TEST(*i==3); ++i;
      TEST(*i==4 ); ++i;
      TEST(*i==5); ++i;
      TEST(i==tree.end());

      tree.insert(1);
    }
    { // erase all
      ENTER_TEST("deletion of all elements");
      
      TEST(tree.erase(3));
      TEST(tree.erase(5));
      TEST(tree.erase(4));
      TEST(tree.erase(1));
      TEST(tree.erase(2));
      
      TEST(tree.empty());
    }
  }
}

void AVLTree_test() {
  ENTER_TEST("template class AVLTree<T> (with T=int)");

  test_Iterator();
  test_Erase();
}
