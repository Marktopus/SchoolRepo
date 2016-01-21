#pragma once
#include "../Drivers/Driver4.hpp"

#include <stack>
class Library;
enum VisitResult
{
  Stop,
  Continue

};

template<typename T>
bool ShouldStop(T* node, Visitor* visitor, bool visit)
{
  return (visit && visitor->Visit(node) == VisitResult::Stop);
}

class Visitor
{
public:
  virtual VisitResult Visit(AbstractNode*   node);

  virtual VisitResult Visit(BlockNode* node);

  virtual VisitResult Visit(ClassNode* node);

  virtual VisitResult Visit(StatementNode* node);

  virtual VisitResult Visit(TypeNode* node);

  virtual VisitResult Visit(VariableNode* node);

  virtual VisitResult Visit(ScopeNode* node);

  virtual VisitResult Visit(ParameterNode* node);

  virtual VisitResult Visit(FunctionNode* node);

  virtual VisitResult Visit(LabelNode* node);

  virtual VisitResult Visit(GotoNode* node);

  virtual VisitResult Visit(ReturnNode* node);

  virtual VisitResult Visit(BreakNode* node);

  virtual VisitResult Visit(ContinueNode* node);

  virtual VisitResult Visit(ExpressionNode* node);

  virtual VisitResult Visit(IfNode* node);

  virtual VisitResult Visit(WhileNode* node);

  virtual VisitResult Visit(ForNode* node);

  virtual VisitResult Visit(ValueNode* node);

  virtual VisitResult Visit(BinaryOperatorNode* node);

  virtual VisitResult Visit(UnaryOperatorNode* node);

  virtual VisitResult Visit(PostExpressionNode* node);

  virtual VisitResult Visit(MemberAccessNode* node);

  virtual VisitResult Visit(CallNode* node);

  virtual VisitResult Visit(CastNode* node);

  virtual VisitResult Visit(IndexNode* node);
private:
};


class PrintVisitor : public Visitor
{
public:
  virtual VisitResult Visit(ClassNode* node) override;

  virtual VisitResult Visit(ReturnNode* node) override;

  virtual VisitResult Visit(TypeNode* node) override;

  virtual VisitResult Visit(VariableNode* node) override;

  virtual VisitResult Visit(ParameterNode* node) override;

  virtual VisitResult Visit(FunctionNode* node) override;

  virtual VisitResult Visit(LabelNode* node) override;

  virtual VisitResult Visit(GotoNode* node) override;

  virtual VisitResult Visit(ValueNode* node) override;

  virtual VisitResult Visit(BinaryOperatorNode* node) override;

  virtual VisitResult Visit(UnaryOperatorNode* node) override;

  virtual VisitResult Visit(MemberAccessNode* node) override;

  virtual VisitResult Visit(CallNode* node) override;

  virtual VisitResult Visit(IndexNode* node) override;

  virtual VisitResult Visit(CastNode* node) override;

  virtual VisitResult Visit(BlockNode* node) override;

  virtual VisitResult Visit(ScopeNode* node) override;

  virtual VisitResult Visit(WhileNode* node) override;

  virtual VisitResult Visit(ForNode* node) override;

  virtual VisitResult Visit(IfNode* node) override;

  virtual VisitResult Visit(ContinueNode* node) override;

  virtual VisitResult Visit(BreakNode* node) override;

private:
};


class PrintAnalyzerVisitor : public Visitor
{
public:
  virtual VisitResult Visit(ClassNode* node) override;

  virtual VisitResult Visit(ReturnNode* node) override;

  virtual VisitResult Visit(TypeNode* node) override;

  virtual VisitResult Visit(VariableNode* node) override;

  virtual VisitResult Visit(ParameterNode* node) override;

  virtual VisitResult Visit(FunctionNode* node) override;

  virtual VisitResult Visit(LabelNode* node) override;

  virtual VisitResult Visit(GotoNode* node) override;

