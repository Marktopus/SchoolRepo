/******************************************************************\
 * Author: 
 * Copyright 2015, DigiPen Institute of Technology
\******************************************************************/
#include "../Drivers/Driver4.hpp"
#include "Visitor.h"





Symbol* find_symbol_by_name(const std::string& typeName,
                            const std::vector<Library*>& dependencies,
                            Library* library,
                            std::vector<std::unordered_map<std::string, Symbol*>>& symbolStack = std::vector<std::unordered_map<std::string, Symbol*>>())
{
  for(int i = symbolStack.size() - 1; i >= 0; --i)
  {
    auto it = symbolStack[i].find(typeName);
    if(it != symbolStack[i].end())
    {
      return it->second;
    }
  }

  auto& type = library->mGlobalsByName.find(typeName);
  if(type != library->mGlobalsByName.end())
  {
    return type->second;
  }

  for(auto it : dependencies)
  {
    auto& type = it->mGlobalsByName.find(typeName);
    if(type != it->mGlobalsByName.end())
    {
      return type->second;
    }
  }
  return nullptr;
}

Type* dereference(Type* input)
{
  return input->mPointerToType;
}

Type* resolvePointers(Type* input)
{
  while(input->mPointerToType)
  {
    input = dereference(input);
  }
  return input;
}

