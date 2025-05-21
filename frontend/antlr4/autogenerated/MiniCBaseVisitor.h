
// Generated from MiniC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "MiniCVisitor.h"


/**
 * This class provides an empty implementation of MiniCVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MiniCBaseVisitor : public MiniCVisitor {
public:

  virtual std::any visitCompUnit(MiniCParser::CompUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefineDirective(MiniCParser::DefineDirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDeclaration(MiniCParser::ConstDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclaration(MiniCParser::VarDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDecl(MiniCParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(MiniCParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatType(MiniCParser::FloatTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(MiniCParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScalarConstInitVal(MiniCParser::ScalarConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayConstInitVal(MiniCParser::ArrayConstInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(MiniCParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(MiniCParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScalarInitVal(MiniCParser::ScalarInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayInitVal(MiniCParser::ArrayInitValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(MiniCParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVoidReturnType(MiniCParser::VoidReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntReturnType(MiniCParser::IntReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatReturnType(MiniCParser::FloatReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(MiniCParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(MiniCParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(MiniCParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockDeclaration(MiniCParser::BlockDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(MiniCParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStatement(MiniCParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmptyStatement(MiniCParser::EmptyStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedBlockStatement(MiniCParser::NestedBlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfElseStatement(MiniCParser::IfElseStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileLoopStatement(MiniCParser::WhileLoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(MiniCParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(MiniCParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(MiniCParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExp(MiniCParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCond(MiniCParser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(MiniCParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExp(MiniCParser::PrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(MiniCParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpPrimary(MiniCParser::UnaryExpPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpFuncCall(MiniCParser::UnaryExpFuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOpUnaryExp(MiniCParser::UnaryOpUnaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOp(MiniCParser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(MiniCParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExp(MiniCParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExp(MiniCParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExp(MiniCParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExp(MiniCParser::EqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndExp(MiniCParser::LAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExp(MiniCParser::LOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExp(MiniCParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

