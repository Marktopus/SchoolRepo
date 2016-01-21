/******************************************************************\
 * Author: 
 * Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#include "../Drivers/Driver2.hpp"



struct Parser
{
  Parser(std::vector<Token>& tokenStreamInit) 
  : tokenStream(tokenStreamInit),
    TokenPosition(0)
  {
    
  }
  ~Parser()
  {

  }

  bool Expect(TokenType::Enum token)
  {
    
    bool success = (TokenPosition < tokenStream.size()) && (tokenStream[TokenPosition].mEnumTokenType == token);
    if(success)
    {
      ++TokenPosition;
      PrintRule::AcceptedToken(token);
      return true;
    }
      

    throw ParsingException("Error: expected " + std::string(TokenNames[token]));
  }

  bool Expect(bool success, const std::string& expect)
  {
    if(success)
    {
      return true;
    }
    throw ParsingException("Error: expected " + expect + " but found " + std::string(TokenNames[tokenStream[TokenPosition].mEnumTokenType]));
  }

  bool Accept(TokenType::Enum token)
  {
    bool success = (TokenPosition < tokenStream.size()) && (tokenStream[TokenPosition].mEnumTokenType == token);
    if(success)
    {
      ++TokenPosition;
      PrintRule::AcceptedToken(token);
    }
    
    return success;
  }

  bool Root()
  {
    PrintRule print("Block");
    bool accepting = true;
    while(accepting && TokenPosition < tokenStream.size())
    {
      accepting = accepting && (Class() ||
                                Function() ||
                                (Var() && Accept(TokenType::Semicolon)));
    }
    
    
    return print.Accept();
  }


  bool Class()
  {

    PrintRule print("Class");
    bool accepting = Accept(TokenType::Class);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    Expect(TokenType::OpenCurley);

    bool var;
    bool function;
    do
    {
      var = Var();
      function = Function();
      if(var)
      {
        Expect(TokenType::Semicolon);
      }
    }
    while(var || function);

    Expect(TokenType::CloseCurley);

    return print.Accept(accepting);
  }

  bool Var()
  {
    PrintRule print("Var");
    bool accepting = Accept(TokenType::Var);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    Expect(SpecifiedType(), "type specifier");
    if(Accept(TokenType::Assignment))
    {
      Expect(Expression(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Function()
  {

    PrintRule print("Function");
    bool accepting = Accept(TokenType::Function);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    Expect(TokenType::OpenParentheses);

    Parameter();
    while(Accept(TokenType::Comma))
    {
      Expect(Parameter(), "parameter");

    }


    Expect(TokenType::CloseParentheses);

    SpecifiedType();

    Expect(Scope(), "scope");

    return print.Accept(accepting);
  }

  bool Parameter()
  {
    PrintRule print("Parameter");
    bool accepting = Accept(TokenType::Identifier);
    if(!accepting)
    {
      return false;
    }
    Expect(SpecifiedType(), "type specifier");
    return print.Accept(accepting);
  }

  bool SpecifiedType()
  {
    PrintRule print("SpecifiedType");
    bool accepting = Accept(TokenType::Colon);
    if(!accepting)
    {
      return false;
    }
    Expect(Type(), "type");
    return print.Accept(accepting);
  }

  bool Type()
  {
    PrintRule print("Type");
    bool accepting = Accept(TokenType::Identifier);

    while(Accept(TokenType::Asterisk))
    {
    }

    return print.Accept(accepting);
  }

  bool Scope()
  {
    PrintRule print("Scope");
    bool accepting = Accept(TokenType::OpenCurley);
    if(!accepting)
    {
      return false;
    }
    while(Statement())
    {
    }
    Expect(TokenType::CloseCurley);

    return print.Accept(accepting);
  }

  bool Statement()
  {
    PrintRule print("Statement");
    bool accepting = FreeStatement();
    if(!accepting)
    {
      accepting = DelimitedStatement();
      if(!accepting)
      {
        return false;
      }
      else
      {
        Expect(TokenType::Semicolon);
      }
    }
    
    return print.Accept(accepting);
  }

  bool DelimitedStatement()
  {
    PrintRule print("DelimitedStatement");
    return print.Accept(Label() || Goto() || Return() || Accept(TokenType::Break) || Accept(TokenType::Continue) || Var() || Expression());
  }

  bool FreeStatement()
  {
    PrintRule print("FreeStatement");
    return print.Accept(If() || While() || For());
  }

  bool Label()
  {
    PrintRule print("Label");
    bool accepting = Accept(TokenType::Label);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    return print.Accept(accepting);
  }

  bool Goto()
  {
    PrintRule print("Goto");
    bool accepting = Accept(TokenType::Goto);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    return print.Accept(accepting);
  }

  bool Return()
  {
    PrintRule print("Return");
    bool accepting = Accept(TokenType::Return);
    if(!accepting)
    {
      return false;
    }
    Expression();
    return print.Accept(accepting);
  }

  bool If()
  {
    PrintRule print("If");
    bool accepting = Accept(TokenType::If);
    if(!accepting)
    {
      return false;
    }
    Expect(GroupedExpression(), "expression in parentheses");
    Expect(Scope(), "scope");
    Else();
    return print.Accept(accepting);
  }

  bool Else()
  {
    PrintRule print("Else");
    bool accepting = Accept(TokenType::Else);
    if(!accepting)
    {
      return false;
    }
    Expect(If() || Scope(), "if statement or scope");
    return print.Accept(accepting);
  }

  bool While()
  {
    PrintRule print("While");
    bool accepting = Accept(TokenType::While);
    if(!accepting)
    {
      return false;
    }
    Expect(GroupedExpression(), "expression");
    Expect(Scope(), "scope");
    return print.Accept(accepting);
  }

  bool For()
  {
    PrintRule print("For");
    bool accepting = Accept(TokenType::For);
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::OpenParentheses);
    Var();
    Expression();

    accepting = accepting && Expect(TokenType::Semicolon);

    Expression();

    accepting = accepting && Expect(TokenType::Semicolon);

    Expression();

    accepting = accepting && Expect(TokenType::CloseParentheses) && Expect(Scope(), "scope");
    return print.Accept(accepting);
  }

  bool GroupedExpression()
  {
    PrintRule print("GroupedExpression");
    bool accepting = Accept(TokenType::OpenParentheses);
    if(!accepting)
    {
      return false;
    }
    Expect(Expression(), "expression");
    Expect(TokenType::CloseParentheses);
    return print.Accept(accepting);
  }

  bool Value()
  {
    PrintRule print("Value");
    return print.Accept(Accept(TokenType::True) ||
                        Accept(TokenType::False) ||
                        Accept(TokenType::Null) ||
                        Accept(TokenType::IntegerLiteral) ||
                        Accept(TokenType::FloatLiteral) ||
                        Accept(TokenType::StringLiteral) ||
                        Accept(TokenType::Identifier) ||
                        GroupedExpression());
  }

  bool Expression()
  {
    PrintRule print("Expression");
    bool accepting = Expression1();
    if(!accepting)
    {
      return false;
    }
    if(Accept(TokenType::Assignment) ||
       Accept(TokenType::AssignmentPlus) ||
       Accept(TokenType::AssignmentMinus) ||
       Accept(TokenType::AssignmentMultiply) ||
       Accept(TokenType::AssignmentDivide) ||
       Accept(TokenType::AssignmentModulo))
    {
      Expect(Expression(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression1()
  {
    PrintRule print("Expression1");
    bool accepting = Expression2();
    if(!accepting)
    {
      return false;
    }
    while(Accept(TokenType::LogicalOr))
    {
      Expect(Expression2(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression2()
  {
    PrintRule print("Expression2");
    bool accepting = Expression3();
    if(!accepting)
    {
      return false;
    }
    while(Accept(TokenType::LogicalAnd))
    {
      Expect(Expression3(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression3()
  {
    PrintRule print("Expression3");
    bool accepting = Expression4();
    if(!accepting)
    {
      return false;
    }
    while(Accept(TokenType::LessThan) ||
          Accept(TokenType::GreaterThan) ||
          Accept(TokenType::LessThanOrEqualTo) ||
          Accept(TokenType::GreaterThanOrEqualTo) ||
          Accept(TokenType::Equality) ||
          Accept(TokenType::Inequality))
    {
      Expect(Expression4(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression4()
  {
    PrintRule print("Expression4");
    bool accepting = Expression5();
    if(!accepting)
    {
      return false;
    }
    while(Accept(TokenType::Plus) ||
          Accept(TokenType::Minus))
    {
      Expect(Expression5(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression5()
  {
    PrintRule print("Expression5");
    bool accepting = Expression6();
    if(!accepting)
    {
      return false;
    }
    while(Accept(TokenType::Asterisk) ||
          Accept(TokenType::Divide) ||
          Accept(TokenType::Modulo))
    {
      Expect(Expression6(), "expression");
    }
    return print.Accept(accepting);
  }

  bool Expression6()
  {
    PrintRule print("Expression6");
    while(Accept(TokenType::Asterisk) || Accept(TokenType::Minus) || Accept(TokenType::LogicalNot) || Accept(TokenType::Increment) || Accept(TokenType::Decrement))
    {

    }
    bool accepting = Expression7();
    if(!accepting)
    {
      return false;
    }
    
    return print.Accept(accepting);
  }

  bool Expression7()
  {
    PrintRule print("Expression7");
    bool accepting = Value();
    if(!accepting)
    {
      return false;
    }
    while(MemberAccess() || Call() || Cast() || Index())
    {
    }

    return print.Accept(accepting);
  }

  bool MemberAccess()
  {
    PrintRule print("MemberAccess");
    bool accepting = (Accept(TokenType::Dot) || Accept(TokenType::Arrow));
    if(!accepting)
    {
      return false;
    }
    Expect(TokenType::Identifier);
    return print.Accept(accepting);
  }

  bool Call()
  {
    PrintRule print("Call");
    bool accepting = Accept(TokenType::OpenParentheses);
    if(!accepting)
    {
      return false;
    }
    Expression();
    while(Accept(TokenType::Comma))
    {
      Expect(Expression(), "expression");
    }
    Expect(TokenType::CloseParentheses);


    return print.Accept(accepting);
  }

  bool Cast()
  {
    PrintRule print("Cast");
    bool accepting = Accept(TokenType::As);
    if(!accepting)
    {
      return false;
    }
    Expect(Type(), "type");
    return print.Accept(accepting);
  }

  bool Index()
  {
    PrintRule print("Index");
    bool accepting = Accept(TokenType::OpenBracket);
    if(!accepting)
    {
      return false;
    }
    Expect(Expression(), "expression");
    Expect(TokenType::CloseBracket);
    return print.Accept(accepting);
  }

  size_t TokenPosition;
  std::vector<Token>& tokenStream;

};



void RemoveWhitespaceAndComments(std::vector<Token>& tokens)
{
  auto iter = tokens.begin();
  while(iter != tokens.end())
  {
    if(iter->mEnumTokenType == TokenType::Whitespace)
    {
      iter = tokens.erase(iter);
    }
    else if(iter->mEnumTokenType == TokenType::MultiLineComment)
    {
      iter = tokens.erase(iter);
    }
    else if(iter->mEnumTokenType == TokenType::MultiLineComment)
    {
      iter = tokens.erase(iter);
    }
    else
    {
      ++iter;
    }
  }
}



void Recognize(std::vector<Token>& tokens)
{
  Parser parser(tokens);
  parser.Root();
  if(parser.tokenStream.size() != parser.TokenPosition)
  {
    throw ParsingException();
  }
  
}
