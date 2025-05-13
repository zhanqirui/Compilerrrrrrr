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
	#include <sstream>

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
	// constDecl : 'const' bType constDef (',' constDef)* ';'
	auto type_node = std::any_cast<ast_node *>(visit(ctx->bType()));
	
	// 创建常量声明列表节点，与变量声明保持一致的结构
	ast_node *const_decl_node = new ast_node(ast_operator_type::AST_OP_CONST_DECL);
	// 添加类型节点作为第一个子节点
	const_decl_node->insert_son_node(type_node);
	
	// 添加所有常量定义节点作为子节点
	for (auto defCtx : ctx->constDef()) {
		auto def_node = std::any_cast<ast_node *>(visit(defCtx));
		if (def_node) {
			const_decl_node->insert_son_node(def_node);
		}
	}
	
	return const_decl_node;
}

std::any MiniCCSTVisitor::visitIntType(MiniCParser::IntTypeContext * ctx) {
	// IntType : 'int' 
	type_attr attr;
	attr.type = BasicType::TYPE_INT;
	attr.lineno = ctx->getStart()->getLine();
	return create_type_node(attr);
}

std::any MiniCCSTVisitor::visitFloatType(MiniCParser::FloatTypeContext * ctx) {
	// FloatType : 'float' 
	type_attr attr;
	attr.type = BasicType::TYPE_FLOAT;
	attr.lineno = ctx->getStart()->getLine();
	return create_type_node(attr);
}

