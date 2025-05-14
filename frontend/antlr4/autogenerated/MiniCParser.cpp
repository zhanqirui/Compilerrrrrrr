
// Generated from MiniC.g4 by ANTLR 4.12.0


#include "MiniCVisitor.h"

#include "MiniCParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct MiniCParserStaticData final {
  MiniCParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  MiniCParserStaticData(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData(MiniCParserStaticData&&) = delete;
  MiniCParserStaticData& operator=(const MiniCParserStaticData&) = delete;
  MiniCParserStaticData& operator=(MiniCParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag minicParserOnceFlag;
MiniCParserStaticData *minicParserStaticData = nullptr;

void minicParserInitialize() {
  assert(minicParserStaticData == nullptr);
  auto staticData = std::make_unique<MiniCParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "constDecl", "bType", "constDef", "constInitVal", 
      "varDecl", "varDef", "initVal", "funcDef", "funcType", "funcFParams", 
      "funcFParam", "block", "blockItem", "stmt", "exp", "cond", "lVal", 
      "primaryExp", "number", "unaryExp", "unaryOp", "funcRParams", "mulExp", 
      "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp"
    },
    std::vector<std::string>{
      "", "','", "';'", "'['", "']'", "'='", "'{'", "'}'", "'('", "')'", 
      "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", "'>'", "'<='", "'>='", 
      "'=='", "'!='", "'&&'", "'||'", "'break'", "'continue'", "'if'", "'else'", 
      "'while'", "'return'", "'const'", "'int'", "'float'", "'void'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "BREAK", "CONTINUE", "IF", "ELSE", "WHILE", 
      "RETURN", "CONST", "INT", "FLOAT", "VOID", "Ident", "IntConst", "FloatConst", 
      "Whitespace", "BlockComment", "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,39,342,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,5,0,65,8,0,10,0,12,0,68,9,0,1,0,1,0,1,
  	1,1,1,3,1,74,8,1,1,2,1,2,1,2,1,2,1,2,5,2,81,8,2,10,2,12,2,84,9,2,1,2,
  	1,2,1,3,1,3,3,3,90,8,3,1,4,1,4,1,4,1,4,1,4,5,4,97,8,4,10,4,12,4,100,9,
  	4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,5,5,110,8,5,10,5,12,5,113,9,5,3,5,115,
  	8,5,1,5,3,5,118,8,5,1,6,1,6,1,6,1,6,5,6,124,8,6,10,6,12,6,127,9,6,1,6,
  	1,6,1,7,1,7,1,7,1,7,1,7,5,7,136,8,7,10,7,12,7,139,9,7,1,7,1,7,3,7,143,
  	8,7,1,8,1,8,1,8,1,8,1,8,5,8,150,8,8,10,8,12,8,153,9,8,3,8,155,8,8,1,8,
  	3,8,158,8,8,1,9,1,9,1,9,1,9,3,9,164,8,9,1,9,1,9,1,9,1,10,1,10,1,10,3,
  	10,172,8,10,1,11,1,11,1,11,5,11,177,8,11,10,11,12,11,180,9,11,1,12,1,
  	12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,190,8,12,10,12,12,12,193,9,12,3,
  	12,195,8,12,1,13,1,13,5,13,199,8,13,10,13,12,13,202,9,13,1,13,1,13,1,
  	14,1,14,3,14,208,8,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,227,8,15,1,15,1,15,1,15,1,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,241,8,15,1,15,3,15,244,
  	8,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,18,1,18,5,18,255,8,18,10,18,
  	12,18,258,9,18,1,19,1,19,1,19,1,19,1,19,1,19,3,19,266,8,19,1,20,1,20,
  	1,21,1,21,1,21,1,21,3,21,274,8,21,1,21,1,21,1,21,1,21,3,21,280,8,21,1,
  	22,1,22,1,23,1,23,1,23,5,23,287,8,23,10,23,12,23,290,9,23,1,24,1,24,1,
  	24,5,24,295,8,24,10,24,12,24,298,9,24,1,25,1,25,1,25,5,25,303,8,25,10,
  	25,12,25,306,9,25,1,26,1,26,1,26,5,26,311,8,26,10,26,12,26,314,9,26,1,
  	27,1,27,1,27,5,27,319,8,27,10,27,12,27,322,9,27,1,28,1,28,1,28,5,28,327,
  	8,28,10,28,12,28,330,9,28,1,29,1,29,1,29,5,29,335,8,29,10,29,12,29,338,
  	9,29,1,30,1,30,1,30,0,0,31,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,0,6,1,0,35,36,1,0,10,12,
  	1,0,13,15,1,0,10,11,1,0,16,19,1,0,20,21,356,0,66,1,0,0,0,2,73,1,0,0,0,
  	4,75,1,0,0,0,6,89,1,0,0,0,8,91,1,0,0,0,10,117,1,0,0,0,12,119,1,0,0,0,
  	14,130,1,0,0,0,16,157,1,0,0,0,18,159,1,0,0,0,20,171,1,0,0,0,22,173,1,
  	0,0,0,24,181,1,0,0,0,26,196,1,0,0,0,28,207,1,0,0,0,30,243,1,0,0,0,32,
  	245,1,0,0,0,34,247,1,0,0,0,36,249,1,0,0,0,38,265,1,0,0,0,40,267,1,0,0,
  	0,42,279,1,0,0,0,44,281,1,0,0,0,46,283,1,0,0,0,48,291,1,0,0,0,50,299,
  	1,0,0,0,52,307,1,0,0,0,54,315,1,0,0,0,56,323,1,0,0,0,58,331,1,0,0,0,60,
  	339,1,0,0,0,62,65,3,2,1,0,63,65,3,18,9,0,64,62,1,0,0,0,64,63,1,0,0,0,
  	65,68,1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,69,1,0,0,0,68,66,1,0,0,0,
  	69,70,5,0,0,1,70,1,1,0,0,0,71,74,3,4,2,0,72,74,3,12,6,0,73,71,1,0,0,0,
  	73,72,1,0,0,0,74,3,1,0,0,0,75,76,5,30,0,0,76,77,3,6,3,0,77,82,3,8,4,0,
  	78,79,5,1,0,0,79,81,3,8,4,0,80,78,1,0,0,0,81,84,1,0,0,0,82,80,1,0,0,0,
  	82,83,1,0,0,0,83,85,1,0,0,0,84,82,1,0,0,0,85,86,5,2,0,0,86,5,1,0,0,0,
  	87,90,5,31,0,0,88,90,5,32,0,0,89,87,1,0,0,0,89,88,1,0,0,0,90,7,1,0,0,
  	0,91,98,5,34,0,0,92,93,5,3,0,0,93,94,3,60,30,0,94,95,5,4,0,0,95,97,1,
  	0,0,0,96,92,1,0,0,0,97,100,1,0,0,0,98,96,1,0,0,0,98,99,1,0,0,0,99,101,
  	1,0,0,0,100,98,1,0,0,0,101,102,5,5,0,0,102,103,3,10,5,0,103,9,1,0,0,0,
  	104,118,3,60,30,0,105,114,5,6,0,0,106,111,3,10,5,0,107,108,5,1,0,0,108,
  	110,3,10,5,0,109,107,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,
  	1,0,0,0,112,115,1,0,0,0,113,111,1,0,0,0,114,106,1,0,0,0,114,115,1,0,0,
  	0,115,116,1,0,0,0,116,118,5,7,0,0,117,104,1,0,0,0,117,105,1,0,0,0,118,
  	11,1,0,0,0,119,120,3,6,3,0,120,125,3,14,7,0,121,122,5,1,0,0,122,124,3,
  	14,7,0,123,121,1,0,0,0,124,127,1,0,0,0,125,123,1,0,0,0,125,126,1,0,0,
  	0,126,128,1,0,0,0,127,125,1,0,0,0,128,129,5,2,0,0,129,13,1,0,0,0,130,
  	137,5,34,0,0,131,132,5,3,0,0,132,133,3,60,30,0,133,134,5,4,0,0,134,136,
  	1,0,0,0,135,131,1,0,0,0,136,139,1,0,0,0,137,135,1,0,0,0,137,138,1,0,0,
  	0,138,142,1,0,0,0,139,137,1,0,0,0,140,141,5,5,0,0,141,143,3,16,8,0,142,
  	140,1,0,0,0,142,143,1,0,0,0,143,15,1,0,0,0,144,158,3,32,16,0,145,154,
  	5,6,0,0,146,151,3,16,8,0,147,148,5,1,0,0,148,150,3,16,8,0,149,147,1,0,
  	0,0,150,153,1,0,0,0,151,149,1,0,0,0,151,152,1,0,0,0,152,155,1,0,0,0,153,
  	151,1,0,0,0,154,146,1,0,0,0,154,155,1,0,0,0,155,156,1,0,0,0,156,158,5,
  	7,0,0,157,144,1,0,0,0,157,145,1,0,0,0,158,17,1,0,0,0,159,160,3,20,10,
  	0,160,161,5,34,0,0,161,163,5,8,0,0,162,164,3,22,11,0,163,162,1,0,0,0,
  	163,164,1,0,0,0,164,165,1,0,0,0,165,166,5,9,0,0,166,167,3,26,13,0,167,
  	19,1,0,0,0,168,172,5,33,0,0,169,172,5,31,0,0,170,172,5,32,0,0,171,168,
  	1,0,0,0,171,169,1,0,0,0,171,170,1,0,0,0,172,21,1,0,0,0,173,178,3,24,12,
  	0,174,175,5,1,0,0,175,177,3,24,12,0,176,174,1,0,0,0,177,180,1,0,0,0,178,
  	176,1,0,0,0,178,179,1,0,0,0,179,23,1,0,0,0,180,178,1,0,0,0,181,182,3,
  	6,3,0,182,194,5,34,0,0,183,184,5,3,0,0,184,191,5,4,0,0,185,186,5,3,0,
  	0,186,187,3,32,16,0,187,188,5,4,0,0,188,190,1,0,0,0,189,185,1,0,0,0,190,
  	193,1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,192,195,1,0,0,0,193,191,1,
  	0,0,0,194,183,1,0,0,0,194,195,1,0,0,0,195,25,1,0,0,0,196,200,5,6,0,0,
  	197,199,3,28,14,0,198,197,1,0,0,0,199,202,1,0,0,0,200,198,1,0,0,0,200,
  	201,1,0,0,0,201,203,1,0,0,0,202,200,1,0,0,0,203,204,5,7,0,0,204,27,1,
  	0,0,0,205,208,3,2,1,0,206,208,3,30,15,0,207,205,1,0,0,0,207,206,1,0,0,
  	0,208,29,1,0,0,0,209,210,3,36,18,0,210,211,5,5,0,0,211,212,3,32,16,0,
  	212,213,5,2,0,0,213,244,1,0,0,0,214,244,5,2,0,0,215,216,3,32,16,0,216,
  	217,5,2,0,0,217,244,1,0,0,0,218,244,3,26,13,0,219,220,5,26,0,0,220,221,
  	5,8,0,0,221,222,3,34,17,0,222,223,5,9,0,0,223,226,3,30,15,0,224,225,5,
  	27,0,0,225,227,3,30,15,0,226,224,1,0,0,0,226,227,1,0,0,0,227,244,1,0,
  	0,0,228,229,5,28,0,0,229,230,5,8,0,0,230,231,3,34,17,0,231,232,5,9,0,
  	0,232,233,3,30,15,0,233,244,1,0,0,0,234,235,5,24,0,0,235,244,5,2,0,0,
  	236,237,5,25,0,0,237,244,5,2,0,0,238,240,5,29,0,0,239,241,3,32,16,0,240,
  	239,1,0,0,0,240,241,1,0,0,0,241,242,1,0,0,0,242,244,5,2,0,0,243,209,1,
  	0,0,0,243,214,1,0,0,0,243,215,1,0,0,0,243,218,1,0,0,0,243,219,1,0,0,0,
  	243,228,1,0,0,0,243,234,1,0,0,0,243,236,1,0,0,0,243,238,1,0,0,0,244,31,
  	1,0,0,0,245,246,3,58,29,0,246,33,1,0,0,0,247,248,3,58,29,0,248,35,1,0,
  	0,0,249,256,5,34,0,0,250,251,5,3,0,0,251,252,3,32,16,0,252,253,5,4,0,
  	0,253,255,1,0,0,0,254,250,1,0,0,0,255,258,1,0,0,0,256,254,1,0,0,0,256,
  	257,1,0,0,0,257,37,1,0,0,0,258,256,1,0,0,0,259,260,5,8,0,0,260,261,3,
  	32,16,0,261,262,5,9,0,0,262,266,1,0,0,0,263,266,3,36,18,0,264,266,3,40,
  	20,0,265,259,1,0,0,0,265,263,1,0,0,0,265,264,1,0,0,0,266,39,1,0,0,0,267,
  	268,7,0,0,0,268,41,1,0,0,0,269,280,3,38,19,0,270,271,5,34,0,0,271,273,
  	5,8,0,0,272,274,3,46,23,0,273,272,1,0,0,0,273,274,1,0,0,0,274,275,1,0,
  	0,0,275,280,5,9,0,0,276,277,3,44,22,0,277,278,3,42,21,0,278,280,1,0,0,
  	0,279,269,1,0,0,0,279,270,1,0,0,0,279,276,1,0,0,0,280,43,1,0,0,0,281,
  	282,7,1,0,0,282,45,1,0,0,0,283,288,3,32,16,0,284,285,5,1,0,0,285,287,
  	3,32,16,0,286,284,1,0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,0,
  	0,0,289,47,1,0,0,0,290,288,1,0,0,0,291,296,3,42,21,0,292,293,7,2,0,0,
  	293,295,3,42,21,0,294,292,1,0,0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,
  	297,1,0,0,0,297,49,1,0,0,0,298,296,1,0,0,0,299,304,3,48,24,0,300,301,
  	7,3,0,0,301,303,3,48,24,0,302,300,1,0,0,0,303,306,1,0,0,0,304,302,1,0,
  	0,0,304,305,1,0,0,0,305,51,1,0,0,0,306,304,1,0,0,0,307,312,3,50,25,0,
  	308,309,7,4,0,0,309,311,3,50,25,0,310,308,1,0,0,0,311,314,1,0,0,0,312,
  	310,1,0,0,0,312,313,1,0,0,0,313,53,1,0,0,0,314,312,1,0,0,0,315,320,3,
  	52,26,0,316,317,7,5,0,0,317,319,3,52,26,0,318,316,1,0,0,0,319,322,1,0,
  	0,0,320,318,1,0,0,0,320,321,1,0,0,0,321,55,1,0,0,0,322,320,1,0,0,0,323,
  	328,3,54,27,0,324,325,5,22,0,0,325,327,3,54,27,0,326,324,1,0,0,0,327,
  	330,1,0,0,0,328,326,1,0,0,0,328,329,1,0,0,0,329,57,1,0,0,0,330,328,1,
  	0,0,0,331,336,3,56,28,0,332,333,5,23,0,0,333,335,3,56,28,0,334,332,1,
  	0,0,0,335,338,1,0,0,0,336,334,1,0,0,0,336,337,1,0,0,0,337,59,1,0,0,0,
  	338,336,1,0,0,0,339,340,3,50,25,0,340,61,1,0,0,0,36,64,66,73,82,89,98,
  	111,114,117,125,137,142,151,154,157,163,171,178,191,194,200,207,226,240,
  	243,256,265,273,279,288,296,304,312,320,328,336
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  minicParserStaticData = staticData.release();
}

}

MiniCParser::MiniCParser(TokenStream *input) : MiniCParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

MiniCParser::MiniCParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  MiniCParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *minicParserStaticData->atn, minicParserStaticData->decisionToDFA, minicParserStaticData->sharedContextCache, options);
}

