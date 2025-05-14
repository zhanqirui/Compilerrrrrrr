
// Generated from MiniC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "MiniCParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by MiniCParser.
 */
class  MiniCVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by MiniCParser.
   */
    virtual std::any visitCompUnit(MiniCParser::CompUnitContext *context) = 0;

    virtual std::any visitConstDeclaration(MiniCParser::ConstDeclarationContext *context) = 0;

    virtual std::any visitVarDeclaration(MiniCParser::VarDeclarationContext *context) = 0;

    virtual std::any visitConstDecl(MiniCParser::ConstDeclContext *context) = 0;

    virtual std::any visitIntType(MiniCParser::IntTypeContext *context) = 0;

    virtual std::any visitFloatType(MiniCParser::FloatTypeContext *context) = 0;

    virtual std::any visitConstDef(MiniCParser::ConstDefContext *context) = 0;

    virtual std::any visitScalarConstInitVal(MiniCParser::ScalarConstInitValContext *context) = 0;

    virtual std::any visitArrayConstInitVal(MiniCParser::ArrayConstInitValContext *context) = 0;

    virtual std::any visitVarDecl(MiniCParser::VarDeclContext *context) = 0;

    virtual std::any visitVarDef(MiniCParser::VarDefContext *context) = 0;

    virtual std::any visitScalarInitVal(MiniCParser::ScalarInitValContext *context) = 0;

    virtual std::any visitArrayInitVal(MiniCParser::ArrayInitValContext *context) = 0;

    virtual std::any visitFuncDef(MiniCParser::FuncDefContext *context) = 0;

    virtual std::any visitVoidReturnType(MiniCParser::VoidReturnTypeContext *context) = 0;

    virtual std::any visitIntReturnType(MiniCParser::IntReturnTypeContext *context) = 0;

    virtual std::any visitFloatReturnType(MiniCParser::FloatReturnTypeContext *context) = 0;

    virtual std::any visitFuncFParams(MiniCParser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(MiniCParser::FuncFParamContext *context) = 0;

    virtual std::any visitBlock(MiniCParser::BlockContext *context) = 0;

    virtual std::any visitBlockDeclaration(MiniCParser::BlockDeclarationContext *context) = 0;

    virtual std::any visitBlockStatement(MiniCParser::BlockStatementContext *context) = 0;

    virtual std::any visitAssignmentStatement(MiniCParser::AssignmentStatementContext *context) = 0;

    virtual std::any visitEmptyStatement(MiniCParser::EmptyStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitNestedBlockStatement(MiniCParser::NestedBlockStatementContext *context) = 0;

    virtual std::any visitIfElseStatement(MiniCParser::IfElseStatementContext *context) = 0;

    virtual std::any visitWhileLoopStatement(MiniCParser::WhileLoopStatementContext *context) = 0;

    virtual std::any visitBreakStatement(MiniCParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(MiniCParser::ContinueStatementContext *context) = 0;

    virtual std::any visitReturnStmt(MiniCParser::ReturnStmtContext *context) = 0;

    virtual std::any visitExp(MiniCParser::ExpContext *context) = 0;

    virtual std::any visitCond(MiniCParser::CondContext *context) = 0;

    virtual std::any visitLVal(MiniCParser::LValContext *context) = 0;

    virtual std::any visitPrimaryExp(MiniCParser::PrimaryExpContext *context) = 0;

    virtual std::any visitNumber(MiniCParser::NumberContext *context) = 0;

    virtual std::any visitUnaryExpPrimary(MiniCParser::UnaryExpPrimaryContext *context) = 0;

    virtual std::any visitUnaryExpFuncCall(MiniCParser::UnaryExpFuncCallContext *context) = 0;

    virtual std::any visitUnaryOpUnaryExp(MiniCParser::UnaryOpUnaryExpContext *context) = 0;

    virtual std::any visitUnaryOp(MiniCParser::UnaryOpContext *context) = 0;

    virtual std::any visitFuncRParams(MiniCParser::FuncRParamsContext *context) = 0;

    virtual std::any visitMulExp(MiniCParser::MulExpContext *context) = 0;

    virtual std::any visitAddExp(MiniCParser::AddExpContext *context) = 0;

    virtual std::any visitRelExp(MiniCParser::RelExpContext *context) = 0;

    virtual std::any visitEqExp(MiniCParser::EqExpContext *context) = 0;

    virtual std::any visitLAndExp(MiniCParser::LAndExpContext *context) = 0;

    virtual std::any visitLOrExp(MiniCParser::LOrExpContext *context) = 0;

    virtual std::any visitConstExp(MiniCParser::ConstExpContext *context) = 0;


};

