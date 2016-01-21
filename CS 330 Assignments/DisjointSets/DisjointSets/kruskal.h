#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "disjoint_sets.h"
#include "graph.h"
#include <list>

//efficient version, using disjoint subsets
template <typename Vertex, typename Edge>
std::vector<Edge> kruskal_disjoint_subsets( Graph<Vertex,Edge> const& g ) 
{
  typename std::vector<Edge> minimalSpanningTree;
 
  DisjointSets sets(g.Size());
  for (int i = 0; i < g.Size(); ++i)
  {
    sets.Make();
  }
  typename std::list<Edge> allEdges = g.GetEdges();
  allEdges.sort();
  //for (std::list<Edge>::iterator it = allEdges.begin();
  //  it != allEdges.end();
  //  ++it)
  //{
  //  sets.Join(it->ID1(), it->ID2());
  //}

  Edge newEdge;

  while ((minimalSpanningTree.size() < (g.Size() - 1)) && !allEdges.empty())
  {
    newEdge = allEdges.front();
    allEdges.pop_front();
    //not sure what to do with the disjoint subsets...

    if (sets[newEdge.ID1()] != sets[newEdge.ID2()])
    {
      sets.Join(newEdge.ID1(), newEdge.ID2());
      minimalSpanningTree.push_back(newEdge);
    }
  }

	return minimalSpanningTree;
}

//inefficient version, using array of vector of "colors"
template <typename Vertex, typename Edge>
std::vector<Edge> kruskal_vector( Graph<Vertex,Edge> const& g ) 
{
  typename std::vector<Edge> minimalSpanningTree;
  
  typename std::list<Edge> allEdges = g.GetEdges();
  allEdges.sort();

  //int is color
  std::vector<int> colors;
  colors.resize(g.Size(), -1);
  int curColor = 0;
  //go through all edges and setup verts to colors
  for ( typename std::list<Edge>::iterator it = allEdges.begin(); 
        it != allEdges.end();
        ++it)
  {
    if (colors[it->ID1()] == -1)
    {
      colors[it->ID1()] = curColor;
      ++curColor;
    }
    if (colors[it->ID2()] == -1)
    {
      colors[it->ID2()] = curColor;
      ++curColor;
    }
  }

  Edge newEdge;

  while (minimalSpanningTree.size() < (g.Size() - 1))
  {
    newEdge = allEdges.front();
    allEdges.pop_front();
    if (colors[newEdge.ID1()] != colors[newEdge.ID2()])
    {
      int& colorToChange = colors[newEdge.ID1()];
      int& goalColor = colors[newEdge.ID2()];
      for (int i = 0; i < colors.size(); ++i)
      {
        if (colors[i] == colorToChange)
        {
          colors[i] = goalColor;
        }
      }
      minimalSpanningTree.push_back(newEdge);
    }

  }
  return minimalSpanningTree;
}

#endif