std::any MiniCCSTVisitor::visitConstDef(MiniCParser::ConstDefContext *ctx) {
	// constDef : Ident ('[' constExp ']')* '=' constInitVal
	var_id_attr id;
	id.id = strdup(ctx->Ident()->getText().c_str());
	id.lineno = ctx->Ident()->getSymbol()->getLine();
	auto id_node = ast_node::New(id);
	
	// 处理数组维度
	std::vector<ast_node *> dimensions;
	for (auto exp : ctx->constExp()) {
		auto dim = std::any_cast<ast_node *>(visit(exp));
		if (dim) dimensions.push_back(dim);
	}
	
	auto init_node = std::any_cast<ast_node *>(visit(ctx->constInitVal()));
	
	// 根据是否有维度信息来区分普通变量和数组
	if (dimensions.empty()) {
		// 普通变量
		return create_const_def_node(id_node, init_node);
	} else {
		// 数组变量 - 使用更清晰的节点结构
		return create_array_const_def_node(id_node, dimensions, init_node);
	}
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
	
	// 创建变量声明列表节点
	ast_node *var_decl_node = new ast_node(ast_operator_type::AST_OP_VAR_DECL);
	// 添加类型节点作为第一个子节点
	var_decl_node->insert_son_node(type_node);
	
	// 添加所有变量定义节点作为子节点
	for (auto defCtx : ctx->varDef()) {
		auto def_node = std::any_cast<ast_node *>(visit(defCtx));
		if (def_node) {
			var_decl_node->insert_son_node(def_node);
		}
	}
	
	return var_decl_node;
}
std::any MiniCCSTVisitor::visitVarDef(MiniCParser::VarDefContext *ctx) {
	// varDef : Ident ('[' constExp ']')* ('=' initVal)?
	var_id_attr id;
	id.id = strdup(ctx->Ident()->getText().c_str());
	id.lineno = ctx->Ident()->getSymbol()->getLine();
	auto id_node = ast_node::New(id);
	
	// 处理数组维度
	std::vector<ast_node *> dimensions;
	for (auto exp : ctx->constExp()) {
		auto dim = std::any_cast<ast_node *>(visit(exp));
		if (dim) dimensions.push_back(dim);
	}
	
	ast_node *init_node = nullptr;
	if (ctx->initVal()) {
		init_node = std::any_cast<ast_node *>(visit(ctx->initVal()));
	}
	
	// 根据是否有维度信息来区分普通变量和数组
	if (dimensions.empty()) {
		// 普通变量
		return create_var_def_node(id_node, init_node);
	} else {
		// 数组变量 - 使用更清晰的节点结构
		return create_array_var_def_node(id_node, dimensions, init_node);
	}
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
	std::string return_type = ctx->funcType()->getText();
	if (return_type == "void") {
		funcReturnType.type = BasicType::TYPE_VOID;
	} else if (return_type == "int") {
		funcReturnType.type = BasicType::TYPE_INT;
	} else if (return_type == "float") {
		funcReturnType.type = BasicType::TYPE_FLOAT;
	} else {
		funcReturnType.type = BasicType::TYPE_MAX;
	}
	std::string return_type = ctx->funcType()->getText();
	if (return_type == "void") {
		funcReturnType.type = BasicType::TYPE_VOID;
	} else if (return_type == "int") {
		funcReturnType.type = BasicType::TYPE_INT;
	} else if (return_type == "float") {
		funcReturnType.type = BasicType::TYPE_FLOAT;
	} else {
		funcReturnType.type = BasicType::TYPE_MAX;
	}
	funcReturnType.lineno = ctx->getStart()->getLine();
	var_id_attr funcId;
	funcId.id = strdup(ctx->Ident()->getText().c_str());
	funcId.lineno = ctx->Ident()->getSymbol()->getLine();

	this->CurrentFunctionName = funcId.id;


	this->CurrentFunctionName = funcId.id;

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
    // 处理参数类型
    auto type_node = std::any_cast<ast_node *>(visit(ctx->bType()));
    
    // 处理参数名
    var_id_attr id;
    id.id = strdup(ctx->Ident()->getText().c_str());
    id.lineno = ctx->Ident()->getSymbol()->getLine();
    auto id_node = ast_node::New(id);
    
    // 检查是否是数组参数 - 使用 LBrackets() 等方法检测方括号
    // 根据 MiniC 语法: funcFParam: bType Ident ('[' ']' ('[' exp ']')*)?;
    bool is_array = ctx->getText().find('[') != std::string::npos;
    
    std::vector<ast_node *> dimensions;
    if (is_array) {
        // 第一维始终是空的 []，需要显式添加一个 nullptr 表示这是一个未知大小的维度
        dimensions.push_back(nullptr);
        
        // 对于后续维度，处理每个表达式
        for (auto expCtx : ctx->exp()) {
            if (expCtx) {
                auto dim_node = std::any_cast<ast_node *>(visit(expCtx));
                dimensions.push_back(dim_node);
            }
        }
    }
    
    return create_func_fparam_node(type_node, id_node, is_array, dimensions);
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
	std::string stmt_string = ctx->getText();
	bool is_return = false;
    is_return = stmt_string.rfind("return", 0) == 0;
	if (is_return) {
		// 处理函数返回语句并计算函数返回值个数
		Instanceof(returnStmtCtx, MiniCParser::ReturnStmtContext *, ctx->stmt());
		if (returnStmtCtx) {
			// 处理函数返回语句
			return visitReturnStmtWithReturnNum(returnStmtCtx, this->CurrentFunctionName);
		}
        return nullptr;	
    }
	return visit(ctx->stmt());
}
std::any MiniCCSTVisitor::visitAssignmentStatement(MiniCParser::AssignmentStatementContext *ctx) {
	// assignmentStatement : lVal '=' exp ';'
	auto lval = std::any_cast<ast_node *>(visit(ctx->lVal()));
	auto expr = std::any_cast<ast_node *>(visit(ctx->exp()));
	return create_assign_stmt_node(lval, expr);
}

std::any MiniCCSTVisitor::visitReturnStmtWithReturnNum(MiniCParser::ReturnStmtContext * ctx, std::string FunctionName)
{
	if(this->NameToReturnNum.find(FunctionName) == this->NameToReturnNum.end())
	{
		this->NameToReturnNum[FunctionName] = 1;
	}
	else
	{
		this->NameToReturnNum[FunctionName]++;
	}

	return visitReturnStmt(ctx);
}