MiniCParser::~MiniCParser() {
  delete _interpreter;
}

const atn::ATN& MiniCParser::getATN() const {
  return *minicParserStaticData->atn;
}

std::string MiniCParser::getGrammarFileName() const {
  return "MiniC.g4";
}

const std::vector<std::string>& MiniCParser::getRuleNames() const {
  return minicParserStaticData->ruleNames;
}

const dfa::Vocabulary& MiniCParser::getVocabulary() const {
  return minicParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView MiniCParser::getSerializedATN() const {
  return minicParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

MiniCParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::CompUnitContext::EOF() {
  return getToken(MiniCParser::EOF, 0);
}

std::vector<MiniCParser::DeclContext *> MiniCParser::CompUnitContext::decl() {
  return getRuleContexts<MiniCParser::DeclContext>();
}

MiniCParser::DeclContext* MiniCParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<MiniCParser::DeclContext>(i);
}

std::vector<MiniCParser::FuncDefContext *> MiniCParser::CompUnitContext::funcDef() {
  return getRuleContexts<MiniCParser::FuncDefContext>();
}

MiniCParser::FuncDefContext* MiniCParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<MiniCParser::FuncDefContext>(i);
}


size_t MiniCParser::CompUnitContext::getRuleIndex() const {
  return MiniCParser::RuleCompUnit;
}


