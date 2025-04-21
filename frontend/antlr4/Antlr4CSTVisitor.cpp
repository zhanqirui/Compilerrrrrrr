	///
	/// @file Antlr4CSTVisitor.cpp
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

	#include <string>

	#include "Antlr4CSTVisitor.h"
	#include "AST.h"
	#include "AttrType.h"

	#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

	/// @brief 构造函数
	MiniCCSTVisitor::MiniCCSTVisitor()
	{}

	/// @brief 析构函数
	MiniCCSTVisitor::~MiniCCSTVisitor()
	{}

	/// @brief 遍历CST产生AST
	/// @param root CST语法树的根结点
	/// @return AST的根节点
	ast_node * MiniCCSTVisitor::run(MiniCParser::CompUnitContext * root)
	{
		return std::any_cast<ast_node *>(visitCompUnit(root));
	}

	/// @brief 非终结运算符compileUnit的遍历
	/// @param ctx CST上下文
	std::any MiniCCSTVisitor::visitCompUnit(MiniCParser::CompUnitContext * ctx)
	{
		// compileUnit : (decl | funcDef)* EOF ;
		ast_node *root = new ast_node(ast_operator_type::AST_OP_COMPILE_UNIT);
		for (auto declCtx : ctx->decl()) {
			auto node = std::any_cast<ast_node *>(visit(declCtx));
			if (node) root->insert_son_node(node);
		}
		for (auto funcDefCtx : ctx->funcDef()) {
			auto node = std::any_cast<ast_node *>(visit(funcDefCtx));
			if (node) root->insert_son_node(node);
		}
		return root;
	}

	// 声明相关
	std::any MiniCCSTVisitor::visitConstDeclaration(MiniCParser::ConstDeclarationContext *ctx) {
		// constDeclaration : constDecl ;
		return visit(ctx->constDecl());
	}
	std::any MiniCCSTVisitor::visitVarDeclaration(MiniCParser::VarDeclarationContext *ctx) {
		// varDeclaration : varDecl ;
		return visit(ctx->varDecl());
	}
	std::any MiniCCSTVisitor::visitConstDecl(MiniCParser::ConstDeclContext *ctx) {
		// constDecl : bType constDef (',' constDef)* ';'
		auto type_node = std::any_cast<ast_node *>(visit(ctx->bType()));
		ast_node *def_list = nullptr;
		for (auto defCtx : ctx->constDef()) {
			auto def_node = std::any_cast<ast_node *>(visit(defCtx));
			if (!def_list) {
				def_list = def_node;
			} else {
				def_list->insert_son_node(def_node);
			}
		}
		return create_const_decl_node(type_node, def_list);
	}
	std::any MiniCCSTVisitor::visitBType(MiniCParser::BTypeContext *ctx) {
		// bType : 'int' | 'float'
		// 这里只处理int
		type_attr attr;
		attr.type = BasicType::TYPE_INT;
		attr.lineno = ctx->getStart()->getLine();
		return create_type_node(attr);
	}
	std::any MiniCCSTVisitor::visitConstDef(MiniCParser::ConstDefContext *ctx) {
		// constDef : Ident ('[' constExp ']')* '=' constInitVal
		var_id_attr id;
		id.id = strdup(ctx->Ident()->getText().c_str());
		id.lineno = ctx->Ident()->getSymbol()->getLine();
		// 这里只处理标量，不处理数组
		auto init_node = std::any_cast<ast_node *>(visit(ctx->constInitVal()));
		auto id_node = ast_node::New(id);
		return create_const_def_node(id_node, init_node);
	}
	std::any MiniCCSTVisitor::visitScalarConstInitVal(MiniCParser::ScalarConstInitValContext *ctx) {
		// scalarConstInitVal : constExp
		auto expr = std::any_cast<ast_node *>(visit(ctx->constExp()));
		return create_scalar_const_init_node(expr);
	}
	std::any MiniCCSTVisitor::visitArrayConstInitVal(MiniCParser::ArrayConstInitValContext *ctx) {
		// arrayConstInitVal : '{' (constInitVal (',' constInitVal)*)? '}'
		std::vector<ast_node *> elements;
		for (auto c : ctx->constInitVal()) {
			auto node = std::any_cast<ast_node *>(visit(c));
			if (node) elements.push_back(node);
		}
		return create_array_const_init_node(elements);
	}
	std::any MiniCCSTVisitor::visitVarDecl(MiniCParser::VarDeclContext *ctx) {
		// varDecl : bType varDef (',' varDef)* ';'
		auto type_node = std::any_cast<ast_node *>(visit(ctx->bType()));
		ast_node *def_list = nullptr;
		for (auto defCtx : ctx->varDef()) {
			auto def_node = std::any_cast<ast_node *>(visit(defCtx));
			if (!def_list) {
				def_list = def_node;
			} else {
				def_list->insert_son_node(def_node);
			}
		}
		return create_var_decl_node(type_node, def_list);
	}
	std::any MiniCCSTVisitor::visitVarDef(MiniCParser::VarDefContext *ctx) {
		// varDef : Ident ('[' constExp ']')* ('=' initVal)?
		var_id_attr id;
		id.id = strdup(ctx->Ident()->getText().c_str());
		id.lineno = ctx->Ident()->getSymbol()->getLine();
		auto id_node = ast_node::New(id);
		ast_node *init_node = nullptr;
		if (ctx->initVal()) {
			init_node = std::any_cast<ast_node *>(visit(ctx->initVal()));
		}
		return create_var_def_node(id_node, init_node);
	}
	std::any MiniCCSTVisitor::visitScalarInitVal(MiniCParser::ScalarInitValContext *ctx) {
		// scalarInitVal : exp
		auto expr = std::any_cast<ast_node *>(visit(ctx->exp()));
		return create_scalar_init_node(expr);
	}
	std::any MiniCCSTVisitor::visitArrayInitVal(MiniCParser::ArrayInitValContext *ctx) {
		// arrayInitVal : '{' (initVal (',' initVal)*)? '}'
		std::vector<ast_node *> elements;
		for (auto c : ctx->initVal()) {
			auto node = std::any_cast<ast_node *>(visit(c));
			if (node) elements.push_back(node);
		}
		return create_array_init_val_node(elements);
	}

	// 函数定义
	std::any MiniCCSTVisitor::visitFuncDef(MiniCParser::FuncDefContext *ctx) {
		// funcDef : funcType Ident '(' funcFParams? ')' block
		type_attr funcReturnType;
		funcReturnType.type = BasicType::TYPE_INT;
		funcReturnType.lineno = ctx->getStart()->getLine();
		var_id_attr funcId;
		funcId.id = strdup(ctx->Ident()->getText().c_str());
		funcId.lineno = ctx->Ident()->getSymbol()->getLine();
		ast_node *formalParamsNode = nullptr;
		if (ctx->funcFParams()) {
			formalParamsNode = std::any_cast<ast_node *>(visit(ctx->funcFParams()));
		}
		auto blockNode = std::any_cast<ast_node *>(visit(ctx->block()));
		return create_func_def(funcReturnType, funcId, blockNode, formalParamsNode);
	}
	std::any MiniCCSTVisitor::visitVoidReturnType(MiniCParser::VoidReturnTypeContext *ctx) {
		type_attr attr;
		attr.type = BasicType::TYPE_VOID;
		attr.lineno = ctx->getStart()->getLine();
		return create_type_node(attr);
	}
	std::any MiniCCSTVisitor::visitIntReturnType(MiniCParser::IntReturnTypeContext *ctx) {
		type_attr attr;
		attr.type = BasicType::TYPE_INT;
		attr.lineno = ctx->getStart()->getLine();
		return create_type_node(attr);
	}
	std::any MiniCCSTVisitor::visitFloatReturnType(MiniCParser::FloatReturnTypeContext *ctx) {
		type_attr attr;
		attr.type = BasicType::TYPE_FLOAT;
		attr.lineno = ctx->getStart()->getLine();
		return create_type_node(attr);
	}
	std::any MiniCCSTVisitor::visitFuncFParams(MiniCParser::FuncFParamsContext *ctx) {
		// funcFParams : funcFParam (',' funcFParam)*
		ast_node *params = new ast_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
		for (auto p : ctx->funcFParam()) {
			auto param = std::any_cast<ast_node *>(visit(p));
			if (param) params->insert_son_node(param);
		}
		return params;
	}
	std::any MiniCCSTVisitor::visitFuncFParam(MiniCParser::FuncFParamContext *ctx) {
		// funcFParam : bType Ident
		return create_func_formal_param(ctx->Ident()->getSymbol()->getLine(), ctx->Ident()->getText().c_str());
	}

	// 语句块与语句
	std::any MiniCCSTVisitor::visitBlock(MiniCParser::BlockContext *ctx) {
		// block : '{' blockItem* '}'
		ast_node *block = new ast_node(ast_operator_type::AST_OP_BLOCK);
		for (auto item : ctx->blockItem()) {
			auto node = std::any_cast<ast_node *>(visit(item));
			if (node) block->insert_son_node(node);
		}
		return block;
	}
	std::any MiniCCSTVisitor::visitBlockDeclaration(MiniCParser::BlockDeclarationContext *ctx) {
		// blockDeclaration : decl
		return visit(ctx->decl());
	}
	std::any MiniCCSTVisitor::visitBlockStatement(MiniCParser::BlockStatementContext *ctx) {
		// blockStatement : stmt
		return visit(ctx->stmt());
	}
	std::any MiniCCSTVisitor::visitAssignmentStatement(MiniCParser::AssignmentStatementContext *ctx) {
		// assignmentStatement : lVal '=' exp ';'
		auto lval = std::any_cast<ast_node *>(visit(ctx->lVal()));
		auto expr = std::any_cast<ast_node *>(visit(ctx->exp()));
		return create_assign_stmt_node(lval, expr);
	}
	// !一定要带前缀：MiniCCSTVisitor
	std::any MiniCCSTVisitor::visitReturnStmt(MiniCParser::ReturnStmtContext * ctx){
		// returnStmt : 'return' exp? ';'
		auto expr = ctx->exp() ? std::any_cast<ast_node *>(visit(ctx->exp())) : nullptr;
		int64_t line = ctx->getStart()->getLine();
		return create_return_stmt_node(expr, line);
	}

	std::any MiniCCSTVisitor::visitExpressionStatement(MiniCParser::ExpressionStatementContext *ctx) {
		// expressionStatement : exp? ';'
		if (ctx->exp()) {
			auto expr = std::any_cast<ast_node *>(visit(ctx->exp()));
			return create_expr_stmt_node(expr);
		}
		return nullptr;
	}
	std::any MiniCCSTVisitor::visitNestedBlockStatement(MiniCParser::NestedBlockStatementContext *ctx) {
		// nestedBlockStatement : block
		auto block = std::any_cast<ast_node *>(visit(ctx->block()));
		return create_nested_block_node(block);
	}
	std::any MiniCCSTVisitor::visitIfElseStatement(MiniCParser::IfElseStatementContext *ctx) {
		// ifElseStatement : 'if' '(' cond ')' stmt ('else' stmt)?
		auto cond = std::any_cast<ast_node *>(visit(ctx->cond()));
		auto then_stmt = std::any_cast<ast_node *>(visit(ctx->stmt(0)));
		ast_node *else_stmt = nullptr;
		if (ctx->stmt().size() > 1) {
			else_stmt = std::any_cast<ast_node *>(visit(ctx->stmt(1)));
		}
		return create_if_else_stmt_node(cond, then_stmt, else_stmt);
	}
	std::any MiniCCSTVisitor::visitWhileLoopStatement(MiniCParser::WhileLoopStatementContext *ctx) {
		// whileLoopStatement : 'while' '(' cond ')' stmt
		auto cond = std::any_cast<ast_node *>(visit(ctx->cond()));
		auto body = std::any_cast<ast_node *>(visit(ctx->stmt()));
		return create_while_loop_node(cond, body);
	}
	std::any MiniCCSTVisitor::visitBreakStatement(MiniCParser::BreakStatementContext *ctx) {
		// breakStatement : 'break' ';'
		int64_t line = ctx->getStart()->getLine();
		return create_break_stmt_node(line);
	}
	std::any MiniCCSTVisitor::visitContinueStatement(MiniCParser::ContinueStatementContext *ctx) {
		// continueStatement : 'continue' ';'
		int64_t line = ctx->getStart()->getLine();
		return create_continue_stmt_node(line);
	}

	// 表达式
	std::any MiniCCSTVisitor::visitExp(MiniCParser::ExpContext *ctx) {
		// exp : addExp
		return visit(ctx->addExp());
	}
	std::any MiniCCSTVisitor::visitCond(MiniCParser::CondContext *ctx) {
		// cond : lOrExp
		return visit(ctx->lOrExp());
	}
	std::any MiniCCSTVisitor::visitLVal(MiniCParser::LValContext *ctx) {
		// lVal : Ident ('[' exp ']')*
		var_id_attr id;
		id.id = strdup(ctx->Ident()->getText().c_str());
		id.lineno = ctx->Ident()->getSymbol()->getLine();
		auto id_node = ast_node::New(id);
		std::vector<ast_node *> indices;
		for (auto e : ctx->exp()) {
			auto idx = std::any_cast<ast_node *>(visit(e));
			if (idx) indices.push_back(idx);
		}
		return create_lval_node(id_node, indices);
	}
	std::any MiniCCSTVisitor::visitPrimaryExp(MiniCParser::PrimaryExpContext *ctx) {
		// primaryExp : '(' exp ')' | lVal | number
		if (ctx->exp()) {
			return visit(ctx->exp());
		} else if (ctx->lVal()) {
			return visit(ctx->lVal());
		} else if (ctx->number()) {
			return visit(ctx->number());
		}
		return nullptr;
	}
	std::any MiniCCSTVisitor::visitNumber(MiniCParser::NumberContext *ctx) {
		// number : IntConst | FloatConst
		if (ctx->IntConst()) {
			int val = std::stoi(ctx->IntConst()->getText());
			return create_number_node(val);
		}
		// FloatConst略
		return nullptr;
	}
	std::any MiniCCSTVisitor::visitUnaryExp(MiniCParser::UnaryExpContext *ctx) {
		// unaryExp : primaryExp | Ident '(' funcRParams? ')' | unaryOp unaryExp
		if (ctx->primaryExp()) {
			return visit(ctx->primaryExp());
		} else if (ctx->unaryOp()) {
			auto op = std::any_cast<ast_node *>(visit(ctx->unaryOp()));
			auto operand = std::any_cast<ast_node *>(visit(ctx->unaryExp()));
			return create_unary_exp_node(op, operand);
		}
		// 这里只处理一元和primary
		return nullptr;
	}
	std::any MiniCCSTVisitor::visitUnaryOp(MiniCParser::UnaryOpContext *ctx) {
		// unaryOp : '+' | '-' | '!'
		int op_type = 0;
		std::string op = ctx->getText();
		if (op == "+") op_type = 1;
		else if (op == "-") op_type = 2;
		else if (op == "!") op_type = 3;
		return create_unary_op_node(op_type);
	}
	std::any MiniCCSTVisitor::visitFuncRParams(MiniCParser::FuncRParamsContext *ctx) {
		// funcRParams : exp (',' exp)*
		std::vector<ast_node *> params;
		for (auto e : ctx->exp()) {
			auto node = std::any_cast<ast_node *>(visit(e));
			if (node) params.push_back(node);
		}
		return create_func_rparams_node(params);
	}
	std::any MiniCCSTVisitor::visitMulExp(MiniCParser::MulExpContext *ctx) {
		// mulExp : unaryExp | mulExp ('*'|'/'|'%') unaryExp
		if (ctx->unaryExp().size() == 1) {
			// 只有一个unaryExp，直接返回
			return visit(ctx->unaryExp(0));
		} else {
			// 形如: mulExp op unaryExp
			// 左递归，左侧是mulExp，右侧是unaryExp
			auto left = std::any_cast<ast_node *>(visit(ctx->unaryExp(0)));
			for (size_t i = 1; i < ctx->unaryExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->unaryExp(i)));
				std::string op = ctx->children[2 * i - 1]->getText();
				int op_type = 0;
				if (op == "*") op_type = 0;
				else if (op == "/") op_type = 1;
				else if (op == "%") op_type = 2;
				left = create_mul_exp_node(left, right, op_type);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitAddExp(MiniCParser::AddExpContext *ctx) {
		// addExp : mulExp | addExp ('+'|'-') mulExp
		if (ctx->mulExp().size() == 1) {
			return visit(ctx->mulExp(0));
		} else {
			auto left = std::any_cast<ast_node *>(visit(ctx->mulExp(0)));
			for (size_t i = 1; i < ctx->mulExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->mulExp(i)));
				std::string op = ctx->children[2 * i - 1]->getText();
				int op_type = 0;
				if (op == "+") op_type = 0;
				else if (op == "-") op_type = 1;
				left = create_add_exp_node(left, right, op_type);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitRelExp(MiniCParser::RelExpContext *ctx) {
		// relExp : addExp | relExp ('<'|'>'|'<='|'>=') addExp
		if (ctx->addExp().size() == 1) {
			return visit(ctx->addExp(0));
		} else {
			auto left = std::any_cast<ast_node *>(visit(ctx->addExp(0)));
			for (size_t i = 1; i < ctx->addExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->addExp(i)));
				std::string op = ctx->children[2 * i - 1]->getText();
				int op_type = 0;
				if (op == "<") op_type = 0;
				else if (op == ">") op_type = 1;
				else if (op == "<=") op_type = 2;
				else if (op == ">=") op_type = 3;
				left = create_rel_exp_node(left, right, op_type);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitEqExp(MiniCParser::EqExpContext *ctx) {
		// eqExp : relExp | eqExp ('=='|'!=') relExp
		if (ctx->relExp().size() == 1) {
			return visit(ctx->relExp(0));
		} else {
			auto left = std::any_cast<ast_node *>(visit(ctx->relExp(0)));
			for (size_t i = 1; i < ctx->relExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->relExp(i)));
				std::string op = ctx->children[2 * i - 1]->getText();
				int op_type = 0;
				if (op == "==") op_type = 0;
				else if (op == "!=") op_type = 1;
				left = create_eq_exp_node(left, right, op_type);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitLAndExp(MiniCParser::LAndExpContext *ctx) {
		// lAndExp : eqExp | lAndExp '&&' eqExp
		if (ctx->eqExp().size() == 1) {
			return visit(ctx->eqExp(0));
		} else {
			auto left = std::any_cast<ast_node *>(visit(ctx->eqExp(0)));
			for (size_t i = 1; i < ctx->eqExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->eqExp(i)));
				left = create_land_exp_node(left, right);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitLOrExp(MiniCParser::LOrExpContext *ctx) {
		// lOrExp : lAndExp | lOrExp '||' lAndExp
		if (ctx->lAndExp().size() == 1) {
			return visit(ctx->lAndExp(0));
		} else {
			auto left = std::any_cast<ast_node *>(visit(ctx->lAndExp(0)));
			for (size_t i = 1; i < ctx->lAndExp().size(); ++i) {
				auto right = std::any_cast<ast_node *>(visit(ctx->lAndExp(i)));
				left = create_lor_exp_node(left, right);
			}
			return left;
		}
	}
	std::any MiniCCSTVisitor::visitConstExp(MiniCParser::ConstExpContext *ctx) {
		// constExp : addExp
		auto expr = std::any_cast<ast_node *>(visit(ctx->addExp()));
		return create_const_exp_node(expr);
	}
