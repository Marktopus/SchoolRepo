/******************************************************************\
* Author: Mark Lauzon
* Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#pragma once

#include <unordered_map>
#include <set>
namespace EdgeType
{
  enum Type
  {
    Specific,
    Default,
    Alpha,
    Numeric,
    AlphaNumeric
  };
}

class DfaState
{
public:
  DfaState(int id);

  ~DfaState();

  void AddEdge(DfaState* newChild, 
               EdgeType::Type type = EdgeType::Specific,
               char symbol = '\0');

  DfaState* FindEdgeWith(const char symbol);

  std::unordered_map<char, DfaState*>& GetChildren();

  void DeleteChildren(std::set<DfaState*>& shit);

  bool Accepting();

  int GetId();
  void SetId(int id);

  //todo? maybe?
  //void RemoveEdge(DfaState* toRemove);
private:
  std::unordered_map<char, DfaState*> children_;
  DfaState* default_edge_;
  int token_id_;
};



