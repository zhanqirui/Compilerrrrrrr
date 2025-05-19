///
/// @file Antlr4CSTVisitor.h
/// @brief Antlr4的具体语法树的遍历产生AST
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#pragma once

#include "AST.h"
#include "MiniCBaseVisitor.h"
#include <map>
#include <string>
#include <unordered_map>

/// @brief 遍历具体语法树产生抽象语法树
class MiniCCSTVisitor : public MiniCBaseVisitor {
public:
    /// @brief 构造函数
    MiniCCSTVisitor();

    /// @brief 析构函数
    virtual ~MiniCCSTVisitor();

    /// @brief 遍历CST产生AST
    /// @param root CST语法树的根结点
    /// @return AST的根节点
    ast_node * run(MiniCParser::CompUnitContext * root);

	std::map<std::string, int> getReturnNum() {
		return NameToReturnNum;
	}
	// 全局或静态成员：宏定义表
	std::unordered_map<std::string, ast_node*> macro_table;

protected:
    /* 下面的函数都是从MiniCBaseVisitor继承下来的虚拟函数，需要重载实现 */

    // 顶层
    std::any visitCompUnit(MiniCParser::CompUnitContext *ctx) override;
    
    // 预处理指令
    std::any visitDefineDirective(MiniCParser::DefineDirectiveContext *ctx) override;

    // 声明相关
    std::any visitConstDeclaration(MiniCParser::ConstDeclarationContext *ctx) override;
    std::any visitVarDeclaration(MiniCParser::VarDeclarationContext *ctx) override;
    std::any visitConstDecl(MiniCParser::ConstDeclContext *ctx) override;
    std::any visitIntType(MiniCParser::IntTypeContext * ctx) override;
    std::any visitFloatType(MiniCParser::FloatTypeContext * ctx) override;
    std::any visitConstDef(MiniCParser::ConstDefContext *ctx) override;
    std::any visitScalarConstInitVal(MiniCParser::ScalarConstInitValContext *ctx) override;
    std::any visitArrayConstInitVal(MiniCParser::ArrayConstInitValContext *ctx) override;
    std::any visitVarDecl(MiniCParser::VarDeclContext *ctx) override;
    std::any visitVarDef(MiniCParser::VarDefContext *ctx) override;
    std::any visitScalarInitVal(MiniCParser::ScalarInitValContext *ctx) override;
    std::any visitArrayInitVal(MiniCParser::ArrayInitValContext *ctx) override;

    // 函数定义
    std::any visitFuncDef(MiniCParser::FuncDefContext *ctx) override;
    std::any visitVoidReturnType(MiniCParser::VoidReturnTypeContext *ctx) override;
    std::any visitIntReturnType(MiniCParser::IntReturnTypeContext *ctx) override;
    std::any visitFloatReturnType(MiniCParser::FloatReturnTypeContext *ctx) override;
    std::any visitFuncFParams(MiniCParser::FuncFParamsContext *ctx) override;
    std::any visitFuncFParam(MiniCParser::FuncFParamContext *ctx) override;

    // 语句块与语句
    std::any visitBlock(MiniCParser::BlockContext *ctx) override;
    std::any visitBlockDeclaration(MiniCParser::BlockDeclarationContext *ctx) override;
    std::any visitBlockStatement(MiniCParser::BlockStatementContext *ctx) override;
    std::any visitAssignmentStatement(MiniCParser::AssignmentStatementContext *ctx) override;
    std::any visitReturnStmtWithReturnNum(MiniCParser::ReturnStmtContext * ctx, std::string FunctionName);
    std::any visitReturnStmt(MiniCParser::ReturnStmtContext * ctx) override;
    std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext * ctx) override;
    std::any visitNestedBlockStatement(MiniCParser::NestedBlockStatementContext *ctx) override;
    std::any visitIfElseStatement(MiniCParser::IfElseStatementContext *ctx) override;
    std::any visitWhileLoopStatement(MiniCParser::WhileLoopStatementContext *ctx) override;
    std::any visitBreakStatement(MiniCParser::BreakStatementContext *ctx) override;
    std::any visitContinueStatement(MiniCParser::ContinueStatementContext *ctx) override;
    std::any visitEmptyStatement(MiniCParser::EmptyStatementContext * ctx) override;
    // 表达式
    std::any visitExp(MiniCParser::ExpContext *ctx) override;
    std::any visitCond(MiniCParser::CondContext *ctx) override;
    std::any visitLVal(MiniCParser::LValContext *ctx) override;
    std::any visitPrimaryExp(MiniCParser::PrimaryExpContext *ctx) override;
    std::any visitNumber(MiniCParser::NumberContext *ctx) override;
    std::any visitUnaryExpPrimary(MiniCParser::UnaryExpPrimaryContext *ctx) override;
    std::any visitUnaryExpFuncCall(MiniCParser::UnaryExpFuncCallContext *ctx) override;
    std::any visitUnaryOpUnaryExp(MiniCParser::UnaryOpUnaryExpContext *ctx) override;
    std::any visitUnaryOp(MiniCParser::UnaryOpContext *ctx) override;
    std::any visitFuncRParams(MiniCParser::FuncRParamsContext *ctx) override;
    std::any visitMulExp(MiniCParser::MulExpContext *ctx) override;
    std::any visitAddExp(MiniCParser::AddExpContext *ctx) override;
    std::any visitRelExp(MiniCParser::RelExpContext *ctx) override;
    std::any visitEqExp(MiniCParser::EqExpContext *ctx) override;
    std::any visitLAndExp(MiniCParser::LAndExpContext *ctx) override;
    std::any visitLOrExp(MiniCParser::LOrExpContext *ctx) override;
    std::any visitConstExp(MiniCParser::ConstExpContext *ctx) override;

    ast_node * processNotOperator(ast_node * exp, ast_node * op);
    ast_node * processPosNegOperator(ast_node * exp, Op current_op);

private:
    // 记录return语句的个数
    std::map<std::string, int> NameToReturnNum;

    // 记录当前函数名
    std::string CurrentFunctionName;
};