std::any MiniCCSTVisitor::visitReturnStmtWithReturnNum(MiniCParser::ReturnStmtContext * ctx, std::string FunctionName)
{
	if(this->NameToReturnNum.find(FunctionName) == this->NameToReturnNum.end())
	{
		this->NameToReturnNum[FunctionName] = 1;
	}
	else
	{
		this->NameToReturnNum[FunctionName]++;
	}

	return visitReturnStmt(ctx);
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
	
	// 使用工厂函数创建if-else节点
	return create_if_else_stmt_node(cond, then_stmt, else_stmt);
}
std::any MiniCCSTVisitor::visitWhileLoopStatement(MiniCParser::WhileLoopStatementContext *ctx) {
	// whileLoopStatement : 'while' '(' cond ')' stmt
	auto cond = std::any_cast<ast_node *>(visit(ctx->cond()));
	auto body = std::any_cast<ast_node *>(visit(ctx->stmt()));
	
	// 使用工厂函数创建while循环节点
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
	auto expr = std::any_cast<ast_node *>(visit(ctx->addExp()));
	return create_exp_node(expr);
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
	
	// 根据是否有索引来区分普通变量和数组访问
	if (indices.empty()) {
		// 普通变量访问
		return create_lval_node(id_node, indices);
	} else {
		// 数组元素访问
		return create_array_access_node(id_node, indices);
	}
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
	// FloatConst
	if (ctx->FloatConst()) {
		float val = std::stof(ctx->FloatConst()->getText());
		return create_float_node(val);
	}
	return nullptr;
}
std::any MiniCCSTVisitor::visitUnaryExpPrimary(MiniCParser::UnaryExpPrimaryContext *ctx) {
	// 处理 unaryExpPrimary: primaryExp -> primaryExp
	return visit(ctx->primaryExp());
}

std::any MiniCCSTVisitor::visitUnaryExpFuncCall(MiniCParser::UnaryExpFuncCallContext *ctx) {
	// 处理 unaryExpFuncCall: Ident '(' funcRParams? ')'
	var_id_attr id;
	id.id = strdup(ctx->Ident()->getText().c_str());
	id.lineno = ctx->Ident()->getSymbol()->getLine();
	auto id_node = ast_node::New(id);
	
	ast_node *params_node = nullptr;
	if (ctx->funcRParams()) {
		params_node = std::any_cast<ast_node *>(visit(ctx->funcRParams()));
	}
	
	return create_func_call(id_node, params_node);
}