  virtual VisitResult Visit(ValueNode* node) override;

  virtual VisitResult Visit(BinaryOperatorNode* node) override;

  virtual VisitResult Visit(UnaryOperatorNode* node) override;

  virtual VisitResult Visit(MemberAccessNode* node) override;

  virtual VisitResult Visit(CallNode* node) override;

  virtual VisitResult Visit(IndexNode* node) override;

  virtual VisitResult Visit(CastNode* node) override;

  virtual VisitResult Visit(BlockNode* node) override;

  virtual VisitResult Visit(ScopeNode* node) override;

  virtual VisitResult Visit(WhileNode* node) override;

  virtual VisitResult Visit(ForNode* node) override;

  virtual VisitResult Visit(IfNode* node) override;

  virtual VisitResult Visit(ContinueNode* node) override;

  virtual VisitResult Visit(BreakNode* node) override;

private:
};


class ClassVisitor : public Visitor
{
public:

  ClassVisitor(Library* lib, const std::vector<Library*>& libraries);

  virtual VisitResult Visit(ClassNode* node) override;

  virtual VisitResult Visit(ReturnNode* node) override;
  
  virtual VisitResult Visit(TypeNode* node) override;
  
  virtual VisitResult Visit(VariableNode* node) override;
  
  virtual VisitResult Visit(ParameterNode* node) override;
  
  virtual VisitResult Visit(FunctionNode* node) override;
  
  virtual VisitResult Visit(LabelNode* node) override;
  
  virtual VisitResult Visit(GotoNode* node) override;
  
  virtual VisitResult Visit(ValueNode* node) override;
  
  virtual VisitResult Visit(BinaryOperatorNode* node) override;
  
  virtual VisitResult Visit(UnaryOperatorNode* node) override;
  
  virtual VisitResult Visit(MemberAccessNode* node) override;
  
  virtual VisitResult Visit(CallNode* node) override;
  
  virtual VisitResult Visit(IndexNode* node) override;
  
  virtual VisitResult Visit(CastNode* node) override;

  virtual VisitResult Visit(BlockNode* node) override;

  virtual VisitResult Visit(ScopeNode* node) override;
  
  virtual VisitResult Visit(WhileNode* node) override;
  
  virtual VisitResult Visit(ForNode* node) override;
  
  virtual VisitResult Visit(IfNode* node) override;
  
  virtual VisitResult Visit(ContinueNode* node) override;
  
  virtual VisitResult Visit(BreakNode* node) override;

private:
  Library* library_;
  std::vector<Library*> dependencies_;
  //Type* parent_type_;
  //Function* parent_function_;
};


class EvaluatorVisitor : public Visitor
{
public:

  EvaluatorVisitor(Library* lib, const std::vector<Library*>& libraries);

  virtual VisitResult Visit(ClassNode* node) override;

  //virtual VisitResult Visit(ReturnNode* node) override;
  //
  //virtual VisitResult Visit(TypeNode* node) override;
  //
  virtual VisitResult Visit(VariableNode* node) override;
  
  virtual VisitResult Visit(ParameterNode* node) override;

  virtual VisitResult Visit(FunctionNode* node) override;
  
  virtual VisitResult Visit(LabelNode* node) override;
  //
  //virtual VisitResult Visit(GotoNode* node) override;
  //
  //virtual VisitResult Visit(ValueNode* node) override;
  //
  //virtual VisitResult Visit(BinaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(UnaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(MemberAccessNode* node) override;
  //
  //virtual VisitResult Visit(CallNode* node) override;
  //
  //virtual VisitResult Visit(IndexNode* node) override;
  //
  //virtual VisitResult Visit(CastNode* node) override;

  virtual VisitResult Visit(BlockNode* node) override;

