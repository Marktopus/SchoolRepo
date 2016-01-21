/******************************************************************\
* Author: Mark Lauzon
* Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#include "../Drivers/Driver1.hpp"

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



DfaState::DfaState(int id) : token_id_(id),
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
      for(char c = 'a'; c <= 'z'; ++c)
      {
        children_.insert(std::make_pair(c, newChild));
      }
      for(char c = 'A'; c <= 'Z'; ++c)
      {
        children_.insert(std::make_pair(c, newChild));
      }
      children_.insert(std::make_pair('_', newChild));
      break;
    case EdgeType::Numeric:
      for(char c = '0'; c <= '9'; ++c)
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
  if(it != children_.end())
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
    for(auto& it : children_)
    {
      toDelete.insert(it.second);
      if(it.second != this)
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





static std::unordered_map<std::string, TokenType::Enum> keywordMap =
{
  #define TOKEN(x, y) std::make_pair(y, TokenType::x),
  #include "../Drivers/TokenKeywords.inl"
  #undef TOKEN
};

static std::unordered_map<std::string, TokenType::Enum> symbolMap =
{
  #define TOKEN(x, y) std::make_pair(y, TokenType::x),
  #include "../Drivers/TokenSymbols.inl"
  #undef TOKEN
};


DfaState* AddState(int acceptingToken)
{
  return new DfaState(acceptingToken);
}

void AddEdge(DfaState* from, DfaState* to, char c)
{
  from->AddEdge(to, EdgeType::Specific, c);
}

void AddDefaultEdge(DfaState* from, DfaState* to)
{
  from->AddEdge(to, EdgeType::Default);
}

void ReadToken(DfaState* startingState, const char* stream, Token& outToken)
{
  outToken.mText = stream;
  DfaState* stateIt = startingState->FindEdgeWith(*stream);
  int length = 1;


  while(stateIt && (*stream != '\0'))
  {
    if(stateIt->Accepting())
    {
      outToken.mLength = length;
      outToken.mTokenType = stateIt->GetId();
    }

    ++stream;
    stateIt = stateIt->FindEdgeWith(*stream);
    if(!stateIt || (*stream == '\0'))
    {
      outToken.mLength = length;
    }
    ++length;
  }



  //outToken.mEnumTokenType = Space i guess?
}

void DeleteStateAndChildren(DfaState* root)
{
  std::set<DfaState*> shit;
  shit.insert(root);
  root->DeleteChildren(shit);

}

void ReadLanguageToken(DfaState* startingState, const char* stream, Token& outToken)
{
  outToken.mText = stream;
  DfaState* stateIt = startingState->FindEdgeWith(*stream);
  DfaState* lastGood = nullptr;
  int lastGoodLen = 0;
  int length = 1;


  while(stateIt && (*stream != '\0'))
  {
    if(stateIt->Accepting())
    {
      lastGood = stateIt;
      lastGoodLen = length;
    }

    ++stream;
    stateIt = stateIt->FindEdgeWith(*stream);
    if(!stateIt || (*stream == '\0'))
    {
      if(lastGood)
      {
        outToken.mEnumTokenType = (TokenType::Enum)lastGood->GetId();
        outToken.mLength = lastGoodLen;
      }
      else
      {
        outToken.mLength = length;
      }

    }
    ++length;
  }


  std::string keyword(outToken.mText, outToken.mLength);
  auto symbol = keywordMap.find(keyword);
  if(symbol != keywordMap.end())
  {
    outToken.mEnumTokenType = symbol->second;
  }

}


void AddNumbers(DfaState* root)
{
  DfaState* numberState = AddState(TokenType::IntegerLiteral);
  DfaState* period = AddState(TokenType::Invalid);
  DfaState* trailingNumber = AddState(TokenType::FloatLiteral);
  DfaState* postFix = AddState(TokenType::FloatLiteral);
  DfaState* exponential = AddState(TokenType::Invalid);
  DfaState* expNumber = AddState(TokenType::FloatLiteral);

  DfaState* exPlus = AddState(TokenType::Invalid);
  DfaState* exMinus = AddState(TokenType::Invalid);

  root->AddEdge(numberState, EdgeType::Numeric);
  //root->AddEdge(period, EdgeType::Specific, '.');

  numberState->AddEdge(numberState, EdgeType::Numeric);
  numberState->AddEdge(period, EdgeType::Specific, '.');

  period->AddEdge(trailingNumber, EdgeType::Numeric);

  trailingNumber->AddEdge(trailingNumber, EdgeType::Numeric);
  trailingNumber->AddEdge(exponential, EdgeType::Specific, 'e');
  trailingNumber->AddEdge(postFix, EdgeType::Specific, 'f');

  exponential->AddEdge(expNumber, EdgeType::Numeric);
  exponential->AddEdge(exPlus, EdgeType::Specific, '+');
  exponential->AddEdge(exMinus, EdgeType::Specific, '-');

  exPlus->AddEdge(expNumber, EdgeType::Numeric);
  exMinus->AddEdge(expNumber, EdgeType::Numeric);

  expNumber->AddEdge(expNumber, EdgeType::Numeric);
  expNumber->AddEdge(postFix, EdgeType::Specific, 'f');
}

void AddGenericIdentifiers(DfaState* root)
{
  DfaState* genericId = AddState(TokenType::Identifier);

  root->AddEdge(genericId, EdgeType::Alpha);
  genericId->AddEdge(genericId, EdgeType::AlphaNumeric);
}

void AddWhitespace(DfaState* root)
{
  DfaState* whitespace = AddState(TokenType::Whitespace);
  root->AddEdge(whitespace, EdgeType::Specific, ' ');
  root->AddEdge(whitespace, EdgeType::Specific, '\n');
  root->AddEdge(whitespace, EdgeType::Specific, '\t');
  root->AddEdge(whitespace, EdgeType::Specific, '\r');

  whitespace->AddEdge(whitespace, EdgeType::Specific, ' ');
  whitespace->AddEdge(whitespace, EdgeType::Specific, '\n');
  whitespace->AddEdge(whitespace, EdgeType::Specific, '\t');
  whitespace->AddEdge(whitespace, EdgeType::Specific, '\r');
}

void AddStringLiteral(DfaState* root)
{
  DfaState* beginString = AddState(TokenType::Invalid);
  DfaState* endString = AddState(TokenType::StringLiteral);
  DfaState* readDefault = AddState(TokenType::Invalid);
  DfaState* readEscaped = AddState(TokenType::Invalid);

  root->AddEdge(beginString, EdgeType::Specific, '\"');
  beginString->AddEdge(endString, EdgeType::Specific, '\"');
  beginString->AddEdge(readEscaped, EdgeType::Specific, '\\');
  beginString->AddEdge(readDefault, EdgeType::Default);

  readEscaped->AddEdge(readDefault, EdgeType::Specific, '"');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 'n');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 't');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 'r');

  readDefault->AddEdge(readEscaped, EdgeType::Specific, '\\');
  readDefault->AddEdge(readDefault, EdgeType::Default);
  readDefault->AddEdge(endString, EdgeType::Specific, '\"');

}

void AddCharLiteral(DfaState* root)
{
  DfaState* beginString = AddState(TokenType::Invalid);
  DfaState* endString = AddState(TokenType::CharacterLiteral);
  DfaState* readDefault = AddState(TokenType::Invalid);
  DfaState* readEscaped = AddState(TokenType::Invalid);

  root->AddEdge(beginString, EdgeType::Specific, '\'');
  beginString->AddEdge(endString, EdgeType::Specific, '\'');
  beginString->AddEdge(readEscaped, EdgeType::Specific, '\\');
  beginString->AddEdge(readDefault, EdgeType::Default);

  readEscaped->AddEdge(readDefault, EdgeType::Specific, '\'');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 'n');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 't');
  readEscaped->AddEdge(readDefault, EdgeType::Specific, 'r');

  readDefault->AddEdge(readEscaped, EdgeType::Specific, '\\');
  readDefault->AddEdge(readDefault, EdgeType::Default);
  readDefault->AddEdge(endString, EdgeType::Specific, '\'');

}

void AddComments(DfaState* root)
{
  DfaState* beginComment = AddState(TokenType::Invalid);
  DfaState* readDefaultSingle = AddState(TokenType::Invalid);
  DfaState* endSingle = AddState(TokenType::SingleLineComment);

  root->AddEdge(beginComment, EdgeType::Specific, '/');

  //single line
  beginComment->AddEdge(readDefaultSingle, EdgeType::Specific, '/');

  readDefaultSingle->AddEdge(readDefaultSingle, EdgeType::Default);

  readDefaultSingle->AddEdge(endSingle, EdgeType::Specific, '\n');
  readDefaultSingle->AddEdge(endSingle, EdgeType::Specific, '\r');
  readDefaultSingle->AddEdge(endSingle, EdgeType::Specific, '\0');

  //multiline

  DfaState* readDefaultMulti = AddState(TokenType::Invalid);
  DfaState* readStar = AddState(TokenType::Invalid);
  DfaState* endMulti = AddState(TokenType::MultiLineComment);
  beginComment->AddEdge(readDefaultMulti, EdgeType::Specific, '*');

  readDefaultMulti->AddEdge(readDefaultMulti, EdgeType::Default);
  readDefaultMulti->AddEdge(readStar, EdgeType::Specific, '*');
  readStar->AddEdge(endMulti, EdgeType::Specific, '/');
  readStar->AddEdge(readDefaultMulti, EdgeType::Default);

  // i think we're done??

}

void AddSymbols(DfaState* root)
{
  DfaState* dfaIt = nullptr;
  DfaState* fwIt = nullptr;
  auto& map = symbolMap;
  std::string tokenString;
  TokenType::Enum identifier;
  int charIt;
  //for every symbol in our map
  for(auto& it : map)
  {
    //set our string and id
    tokenString = it.first;
    identifier = it.second;

    //iterator to the root for each one
    dfaIt = root;
    //now we iterate through the string
    for(charIt = 0; charIt < tokenString.size(); ++charIt)
    {
      fwIt = dfaIt->FindEdgeWith(tokenString[charIt]);//find an edge with our first char
      if(!fwIt)//didn't find one, so create it
      {
        fwIt = AddState((charIt == tokenString.size() - 1) ? identifier : TokenType::Invalid);
        dfaIt->AddEdge(fwIt, EdgeType::Specific, tokenString[charIt]);
      }
      dfaIt = fwIt;
    }

    //we didn't add the state, but right now its invalid so we validate it
    if(fwIt->GetId() == TokenType::Invalid)
    {
      fwIt->SetId(identifier);
    }

  }

}

DfaState* CreateLanguageDfa()
{
  DfaState* root = AddState(TokenType::Invalid);

  AddNumbers(root);
  AddGenericIdentifiers(root);
  AddWhitespace(root);
  AddStringLiteral(root);
  AddCharLiteral(root);
  AddComments(root);
  AddSymbols(root);
  //we can parse the symbol map programmatically...
  /*DfaState* dfaIt = nullptr;
  DfaState* fwIt = nullptr;
  auto& map = GenerateSymbolMap();
  std::string tokenString;
  TokenType::Enum identifier;
  int charIt;
  //for every symbol in our map
  for(auto& it : map)
  {
  //set our string and id
  tokenString = it.first;
  identifier = it.second;

  //iterator to the root for each one
  dfaIt = root;
  //now we iterate through the string
  for(charIt = 0; charIt < tokenString.size(); ++charIt)
  {
  fwIt = dfaIt->FindEdgeWith(tokenString[charIt]);//find an edge with our first char
  if(!fwIt)//didn't find one, so create it
  {
  fwIt = AddState((charIt == tokenString.size() - 1) ? identifier : TokenType::Invalid);
  dfaIt->AddEdge(fwIt, tokenString[charIt]);
  }
  dfaIt = fwIt;
  }

  //we didn't add the state, but right now its invalid so we validate it
  if(fwIt->GetId() == TokenType::Invalid)
  {
  fwIt->SetId(identifier);
  }

  }*/


  return root;
}
