#include "catch.hpp"

#include "cover_tree.hpp"
#include "example_point.hpp"
#include <vector>
#include <random>


TEST_CASE( "basic functionality" ) {


    std::vector<double> ref_positions = {2.1, 2.5, 1.1, 1, 3.1};

    std::vector<double> a(1,1.0);

    CoverTree<example_point> cTree;
    cTree.insert(example_point(a,'a'));
    cTree.insert(example_point(a,'b'));
    cTree.insert(example_point(a,'c'));
    cTree.remove(example_point(a,'b'));
    cTree.remove(example_point(a,'c'));

    for( const double& p : ref_positions ){
            a[0]=p;
            cTree.insert(example_point(a,'a'));
        }

    SECTION("insert within radius"){

        REQUIRE(cTree.isValidTree());
    }



    SECTION("check kNN algorithm"){

        a.front() = 2.0;
        auto points = cTree.kNearestNeighbors(example_point(a,'a'),5);

        int cnt=0;
        for( const auto& f :  points ){
            a[0]=(double)ref_positions[cnt++];
            example_point ex{a,'a'};
            INFO("logging " << cnt << " at " << a.front() << " should be " << f.getVec().front() )
            REQUIRE(ex==f);

        }

    }

    a.front() = ref_positions.back();
    cTree.insert(example_point(a,'b'));
    cTree.insert(example_point(a,'c'));

    SECTION("three way tie"){

        auto points = cTree.kNearestNeighbors(example_point(a,'a'),1);
        REQUIRE(points.size() ==3);
        REQUIRE(points.back().distance(example_point(a,'a'))==Approx(0.0));
    }

    cTree.remove(example_point(a,'b'));

    SECTION("two way tie"){

        auto points = cTree.kNearestNeighbors(example_point(a,'a'),1);
        REQUIRE(points.size() ==2);
        REQUIRE(points.back().distance(example_point(a,'a'))==Approx(0.0));
    }

    SECTION("remove non-existent points"){

        a[0]=2.124;  cTree.remove(example_point(a,'a'));
        a[0]=4.683;  cTree.remove(example_point(a,'a'));
        a[0]=9.123;  cTree.remove(example_point(a,'a'));
        REQUIRE(cTree.isValidTree());

        a[0]=1.1;   cTree.remove(example_point(a,'b')); //this has dist 0 to a
        //node in cTree, but it is a different point, so the removal should not
        //alter the tree at all.
        auto points = cTree.kNearestNeighbors(example_point(a,'c'),1);
        REQUIRE(cTree.isValidTree());
        REQUIRE(points[0]==example_point(a,'a'));
    }


    SECTION("remove succeeded"){
        a[0]=3.2;  cTree.remove(example_point(a,'a'));
        a[0]=1.1;  cTree.remove(example_point(a,'a'));
        a[0]=2.5;  cTree.remove(example_point(a,'a'));

        REQUIRE(cTree.isValidTree());

        //remove root
        a[0]=1.0;  cTree.remove(example_point(a,'a'));
        REQUIRE(cTree.isValidTree());
    }


}

TEST_CASE( "basic functionality radnomized" ) {

    std::mt19937 gen(1307);
    std::uniform_real_distribution<> dis(0,1.);

    std::vector<double> start(5,0);
    for(unsigned j=0;j<start.size();j++)
        start[j] = dis(gen);

    std::vector<example_point> initVec(1,example_point(start,'a'));

    CoverTree<example_point> cTree2(initVec);
    cTree2.remove(example_point(start,'a'));//Now the tree has no nodes...
    //make sure it can handle trying to remove a node when
    //it has no nodes to begin with...
    cTree2.remove(example_point(start,'a'));

    auto points = std::vector<example_point>();
    for(int i=0;i<500;i++) {
        std::vector<double> a(5);
        for(int j=0;j<5;j++) {
            a[j] = (dis(gen));
        }
        cTree2.insert(example_point(a,'a'));
        points.push_back(example_point(a,'a'));
    }
    REQUIRE(cTree2.isValidTree());

    SECTION("loop through 100"){

        for(int i=0;i<100;i++) {
            auto v = cTree2.kNearestNeighbors(points[i],1);
            REQUIRE(v[0].distance(points[i])==Approx(0.0));
        }

    }

    for(int i=0;i<490;i++) {
        cTree2.remove(points[i]);
    }
    REQUIRE(cTree2.isValidTree());
}

TEST_CASE( "bigtest" ) {
    std::size_t numDimensions = 50;
    std::size_t numNodes = 3000;

    std::mt19937 gen(1307);
    std::uniform_real_distribution<> dis(0,1.);

    std::vector<example_point> points;
    std::vector<double> a(numDimensions,0);

    for(unsigned int i=0;i<numNodes;i++) {
        for(unsigned int j=0;j<numDimensions;j++) {
            a[j] = (dis(gen));
        }
        points.push_back(example_point(a,'a'));
    }

    CoverTree<example_point> cTree(points);

    REQUIRE(cTree.isValidTree());


    for(int i=0;i<2000;i++) {
        for(unsigned int j=0;j<numDimensions;j++) {
            a[j] = (dis(gen));
        }
        cTree.kNearestNeighbors(example_point(a,'a'),1);
    }

    REQUIRE(cTree.isValidTree());

    for(unsigned int i=0; i<numNodes; i++) {
        cTree.remove(points[i]);
    }

    REQUIRE(cTree.isValidTree());

}