  //virtual VisitResult Visit(ScopeNode* node) override;
  //
  //virtual VisitResult Visit(WhileNode* node) override;
  //
  //virtual VisitResult Visit(ForNode* node) override;
  //
  //virtual VisitResult Visit(IfNode* node) override;
  //
  //virtual VisitResult Visit(ContinueNode* node) override;
  //
  //virtual VisitResult Visit(BreakNode* node) override;

private:
  Library* library_;
  std::vector<Library*> dependencies_;
  Type* parent_type_;
  Function* parent_function_;
  std::vector<std::unordered_map<std::string, Symbol*>> symbol_stack_;

};

class ExpressionVisitor : public Visitor
{
public:

  ExpressionVisitor(Library* lib, const std::vector<Library*>& libraries);

  virtual VisitResult Visit(ClassNode* node) override;
  
  virtual VisitResult Visit(ReturnNode* node) override;
  
  //virtual VisitResult Visit(TypeNode* node) override;
  
  virtual VisitResult Visit(VariableNode* node) override;
  
  virtual VisitResult Visit(ParameterNode* node) override;
  
  virtual VisitResult Visit(FunctionNode* node) override;
  
  virtual VisitResult Visit(LabelNode* node) override;
  
  virtual VisitResult Visit(GotoNode* node) override;
  
  virtual VisitResult Visit(ValueNode* node) override;
  
  virtual VisitResult Visit(BinaryOperatorNode* node) override;
  
  virtual VisitResult Visit(UnaryOperatorNode* node) override;
  
  virtual VisitResult Visit(MemberAccessNode* node) override;
  
  virtual VisitResult Visit(CallNode* node) override;
  
  virtual VisitResult Visit(IndexNode* node) override;
  
  virtual VisitResult Visit(CastNode* node) override;
  
  virtual VisitResult Visit(BlockNode* node) override;
  
  virtual VisitResult Visit(ScopeNode* node) override;
  
  virtual VisitResult Visit(WhileNode* node) override;
  
  virtual VisitResult Visit(ForNode* node) override;
  
  virtual VisitResult Visit(IfNode* node) override;
  
  virtual VisitResult Visit(ContinueNode* node) override;
  
  virtual VisitResult Visit(BreakNode* node) override;

private:
  Library* library_;
  std::vector<Library*> dependencies_;
  Type* parent_type_;
  Function* parent_function_;
  std::vector<std::unordered_map<std::string, Symbol*>> symbol_stack_;

};

class FunctionVisitor : public Visitor
{
public:

  FunctionVisitor(Library* lib, const std::vector<Library*>& libraries);

  //virtual VisitResult Visit(ClassNode* node) override;
  //
  virtual VisitResult Visit(ReturnNode* node) override;
  //
  //virtual VisitResult Visit(TypeNode* node) override;
  //
  virtual VisitResult Visit(VariableNode* node) override;

  virtual VisitResult Visit(ParameterNode* node) override;

  virtual VisitResult Visit(FunctionNode* node) override;
  //
  //virtual VisitResult Visit(LabelNode* node) override;
  //
  //virtual VisitResult Visit(GotoNode* node) override;
  //
  //virtual VisitResult Visit(ValueNode* node) override;
  //
  //virtual VisitResult Visit(BinaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(UnaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(MemberAccessNode* node) override;
  //
  //virtual VisitResult Visit(CallNode* node) override;
  //
  //virtual VisitResult Visit(IndexNode* node) override;
  //
  virtual VisitResult Visit(CastNode* node) override;
  //
  //virtual VisitResult Visit(BlockNode* node) override;
  //
  //virtual VisitResult Visit(ScopeNode* node) override;
  //
  //virtual VisitResult Visit(WhileNode* node) override;
  //
  //virtual VisitResult Visit(ForNode* node) override;
  //
  //virtual VisitResult Visit(IfNode* node) override;
  //
  //virtual VisitResult Visit(ContinueNode* node) override;
  //
  //virtual VisitResult Visit(BreakNode* node) override;

private:
  Library* library_;
  std::vector<Library*> dependencies_;
  std::vector<Type*> current_parameters_;
  Type* current_return_value_;
  Type* parent_type_;
  Function* parent_function_;
};