std::any MiniCCSTVisitor::visitUnaryOpUnaryExp(MiniCParser::UnaryOpUnaryExpContext *ctx) {
	// 处理 unaryOpUnaryExp: unaryOp unaryExp
	auto op = std::any_cast<ast_node *>(visit(ctx->unaryOp()));
	auto operand = std::any_cast<ast_node *>(visit(ctx->unaryExp()));
	return create_unary_exp_node(op, operand);
}
std::any MiniCCSTVisitor::visitUnaryOp(MiniCParser::UnaryOpContext *ctx) {
	// unaryOp : '+' | '-' | '!'
	Op op_type = Op::NONE;
	std::string op = ctx->getText();
	if (op == "+") op_type = Op::POS;
	else if (op == "-") op_type = Op::NEG;
	else if (op == "!") op_type = Op::NOT;
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
	// 根据文法规则: mulExp : unaryExp (('*' | '/' | '%') unaryExp)*
	if (ctx->unaryExp().size() == 1) {
		// 只有一个unaryExp，直接返回
		return visit(ctx->unaryExp(0));
	} else {
		// 处理多个unaryExp的情况
		auto left = std::any_cast<ast_node *>(visit(ctx->unaryExp(0)));
		
		// 遍历所有操作符和右操作数
		for (size_t i = 1; i < ctx->unaryExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->unaryExp(i)));
			
			// 获取操作符 - 通过直接检查相应位置的文本
			// 操作符位于两个unaryExp之间，因此需要使用索引(2*i-1)
			std::string op = ctx->children[2*i-1]->getText();
			
			Op op_type = Op::NONE;
			if (op == "*") op_type = Op::MUL;
			else if (op == "/") op_type = Op::DIV;
			else if (op == "%") op_type = Op::MOD;
			
			// 创建新的乘法表达式节点，并将其作为新的左操作数
			left = create_mul_exp_node(left, right, op_type);
		}
		return left;
	}
}
std::any MiniCCSTVisitor::visitAddExp(MiniCParser::AddExpContext *ctx) {
	// 根据文法规则: addExp : mulExp (('+' | '-') mulExp)*
	if (ctx->mulExp().size() == 1) {
		// 只有一个mulExp，直接返回
		return visit(ctx->mulExp(0));
	} else {
		// 处理多个mulExp的情况
		auto left = std::any_cast<ast_node *>(visit(ctx->mulExp(0)));
		
		// 遍历所有操作符和右操作数
		for (size_t i = 1; i < ctx->mulExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->mulExp(i)));
			
			// 获取运算符，运算符是在两个mulExp之间的token
			std::string op = ctx->children[2 * i - 1]->getText();
		
			Op op_type = Op::NONE;
			if (op == "+") op_type = Op::ADD;
			else if (op == "-") op_type = Op::SUB;
			
			// 创建新的加法表达式节点，并将其作为新的左操作数
			left = create_add_exp_node(left, right, op_type);
		}
		return left;
	}
}
std::any MiniCCSTVisitor::visitRelExp(MiniCParser::RelExpContext *ctx) {
	// 根据文法规则: relExp : addExp (('<' | '>' | '<=' | '>=') addExp)*
	if (ctx->addExp().size() == 1) {
		// 只有一个addExp，直接返回
		return visit(ctx->addExp(0));
	} else {
		// 处理多个addExp的情况
		auto left = std::any_cast<ast_node *>(visit(ctx->addExp(0)));
		
		// 获取所有运算符
		auto relOps = ctx->children;
		size_t opIndex = 1;
		
		for (size_t i = 1; i < ctx->addExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->addExp(i)));
			
			// 获取运算符，运算符是在两个addExp之间的token
			std::string op = relOps[opIndex]->getText();
			opIndex += 2; // 跳过下一个addExp
			
			Op op_type = Op::NONE;
			if (op == "<") op_type = Op::LT;
			else if (op == ">") op_type = Op::GT;
			else if (op == "<=") op_type = Op::LE;
			else if (op == ">=") op_type = Op::GE;
			
			// 创建新的关系表达式节点，并将其作为新的左操作数
			left = create_rel_exp_node(left, right, op_type);
		}
		return left;
	}
}
std::any MiniCCSTVisitor::visitEqExp(MiniCParser::EqExpContext *ctx) {
	// 根据文法规则: eqExp : relExp (('==' | '!=') relExp)*
	if (ctx->relExp().size() == 1) {
		// 只有一个relExp，直接返回
		return visit(ctx->relExp(0));
	} else {
		// 处理多个relExp的情况
		auto left = std::any_cast<ast_node *>(visit(ctx->relExp(0)));
		
		// 获取所有运算符
		auto eqOps = ctx->children;
		size_t opIndex = 1;
		
		for (size_t i = 1; i < ctx->relExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->relExp(i)));
			
			// 获取运算符，运算符是在两个relExp之间的token
			std::string op = eqOps[opIndex]->getText();
			opIndex += 2; // 跳过下一个relExp
			
			Op op_type = Op::NONE;
			if (op == "==") op_type = Op::EQ;
			else if (op == "!=") op_type = Op::NE;
			
			// 创建新的等价表达式节点，并将其作为新的左操作数
			left = create_eq_exp_node(left, right, op_type);
		}
		return left;
	}
}
std::any MiniCCSTVisitor::visitLAndExp(MiniCParser::LAndExpContext *ctx) {
	// 根据文法规则: lAndExp : eqExp ('&&' eqExp)*
	if (ctx->eqExp().size() == 1) {
		// 只有一个eqExp，直接返回
		return visit(ctx->eqExp(0));
	} else {
		// 处理多个eqExp的情况，这是非递归规则，使用循环构建
		auto left = std::any_cast<ast_node *>(visit(ctx->eqExp(0)));
		
		for (size_t i = 1; i < ctx->eqExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->eqExp(i)));
			
			// 创建新的逻辑与表达式节点，并将其作为左操作数继续处理
			left = create_land_exp_node(left, right);
		}
		return left;
	}
}
std::any MiniCCSTVisitor::visitLOrExp(MiniCParser::LOrExpContext *ctx) {
	// 根据文法规则: lOrExp : lAndExp ('||' lAndExp)*
	if (ctx->lAndExp().size() == 1) {
		// 只有一个lAndExp，直接返回
		return visit(ctx->lAndExp(0));
	} else {
		// 处理多个lAndExp的情况，这是非递归规则，使用循环构建
		auto left = std::any_cast<ast_node *>(visit(ctx->lAndExp(0)));
		
		for (size_t i = 1; i < ctx->lAndExp().size(); ++i) {
			auto right = std::any_cast<ast_node *>(visit(ctx->lAndExp(i)));
			
			// 创建新的逻辑或表达式节点，并将其作为左操作数继续处理
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


