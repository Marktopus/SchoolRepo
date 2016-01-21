/******************************************************************\
* Author:
* Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#include "../Drivers/Driver2.hpp"
#include "../Drivers/Driver3.hpp"

enum VisitResult
{
  Stop,
  Continue

};



class Visitor
{
public:
  virtual VisitResult Visit(AbstractNode*   node)
  {
    return Continue;
  }
  virtual VisitResult Visit(BlockNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(ClassNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(StatementNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(TypeNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(VariableNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ScopeNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ParameterNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(FunctionNode* node)
  {
    return this->Visit((AbstractNode*) node);
  }

  virtual VisitResult Visit(LabelNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(GotoNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ReturnNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(BreakNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ContinueNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ExpressionNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(IfNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(WhileNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ForNode* node)
  {
    return this->Visit((StatementNode*) node);
  }

  virtual VisitResult Visit(ValueNode* node)
  {
    return this->Visit((ExpressionNode*) node);
  }

  virtual VisitResult Visit(BinaryOperatorNode* node)
  {
    return this->Visit((ExpressionNode*) node);
  }

  virtual VisitResult Visit(UnaryOperatorNode* node)
  {
    return this->Visit((ExpressionNode*) node);
  }

  virtual VisitResult Visit(PostExpressionNode* node)
  {
    return this->Visit((ExpressionNode*) node);
  }

  virtual VisitResult Visit(MemberAccessNode* node)
  {
    return this->Visit((PostExpressionNode*) node);
  }

  virtual VisitResult Visit(CallNode* node)
  {
    return this->Visit((PostExpressionNode*) node);
  }

  virtual VisitResult Visit(CastNode* node)
  {
    return this->Visit((PostExpressionNode*) node);
  }

  virtual VisitResult Visit(IndexNode* node)
  {
    return this->Visit((PostExpressionNode*) node);
  }
private:
};


class PrintVisitor : public Visitor
{
public:
  virtual VisitResult Visit(ClassNode* node) override
  {
    NodePrinter printer;
    printer << "ClassNode(" << node->mName.str() << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(ReturnNode* node) override
  {
    NodePrinter printer;
    printer << "ReturnNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(TypeNode* node) override
  {
    NodePrinter printer;
    printer << "TypeNode(" << node->mName.str() << "," << node->mPointerCount << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(VariableNode* node) override
  {
    NodePrinter printer;
    printer << "VariableNode(" << node->mName << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(ParameterNode* node) override
  {
    NodePrinter printer;
    printer << "ParameterNode(" << node->mName << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(FunctionNode* node) override
  {
    NodePrinter printer;
    printer << "FunctionNode(" << node->mName << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(LabelNode* node) override
  {
    NodePrinter printer;
    printer << "LabelNode(" << node->mName << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(GotoNode* node) override
  {
    NodePrinter printer;
    printer << "GotoNode(" << node->mName << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(ValueNode* node) override
  {
    NodePrinter printer;
    printer << "ValueNode(" << node->mToken.str() << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(BinaryOperatorNode* node) override
  {
    NodePrinter printer;
    printer << "BinaryOperatorNode(" << node->mOperator.str() << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(UnaryOperatorNode* node) override
  {
    NodePrinter printer;
    printer << "UnaryOperatorNode(" << node->mOperator.str() << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(MemberAccessNode* node) override
  {
    NodePrinter printer;
    printer << "MemberAccessNode(" << node->mOperator.str() << "," << node->mName.str() << ")";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(CallNode* node) override
  {
    NodePrinter printer;
    printer << "CallNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(IndexNode* node) override
  {
    NodePrinter printer;
    printer << "IndexNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(CastNode* node) override
  {
    NodePrinter printer;
    printer << "CastNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(BlockNode* node) override
  {
    NodePrinter printer;
    printer << "BlockNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(ScopeNode* node) override
  {
    NodePrinter printer;
    printer << "ScopeNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(WhileNode* node) override
  {
    NodePrinter printer;
    printer << "WhileNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }
  virtual VisitResult Visit(ForNode* node) override
  {
    NodePrinter printer;
    printer << "ForNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(IfNode* node) override
  {
    NodePrinter printer;
    printer << "IfNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(ContinueNode* node) override
  {
    NodePrinter printer;
    printer << "ContinueNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

  virtual VisitResult Visit(BreakNode* node) override
  {
    NodePrinter printer;
    printer << "BreakNode";
    node->Walk(this, false);
    return VisitResult::Stop;
  }

private:
};

template<typename T>
bool ShouldStop(T* node, Visitor* visitor, bool visit)
{
  return (visit && visitor->Visit(node) == VisitResult::Stop);
}


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
    if(TokenPosition >= tokenStream.size())
    {
      throw ParsingException("Error: expected " + expect + " but found nothing");
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

  std::unique_ptr<BlockNode> Root()
  {
    PrintRule print("Block");
    std::unique_ptr<BlockNode> root = std::make_unique<BlockNode>();
    std::unique_ptr<AbstractNode> iter;
    bool accepting = true;
    while(accepting && TokenPosition < tokenStream.size())
    {
      iter = Class();
      root->mGlobals.push_back(std::move(iter));
      iter = Function();
      root->mGlobals.push_back(std::move(iter));
      iter = Var();
      if(iter)
      {
        Accept(TokenType::Semicolon);
      }
      root->mGlobals.push_back(std::move(iter));
      accepting = (bool)iter;
    }

    print.Accept();
    return std::move(root);
  }


  std::unique_ptr<ClassNode> Class()
  {
    PrintRule print("Class");
    bool accepting = Accept(TokenType::Class);
    if(!accepting)
    {
      return false;
    }
    std::unique_ptr<ClassNode> newClass = std::make_unique<ClassNode>();
    Expect(TokenType::Identifier);
    newClass->mName = tokenStream[TokenPosition - 1];
    Expect(TokenType::OpenCurley);

    std::unique_ptr<AbstractNode> stmt;
    bool readClass = true;
    do
    {
      readClass = false;
      stmt = Var();
      if(stmt)
      {
        readClass = true;
        Expect(TokenType::Semicolon);
        newClass->mMembers.push_back(std::move(stmt));
      }
      else
      {
        
        stmt = Function();
        if(stmt)
        {
          readClass = true;
          newClass->mMembers.push_back(std::move(stmt));
        }
        
      }
      
      
      
    }
    while(readClass);

    Expect(TokenType::CloseCurley);

    print.Accept(accepting);

    return std::move(newClass);
  }

  std::unique_ptr<VariableNode> Var()
  {
    PrintRule print("Var");
    bool accepting = Accept(TokenType::Var);
    if(!accepting)
    {
      return false;
    }
    auto variable = std::make_unique<VariableNode>();
    Expect(TokenType::Identifier);
    variable->mName = tokenStream[TokenPosition - 1];
    variable->mType = SpecifiedType();
    Expect((bool) variable->mType, "type specifier");
    if(Accept(TokenType::Assignment))
    {
      variable->mInitialValue = Expression();
      Expect((bool) variable->mInitialValue, "expression");
    }
    print.Accept(accepting);

    return std::move(variable);
  }

  std::unique_ptr<FunctionNode> Function()
  {
    PrintRule print("Function");
    bool accepting = Accept(TokenType::Function);
    if(!accepting)
    {
      return nullptr;
    }
    auto fnNode = std::make_unique<FunctionNode>();
    Expect(TokenType::Identifier);
    fnNode->mName = tokenStream[TokenPosition - 1];
    Expect(TokenType::OpenParentheses);

    if(fnNode->mParameters.push_back(Parameter()))
    {
      while(Accept(TokenType::Comma))
      {
        Expect(fnNode->mParameters.push_back(Parameter()), "parameter");
      }
    }

    Expect(TokenType::CloseParentheses);

    fnNode->mReturnType = SpecifiedType();
    
    fnNode->mScope = Scope();
    Expect((bool) fnNode->mScope, "scope");

    print.Accept(accepting);
    return std::move(fnNode);
  }

  std::unique_ptr<ParameterNode> Parameter()
  {
    PrintRule print("Parameter");
    bool accepting = Accept(TokenType::Identifier);
    if(!accepting)
    {
      return nullptr;
    }
    auto paramNode = std::make_unique<ParameterNode>();
    paramNode->mName = tokenStream[TokenPosition - 1];
    paramNode->mType = SpecifiedType();
    Expect((bool) paramNode->mType, "type specifier");
    print.Accept(accepting);
    return std::move(paramNode);
  }

  std::unique_ptr<TypeNode> SpecifiedType()
  {
    PrintRule print("SpecifiedType");
    bool accepting = Accept(TokenType::Colon);
    if(!accepting)
    {
      return false;
    }
    
    std::unique_ptr<TypeNode> type = Type();
    Expect((bool)type, "type");
    
    print.Accept(accepting);
    return std::move(type);
  }

  std::unique_ptr<TypeNode> Type()
  {
    PrintRule print("Type");
    std::unique_ptr<TypeNode> newType = std::make_unique<TypeNode>();
    bool accepting = Accept(TokenType::Identifier);
    newType->mName = tokenStream[TokenPosition - 1];
    newType->mPointerCount = 0;
    while(Accept(TokenType::Asterisk))
    {
      newType->mPointerCount++;
    }

    print.Accept(accepting);
    return std::move(newType);
  }

  std::unique_ptr<ScopeNode> Scope()
  {
    PrintRule print("Scope");
    bool accepting = Accept(TokenType::OpenCurley);
    if(!accepting)
    {
      return nullptr;
    }
    auto scopeNode = std::make_unique<ScopeNode>();
    while(scopeNode->mStatements.push_back(Statement()))
    {

    }

    Expect(TokenType::CloseCurley);

    print.Accept(accepting);
    return std::move(scopeNode);
  }

  std::unique_ptr<StatementNode> Statement()
  {
    PrintRule print("Statement");
    auto statement = FreeStatement();
    bool accepting = false;
    if(statement)
    {
      accepting = true;
    }
    if(!accepting)
    {
      statement = DelimitedStatement();
      accepting = (bool)statement;

      if(accepting)
      {
        Expect(TokenType::Semicolon);
      }
    }

    print.Accept(accepting);
    return std::move(statement);
  }

  std::unique_ptr<StatementNode> DelimitedStatement()
  {
    PrintRule print("DelimitedStatement");
    std::unique_ptr<StatementNode> stmtPtr = Label();
    if(!stmtPtr)
    {
      stmtPtr = Goto();
    }
    if(!stmtPtr)
    {
      stmtPtr = Return();
    }
    if(!stmtPtr)
    {
      stmtPtr = Var();
    }
    if(!stmtPtr)
    {
      stmtPtr = Expression();
    }

     
    if(Accept(TokenType::Break))
    {
      stmtPtr = std::make_unique<BreakNode>();
    }
    if(Accept(TokenType::Continue))
    {
      stmtPtr = std::make_unique<ContinueNode>();
    }
    print.Accept((bool)stmtPtr);
    return std::move(stmtPtr);
  }

  std::unique_ptr<StatementNode> FreeStatement()
  {
    PrintRule print("FreeStatement");
    std::unique_ptr<StatementNode> endStatement;
    endStatement = std::move(If());
    if(!endStatement)
    {
      endStatement = std::move(While());
    }
    if(!endStatement)
    {
      endStatement = std::move(For());
    }
    print.Accept((bool)endStatement);
    return std::move(endStatement);
  }

  std::unique_ptr<LabelNode> Label()
  {
    PrintRule print("Label");
    bool accepting = Accept(TokenType::Label);
    if(!accepting)
    {
      return nullptr;
    }
    Expect(TokenType::Identifier);
    auto labelNode = std::make_unique<LabelNode>();
    labelNode->mName = tokenStream[TokenPosition - 1];
    print.Accept(accepting);
    return std::move(labelNode);
  }

  std::unique_ptr<GotoNode> Goto()
  {
    PrintRule print("Goto");
    bool accepting = Accept(TokenType::Goto);
    if(!accepting)
    {
      return nullptr;
    }
    Expect(TokenType::Identifier);
    auto gotoNode = std::make_unique<GotoNode>();
    gotoNode->mName = tokenStream[TokenPosition - 1];
    print.Accept(accepting);
    return std::move(gotoNode);
  }

  std::unique_ptr<ReturnNode> Return()
  {
    PrintRule print("Return");
    bool accepting = Accept(TokenType::Return);
    if(!accepting)
    {
      return nullptr;
    }
    
    auto gotoNode = std::make_unique<ReturnNode>();
    gotoNode->mReturnValue = Expression();
    print.Accept(accepting);
    return std::move(gotoNode);
  }

  std::unique_ptr<IfNode> If()
  {
    PrintRule print("If");
    
    bool accepting = Accept(TokenType::If);
    
    if(!accepting)
    {
      return nullptr;
    }
    std::unique_ptr<IfNode> ifNode = std::make_unique<IfNode>();
    ifNode->mCondition = GroupedExpression();
    Expect((bool)ifNode->mCondition, "expression in parentheses");
    ifNode->mScope = Scope();
    Expect((bool)ifNode->mScope, "scope");
    ifNode->mElse = Else();
    print.Accept(accepting);
    return std::move(ifNode);
  }

  std::unique_ptr<IfNode> Else()
  {
    PrintRule print("Else");
    bool accepting = Accept(TokenType::Else);
    if(!accepting)
    {
      return nullptr;
    }
    auto elsePtr = If();
    if(!elsePtr)
    {
      auto scope = Scope();
      if(scope)
      {
        elsePtr = std::make_unique<IfNode>();
        elsePtr->mScope = std::move(scope);
      }
    }
    Expect((bool)elsePtr, "if statement or scope");
    print.Accept(accepting);
    return std::move(elsePtr);
  }

  std::unique_ptr<WhileNode> While()
  {
    PrintRule print("While");
    bool accepting = Accept(TokenType::While);
    if(!accepting)
    {
      return nullptr;
    }
    auto whilePtr = std::make_unique<WhileNode>();
    whilePtr->mCondition = GroupedExpression();
    Expect((bool) whilePtr->mCondition, "expression");
    whilePtr->mScope = Scope();
    Expect((bool) whilePtr->mScope, "scope");
    print.Accept(accepting);
    return std::move(whilePtr);
  }

  std::unique_ptr<ForNode> For()
  {
    PrintRule print("For");
    bool accepting = Accept(TokenType::For);
    if(!accepting)
    {
      return nullptr;
    }
    auto forPtr = std::make_unique<ForNode>();
    Expect(TokenType::OpenParentheses);
    forPtr->mInitialVariable = Var();
    forPtr->mInitialExpression = Expression();

    accepting = accepting && Expect(TokenType::Semicolon);

    forPtr->mCondition = Expression();

    accepting = accepting && Expect(TokenType::Semicolon);

    forPtr->mIterator = Expression();
    Expect(TokenType::CloseParentheses);
    forPtr->mScope = Scope();
    accepting = Expect((bool) forPtr->mScope, "scope");
    print.Accept(accepting);

    return std::move(forPtr);
  }

  std::unique_ptr<ExpressionNode> GroupedExpression()
  {
    PrintRule print("GroupedExpression");
    bool accepting = Accept(TokenType::OpenParentheses);
    if(!accepting)
    {
      return nullptr;
    }
    std::unique_ptr<ExpressionNode> expression = std::move(Expression());
    Expect((bool)expression, "expression");
    Expect(TokenType::CloseParentheses);
    print.Accept(accepting);
    return std::move(expression);
  }

  std::unique_ptr<ExpressionNode> Value()
  {
    PrintRule print("Value");
    
    std::unique_ptr<ExpressionNode> expr;
    
    bool accepting = 
      Accept(TokenType::True) ||
      Accept(TokenType::False) ||
      Accept(TokenType::Null) ||
      Accept(TokenType::IntegerLiteral) ||
      Accept(TokenType::FloatLiteral) ||
      Accept(TokenType::StringLiteral) ||
      Accept(TokenType::Identifier);
    
    if(!accepting)
    {
      expr = std::move(GroupedExpression());
      accepting = (bool) expr;
    }
    else
    {
      std::unique_ptr<ValueNode> valueNode = std::make_unique<ValueNode>();
      valueNode->mToken = tokenStream[TokenPosition - 1];
      expr = std::move(valueNode);
    }
    print.Accept(accepting);
    return std::move(expr);
  }

  std::unique_ptr<ExpressionNode> Expression()
  {
    PrintRule print("Expression");
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression1());
    bool accepting = (bool) lhs;
    if(!accepting)
    {
      return nullptr;
    }
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    if(Accept(TokenType::Assignment) ||
       Accept(TokenType::AssignmentPlus) ||
       Accept(TokenType::AssignmentMinus) ||
       Accept(TokenType::AssignmentMultiply) ||
       Accept(TokenType::AssignmentDivide) ||
       Accept(TokenType::AssignmentModulo))
    {
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression());
      Expect((bool)rhs, "expression");
      operatorNode->mRight = std::move(rhs);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression1()
  {
    PrintRule print("Expression1");
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression2());
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    bool accepting = (bool) lhs;
    if(!accepting)
    {
      return nullptr;
    }
    while(Accept(TokenType::LogicalOr))
    {
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression2());
      Expect((bool)rhs, "expression");
      operatorNode->mRight = std::move(rhs);
      lhs = std::move(operatorNode);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression2()
  {
    PrintRule print("Expression2");
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression3());
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    bool accepting = (bool) lhs;
    if(!accepting)
    {
      return nullptr;
    }
    while(Accept(TokenType::LogicalAnd))
    {
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression3());
      Expect((bool) rhs, "expression");
      operatorNode->mRight = std::move(rhs);
      lhs = std::move(operatorNode);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression3()
  {
    PrintRule print("Expression3");
    bool accepting = false;
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression4());
    accepting = (bool)lhs;
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    if(!accepting)
    {
      return nullptr;
    }
    while(Accept(TokenType::LessThan) ||
          Accept(TokenType::GreaterThan) ||
          Accept(TokenType::LessThanOrEqualTo) ||
          Accept(TokenType::GreaterThanOrEqualTo) ||
          Accept(TokenType::Equality) ||
          Accept(TokenType::Inequality))
    {
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression4());
      Expect((bool) rhs, "expression");
      operatorNode->mRight = std::move(rhs);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression4()
  {
    PrintRule print("Expression4");
    bool accepting = false;
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression5());
    accepting = (bool) lhs;
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    if(!accepting)
    {
      return nullptr;
    }
    while(Accept(TokenType::Plus) ||
          Accept(TokenType::Minus))
    {
      if(operatorNode)
      {
        lhs = std::move(operatorNode);
      }
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression5());
      Expect((bool) rhs, "expression");
      operatorNode->mRight = std::move(rhs);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression5()
  {
    PrintRule print("Expression5");
    bool accepting = false;
    std::unique_ptr<ExpressionNode> lhs = std::move(Expression6());
    accepting = (bool) lhs;
    std::unique_ptr<BinaryOperatorNode> operatorNode;
    std::unique_ptr<ExpressionNode> rhs;
    if(!accepting)
    {
      return nullptr;
    }
    while(Accept(TokenType::Asterisk) ||
          Accept(TokenType::Divide) ||
          Accept(TokenType::Modulo))
    {
      if(operatorNode)
      {
        lhs = std::move(operatorNode);
      }
      operatorNode = std::make_unique<BinaryOperatorNode>();
      operatorNode->mLeft = std::move(lhs);
      operatorNode->mOperator = tokenStream[TokenPosition - 1];
      rhs = std::move(Expression6());
      Expect((bool) rhs, "expression");
      operatorNode->mRight = std::move(rhs);
    }
    print.Accept(accepting);
    if(operatorNode)
    {
      return std::move(operatorNode);
    }
    return std::move(lhs);
  }

  std::unique_ptr<ExpressionNode> Expression6()
  {
    PrintRule print("Expression6");
    unique_vector<UnaryOperatorNode> operatorStore;
    std::unique_ptr<ExpressionNode>* iter = nullptr;

    std::unique_ptr<ExpressionNode> rhs;
    while(Accept(TokenType::Asterisk) || 
          Accept(TokenType::Minus) || 
          Accept(TokenType::LogicalNot) || 
          Accept(TokenType::Increment) || 
          Accept(TokenType::Decrement))
    {
      operatorStore.push_back(std::make_unique<UnaryOperatorNode>());
      operatorStore[operatorStore.size() -1]->mOperator = tokenStream[TokenPosition - 1];
    }
    

    rhs = std::move(Expression7());
    bool accepting = (bool) rhs;
    if(!accepting)
    {
      return nullptr;
    }
    if(!operatorStore.empty())
    {
      operatorStore.back()->mRight = std::move(rhs);
      if(operatorStore.size() > 1)
      {
        operatorStore[0]->mRight = std::move(operatorStore[1]);
        iter = &operatorStore[0]->mRight;
        for(int i = 2; i < operatorStore.size(); ++i)
        {
          ((UnaryOperatorNode*) iter->get())->mRight = std::move(operatorStore[i]);
          iter = &operatorStore[i]->mRight;
        }
      }
      print.Accept(accepting);
      return std::move(operatorStore[0]);
    }
    print.Accept(accepting);
    return std::move(rhs);
  }

  std::unique_ptr<ExpressionNode> Expression7()
  {
    PrintRule print("Expression7");
    auto rhs = Value();
    bool accepting = (bool)rhs;
    if(!accepting)
    {
      return nullptr;
    }
    std::unique_ptr<PostExpressionNode> postNode;

    unique_vector<PostExpressionNode> argVec;
    //argVec.push_back(std::move(rhs));
    do
    {
      postNode = std::move(MemberAccess());
      if(!postNode)
      {
        postNode = std::move(Call());
        if(!postNode)
        {
          postNode = std::move(Cast());
          if(!postNode)
          {
            postNode = std::move(Index());
          }
        }
      }
      if(postNode)
      {
        argVec.push_back(std::move(postNode));
      }
      else
      {
        break;
      }
    }
    while(true);
    
    print.Accept(accepting);
    if(!argVec.empty())
    {
      std::reverse(argVec.begin(), argVec.end());
      argVec[argVec.size() - 1]->mLeft = std::move(rhs);
      for(int i = argVec.size() - 1; i > 0; --i)
      {
        argVec[i - 1]->mLeft = std::move(argVec[i]);
      }
      
      return std::move(argVec[0]);
    }

    return std::move(rhs);
  }

  std::unique_ptr<MemberAccessNode> MemberAccess()
  {
    PrintRule print("MemberAccess");
    bool accepting = (Accept(TokenType::Dot) || Accept(TokenType::Arrow));
    if(!accepting)
    {
      return nullptr;
    }
    auto memAccessPtr = std::make_unique<MemberAccessNode>();
    memAccessPtr->mOperator = tokenStream[TokenPosition - 1];
    Expect(TokenType::Identifier);
    memAccessPtr->mName = tokenStream[TokenPosition - 1];
    print.Accept(accepting);
    return std::move(memAccessPtr);
  }

  std::unique_ptr<CallNode> Call()
  {
    PrintRule print("Call");
    bool accepting = Accept(TokenType::OpenParentheses);
    if(!accepting)
    {
      return nullptr;
    }
    auto callPtr = std::make_unique<CallNode>();
    callPtr->mArguments.push_back(Expression());
    if(!callPtr->mArguments.empty())
    {
      while(Accept(TokenType::Comma))
      {
        Expect(callPtr->mArguments.push_back(Expression()), "expression");
      }
    }
    
    Expect(TokenType::CloseParentheses);
    
    print.Accept(accepting);
    return std::move(callPtr);
  }

  std::unique_ptr<CastNode> Cast()
  {
    PrintRule print("Cast");
    bool accepting = Accept(TokenType::As);
    if(!accepting)
    {
      return nullptr;
    }
    auto castPtr = std::make_unique<CastNode>();
    castPtr->mType = Type();
    Expect((bool) castPtr->mType, "type");
    print.Accept(accepting);
    return std::move(castPtr);
  }

  std::unique_ptr<IndexNode> Index()
  {
    PrintRule print("Index");
    bool accepting = Accept(TokenType::OpenBracket);
    if(!accepting)
    {
      return nullptr;
    }
    auto indexPtr = std::make_unique<IndexNode>();
    indexPtr->mIndex = Expression();
    Expect((bool) indexPtr->mIndex, "expression");
    Expect(TokenType::CloseBracket);
    print.Accept(accepting);
    return std::move(indexPtr);
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
    else if(iter->mEnumTokenType == TokenType::SingleLineComment)
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


//assignment 3

// Parse the following stream of tokens into an Expression Tree (starting from the Expression rule)
// This function should return a root node (which holds all of the parsed operators, literals, etc)
// If we fail parsing, we should throw ParsingException (otherwise success is assumed)
std::unique_ptr<ExpressionNode> ParseExpression(std::vector<Token>& tokens)
{
  Parser parser(tokens);
  return parser.Expression();
}

// Print the tree out starting from the given node
// The printed tree must match the tree from the driver
void PrintTree(AbstractNode* node)
{
  PrintVisitor visitor;
  Visitor* visitorPtr =(Visitor*) &visitor;
  node->Walk(visitorPtr);
}

/***************************** PART 2 *****************************/