class InfoVisitor : public Visitor
{
public:

  InfoVisitor(Library* lib, const std::vector<Library*>& libraries);

  //virtual VisitResult Visit(ClassNode* node) override;

  //virtual VisitResult Visit(ReturnNode* node) override;
  
  virtual VisitResult Visit(TypeNode* node) override;
  
  //virtual VisitResult Visit(VariableNode* node) override;
  //
  //virtual VisitResult Visit(ParameterNode* node) override;
  //
  //virtual VisitResult Visit(FunctionNode* node) override;
  //
  //virtual VisitResult Visit(LabelNode* node) override;
  //
  //virtual VisitResult Visit(GotoNode* node) override;
  //
  //virtual VisitResult Visit(ValueNode* node) override;
  //
  //virtual VisitResult Visit(BinaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(UnaryOperatorNode* node) override;
  //
  //virtual VisitResult Visit(MemberAccessNode* node) override;
  //
  //virtual VisitResult Visit(CallNode* node) override;
  //
  //virtual VisitResult Visit(IndexNode* node) override;
  //
  //virtual VisitResult Visit(CastNode* node) override;

  //virtual VisitResult Visit(BlockNode* node) override;

  //virtual VisitResult Visit(ScopeNode* node) override;
  //
  //virtual VisitResult Visit(WhileNode* node) override;
  //
  //virtual VisitResult Visit(ForNode* node) override;
  //
  //virtual VisitResult Visit(IfNode* node) override;
  //
  //virtual VisitResult Visit(ContinueNode* node) override;
  //
  //virtual VisitResult Visit(BreakNode* node) override;

private:
  Library* library_;
  std::vector<Library*> dependencies_;
};


struct Parser
{
  Parser(std::vector<Token>& tokenStreamInit);
  ~Parser();

  bool Expect(TokenType::Enum token);

  bool Expect(bool success, const std::string& expect);

  bool Accept(TokenType::Enum token);

  std::unique_ptr<BlockNode> Root();

  std::unique_ptr<ClassNode> Class();

  std::unique_ptr<VariableNode> Var();

  std::unique_ptr<FunctionNode> Function();

  std::unique_ptr<ParameterNode> Parameter();

  std::unique_ptr<TypeNode> SpecifiedType();

  std::unique_ptr<TypeNode> Type();

  std::unique_ptr<ScopeNode> Scope();

  std::unique_ptr<StatementNode> Statement();

  std::unique_ptr<StatementNode> DelimitedStatement();

  std::unique_ptr<StatementNode> FreeStatement();

  std::unique_ptr<LabelNode> Label();

  std::unique_ptr<GotoNode> Goto();

  std::unique_ptr<ReturnNode> Return();

  std::unique_ptr<IfNode> If();

  std::unique_ptr<IfNode> Else();

  std::unique_ptr<WhileNode> While();

  std::unique_ptr<ForNode> For();

  std::unique_ptr<ExpressionNode> GroupedExpression();

  std::unique_ptr<ExpressionNode> Value();

  std::unique_ptr<ExpressionNode> Expression();

  std::unique_ptr<ExpressionNode> Expression1();

  std::unique_ptr<ExpressionNode> Expression2();

  std::unique_ptr<ExpressionNode> Expression3();

  std::unique_ptr<ExpressionNode> Expression4();

  std::unique_ptr<ExpressionNode> Expression5();

  std::unique_ptr<ExpressionNode> Expression6();

  std::unique_ptr<ExpressionNode> Expression7();

  std::unique_ptr<MemberAccessNode> MemberAccess();

  std::unique_ptr<CallNode> Call();

  std::unique_ptr<CastNode> Cast();

  std::unique_ptr<IndexNode> Index();

  size_t TokenPosition;
  std::vector<Token>& tokenStream;

};

