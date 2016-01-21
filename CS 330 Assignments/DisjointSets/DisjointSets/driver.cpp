#include "kruskal.h"
#include "graph.h"
#include "disjoint_sets.h"
#include <vector>
#include <cstdio> //sscanf

class  Edge {
    public:
        Edge(size_t id1=0, size_t id2=0, float weight=0) : id1(id1), id2(id2), weight(weight) {}
        size_t ID1() const { return id1; }
        size_t ID2() const { return id2; }
        float  Weight() const { return weight; }
        bool operator< ( Edge const& rhs) const { 
            return weight < rhs.weight
                || ( weight == rhs.weight && id1 <  rhs.id1 )
                || ( weight == rhs.weight && id1 == rhs.id1 && id2 < rhs.id2) ; 
        }
        friend std::ostream& operator<< (std::ostream& os, Edge const& e) {
            os << "(" << e.id1 << " -> " << e.id2 << ")";
            return os;
        }
    private:
        size_t id1;
        size_t id2;
        float weight; 
};

class Vertex {
    public:
        Vertex( size_t _id=0 ) : id(_id) {}
        size_t ID() const { return id; }
        bool operator< ( Vertex const& rhs) const { return id < rhs.id; }
        friend std::ostream& operator<< (std::ostream& os, Vertex const& v) {
            os << "Vertex(" << v.id << " )";
            return os;
        }
    private:
        size_t id;
};

// A simple test - use for debugging
void test0() {
    Edge array[] = {
        Edge(0,3,2),
        Edge(1,3,2),
        Edge(0,1,1),
        Edge(1,2,1),
        Edge(2,3,1),
        Edge(0,2,2) 
    }; // (0 -> 1) (1 -> 2) (2 -> 3)

    Graph<Vertex,Edge> g;
    g.BuildFromEdgeArray( array, sizeof(array)/sizeof(array[0]) );

    std::vector<Edge> mst = kruskal_disjoint_subsets( g );

    std::sort( mst.begin(), mst.end() );

    std::vector<Edge>::const_iterator 
        it_edges     = mst.begin(),
                     it_edges_end = mst.end();
    float length = 0.0f;
    for( ; it_edges != it_edges_end; ++it_edges ) {
        std::cout << *it_edges << " ";
        length += it_edges->Weight();
    }
    std::cout << "  total length = " << length << std::endl;
}

void test1() { //Kruskal with colors
    // +---+-----+---+------+---+---....---+---+------+---+
    // |   |     |   |      |   |   ....   |   |      |   |
    // +---+     +---+      +---+   ....   +---+      +---+
    // 
    // where each '+' is a vertex, edges of squares have weight 1 
    // and edges connecting 2 squares have weight 2.
    // Solution: assuming N squares (4*N vertices) MST consists of 3*N square edges 
    // and N-1 long edges. Total weight of MST is 5*N-2.
    size_t const N = 3333;
    Edge array[5*N-1];
    //  i       i+3              i+4       i+7
    //  +--------+----------------+---------+
    //  |        |                |         |
    //  |        |                |         |
    //  |i+1     |i+2             |i+5      |i+6
    //  +--------+                +---------+
    //square, all edges length 1
    size_t index_insert = 0;
    for ( size_t i=0; i<4*N; i+=4 ) {
        array[ index_insert++ ] = Edge( i  , i+1, 1 ); 
        array[ index_insert++ ] = Edge( i+1, i+2, 1 );
        array[ index_insert++ ] = Edge( i+2, i+3, 1 );
        array[ index_insert++ ] = Edge( i+3, i  , 1 );
    }
    //edges of length 2 connecting squares
    for ( size_t i=0; i<N-1; ++i ) {
        array[ index_insert++ ] = Edge( 4*i+3, 4*i+4, 2 );
    }

    Graph<Vertex,Edge> g;
    g.BuildFromEdgeArray( array, 5*N-1 );

    // call "external" function, so that time to build the array is not counted
    std::vector<Edge> mst = kruskal_vector( g );

    std::sort( mst.begin(), mst.end() );

    std::vector<Edge>::const_iterator 
        it_edges     = mst.begin(),
                     it_edges_end = mst.end();

    float length = 0.0f;
    for( ; it_edges != it_edges_end; ++it_edges ) {
        //std::cout << *it_edges << " ";
        length += it_edges->Weight();
    }
    std::cout << "  total length = " << length << std::endl;
    std::cout << ( (length==5*N-2)?"correct":"wrong" ) << std::endl;
}

void test2() { //same as before, but using disjoint sets
    size_t const N = 3333;
    Edge array[5*N-1];
    //square, all edges length 1
    size_t index_insert = 0;
    for ( size_t i=0; i<4*N; i+=4 ) {
        array[ index_insert++ ] = Edge( i  , i+1, 1 ); 
        array[ index_insert++ ] = Edge( i+1, i+2, 1 );
        array[ index_insert++ ] = Edge( i+2, i+3, 1 );
        array[ index_insert++ ] = Edge( i+3, i  , 1 );
    }
    //edges of length 2 connecting squares
    for ( size_t i=0; i<N-1; ++i ) {
        array[ index_insert++ ] = Edge( 4*i+3, 4*i+4, 2 );
    }

    Graph<Vertex,Edge> g;
    g.BuildFromEdgeArray( array, 5*N-1 );

    // call "external" function, so that time to build the array is not counted
    std::vector<Edge> mst = kruskal_disjoint_subsets( g );

    std::sort( mst.begin(), mst.end() );

    std::vector<Edge>::const_iterator 
        it_edges     = mst.begin(),
                     it_edges_end = mst.end();
    float length = 0.0f;

    for( ; it_edges != it_edges_end; ++it_edges ) {
        //std::cout << *it_edges << " ";
        length += it_edges->Weight();
    }
    std::cout << "  total length = " << length << std::endl;
    std::cout << ( (length==5*N-2)?"correct":"wrong" ) << std::endl;
}

void (*pTests[])(void) = { test0,test1,test2 };

int main( int argc, char ** argv) {
    if (argc!=2) return 1;
    else {
        int test = 0;
        std::sscanf(argv[1],"%i",&test);
        pTests[ test ]();
    }
    return 0;
}