// Parse the following stream of tokens into an Abstract Syntax Tree (starting from the Block rule)
// This function should return a root node (which holds all of the parsed classes and functions)
// If we fail parsing, we should throw ParsingException (otherwise success is assumed)
std::unique_ptr<BlockNode> ParseBlock(std::vector<Token>& tokens)
{
  Parser parser(tokens);
  return parser.Root();
}



void BlockNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);

  for(auto& it : mGlobals)
  {
    if(it)
    {
      it->Walk(visitor);
    }
  }

}

void ClassNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);
  for(auto& it : mMembers)
  {
    if(it)
    {
      it->Walk(visitor);
    }
  }
}

void StatementNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);
}

void TypeNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);
}

void VariableNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  if(mType)
  {
    mType->Walk(visitor);
  }
  if(mInitialValue)
  {
    mInitialValue->Walk(visitor);
  }
};

void ScopeNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  for(auto& it : mStatements)
  {
    if(it)
    {
      it->Walk(visitor);
    }
  }
}

void ParameterNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);
  if(mType)
  {
    mType->Walk(visitor);
  }
}

void FunctionNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  AbstractNode::Walk(visitor, false);
  for(auto& it : mParameters)
  {
    if(it)
    {
      it->Walk(visitor);
    }
  }
  if(mReturnType)
  {
    mReturnType->Walk(visitor);
  }
  if(mScope)
  {
    mScope->Walk(visitor);
  }
}

void LabelNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
}

void GotoNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
}

void ReturnNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  if(mReturnValue)
  {
    mReturnValue->Walk(visitor);
  }
}

void BreakNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
}

void ContinueNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
}

void ExpressionNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
}

void IfNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  if(mCondition)
  {
    mCondition->Walk(visitor);
  }
  if(mScope)
  {
    mScope->Walk(visitor);
  }
  if(mElse)
  {
    mElse->Walk(visitor);
  }
}

void WhileNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  if(mCondition)
  {
    mCondition->Walk(visitor);
  }
  if(mScope)
  {
    mScope->Walk(visitor);
  }
}

void ForNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  StatementNode::Walk(visitor, false);
  if(mInitialVariable)
  {
    mInitialVariable->Walk(visitor);
  }
  if(mInitialExpression)
  {
    mInitialExpression->Walk(visitor);
  }
  if(mCondition)
  {
    mCondition->Walk(visitor);
  }
  if(mScope)
  {
    mScope->Walk(visitor);
  }
  if(mIterator)
  {
    mIterator->Walk(visitor);
  }
}

void ValueNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  ExpressionNode::Walk(visitor, false);
}

void BinaryOperatorNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  ExpressionNode::Walk(visitor, false);
  if(mLeft)
  {
    mLeft->Walk(visitor);
  }
  if(mRight)
  {
    mRight->Walk(visitor);
  }
}

void UnaryOperatorNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  ExpressionNode::Walk(visitor, false);
  if(mRight)
  {
    mRight->Walk(visitor);
  }
}

void PostExpressionNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  ExpressionNode::Walk(visitor, false);
  if(mLeft)
  {
    mLeft->Walk(visitor);
  }
}

void MemberAccessNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  PostExpressionNode::Walk(visitor, false);
}

void CallNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  PostExpressionNode::Walk(visitor, false);
  for(auto& it : mArguments)
  {
    if(it)
    {
      it->Walk(visitor);
    }
  }
}

void CastNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  PostExpressionNode::Walk(visitor, false);
  if(mType)
  {
    mType->Walk(visitor);
  }
}

void IndexNode::Walk(Visitor* visitor, bool visit)
{
  if(ShouldStop(this, visitor, visit))
  {
    return;
  }
  PostExpressionNode::Walk(visitor, false);
  if(mIndex)
  {
    mIndex->Walk(visitor);
  }
}