VisitResult PrintAnalyzerVisitor::Visit(ClassNode * node)
{
  NodePrinter printer;
  printer << "ClassNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ReturnNode * node)
{
  NodePrinter printer;
  printer << "ReturnNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(TypeNode * node)
{
  NodePrinter printer;
  printer << "TypeNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(VariableNode * node)
{
  NodePrinter printer;
  
  printer << "VariableNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ParameterNode * node)
{
  NodePrinter printer;
  printer << "ParameterNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(FunctionNode * node)
{
  NodePrinter printer;
  printer << "FunctionNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(LabelNode * node)
{
  NodePrinter printer;
  printer << "LabelNode(" << node->mSymbol << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(GotoNode * node)
{
  NodePrinter printer;
  printer << "GotoNode(" << node->mResolvedLabel << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ValueNode * node)
{
  NodePrinter printer;
  printer << "ValueNode(" << node->mToken << ", " << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(BinaryOperatorNode * node)
{
  NodePrinter printer;
  printer << "BinaryOperatorNode(" << node->mOperator << ", " << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(UnaryOperatorNode * node)
{
  NodePrinter printer;
  printer << "UnaryOperatorNode(" << node->mOperator << ", " << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(MemberAccessNode * node)
{
  NodePrinter printer;
  printer << "MemberAccessNode(" << node->mOperator << ", " << node->mResolvedMember << ", " << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(CallNode * node)
{
  NodePrinter printer;
  printer << "CallNode" << "(" << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(IndexNode * node)
{
  NodePrinter printer;
  printer << "IndexNode" << "(" << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(CastNode * node)
{
  NodePrinter printer;
  printer << "CastNode" << "(" << node->mResolvedType << ")";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(BlockNode * node)
{
  NodePrinter printer;
  printer << "BlockNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ScopeNode * node)
{
  NodePrinter printer;
  printer << "ScopeNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(WhileNode * node)
{
  NodePrinter printer;
  printer << "WhileNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ForNode * node)
{
  NodePrinter printer;
  printer << "ForNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(IfNode * node)
{
  NodePrinter printer;
  printer << "IfNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(ContinueNode * node)
{
  NodePrinter printer;
  printer << "ContinueNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult PrintAnalyzerVisitor::Visit(BreakNode * node)
{
  NodePrinter printer;
  printer << "BreakNode";
  node->Walk(this, false);
  return VisitResult::Stop;
}



FunctionVisitor::FunctionVisitor(Library* lib, const std::vector<Library*>& libraries)
: library_(lib),
  dependencies_(libraries),
  parent_type_(nullptr),
  parent_function_(nullptr),
  current_return_value_(nullptr)
{

}

VisitResult FunctionVisitor::Visit(ReturnNode* node)
{
  node->Walk(this, false);
  
  return VisitResult::Stop;
}

VisitResult FunctionVisitor::Visit(VariableNode* node)
{
  node->Walk(this, false);
  auto& name = node->mType->mName;
  std::string typeName(name.mText, name.mLength);
  //find type

  Type* foundType = static_cast<Type*>(find_symbol_by_name(typeName, dependencies_, library_));
  if(foundType)
  {
    foundType = library_->GetPointerType(foundType, node->mType->mPointerCount);
  }
  else
  {
    ErrorSymbolNotFound(typeName);
  }

  //? not sure if this is needed
  node->mType->mSymbol = foundType;
  
  
  return VisitResult::Stop;
}

VisitResult FunctionVisitor::Visit(ParameterNode* node)
{
  node->Walk(this, false);
  auto& name = node->mType->mName;
  std::string typeName(name.mText, name.mLength);
  //find type
  
  Type* foundType = static_cast<Type*>(find_symbol_by_name(typeName, dependencies_, library_));
  foundType = library_->GetPointerType(foundType, node->mType->mPointerCount);
  current_parameters_.push_back(foundType);
  return VisitResult::Stop;
}

VisitResult FunctionVisitor::Visit(FunctionNode* node)
{

  node->Walk(this, false);
  std::string retTypeName;
  if(node->mReturnType)
  {
    retTypeName = std::string(node->mReturnType->mName.mText, node->mReturnType->mName.mLength);
  }
  else
  {
    retTypeName = "Void";
  }

  Symbol* retType = find_symbol_by_name(retTypeName, dependencies_, library_);
  if(retTypeName != "Void")
  {
    retType = library_->GetPointerType(static_cast<Type*>(retType), node->mReturnType->mPointerCount);
  }
  

  Type* signatureType = library_->GetFunctionType(current_parameters_, static_cast<Type*>(retType));
  node->mSignatureType = signatureType;
  
  current_parameters_.clear();
  current_return_value_ = nullptr;
  return VisitResult::Stop;
}

VisitResult FunctionVisitor::Visit(CastNode* node)
{
  node->Walk(this, false);
  Type* type = static_cast<Type*>(find_symbol_by_name(std::string(node->mType->mName.mText, node->mType->mName.mLength), dependencies_, library_));
  library_->GetPointerType(type, node->mType->mPointerCount);
  return VisitResult::Stop;
}


ClassVisitor::ClassVisitor(Library* lib, const std::vector<Library*>& libraries)
: library_(lib),
  dependencies_(libraries)
{

}


VisitResult ClassVisitor::Visit(ClassNode * node)
{
  auto type = library_->CreateType(std::string(node->mName.mText, node->mName.mLength), true);
  node->mSymbol = type;
  type->mMode = TypeMode::Class;
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ReturnNode* node)
{
  node->Walk(this, false);
  node->mReturnValue->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(TypeNode* node)
{
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(VariableNode* node)
{
  node->Walk(this, false);
  if(node->mInitialValue)
  {
    node->mInitialValue->mParent = node;
  }
  
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ParameterNode* node)
{
  node->Walk(this, false);
  if(node->mInitialValue)
  {
    node->mInitialValue->mParent = node;
  }
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(FunctionNode* node)
{
  node->Walk(this, false);
  for(auto& it : node->mParameters)
  {
    it->mParent = node;
  }
  node->mScope->mParent = node;
  if(node->mReturnType)
  {
    node->mReturnType->mParent = node;
  }
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(LabelNode* node)
{
  node->Walk(this, false);
  
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(GotoNode* node)
{
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ValueNode* node)
{
  node->Walk(this, false);
  
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(BinaryOperatorNode* node)
{
  node->Walk(this, false);
  node->mLeft->mParent = node;
  node->mRight->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(UnaryOperatorNode* node)
{
  node->Walk(this, false);
  node->mRight->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(MemberAccessNode* node)
{
  node->Walk(this, false);
  node->mLeft->mParent = node;
  //node->
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(CallNode* node)
{
  node->Walk(this, false);
  node->mLeft->mParent = node;
  for(auto& it : node->mArguments)
  {
    it->mParent = node;
  }
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(IndexNode* node)
{
  node->Walk(this, false);
  node->mLeft->mParent = node;
  node->mIndex->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(CastNode* node)
{
  node->Walk(this, false);
  node->mLeft->mParent = node;
  node->mType->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(BlockNode* node)
{
  node->Walk(this, false);
  for(auto& it : node->mGlobals)
  {
    it->mParent = node;
  }
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ScopeNode* node)
{
  node->Walk(this, false);
  for(auto& it : node->mStatements)
  {
    it->mParent = node;
  }
  
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(WhileNode* node)
{
  node->Walk(this, false);
  node->mCondition->mParent = node;
  node->mScope->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ForNode* node)
{
  node->Walk(this, false);
  node->mCondition->mParent = node;
  if(node->mInitialExpression)
  {
    node->mInitialExpression->mParent = node;
  }
  if(node->mInitialVariable)
  {
    node->mInitialVariable->mParent = node;
  }
  if(node->mIterator)
  {
    node->mIterator->mParent = node;
  }
  
  node->mScope->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(IfNode* node)
{
  node->Walk(this, false);
  if(node->mCondition)
  {
    node->mCondition->mParent = node;
  }
  if(node->mElse)
  {
    node->mElse->mParent = node;
  }
  node->mScope->mParent = node;
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(ContinueNode* node)
{
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ClassVisitor::Visit(BreakNode* node)
{
  node->Walk(this, false);
  return VisitResult::Stop;
}
//VisitResult TypeVisitor::Visit(FunctionNode* node)
//{
//  Function* function = library_->CreateFunction(std::string(node->mName.mText, node->mName.mLength), !parent_type_);
//  node->mSymbol = function;
//  function->mParentType = parent_type_;
//  auto storeParent = parent_function_;
//  parent_function_ = node->mSymbol;
//  node->Walk(this, false);
//  parent_function_ = storeParent;
//  return VisitResult::Stop;
//}




EvaluatorVisitor::EvaluatorVisitor(Library* lib, const std::vector<Library*>& libraries)
: library_(lib),
  dependencies_(libraries),
  parent_type_(nullptr),
  parent_function_(nullptr)
{

}

VisitResult EvaluatorVisitor::Visit(ClassNode * node)
{
  if(parent_type_)
  {
    node->mSymbol->mParentType = parent_type_;
    parent_type_->mMembers.push_back(node->mSymbol);
    parent_type_->mMembersByName.insert(std::make_pair(node->mSymbol->mName, node->mSymbol));
  }
  auto storeParent = parent_type_;
  parent_type_ = node->mSymbol;
  
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  node->Walk(this, false);

  symbol_stack_.pop_back();
  parent_type_ = storeParent;
  return VisitResult::Stop;
}

VisitResult EvaluatorVisitor::Visit(VariableNode * node)
{
  std::string varName(node->mName.mText, node->mName.mLength);
  auto& currentSymbols = symbol_stack_.back();
  Variable* newVar;
  auto varSymbol = currentSymbols.find(varName);
  if(varSymbol != currentSymbols.end())//alright so we found something of the same name
  {
    node->mSymbol = static_cast<Variable*>(varSymbol->second);
    ErrorSameName(varName);
  }
  else
  {
    newVar = library_->CreateVariable(std::string(node->mName.mText, node->mName.mLength), !parent_type_ && !parent_function_);
    currentSymbols.insert(std::make_pair(varName, newVar));
  }
  

  //search for type from dependencies and globals?
  auto& name = node->mType->mName;
  std::string typeName(name.mText, name.mLength);
  //find type
  
  newVar->mType = static_cast<Type*>(find_symbol_by_name(typeName, dependencies_, library_));
  newVar->mType = library_->GetPointerType(newVar->mType, node->mType->mPointerCount);
  newVar->mParentFunction = parent_function_;
  newVar->mParentType = parent_type_;
  node->mSymbol = newVar;

  if(parent_type_)
  {
    if(parent_function_)
    {
      //same as function
      parent_function_->mLocals.push_back(newVar);
    }
    else
    {
      parent_type_->mMembers.push_back(newVar);
      parent_type_->mMembersByName.insert(std::make_pair(newVar->mName, newVar));
      //just class
    }
  }
  else if(parent_function_)
  {
    parent_function_->mLocals.push_back(newVar);
  }
  
  

  node->Walk(this, false);
  return VisitResult::Stop;
}


VisitResult EvaluatorVisitor::Visit(ParameterNode* node)
{
  auto returnType =  Visit((VariableNode*)node);
  node->mSymbol->mIsParameter = true;
  return returnType;
}

VisitResult EvaluatorVisitor::Visit(FunctionNode* node)
{
  std::string functionName(node->mName.mText, node->mName.mLength);
  auto& currentSymbols = symbol_stack_.back();
  Function* functionSymbol;
  if(currentSymbols.find(functionName) == currentSymbols.end())
  {
    functionSymbol = library_->CreateFunction(functionName, !parent_type_);
  }
  else
  {
    ErrorSameName(functionName);
  }
  node->mSymbol = functionSymbol;
  functionSymbol->mType = node->mSignatureType;
  if(parent_type_)
  {
    node->mSymbol->mParentType = parent_type_;
    parent_type_->mMembers.push_back(node->mSymbol);
    parent_type_->mMembersByName.insert(std::make_pair(node->mSymbol->mName, node->mSymbol));

  }
  //
  symbol_stack_.back().insert(std::make_pair(functionSymbol->mName, functionSymbol));
  auto storeParent = parent_function_;
  parent_function_ = node->mSymbol;
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  node->Walk(this, false);

  symbol_stack_.pop_back();

  parent_function_ = storeParent;
  return VisitResult::Stop;
}

VisitResult EvaluatorVisitor::Visit(LabelNode* node)
{
  std::string name(node->mName.mText, node->mName.mLength);
  auto& currentSymbols = symbol_stack_.back();
  auto labelIt = parent_function_->mLabelsByName.find(name);
  if(labelIt != parent_function_->mLabelsByName.end())
  {
    node->mSymbol = labelIt->second;
    ErrorSameName(name);
  }
  Label* label = library_->CreateLabel(name);
  label->mParentFunction = parent_function_;
  
  parent_function_->mLabelsByName.insert(std::make_pair(name, label));
  parent_function_->mLocals.push_back(label);
  node->mSymbol = label;

  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult EvaluatorVisitor::Visit(BlockNode* node)
{
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  node->Walk(this, false);
  symbol_stack_.pop_back();
  return VisitResult::Stop;
}


ExpressionVisitor::ExpressionVisitor(Library* lib, const std::vector<Library*>& libraries)
: library_(lib),
  dependencies_(libraries),
  parent_type_(nullptr),
  parent_function_(nullptr)
{

}

VisitResult ExpressionVisitor::Visit(ClassNode* node)
{
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  auto oldParent = parent_type_;
  parent_type_ = node->mSymbol;
  node->Walk(this, false);
  parent_type_ = oldParent;
  symbol_stack_.pop_back();
  return VisitResult::Stop;
}

VisitResult ExpressionVisitor::Visit(ReturnNode* node)
{
  node->Walk(this, false);
  
  if(node->mReturnValue->mResolvedType != parent_function_->mType->mReturnType)
  {
    ErrorTypeMismatch(parent_function_->mType->mReturnType, node->mReturnValue->mResolvedType);
  }
  
  return VisitResult::Stop;
}

VisitResult ExpressionVisitor::Visit(VariableNode* node)
{
  symbol_stack_.back().insert(std::make_pair(std::string(node->mName.mText, node->mName.mLength), node->mSymbol));
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ExpressionVisitor::Visit(ParameterNode* node)
{
  symbol_stack_.back().insert(std::make_pair(std::string(node->mName.mText, node->mName.mLength), node->mSymbol));
  node->Walk(this, false);
  return VisitResult::Stop;
}

VisitResult ExpressionVisitor::Visit(FunctionNode* node)
{
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  auto oldParent = parent_function_;
  parent_function_ = node->mSymbol;
  node->Walk(this, false);
  parent_function_ = oldParent;
  symbol_stack_.pop_back();
  return VisitResult::Stop;
}

VisitResult ExpressionVisitor::Visit(LabelNode* node)
{
  //symbol_stack_.back().insert(std::make_pair(std::string(node->mName.mText, node->mName.mLength), node->mSymbol));
  node->Walk(this, false);
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(GotoNode* node)
{
  node->Walk(this, false);
  std::string nodeName = std::string(node->mName.mText, node->mName.mLength);
  auto labelNode = parent_function_->mLabelsByName.find(nodeName);
  
  if(labelNode == parent_function_->mLabelsByName.end())
  {
    ErrorGotoLabelNotFound(nodeName);
  }
  node->mResolvedLabel = static_cast<Label*>(labelNode->second);
  
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(ValueNode* node)
{
  node->Walk(this, false);
  switch(node->mToken.mEnumTokenType)
  {
    case TokenType::StringLiteral:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Byte", dependencies_, library_, symbol_stack_));
      node->mResolvedType = library_->GetPointerType(node->mResolvedType, 1);
      break;
    }
    case TokenType::True:
    case TokenType::False:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Boolean", dependencies_, library_, symbol_stack_));
      break;
    }
    case TokenType::Null:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Null", dependencies_, library_, symbol_stack_));
      node->mResolvedType = library_->GetPointerType(node->mResolvedType, 1);
      break;
    }
    case TokenType::IntegerLiteral:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Integer", dependencies_, library_, symbol_stack_));
      break;
    }
    case TokenType::CharacterLiteral:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Byte", dependencies_, library_, symbol_stack_));
      break;
    }
    case TokenType::FloatLiteral:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Float", dependencies_, library_, symbol_stack_));
      break;
    }
    case TokenType::Identifier:
    {
      std::string name = std::string(node->mToken.mText, node->mToken.mLength);
      auto identifier = find_symbol_by_name(name, dependencies_, library_, symbol_stack_);
      if(identifier)
      {
        node->mResolvedType = identifier->mType;
      }
      else
      {
        ErrorSymbolNotFound(name);
      }
      //if(symbol_stack_.size())
      //{
      //  auto fromStack = symbol_stack_.back().find(name);
      //  if(fromStack != symbol_stack_.back().end())
      //  {
      //    node->mResolvedType = static_cast<Type*>(fromStack->second);
      //  }
      //}
      
      break;
    }
  }
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(BinaryOperatorNode* node)
{
  node->Walk(this, false);
  ValueNode* rhs = static_cast<ValueNode*>(node->mRight.get());
  ValueNode* lhs = static_cast<ValueNode*>(node->mLeft.get());
  switch(node->mOperator.mEnumTokenType)
  {
    case TokenType::Minus:
    {
      if((rhs->mResolvedType == lhs->mResolvedType) &&
         (rhs->mResolvedType->mMode != TypeMode::Pointer))
      {
        if(rhs->mResolvedType->mName == "Integer" ||
           rhs->mResolvedType->mName == "Float" ||
           rhs->mResolvedType->mName == "Byte")
        {
          node->mResolvedType = rhs->mResolvedType;
        }
        else
        {
          ErrorInvalidBinaryOperator(node);
        }
      }
      else if(rhs->mResolvedType->mMode == TypeMode::Pointer && lhs->mResolvedType->mName == "Integer")
      {
        node->mResolvedType = rhs->mResolvedType;
      }
      else if(lhs->mResolvedType->mMode == TypeMode::Pointer && rhs->mResolvedType->mName == "Integer")
      {
        node->mResolvedType = lhs->mResolvedType;
      }
      else if(lhs->mResolvedType->mMode == TypeMode::Pointer && rhs->mResolvedType->mMode == TypeMode::Pointer)
      {
        node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Integer", dependencies_, library_, symbol_stack_));
      }
      else
      {
        ErrorInvalidBinaryOperator(node);
      }
      break;
    }
    case TokenType::Plus:
    {
      if(rhs->mResolvedType == lhs->mResolvedType)
      {
        if(rhs->mResolvedType->mName == "Integer" ||
           rhs->mResolvedType->mName == "Float" ||
           rhs->mResolvedType->mName == "Byte")
        {
          node->mResolvedType = rhs->mResolvedType;
        }
        else
        {
          ErrorInvalidBinaryOperator(node);
        }
      }
      else if(rhs->mResolvedType->mMode == TypeMode::Pointer && lhs->mResolvedType->mName == "Integer")
      {
        node->mResolvedType = rhs->mResolvedType;
      }
      else if(lhs->mResolvedType->mMode == TypeMode::Pointer && rhs->mResolvedType->mName == "Integer")
      {
        node->mResolvedType = lhs->mResolvedType;
      }
      else
      {
        ErrorInvalidBinaryOperator(node);
      }
      break;
    }
    case TokenType::Asterisk:
    case TokenType::Divide:
    case TokenType::Modulo:
    {
      //if they're the same type and they're integer/float/byte
      if(rhs->mResolvedType == lhs->mResolvedType)
      {
        if(rhs->mResolvedType->mName == "Integer" ||
           rhs->mResolvedType->mName == "Float" ||
           rhs->mResolvedType->mName == "Byte")
        {
          node->mResolvedType = rhs->mResolvedType;
        }
        else
        {
          ErrorInvalidBinaryOperator(node);
        }
      }
      else
      {
        ErrorInvalidBinaryOperator(node);
      }

      break;
    }
    case TokenType::GreaterThan:
    case TokenType::GreaterThanOrEqualTo:
    case TokenType::Equality:
    case TokenType::Inequality:
    case TokenType::LessThanOrEqualTo:
    case TokenType::LessThan:
    {
      node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Boolean", dependencies_, library_, symbol_stack_));
      break;
    }
    case TokenType::LogicalAnd:
    case TokenType::LogicalOr:
    {
      if((rhs->mResolvedType->mName == "Boolean" || rhs->mResolvedType->mMode == TypeMode::Pointer) &&
         (lhs->mResolvedType->mName == "Boolean" || lhs->mResolvedType->mMode == TypeMode::Pointer))
      {
        node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Boolean", dependencies_, library_, symbol_stack_));
      }
      else
      {
        ErrorInvalidBinaryOperator(node);
      }
      break;
    }
    case TokenType::Assignment:
    {
      if(rhs->mResolvedType == lhs->mResolvedType)
      {
        if(lhs->mResolvedType->mName == "Function" ||
           rhs->mResolvedType->mName == "Function")
        {
          ErrorInvalidBinaryOperator(node);
        }
        else
        {
          node->mResolvedType = lhs->mResolvedType;
        }
      }
      else
      {
        ErrorInvalidBinaryOperator(node);
      }
      break;
    }
    default:
      ErrorInvalidBinaryOperator(node);
      break;
  }
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(UnaryOperatorNode* node)
{
  node->Walk(this, false);
  ValueNode* valNode = static_cast<ValueNode*>(node->mRight.get());
  if(valNode->mResolvedType->mMode == TypeMode::Pointer)
  {
    switch(node->mOperator.mEnumTokenType)
    {
      case TokenType::Decrement:
      case TokenType::Increment:
      {
        node->mResolvedType = valNode->mResolvedType;
        break;
      }
      case TokenType::BitwiseAndAddressOf:
      {
        node->mResolvedType = library_->GetPointerType(valNode->mResolvedType, 1);
        break;
      }
      case TokenType::Asterisk:
      {
        node->mResolvedType = dereference(valNode->mResolvedType);
        break;
      }
      case TokenType::LogicalNot:
      {
        node->mResolvedType = static_cast<Type*>(find_symbol_by_name("Boolean", dependencies_, library_, symbol_stack_));
        break;
      }
      default:
        ErrorInvalidUnaryOperator(node);
    }
  }
  else if(valNode->mResolvedType->mName == "Integer" ||
          valNode->mResolvedType->mName == "Float" ||
          valNode->mResolvedType->mName == "Byte")
  {
    switch(node->mOperator.mEnumTokenType)
    {
      case TokenType::Plus:
      case TokenType::Minus:
      case TokenType::Decrement:
      case TokenType::Increment:
      {
        node->mResolvedType = valNode->mResolvedType;
        break;
      }
      case TokenType::BitwiseAndAddressOf:
      {
        node->mResolvedType = library_->GetPointerType(valNode->mResolvedType, 1);
        break;
      }
      default:
        ErrorInvalidUnaryOperator(node);
    }
  }
  else if(valNode->mResolvedType->mName == "Boolean")
  {
    switch(node->mOperator.mEnumTokenType)
    {
      case TokenType::BitwiseAndAddressOf:
      {
        node->mResolvedType = library_->GetPointerType(valNode->mResolvedType, 1);
        break;
      }
      case TokenType::LogicalNot:
      {
        node->mResolvedType = valNode->mResolvedType;
        break;
      }
      default:
        ErrorInvalidUnaryOperator(node);
    }
  }
  else
  {
    ErrorInvalidUnaryOperator(node);
  }
  
  
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(MemberAccessNode* node)
{
  node->Walk(this, false);
  ValueNode* valNode = static_cast<ValueNode*>(node->mLeft.get());

  switch(node->mOperator.mEnumTokenType)
  {
    case TokenType::Dot:
    {
      if(valNode->mResolvedType->mMode != TypeMode::Class)
      {
        ErrorInvalidMemberAccess(node);
      }
      break;
    }
    case TokenType::Arrow:
    {
      if(valNode->mResolvedType->mMode != TypeMode::Pointer)
      {
        ErrorInvalidMemberAccess(node);
      }
      break;
    }
    default:
      ErrorInvalidMemberAccess(node);

  }

  std::string leftExpression(valNode->mToken.mText, valNode->mToken.mLength);
  std::string rightExpression(node->mName.mText, node->mName.mLength);
  Variable* leftSide = static_cast<Variable*>(find_symbol_by_name(leftExpression, dependencies_, library_, symbol_stack_));
  Variable* rightSide = nullptr;// = ;//find_symbol_by_name(rightExpression, dependencies_, library_, symbol_stack_);
  Type* lefttype = resolvePointers(leftSide->mType);
  auto rightIt = lefttype->mMembersByName.find(rightExpression);
  if(rightIt != lefttype->mMembersByName.end())
  {
    rightSide = static_cast<Variable*>(rightIt->second);
  }
  
  node->mResolvedMember = rightSide;
  node->mResolvedType = rightSide->mType;
  
  
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(CallNode* node)
{
  node->Walk(this, false);
  //check args against function signature type
  //node->
  if(node->mLeft->mResolvedType->mMode != TypeMode::Function)
  {
    ErrorInvalidCall(node);
  }
  for(int i = 0; i < node->mArguments.size(); ++i)
  {
    if(node->mArguments[i]->mResolvedType != node->mLeft->mResolvedType->mParameterTypes[i])
    {
      ErrorInvalidCall(node);
    }
  }
  node->mResolvedType = node->mLeft->mResolvedType->mReturnType;
  //node->mArguments
  //node->mResolvedType->mParameterTypes;
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(IndexNode* node)
{
  node->Walk(this, false);
  ValueNode* leftSide = static_cast<ValueNode*>(node->mLeft.get());
  ValueNode* indexExpr = static_cast<ValueNode*>(node->mIndex.get());
  std::string leftSymbolName(leftSide->mToken.mText, leftSide->mToken.mLength);
  std::string indexSymbolName(indexExpr->mToken.mText, indexExpr->mToken.mLength);
  if(leftSide->mResolvedType->mMode == TypeMode::Pointer)
  {
    node->mResolvedType = dereference(leftSide->mResolvedType);
  }
  else
  {
    ErrorInvalidIndexer(node);
  }
  if(indexExpr->mResolvedType->mName != "Integer")
  {
    ErrorInvalidIndexer(node);
  }

  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(CastNode* node)
{
  node->Walk(this, false);
  ValueNode* valNode = static_cast<ValueNode*>(node->mLeft.get());

  Type* tocast = valNode->mResolvedType;

  std::string targetTypeName(node->mType->mName.mText, node->mType->mName.mLength);
  Type* targetType = static_cast<Type*>(find_symbol_by_name(targetTypeName, dependencies_, library_, symbol_stack_));
  targetType = library_->GetPointerType(targetType, node->mType->mPointerCount);
  
  node->mResolvedType = static_cast<Type*>(targetType);


  switch(tocast->mMode)
  {
    case TypeMode::Class:
      
      if(tocast->mName == "Integer")
      {
        if(targetType->mName != "Integer" &&
           targetType->mName != "Boolean" &&
           targetType->mName != "Byte" &&
           targetType->mName != "Float" &&
           targetType->mMode != TypeMode::Pointer)
        {
          ErrorInvalidCast(tocast, targetType);
        }
      }

      else if(tocast->mName == "Boolean" ||
              tocast->mName == "Byte" ||
              tocast->mName == "Float")
      {
        if(targetType->mName != "Integer" &&
           targetType->mName != "Boolean" &&
           targetType->mName != "Byte" &&
           targetType->mName != "Float")
        {
          ErrorInvalidCast(tocast, targetType);
        }
      }
      break;
    case TypeMode::Pointer:
      if(targetType->mMode != TypeMode::Pointer)
      {
        if(targetType->mName != "Integer" && targetType->mName != "Boolean")
        {
          ErrorInvalidCast(tocast, targetType);
        }
      }

      break;
    case TypeMode::Function:
      ErrorInvalidCast(tocast, targetType);
  }

  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(BlockNode* node)
{
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  node->Walk(this, false);
  symbol_stack_.pop_back();
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(ScopeNode* node)
{
  symbol_stack_.push_back(std::unordered_map<std::string, Symbol*>());
  node->Walk(this, false);
  symbol_stack_.pop_back();
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(WhileNode* node)
{
  node->Walk(this, false);
  if(node->mCondition->mResolvedType->mMode != TypeMode::Pointer &&
     node->mCondition->mResolvedType->mName != "Boolean")
  {
    ErrorConditionExpectedBooleanOrPointer(node->mCondition->mResolvedType);
  }
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(ForNode* node)
{
  node->Walk(this, false);
  if(node->mCondition->mResolvedType->mMode != TypeMode::Pointer &&
     node->mCondition->mResolvedType->mName != "Boolean")
  {
    ErrorConditionExpectedBooleanOrPointer(node->mCondition->mResolvedType);
  }
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(IfNode* node)
{
  node->Walk(this, false);
  if(node->mCondition)
  {
    if(node->mCondition->mResolvedType->mMode != TypeMode::Pointer &&
       node->mCondition->mResolvedType->mName != "Boolean")
    {
      ErrorConditionExpectedBooleanOrPointer(node->mCondition->mResolvedType);
    }
  }
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(ContinueNode* node)
{
  AbstractNode* parent = node->mParent;
  ForNode* forLoopPointer = nullptr;;
  WhileNode* whileLoopPointer = nullptr;

  while(!forLoopPointer && !whileLoopPointer && parent)
  {
    forLoopPointer = dynamic_cast<ForNode*>(parent);
    whileLoopPointer = dynamic_cast<WhileNode*>(parent);
    parent = parent->mParent;
  }
  if(!forLoopPointer && !whileLoopPointer)
  {
    ErrorBreakContinueMustBeInsideLoop();
  }
  node->Walk(this, false);
  return VisitResult::Stop;

}

VisitResult ExpressionVisitor::Visit(BreakNode* node)
{
  AbstractNode* parent = node->mParent;
  ForNode* forLoopPointer = nullptr;;
  WhileNode* whileLoopPointer = nullptr;
  
  while(!forLoopPointer && !whileLoopPointer && parent)
  {
    forLoopPointer = dynamic_cast<ForNode*>(parent);
    whileLoopPointer = dynamic_cast<WhileNode*>(parent);
    parent = parent->mParent;
  }
  if(!forLoopPointer && !whileLoopPointer)
  {
    ErrorBreakContinueMustBeInsideLoop();
  }
  node->Walk(this, false);
  return VisitResult::Stop;

}

InfoVisitor::InfoVisitor(Library* lib, const std::vector<Library*>& libraries)
: library_(lib),
  dependencies_(libraries)
{
  
}

VisitResult InfoVisitor::Visit(TypeNode* node)
{
  //look for type in library i think?
  //i think this is fine?
  std::string name(node->mName.mText, node->mName.mLength);
  
  Type* type = nullptr;

  for(int i = 0; i < dependencies_.size(); ++i)
  {
    auto it = dependencies_[i]->mGlobalsByName.find(name);
    if(it != dependencies_[i]->mGlobalsByName.end())
    {
      type = static_cast<Type*>(it->second);
      //we found it soo
      if(type->mMode == TypeMode::Class)
      {

        type = library_->GetPointerType(type, node->mPointerCount);
        node->mSymbol = type;
      }
      else
      {
        ErrorIncorrectSymbolType(name);
      }
    }
  }
  if(!type)
  {
    auto& typeIt = library_->mGlobalsByName.find(name);
    if(typeIt != library_->mGlobalsByName.end())
    {
      type = static_cast<Type*>(typeIt->second);
      if(type->mMode == TypeMode::Class)
      {
        type = library_->GetPointerType(type, node->mPointerCount);
        node->mSymbol = type;
      }
      else
      {
        ErrorIncorrectSymbolType(name);
      }
    }
    else
    {
      ErrorSymbolNotFound(name);
    }
  }
  
  node->Walk(this, false);
  return VisitResult::Stop;
}


Type* Library::CreateType(const std::string& name, bool isGlobal)
{
  Type* toReturn = nullptr;
  if(isGlobal)
  {
    auto findGlobal = mGlobalsByName.find(name);
    if(findGlobal == mGlobalsByName.end())
    {
      std::unique_ptr<Type> newType = std::make_unique<Type>();
      newType->mName = name;
      newType->mMode = TypeMode::Class;
      mGlobals.push_back(newType.get());
      toReturn = newType.get();
      mGlobalsByName.insert(std::make_pair(name, newType.get()));
      mAllSymbols.push_back(std::move(newType));
    }
    else
    {
      ErrorSameName(name);
    }
  }
  else
  {
    std::unique_ptr<Type> newType = std::make_unique<Type>();
    newType->mName = name;
    newType->mMode = TypeMode::Class;
    toReturn = newType.get();
    mAllSymbols.push_back(std::move(newType));
    
  }
  return toReturn;
}

Variable* Library::CreateVariable(const std::string& name, bool isGlobal)
{
  Variable* toReturn = nullptr;
  if(isGlobal)
  {
    auto findGlobal = mGlobalsByName.find(name);
    if(findGlobal == mGlobalsByName.end())
    {
      std::unique_ptr<Variable> newType = std::make_unique<Variable>();
      newType->mName = name;
      mGlobals.push_back(newType.get());
      toReturn = newType.get();
      mGlobalsByName.insert(std::make_pair(name, newType.get()));
      mAllSymbols.push_back(std::move(newType));
      
    }
    else
    {
      ErrorSameName(name);
    }
  }
  else
  {
    std::unique_ptr<Variable> newType = std::make_unique<Variable>();
    newType->mName = name;
    toReturn = newType.get();
    mAllSymbols.push_back(std::move(newType));
    
  }
  return toReturn;
}

Function* Library::CreateFunction(const std::string& name, bool isGlobal)
{
  Function* toReturn = nullptr;
  if(isGlobal)
  {
    auto findGlobal = mGlobalsByName.find(name);
    if(findGlobal == mGlobalsByName.end())
    {
      std::unique_ptr<Function> newType = std::make_unique<Function>();
      newType->mName = name;
      mGlobals.push_back(newType.get());
      toReturn = newType.get();
      mGlobalsByName.insert(std::make_pair(name, newType.get()));
      mAllSymbols.push_back(std::move(newType));
    }
    else
    {
      ErrorSameName(name);
    }
  }
  else
  {
    std::unique_ptr<Function> newType = std::make_unique<Function>();
    newType->mName = name;
    toReturn = newType.get();
    mAllSymbols.push_back(std::move(newType));
  }
  return toReturn;
}

Label* Library::CreateLabel(const std::string& name, bool isGlobal)
{
  Label* toReturn = nullptr;
  if(isGlobal)
  {
    auto findGlobal = mGlobalsByName.find(name);
    if(findGlobal == mGlobalsByName.end())
    {
      std::unique_ptr<Label> newType = std::make_unique<Label>();
      newType->mName = name;
      mGlobals.push_back(newType.get());
      toReturn = newType.get();
      mGlobalsByName.insert(std::make_pair(name, newType.get()));
      mAllSymbols.push_back(std::move(newType));
    }
    else
    {
      ErrorSameName(name);
    }
  }
  else
  {
    std::unique_ptr<Label> newType = std::make_unique<Label>();
    newType->mName = name;
    
    toReturn = newType.get();
    mAllSymbols.push_back(std::move(newType));
  }
  return toReturn;
}

Type* Library::GetPointerType(Type* pointerToType)
{
  std::string newName = pointerToType->mName + "*";
  auto typeIt = mGlobalsByName.find(newName);
  if(typeIt != mGlobalsByName.end())
  {
    return static_cast<Type*>(typeIt->second);
  }
  

  auto type = CreateType(newName, true);
  type->mPointerToType = pointerToType;
  type->mMode = TypeMode::Pointer;
  
  return type;
}

Type* Library::GetPointerType(Type* pointerToType, size_t pointerCount)
{
  while(pointerCount)
  {
    pointerToType = GetPointerType(pointerToType);
    --pointerCount;
  }
  return pointerToType;
}

Type* Library::GetFunctionType(std::vector<Type*> parameterTypes, Type* returnType)
{
  std::string functionName = "function(";
  Type* retVal;
  auto typeIt = parameterTypes.begin();
  if(typeIt != parameterTypes.end())
  {
    functionName += (*typeIt)->mName;
    ++typeIt;
  }
  for(typeIt; typeIt != parameterTypes.end(); ++typeIt)
  {
    functionName += ", " + (*typeIt)->mName;
  }
  functionName += ") : " + returnType->mName;
  auto type = mGlobalsByName.find(functionName);
  if(type != mGlobalsByName.end())
  {
    return static_cast<Type*>(type->second);
  }
  retVal = CreateType(functionName, true);
  retVal->mMode = TypeMode::Function;
  retVal->mReturnType = returnType;
  retVal->mParameterTypes = parameterTypes;

  return retVal;
}

void SemanticAnalyize(AbstractNode* node, std::vector<Library*>& dependencies, Library* library)
{
  ClassVisitor createVisit(library, dependencies);
  node->Walk(&createVisit);

  FunctionVisitor funVisit(library, dependencies);
  node->Walk(&funVisit);

  InfoVisitor infoVisit(library, dependencies);
  node->Walk(&infoVisit);
  
  EvaluatorVisitor typeVisit(library, dependencies);
  node->Walk(&typeVisit);

  ExpressionVisitor expressionVisit(library, dependencies);
  node->Walk(&expressionVisit);
  

}

void PrintTreeWithSymbols(AbstractNode* node)
{
  PrintAnalyzerVisitor visitor;
  node->Walk(&visitor, true);
}
