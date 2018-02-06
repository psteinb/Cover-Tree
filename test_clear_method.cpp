#include "catch.hpp"

#include "Cover_Tree.h"
#include "Cover_Tree_Point.h"
#include <vector>


TEST_CASE( "use_size" ) {

    std::vector<double> a;
    a.push_back(1.0);
    CoverTree<CoverTreePoint> cTree;
    cTree.insert(CoverTreePoint(a,'a'));
    cTree.insert(CoverTreePoint(a,'b'));
    cTree.insert(CoverTreePoint(a,'c'));
    cTree.remove(CoverTreePoint(a,'b'));
    cTree.remove(CoverTreePoint(a,'c'));

    REQUIRE(cTree.size() != 0.);
    REQUIRE(cTree.size() == 1);

}



TEST_CASE( "use_clear" ) {

    std::vector<double> a;
    a.push_back(1.0);
    CoverTree<CoverTreePoint> cTree;
    cTree.insert(CoverTreePoint(a,'a'));
    cTree.insert(CoverTreePoint(a,'b'));
    cTree.insert(CoverTreePoint(a,'c'));

    REQUIRE(cTree.size() != 0);

    cTree.clear();

    REQUIRE(cTree.size() == 0);

}
