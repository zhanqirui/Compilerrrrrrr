grammar MiniC;

// 核心编译单元
compUnit: (decl | funcDef)* EOF;

// 声明部分（常量/变量）
decl: constDecl # constDeclaration | varDecl # varDeclaration;

// 常量声明
constDecl: 'const' bType constDef (',' constDef)* ';';

// 基本类型系统（支持 int 和 int float 混合类型）
bType: 'int' # intType | 'float' # floatType;

// 常量定义（标量/数组）
constDef: Ident ('[' constExp ']')* '=' constInitVal;

// 常量初始化值
constInitVal:
	constExp										# scalarConstInitVal
	| '{' (constInitVal (',' constInitVal)*)? '}'	# arrayConstInitVal;

// 变量声明
varDecl: bType varDef (',' varDef)* ';';

// 变量定义（可选初始化）
varDef: Ident ('[' constExp ']')* ('=' initVal)?;

// 变量初始化
initVal:
	exp									# scalarInitVal
	| '{' (initVal (',' initVal)*)? '}'	# arrayInitVal;

// 函数定义
funcDef: funcType Ident '(' funcFParams? ')' block;

// 函数返回类型
funcType:
	'void'		# voidReturnType
	| 'int'		# intReturnType
	| 'float'	# floatReturnType;

// 函数形参列表
funcFParams: funcFParam (',' funcFParam)*;

// 单个形参（支持多维数组参数）
funcFParam: bType Ident ('[' ']' ('[' exp ']')*)?;

// 语句块
block: '{' blockItem* '}';

// 块内元素
blockItem: decl # blockDeclaration | stmt # blockStatement;

// 语句系统
stmt:
	lVal '=' exp ';'						# assignmentStatement
	| exp? ';'								# expressionStatement
	| block									# nestedBlockStatement
	| 'if' '(' cond ')' stmt ('else' stmt)?	# ifElseStatement
	| 'while' '(' cond ')' stmt				# whileLoopStatement
	| 'break' ';'							# breakStatement
	| 'continue' ';'						# continueStatement
	| 'return' exp? ';'						# returnStmt; // 新增 return 语句规则

// 表达式体系
exp: lOrExp;

// 条件表达式
cond: lOrExp;

// 左值访问
lVal: Ident ('[' exp ']')*;

// 基础表达式
primaryExp: '(' exp ')' | lVal | number;

// 数值类型
number: IntConst | FloatConst;

// 一元表达式
unaryExp:
	primaryExp						# UnaryExpPrimary
	| Ident '(' funcRParams? ')'	# UnaryExpFuncCall
	| unaryOp unaryExp				# UnaryOpUnaryExp;

// 一元运算符
unaryOp: '+' | '-' | '!';

// 实参列表
funcRParams: exp (',' exp)*;

// 算术表达式层级（保持优先级）
mulExp: unaryExp (('*' | '/' | '%') unaryExp)*;

addExp: mulExp (('+' | '-') mulExp)*;

relExp: addExp (('<' | '>' | '<=' | '>=') addExp)*;

eqExp: relExp (('==' | '!=') relExp)*;

lAndExp: eqExp ('&&' eqExp)*;

lOrExp: lAndExp ('||' lAndExp)*;

// 常量表达式
constExp: addExp;

// return 

RETURN: 'return';

// 词法规则
Ident: [a-zA-Z_] [a-zA-Z0-9_]*;
IntConst:
	'0x' [0-9a-fA-F]+ // 16进制
	| '0X' [0-9a-fA-F]+ // 16进制
	| '0' [0-7]+ // 8进制
	| [1-9][0-9]* // 十进制
	| '0'; // 单独的0

FloatConst:
	[0-9]+ '.' [0-9]* ([eE] [+\-]? [0-9]+)? // 1.23, 1.23e10, 1.23E-10
	| '.' [0-9]+ ([eE] [+\-]? [0-9]+)? // .23, .23e5
	| [0-9]+ [eE] [+\-]? [0-9]+; // 1e10, 1E-10

// 空白和注释
Whitespace: [ \t\r\n]+ -> skip;
BlockComment: '/*' .*? '*/' -> skip;
LineComment: '//' ~[\r\n]* -> skip;