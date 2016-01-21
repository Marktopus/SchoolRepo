/******************************************************************\
* Author: Mark Lauzon
* Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#include "DfaState.h"

DfaState::DfaState(int id) :  token_id_(id),
                              default_edge_(nullptr)
{
}

DfaState::~DfaState()
{
}

void DfaState::AddEdge(DfaState* newChild, 
                       EdgeType::Type type, 
                       char symbol)
{
  switch(type)
  {
    case EdgeType::Specific:
      children_.insert(std::make_pair(symbol, newChild));
      break;
    case EdgeType::AlphaNumeric:
      //lazy
      AddEdge(newChild, EdgeType::Alpha);
      AddEdge(newChild, EdgeType::Numeric);
      break;
    case EdgeType::Alpha:
      for (char c = 'a'; c <= 'z'; ++c)
      {
        children_.insert(std::make_pair(c, newChild));
      }
      for (char c = 'A'; c <= 'Z'; ++c)
      {
        children_.insert(std::make_pair(c, newChild));
      }
      children_.insert(std::make_pair('_', newChild));
      break;
    case EdgeType::Numeric:
      for (char c = '0'; c <= '9'; ++c)
      {
        children_.insert(std::make_pair(c, newChild));
      }
      break;
    case EdgeType::Default:
      default_edge_ = newChild;
      break;
    default:
      __debugbreak();
      break;
  }
}


DfaState * DfaState::FindEdgeWith(const char symbol)
{
  auto it = children_.find(symbol);
  if (it != children_.end())
  {
    return (*it).second;
  }
  return default_edge_;
}


std::unordered_map<char, DfaState*>& DfaState::GetChildren()
{
  return children_;
}

void DfaState::DeleteChildren(std::set<DfaState*>& toDelete)
{
  if(toDelete.find(this) == toDelete.end())
  {
    for (auto& it : children_)
    {
      toDelete.insert(it.second);
      if (it.second != this)
      {
        it.second->DeleteChildren(toDelete);
      }
    }
  }
}

bool DfaState::Accepting()
{
  return static_cast<bool>(token_id_);
}

int DfaState::GetId()
{
  return token_id_;
}

void DfaState::SetId(int id)
{
  token_id_ = id;
}