std::any MiniCParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::CompUnitContext* MiniCParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, MiniCParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16106127360) != 0)) {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(62);
        decl();
        break;
      }

      case 2: {
        setState(63);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(68);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(69);
    match(MiniCParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

MiniCParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::DeclContext::getRuleIndex() const {
  return MiniCParser::RuleDecl;
}

void MiniCParser::DeclContext::copyFrom(DeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstDeclarationContext ------------------------------------------------------------------

MiniCParser::ConstDeclContext* MiniCParser::ConstDeclarationContext::constDecl() {
  return getRuleContext<MiniCParser::ConstDeclContext>(0);
}

MiniCParser::ConstDeclarationContext::ConstDeclarationContext(DeclContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ConstDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitConstDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDeclarationContext ------------------------------------------------------------------

MiniCParser::VarDeclContext* MiniCParser::VarDeclarationContext::varDecl() {
  return getRuleContext<MiniCParser::VarDeclContext>(0);
}

MiniCParser::VarDeclarationContext::VarDeclarationContext(DeclContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::VarDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDeclaration(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::DeclContext* MiniCParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniCParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::CONST: {
        _localctx = _tracker.createInstance<MiniCParser::ConstDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(71);
        constDecl();
        break;
      }

      case MiniCParser::INT:
      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::VarDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(72);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

MiniCParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::ConstDeclContext::CONST() {
  return getToken(MiniCParser::CONST, 0);
}

MiniCParser::BTypeContext* MiniCParser::ConstDeclContext::bType() {
  return getRuleContext<MiniCParser::BTypeContext>(0);
}

std::vector<MiniCParser::ConstDefContext *> MiniCParser::ConstDeclContext::constDef() {
  return getRuleContexts<MiniCParser::ConstDefContext>();
}

MiniCParser::ConstDefContext* MiniCParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<MiniCParser::ConstDefContext>(i);
}


size_t MiniCParser::ConstDeclContext::getRuleIndex() const {
  return MiniCParser::RuleConstDecl;
}


std::any MiniCParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ConstDeclContext* MiniCParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, MiniCParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    match(MiniCParser::CONST);
    setState(76);
    bType();
    setState(77);
    constDef();
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__0) {
      setState(78);
      match(MiniCParser::T__0);
      setState(79);
      constDef();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
    match(MiniCParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

MiniCParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::BTypeContext::getRuleIndex() const {
  return MiniCParser::RuleBType;
}

void MiniCParser::BTypeContext::copyFrom(BTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FloatTypeContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::FloatTypeContext::FLOAT() {
  return getToken(MiniCParser::FLOAT, 0);
}

MiniCParser::FloatTypeContext::FloatTypeContext(BTypeContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::FloatTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFloatType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntTypeContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::IntTypeContext::INT() {
  return getToken(MiniCParser::INT, 0);
}

MiniCParser::IntTypeContext::IntTypeContext(BTypeContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::BTypeContext* MiniCParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, MiniCParser::RuleBType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(89);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::INT: {
        _localctx = _tracker.createInstance<MiniCParser::IntTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(87);
        match(MiniCParser::INT);
        break;
      }

      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::FloatTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(88);
        match(MiniCParser::FLOAT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

MiniCParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::ConstDefContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

MiniCParser::ConstInitValContext* MiniCParser::ConstDefContext::constInitVal() {
  return getRuleContext<MiniCParser::ConstInitValContext>(0);
}

std::vector<MiniCParser::ConstExpContext *> MiniCParser::ConstDefContext::constExp() {
  return getRuleContexts<MiniCParser::ConstExpContext>();
}

MiniCParser::ConstExpContext* MiniCParser::ConstDefContext::constExp(size_t i) {
  return getRuleContext<MiniCParser::ConstExpContext>(i);
}


size_t MiniCParser::ConstDefContext::getRuleIndex() const {
  return MiniCParser::RuleConstDef;
}


std::any MiniCParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ConstDefContext* MiniCParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 8, MiniCParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(MiniCParser::Ident);
    setState(98);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__2) {
      setState(92);
      match(MiniCParser::T__2);
      setState(93);
      constExp();
      setState(94);
      match(MiniCParser::T__3);
      setState(100);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(101);
    match(MiniCParser::T__4);
    setState(102);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

MiniCParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::ConstInitValContext::getRuleIndex() const {
  return MiniCParser::RuleConstInitVal;
}

void MiniCParser::ConstInitValContext::copyFrom(ConstInitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArrayConstInitValContext ------------------------------------------------------------------

std::vector<MiniCParser::ConstInitValContext *> MiniCParser::ArrayConstInitValContext::constInitVal() {
  return getRuleContexts<MiniCParser::ConstInitValContext>();
}

MiniCParser::ConstInitValContext* MiniCParser::ArrayConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<MiniCParser::ConstInitValContext>(i);
}

MiniCParser::ArrayConstInitValContext::ArrayConstInitValContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ArrayConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitArrayConstInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ScalarConstInitValContext ------------------------------------------------------------------

MiniCParser::ConstExpContext* MiniCParser::ScalarConstInitValContext::constExp() {
  return getRuleContext<MiniCParser::ConstExpContext>(0);
}

MiniCParser::ScalarConstInitValContext::ScalarConstInitValContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ScalarConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitScalarConstInitVal(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::ConstInitValContext* MiniCParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 10, MiniCParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__7:
      case MiniCParser::T__9:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::Ident:
      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        _localctx = _tracker.createInstance<MiniCParser::ScalarConstInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(104);
        constExp();
        break;
      }

      case MiniCParser::T__5: {
        _localctx = _tracker.createInstance<MiniCParser::ArrayConstInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(105);
        match(MiniCParser::T__5);
        setState(114);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120259091776) != 0)) {
          setState(106);
          constInitVal();
          setState(111);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MiniCParser::T__0) {
            setState(107);
            match(MiniCParser::T__0);
            setState(108);
            constInitVal();
            setState(113);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(116);
        match(MiniCParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

MiniCParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BTypeContext* MiniCParser::VarDeclContext::bType() {
  return getRuleContext<MiniCParser::BTypeContext>(0);
}

std::vector<MiniCParser::VarDefContext *> MiniCParser::VarDeclContext::varDef() {
  return getRuleContexts<MiniCParser::VarDefContext>();
}

MiniCParser::VarDefContext* MiniCParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<MiniCParser::VarDefContext>(i);
}


size_t MiniCParser::VarDeclContext::getRuleIndex() const {
  return MiniCParser::RuleVarDecl;
}


std::any MiniCParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDeclContext* MiniCParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 12, MiniCParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    bType();
    setState(120);
    varDef();
    setState(125);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__0) {
      setState(121);
      match(MiniCParser::T__0);
      setState(122);
      varDef();
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(128);
    match(MiniCParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

MiniCParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::VarDefContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

std::vector<MiniCParser::ConstExpContext *> MiniCParser::VarDefContext::constExp() {
  return getRuleContexts<MiniCParser::ConstExpContext>();
}

MiniCParser::ConstExpContext* MiniCParser::VarDefContext::constExp(size_t i) {
  return getRuleContext<MiniCParser::ConstExpContext>(i);
}

MiniCParser::InitValContext* MiniCParser::VarDefContext::initVal() {
  return getRuleContext<MiniCParser::InitValContext>(0);
}


size_t MiniCParser::VarDefContext::getRuleIndex() const {
  return MiniCParser::RuleVarDef;
}


std::any MiniCParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::VarDefContext* MiniCParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 14, MiniCParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(MiniCParser::Ident);
    setState(137);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__2) {
      setState(131);
      match(MiniCParser::T__2);
      setState(132);
      constExp();
      setState(133);
      match(MiniCParser::T__3);
      setState(139);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T__4) {
      setState(140);
      match(MiniCParser::T__4);
      setState(141);
      initVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

MiniCParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::InitValContext::getRuleIndex() const {
  return MiniCParser::RuleInitVal;
}

void MiniCParser::InitValContext::copyFrom(InitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ScalarInitValContext ------------------------------------------------------------------

MiniCParser::ExpContext* MiniCParser::ScalarInitValContext::exp() {
  return getRuleContext<MiniCParser::ExpContext>(0);
}

MiniCParser::ScalarInitValContext::ScalarInitValContext(InitValContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ScalarInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitScalarInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayInitValContext ------------------------------------------------------------------

std::vector<MiniCParser::InitValContext *> MiniCParser::ArrayInitValContext::initVal() {
  return getRuleContexts<MiniCParser::InitValContext>();
}

MiniCParser::InitValContext* MiniCParser::ArrayInitValContext::initVal(size_t i) {
  return getRuleContext<MiniCParser::InitValContext>(i);
}

MiniCParser::ArrayInitValContext::ArrayInitValContext(InitValContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ArrayInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitArrayInitVal(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::InitValContext* MiniCParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 16, MiniCParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__7:
      case MiniCParser::T__9:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::Ident:
      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        _localctx = _tracker.createInstance<MiniCParser::ScalarInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(144);
        exp();
        break;
      }

      case MiniCParser::T__5: {
        _localctx = _tracker.createInstance<MiniCParser::ArrayInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(145);
        match(MiniCParser::T__5);
        setState(154);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 120259091776) != 0)) {
          setState(146);
          initVal();
          setState(151);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MiniCParser::T__0) {
            setState(147);
            match(MiniCParser::T__0);
            setState(148);
            initVal();
            setState(153);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(156);
        match(MiniCParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

MiniCParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::FuncTypeContext* MiniCParser::FuncDefContext::funcType() {
  return getRuleContext<MiniCParser::FuncTypeContext>(0);
}

tree::TerminalNode* MiniCParser::FuncDefContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

MiniCParser::BlockContext* MiniCParser::FuncDefContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::FuncFParamsContext* MiniCParser::FuncDefContext::funcFParams() {
  return getRuleContext<MiniCParser::FuncFParamsContext>(0);
}


size_t MiniCParser::FuncDefContext::getRuleIndex() const {
  return MiniCParser::RuleFuncDef;
}


std::any MiniCParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncDefContext* MiniCParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 18, MiniCParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    funcType();
    setState(160);
    match(MiniCParser::Ident);
    setState(161);
    match(MiniCParser::T__7);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::INT

    || _la == MiniCParser::FLOAT) {
      setState(162);
      funcFParams();
    }
    setState(165);
    match(MiniCParser::T__8);
    setState(166);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

MiniCParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::FuncTypeContext::getRuleIndex() const {
  return MiniCParser::RuleFuncType;
}

void MiniCParser::FuncTypeContext::copyFrom(FuncTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntReturnTypeContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::IntReturnTypeContext::INT() {
  return getToken(MiniCParser::INT, 0);
}

MiniCParser::IntReturnTypeContext::IntReturnTypeContext(FuncTypeContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::IntReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitIntReturnType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FloatReturnTypeContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::FloatReturnTypeContext::FLOAT() {
  return getToken(MiniCParser::FLOAT, 0);
}

MiniCParser::FloatReturnTypeContext::FloatReturnTypeContext(FuncTypeContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::FloatReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFloatReturnType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VoidReturnTypeContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::VoidReturnTypeContext::VOID() {
  return getToken(MiniCParser::VOID, 0);
}

MiniCParser::VoidReturnTypeContext::VoidReturnTypeContext(FuncTypeContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::VoidReturnTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitVoidReturnType(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::FuncTypeContext* MiniCParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, MiniCParser::RuleFuncType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(171);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::VOID: {
        _localctx = _tracker.createInstance<MiniCParser::VoidReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(168);
        match(MiniCParser::VOID);
        break;
      }

      case MiniCParser::INT: {
        _localctx = _tracker.createInstance<MiniCParser::IntReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(169);
        match(MiniCParser::INT);
        break;
      }

      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::FloatReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(170);
        match(MiniCParser::FLOAT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

MiniCParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::FuncFParamContext *> MiniCParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<MiniCParser::FuncFParamContext>();
}

MiniCParser::FuncFParamContext* MiniCParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<MiniCParser::FuncFParamContext>(i);
}


size_t MiniCParser::FuncFParamsContext::getRuleIndex() const {
  return MiniCParser::RuleFuncFParams;
}


std::any MiniCParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncFParamsContext* MiniCParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 22, MiniCParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    funcFParam();
    setState(178);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__0) {
      setState(174);
      match(MiniCParser::T__0);
      setState(175);
      funcFParam();
      setState(180);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

MiniCParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::BTypeContext* MiniCParser::FuncFParamContext::bType() {
  return getRuleContext<MiniCParser::BTypeContext>(0);
}

tree::TerminalNode* MiniCParser::FuncFParamContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

std::vector<MiniCParser::ExpContext *> MiniCParser::FuncFParamContext::exp() {
  return getRuleContexts<MiniCParser::ExpContext>();
}

MiniCParser::ExpContext* MiniCParser::FuncFParamContext::exp(size_t i) {
  return getRuleContext<MiniCParser::ExpContext>(i);
}


size_t MiniCParser::FuncFParamContext::getRuleIndex() const {
  return MiniCParser::RuleFuncFParam;
}


std::any MiniCParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncFParamContext* MiniCParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 24, MiniCParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(181);
    bType();
    setState(182);
    match(MiniCParser::Ident);
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T__2) {
      setState(183);
      match(MiniCParser::T__2);
      setState(184);
      match(MiniCParser::T__3);
      setState(191);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MiniCParser::T__2) {
        setState(185);
        match(MiniCParser::T__2);
        setState(186);
        exp();
        setState(187);
        match(MiniCParser::T__3);
        setState(193);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

MiniCParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::BlockItemContext *> MiniCParser::BlockContext::blockItem() {
  return getRuleContexts<MiniCParser::BlockItemContext>();
}

MiniCParser::BlockItemContext* MiniCParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<MiniCParser::BlockItemContext>(i);
}


size_t MiniCParser::BlockContext::getRuleIndex() const {
  return MiniCParser::RuleBlock;
}


std::any MiniCParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::BlockContext* MiniCParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 26, MiniCParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(196);
    match(MiniCParser::T__5);
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 128698031428) != 0)) {
      setState(197);
      blockItem();
      setState(202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(203);
    match(MiniCParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

MiniCParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::BlockItemContext::getRuleIndex() const {
  return MiniCParser::RuleBlockItem;
}

void MiniCParser::BlockItemContext::copyFrom(BlockItemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BlockDeclarationContext ------------------------------------------------------------------

MiniCParser::DeclContext* MiniCParser::BlockDeclarationContext::decl() {
  return getRuleContext<MiniCParser::DeclContext>(0);
}

MiniCParser::BlockDeclarationContext::BlockDeclarationContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BlockDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockDeclaration(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStatementContext ------------------------------------------------------------------

MiniCParser::StmtContext* MiniCParser::BlockStatementContext::stmt() {
  return getRuleContext<MiniCParser::StmtContext>(0);
}

MiniCParser::BlockStatementContext::BlockStatementContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::BlockItemContext* MiniCParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 28, MiniCParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(207);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::CONST:
      case MiniCParser::INT:
      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::BlockDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(205);
        decl();
        break;
      }

      case MiniCParser::T__1:
      case MiniCParser::T__5:
      case MiniCParser::T__7:
      case MiniCParser::T__9:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::BREAK:
      case MiniCParser::CONTINUE:
      case MiniCParser::IF:
      case MiniCParser::WHILE:
      case MiniCParser::RETURN:
      case MiniCParser::Ident:
      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        _localctx = _tracker.createInstance<MiniCParser::BlockStatementContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(206);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

MiniCParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::StmtContext::getRuleIndex() const {
  return MiniCParser::RuleStmt;
}

void MiniCParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EmptyStatementContext ------------------------------------------------------------------

MiniCParser::EmptyStatementContext::EmptyStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::EmptyStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitEmptyStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileLoopStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::WhileLoopStatementContext::WHILE() {
  return getToken(MiniCParser::WHILE, 0);
}

MiniCParser::CondContext* MiniCParser::WhileLoopStatementContext::cond() {
  return getRuleContext<MiniCParser::CondContext>(0);
}

MiniCParser::StmtContext* MiniCParser::WhileLoopStatementContext::stmt() {
  return getRuleContext<MiniCParser::StmtContext>(0);
}

MiniCParser::WhileLoopStatementContext::WhileLoopStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::WhileLoopStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitWhileLoopStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentStatementContext ------------------------------------------------------------------

MiniCParser::LValContext* MiniCParser::AssignmentStatementContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

MiniCParser::ExpContext* MiniCParser::AssignmentStatementContext::exp() {
  return getRuleContext<MiniCParser::ExpContext>(0);
}

MiniCParser::AssignmentStatementContext::AssignmentStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::AssignmentStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAssignmentStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NestedBlockStatementContext ------------------------------------------------------------------

MiniCParser::BlockContext* MiniCParser::NestedBlockStatementContext::block() {
  return getRuleContext<MiniCParser::BlockContext>(0);
}

MiniCParser::NestedBlockStatementContext::NestedBlockStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::NestedBlockStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitNestedBlockStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfElseStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::IfElseStatementContext::IF() {
  return getToken(MiniCParser::IF, 0);
}

MiniCParser::CondContext* MiniCParser::IfElseStatementContext::cond() {
  return getRuleContext<MiniCParser::CondContext>(0);
}

std::vector<MiniCParser::StmtContext *> MiniCParser::IfElseStatementContext::stmt() {
  return getRuleContexts<MiniCParser::StmtContext>();
}

MiniCParser::StmtContext* MiniCParser::IfElseStatementContext::stmt(size_t i) {
  return getRuleContext<MiniCParser::StmtContext>(i);
}

tree::TerminalNode* MiniCParser::IfElseStatementContext::ELSE() {
  return getToken(MiniCParser::ELSE, 0);
}

MiniCParser::IfElseStatementContext::IfElseStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::IfElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitIfElseStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::BreakStatementContext::BREAK() {
  return getToken(MiniCParser::BREAK, 0);
}

MiniCParser::BreakStatementContext::BreakStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::BreakStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitBreakStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionStatementContext ------------------------------------------------------------------

MiniCParser::ExpContext* MiniCParser::ExpressionStatementContext::exp() {
  return getRuleContext<MiniCParser::ExpContext>(0);
}

MiniCParser::ExpressionStatementContext::ExpressionStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ExpressionStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExpressionStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContinueStatementContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ContinueStatementContext::CONTINUE() {
  return getToken(MiniCParser::CONTINUE, 0);
}

MiniCParser::ContinueStatementContext::ContinueStatementContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ContinueStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitContinueStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::ReturnStmtContext::RETURN() {
  return getToken(MiniCParser::RETURN, 0);
}

MiniCParser::ExpContext* MiniCParser::ReturnStmtContext::exp() {
  return getRuleContext<MiniCParser::ExpContext>(0);
}

MiniCParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::StmtContext* MiniCParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 30, MiniCParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(243);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(209);
      lVal();
      setState(210);
      match(MiniCParser::T__4);
      setState(211);
      exp();
      setState(212);
      match(MiniCParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::EmptyStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(214);
      match(MiniCParser::T__1);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(215);
      exp();
      setState(216);
      match(MiniCParser::T__1);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MiniCParser::NestedBlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(218);
      block();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MiniCParser::IfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(219);
      match(MiniCParser::IF);
      setState(220);
      match(MiniCParser::T__7);
      setState(221);
      cond();
      setState(222);
      match(MiniCParser::T__8);
      setState(223);
      stmt();
      setState(226);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(224);
        match(MiniCParser::ELSE);
        setState(225);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<MiniCParser::WhileLoopStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(228);
      match(MiniCParser::WHILE);
      setState(229);
      match(MiniCParser::T__7);
      setState(230);
      cond();
      setState(231);
      match(MiniCParser::T__8);
      setState(232);
      stmt();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MiniCParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(234);
      match(MiniCParser::BREAK);
      setState(235);
      match(MiniCParser::T__1);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MiniCParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(236);
      match(MiniCParser::CONTINUE);
      setState(237);
      match(MiniCParser::T__1);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MiniCParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(238);
      match(MiniCParser::RETURN);
      setState(240);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120259091712) != 0)) {
        setState(239);
        exp();
      }
      setState(242);
      match(MiniCParser::T__1);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

MiniCParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::LOrExpContext* MiniCParser::ExpContext::lOrExp() {
  return getRuleContext<MiniCParser::LOrExpContext>(0);
}


size_t MiniCParser::ExpContext::getRuleIndex() const {
  return MiniCParser::RuleExp;
}


std::any MiniCParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ExpContext* MiniCParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 32, MiniCParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(245);
    lOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

MiniCParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::LOrExpContext* MiniCParser::CondContext::lOrExp() {
  return getRuleContext<MiniCParser::LOrExpContext>(0);
}


size_t MiniCParser::CondContext::getRuleIndex() const {
  return MiniCParser::RuleCond;
}


std::any MiniCParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::CondContext* MiniCParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 34, MiniCParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(247);
    lOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

MiniCParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::LValContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

std::vector<MiniCParser::ExpContext *> MiniCParser::LValContext::exp() {
  return getRuleContexts<MiniCParser::ExpContext>();
}

MiniCParser::ExpContext* MiniCParser::LValContext::exp(size_t i) {
  return getRuleContext<MiniCParser::ExpContext>(i);
}


size_t MiniCParser::LValContext::getRuleIndex() const {
  return MiniCParser::RuleLVal;
}


std::any MiniCParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LValContext* MiniCParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 36, MiniCParser::RuleLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(249);
    match(MiniCParser::Ident);
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__2) {
      setState(250);
      match(MiniCParser::T__2);
      setState(251);
      exp();
      setState(252);
      match(MiniCParser::T__3);
      setState(258);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::ExpContext* MiniCParser::PrimaryExpContext::exp() {
  return getRuleContext<MiniCParser::ExpContext>(0);
}

MiniCParser::LValContext* MiniCParser::PrimaryExpContext::lVal() {
  return getRuleContext<MiniCParser::LValContext>(0);
}

MiniCParser::NumberContext* MiniCParser::PrimaryExpContext::number() {
  return getRuleContext<MiniCParser::NumberContext>(0);
}


size_t MiniCParser::PrimaryExpContext::getRuleIndex() const {
  return MiniCParser::RulePrimaryExp;
}


std::any MiniCParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::PrimaryExpContext* MiniCParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 38, MiniCParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(265);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__7: {
        enterOuterAlt(_localctx, 1);
        setState(259);
        match(MiniCParser::T__7);
        setState(260);
        exp();
        setState(261);
        match(MiniCParser::T__8);
        break;
      }

      case MiniCParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(263);
        lVal();
        break;
      }

      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        enterOuterAlt(_localctx, 3);
        setState(264);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

MiniCParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::NumberContext::IntConst() {
  return getToken(MiniCParser::IntConst, 0);
}

tree::TerminalNode* MiniCParser::NumberContext::FloatConst() {
  return getToken(MiniCParser::FloatConst, 0);
}


size_t MiniCParser::NumberContext::getRuleIndex() const {
  return MiniCParser::RuleNumber;
}


std::any MiniCParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::NumberContext* MiniCParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 40, MiniCParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    _la = _input->LA(1);
    if (!(_la == MiniCParser::IntConst

    || _la == MiniCParser::FloatConst)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

MiniCParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::UnaryExpContext::getRuleIndex() const {
  return MiniCParser::RuleUnaryExp;
}

void MiniCParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryExpFuncCallContext ------------------------------------------------------------------

tree::TerminalNode* MiniCParser::UnaryExpFuncCallContext::Ident() {
  return getToken(MiniCParser::Ident, 0);
}

MiniCParser::FuncRParamsContext* MiniCParser::UnaryExpFuncCallContext::funcRParams() {
  return getRuleContext<MiniCParser::FuncRParamsContext>(0);
}

MiniCParser::UnaryExpFuncCallContext::UnaryExpFuncCallContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::UnaryExpFuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitUnaryExpFuncCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryExpPrimaryContext ------------------------------------------------------------------

MiniCParser::PrimaryExpContext* MiniCParser::UnaryExpPrimaryContext::primaryExp() {
  return getRuleContext<MiniCParser::PrimaryExpContext>(0);
}

MiniCParser::UnaryExpPrimaryContext::UnaryExpPrimaryContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::UnaryExpPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitUnaryExpPrimary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryOpUnaryExpContext ------------------------------------------------------------------

MiniCParser::UnaryOpContext* MiniCParser::UnaryOpUnaryExpContext::unaryOp() {
  return getRuleContext<MiniCParser::UnaryOpContext>(0);
}

MiniCParser::UnaryExpContext* MiniCParser::UnaryOpUnaryExpContext::unaryExp() {
  return getRuleContext<MiniCParser::UnaryExpContext>(0);
}

MiniCParser::UnaryOpUnaryExpContext::UnaryOpUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any MiniCParser::UnaryOpUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitUnaryOpUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
MiniCParser::UnaryExpContext* MiniCParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 42, MiniCParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(279);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryExpPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(269);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryExpFuncCallContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(270);
      match(MiniCParser::Ident);
      setState(271);
      match(MiniCParser::T__7);
      setState(273);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 120259091712) != 0)) {
        setState(272);
        funcRParams();
      }
      setState(275);
      match(MiniCParser::T__8);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryOpUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(276);
      unaryOp();
      setState(277);
      unaryExp();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

MiniCParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MiniCParser::UnaryOpContext::getRuleIndex() const {
  return MiniCParser::RuleUnaryOp;
}


std::any MiniCParser::UnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitUnaryOp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::UnaryOpContext* MiniCParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 44, MiniCParser::RuleUnaryOp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7168) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

MiniCParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::ExpContext *> MiniCParser::FuncRParamsContext::exp() {
  return getRuleContexts<MiniCParser::ExpContext>();
}

MiniCParser::ExpContext* MiniCParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<MiniCParser::ExpContext>(i);
}


size_t MiniCParser::FuncRParamsContext::getRuleIndex() const {
  return MiniCParser::RuleFuncRParams;
}


std::any MiniCParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::FuncRParamsContext* MiniCParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 46, MiniCParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(283);
    exp();
    setState(288);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__0) {
      setState(284);
      match(MiniCParser::T__0);
      setState(285);
      exp();
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

MiniCParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::UnaryExpContext *> MiniCParser::MulExpContext::unaryExp() {
  return getRuleContexts<MiniCParser::UnaryExpContext>();
}

MiniCParser::UnaryExpContext* MiniCParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<MiniCParser::UnaryExpContext>(i);
}


size_t MiniCParser::MulExpContext::getRuleIndex() const {
  return MiniCParser::RuleMulExp;
}


std::any MiniCParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::MulExpContext* MiniCParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 48, MiniCParser::RuleMulExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    unaryExp();
    setState(296);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 57344) != 0)) {
      setState(292);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 57344) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(293);
      unaryExp();
      setState(298);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

MiniCParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::MulExpContext *> MiniCParser::AddExpContext::mulExp() {
  return getRuleContexts<MiniCParser::MulExpContext>();
}

MiniCParser::MulExpContext* MiniCParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<MiniCParser::MulExpContext>(i);
}


size_t MiniCParser::AddExpContext::getRuleIndex() const {
  return MiniCParser::RuleAddExp;
}


std::any MiniCParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::AddExpContext* MiniCParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 50, MiniCParser::RuleAddExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(299);
    mulExp();
    setState(304);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__9

    || _la == MiniCParser::T__10) {
      setState(300);
      _la = _input->LA(1);
      if (!(_la == MiniCParser::T__9

      || _la == MiniCParser::T__10)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(301);
      mulExp();
      setState(306);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

MiniCParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::AddExpContext *> MiniCParser::RelExpContext::addExp() {
  return getRuleContexts<MiniCParser::AddExpContext>();
}

MiniCParser::AddExpContext* MiniCParser::RelExpContext::addExp(size_t i) {
  return getRuleContext<MiniCParser::AddExpContext>(i);
}


size_t MiniCParser::RelExpContext::getRuleIndex() const {
  return MiniCParser::RuleRelExp;
}


std::any MiniCParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::RelExpContext* MiniCParser::relExp() {
  RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, getState());
  enterRule(_localctx, 52, MiniCParser::RuleRelExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    addExp();
    setState(312);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 983040) != 0)) {
      setState(308);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 983040) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(309);
      addExp();
      setState(314);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

MiniCParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::RelExpContext *> MiniCParser::EqExpContext::relExp() {
  return getRuleContexts<MiniCParser::RelExpContext>();
}

MiniCParser::RelExpContext* MiniCParser::EqExpContext::relExp(size_t i) {
  return getRuleContext<MiniCParser::RelExpContext>(i);
}


size_t MiniCParser::EqExpContext::getRuleIndex() const {
  return MiniCParser::RuleEqExp;
}


std::any MiniCParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::EqExpContext* MiniCParser::eqExp() {
  EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, getState());
  enterRule(_localctx, 54, MiniCParser::RuleEqExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(315);
    relExp();
    setState(320);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__19

    || _la == MiniCParser::T__20) {
      setState(316);
      _la = _input->LA(1);
      if (!(_la == MiniCParser::T__19

      || _la == MiniCParser::T__20)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(317);
      relExp();
      setState(322);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

MiniCParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::EqExpContext *> MiniCParser::LAndExpContext::eqExp() {
  return getRuleContexts<MiniCParser::EqExpContext>();
}

MiniCParser::EqExpContext* MiniCParser::LAndExpContext::eqExp(size_t i) {
  return getRuleContext<MiniCParser::EqExpContext>(i);
}


size_t MiniCParser::LAndExpContext::getRuleIndex() const {
  return MiniCParser::RuleLAndExp;
}


std::any MiniCParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LAndExpContext* MiniCParser::lAndExp() {
  LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, getState());
  enterRule(_localctx, 56, MiniCParser::RuleLAndExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(323);
    eqExp();
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__21) {
      setState(324);
      match(MiniCParser::T__21);
      setState(325);
      eqExp();
      setState(330);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

MiniCParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MiniCParser::LAndExpContext *> MiniCParser::LOrExpContext::lAndExp() {
  return getRuleContexts<MiniCParser::LAndExpContext>();
}

MiniCParser::LAndExpContext* MiniCParser::LOrExpContext::lAndExp(size_t i) {
  return getRuleContext<MiniCParser::LAndExpContext>(i);
}


size_t MiniCParser::LOrExpContext::getRuleIndex() const {
  return MiniCParser::RuleLOrExp;
}


std::any MiniCParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::LOrExpContext* MiniCParser::lOrExp() {
  LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, getState());
  enterRule(_localctx, 58, MiniCParser::RuleLOrExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    lAndExp();
    setState(336);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__22) {
      setState(332);
      match(MiniCParser::T__22);
      setState(333);
      lAndExp();
      setState(338);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

MiniCParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MiniCParser::AddExpContext* MiniCParser::ConstExpContext::addExp() {
  return getRuleContext<MiniCParser::AddExpContext>(0);
}


size_t MiniCParser::ConstExpContext::getRuleIndex() const {
  return MiniCParser::RuleConstExp;
}


std::any MiniCParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::ConstExpContext* MiniCParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 60, MiniCParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(339);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void MiniCParser::initialize() {
  ::antlr4::internal::call_once(minicParserOnceFlag, minicParserInitialize);
}
