#include "catch.hpp"

#include "cover_tree.hpp"
#include "example_point.hpp"
#include <vector>


TEST_CASE( "use_size" ) {

    std::vector<double> a;
    a.push_back(1.0);
    CoverTree<example_point> cTree;
    cTree.insert(example_point(a,'a'));
    cTree.insert(example_point(a,'b'));
    cTree.insert(example_point(a,'c'));
    cTree.remove(example_point(a,'b'));
    cTree.remove(example_point(a,'c'));

    REQUIRE(cTree.size() != 0.);
    REQUIRE(cTree.size() == 1);

}



TEST_CASE( "use_clear" ) {

    std::vector<double> a;
    a.push_back(1.0);
    CoverTree<example_point> cTree;
    cTree.insert(example_point(a,'a'));
    cTree.insert(example_point(a,'b'));
    cTree.insert(example_point(a,'c'));

    REQUIRE(cTree.size() != 0);

    cTree.clear();

    REQUIRE(cTree.size() == 0);

}
