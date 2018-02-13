#include "catch.hpp"

#include "cover_tree.hpp"
#include "example_point.hpp"
#include <vector>
#include <random>


TEST_CASE( "bigtest" ) {
    std::size_t numDimensions = 50;
    std::size_t numNodes = 3000;

    std::mt19937 gen(1307);
    std::uniform_real_distribution<> dis(0,1.);

    std::vector<example_point> points;
    std::vector<double> a(numDimensions,0);

    BENCHMARK("random-create-vector"){
    for(unsigned int i=0;i<numNodes;i++) {
        for(unsigned int j=0;j<numDimensions;j++) {
            a[j] = (dis(gen));
        }
        points.push_back(example_point(a,'a'));
    }
    }

    CoverTree<example_point> insert_me;
    BENCHMARK("inserts"){
        for(const auto& p : points) {
            insert_me.insert(p);
        }
    }
    REQUIRE(insert_me.isValidTree());
    REQUIRE(insert_me.size() != 0);
    REQUIRE(insert_me.size() == points.size());


    CoverTree<example_point> cTree(points);

    REQUIRE(cTree.isValidTree());

    BENCHMARK("nearest-neighbor"){
    for(int i=0;i<2000;i++) {
        for(unsigned int j=0;j<numDimensions;j++) {
            a[j] = (dis(gen));
        }
        cTree.kNearestNeighbors(example_point(a,'a'),1);
    }
    }
    REQUIRE(cTree.isValidTree());

    BENCHMARK("remove-all"){
        for(unsigned int i=0; i<numNodes; i++) {
            cTree.remove(points[i]);
        }
    }

    REQUIRE(cTree.isValidTree());

}
