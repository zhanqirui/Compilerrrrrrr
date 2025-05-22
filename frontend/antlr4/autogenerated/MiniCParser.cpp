
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
      "compUnit", "defineDirective", "decl", "constDecl", "bType", "constDef", 
      "constInitVal", "varDecl", "varDef", "initVal", "funcDef", "funcType", 
      "funcFParams", "funcFParam", "block", "blockItem", "stmt", "exp", 
      "cond", "lVal", "primaryExp", "number", "unaryExp", "unaryOp", "funcRParams", 
      "mulExp", "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp"
    },
    std::vector<std::string>{
      "", "'#'", "','", "';'", "'['", "']'", "'='", "'{'", "'}'", "'('", 
      "')'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", "'>'", "'<='", 
      "'>='", "'=='", "'!='", "'&&'", "'||'", "'define'", "'break'", "'continue'", 
      "'if'", "'else'", "'while'", "'return'", "'const'", "'int'", "'float'", 
      "'void'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "DEFINE", "BREAK", "CONTINUE", "IF", 
      "ELSE", "WHILE", "RETURN", "CONST", "INT", "FLOAT", "VOID", "Ident", 
      "IntConst", "FloatConst", "StringConst", "Whitespace", "BlockComment", 
      "LineComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,42,350,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,1,0,1,0,5,0,68,8,0,10,0,12,0,71,
  	9,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,3,2,82,8,2,1,3,1,3,1,3,1,3,1,
  	3,5,3,89,8,3,10,3,12,3,92,9,3,1,3,1,3,1,4,1,4,3,4,98,8,4,1,5,1,5,1,5,
  	1,5,1,5,5,5,105,8,5,10,5,12,5,108,9,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,
  	5,6,118,8,6,10,6,12,6,121,9,6,3,6,123,8,6,1,6,3,6,126,8,6,1,7,1,7,1,7,
  	1,7,5,7,132,8,7,10,7,12,7,135,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,5,8,144,
  	8,8,10,8,12,8,147,9,8,1,8,1,8,3,8,151,8,8,1,9,1,9,1,9,1,9,1,9,5,9,158,
  	8,9,10,9,12,9,161,9,9,3,9,163,8,9,1,9,3,9,166,8,9,1,10,1,10,1,10,1,10,
  	3,10,172,8,10,1,10,1,10,1,10,1,11,1,11,1,11,3,11,180,8,11,1,12,1,12,1,
  	12,5,12,185,8,12,10,12,12,12,188,9,12,1,13,1,13,1,13,1,13,1,13,1,13,1,
  	13,1,13,5,13,198,8,13,10,13,12,13,201,9,13,3,13,203,8,13,1,14,1,14,5,
  	14,207,8,14,10,14,12,14,210,9,14,1,14,1,14,1,15,1,15,3,15,216,8,15,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,3,16,235,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,3,16,249,8,16,1,16,3,16,252,8,16,1,17,1,17,1,18,1,18,
  	1,19,1,19,1,19,1,19,1,19,5,19,263,8,19,10,19,12,19,266,9,19,1,20,1,20,
  	1,20,1,20,1,20,1,20,3,20,274,8,20,1,21,1,21,1,22,1,22,1,22,1,22,3,22,
  	282,8,22,1,22,1,22,1,22,1,22,3,22,288,8,22,1,23,1,23,1,24,1,24,1,24,5,
  	24,295,8,24,10,24,12,24,298,9,24,1,25,1,25,1,25,5,25,303,8,25,10,25,12,
  	25,306,9,25,1,26,1,26,1,26,5,26,311,8,26,10,26,12,26,314,9,26,1,27,1,
  	27,1,27,5,27,319,8,27,10,27,12,27,322,9,27,1,28,1,28,1,28,5,28,327,8,
  	28,10,28,12,28,330,9,28,1,29,1,29,1,29,5,29,335,8,29,10,29,12,29,338,
  	9,29,1,30,1,30,1,30,5,30,343,8,30,10,30,12,30,346,9,30,1,31,1,31,1,31,
  	0,0,32,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,
  	46,48,50,52,54,56,58,60,62,0,7,1,0,36,39,1,0,37,38,1,0,11,13,1,0,14,16,
  	1,0,11,12,1,0,17,20,1,0,21,22,364,0,69,1,0,0,0,2,74,1,0,0,0,4,81,1,0,
  	0,0,6,83,1,0,0,0,8,97,1,0,0,0,10,99,1,0,0,0,12,125,1,0,0,0,14,127,1,0,
  	0,0,16,138,1,0,0,0,18,165,1,0,0,0,20,167,1,0,0,0,22,179,1,0,0,0,24,181,
  	1,0,0,0,26,189,1,0,0,0,28,204,1,0,0,0,30,215,1,0,0,0,32,251,1,0,0,0,34,
  	253,1,0,0,0,36,255,1,0,0,0,38,257,1,0,0,0,40,273,1,0,0,0,42,275,1,0,0,
  	0,44,287,1,0,0,0,46,289,1,0,0,0,48,291,1,0,0,0,50,299,1,0,0,0,52,307,
  	1,0,0,0,54,315,1,0,0,0,56,323,1,0,0,0,58,331,1,0,0,0,60,339,1,0,0,0,62,
  	347,1,0,0,0,64,68,3,2,1,0,65,68,3,4,2,0,66,68,3,20,10,0,67,64,1,0,0,0,
  	67,65,1,0,0,0,67,66,1,0,0,0,68,71,1,0,0,0,69,67,1,0,0,0,69,70,1,0,0,0,
  	70,72,1,0,0,0,71,69,1,0,0,0,72,73,5,0,0,1,73,1,1,0,0,0,74,75,5,1,0,0,
  	75,76,5,25,0,0,76,77,5,36,0,0,77,78,7,0,0,0,78,3,1,0,0,0,79,82,3,6,3,
  	0,80,82,3,14,7,0,81,79,1,0,0,0,81,80,1,0,0,0,82,5,1,0,0,0,83,84,5,32,
  	0,0,84,85,3,8,4,0,85,90,3,10,5,0,86,87,5,2,0,0,87,89,3,10,5,0,88,86,1,
  	0,0,0,89,92,1,0,0,0,90,88,1,0,0,0,90,91,1,0,0,0,91,93,1,0,0,0,92,90,1,
  	0,0,0,93,94,5,3,0,0,94,7,1,0,0,0,95,98,5,33,0,0,96,98,5,34,0,0,97,95,
  	1,0,0,0,97,96,1,0,0,0,98,9,1,0,0,0,99,106,5,36,0,0,100,101,5,4,0,0,101,
  	102,3,62,31,0,102,103,5,5,0,0,103,105,1,0,0,0,104,100,1,0,0,0,105,108,
  	1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,0,107,109,1,0,0,0,108,106,1,0,0,
  	0,109,110,5,6,0,0,110,111,3,12,6,0,111,11,1,0,0,0,112,126,3,62,31,0,113,
  	122,5,7,0,0,114,119,3,12,6,0,115,116,5,2,0,0,116,118,3,12,6,0,117,115,
  	1,0,0,0,118,121,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,123,1,0,0,
  	0,121,119,1,0,0,0,122,114,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,
  	126,5,8,0,0,125,112,1,0,0,0,125,113,1,0,0,0,126,13,1,0,0,0,127,128,3,
  	8,4,0,128,133,3,16,8,0,129,130,5,2,0,0,130,132,3,16,8,0,131,129,1,0,0,
  	0,132,135,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,136,1,0,0,0,135,
  	133,1,0,0,0,136,137,5,3,0,0,137,15,1,0,0,0,138,145,5,36,0,0,139,140,5,
  	4,0,0,140,141,3,62,31,0,141,142,5,5,0,0,142,144,1,0,0,0,143,139,1,0,0,
  	0,144,147,1,0,0,0,145,143,1,0,0,0,145,146,1,0,0,0,146,150,1,0,0,0,147,
  	145,1,0,0,0,148,149,5,6,0,0,149,151,3,18,9,0,150,148,1,0,0,0,150,151,
  	1,0,0,0,151,17,1,0,0,0,152,166,3,34,17,0,153,162,5,7,0,0,154,159,3,18,
  	9,0,155,156,5,2,0,0,156,158,3,18,9,0,157,155,1,0,0,0,158,161,1,0,0,0,
  	159,157,1,0,0,0,159,160,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,162,154,
  	1,0,0,0,162,163,1,0,0,0,163,164,1,0,0,0,164,166,5,8,0,0,165,152,1,0,0,
  	0,165,153,1,0,0,0,166,19,1,0,0,0,167,168,3,22,11,0,168,169,5,36,0,0,169,
  	171,5,9,0,0,170,172,3,24,12,0,171,170,1,0,0,0,171,172,1,0,0,0,172,173,
  	1,0,0,0,173,174,5,10,0,0,174,175,3,28,14,0,175,21,1,0,0,0,176,180,5,35,
  	0,0,177,180,5,33,0,0,178,180,5,34,0,0,179,176,1,0,0,0,179,177,1,0,0,0,
  	179,178,1,0,0,0,180,23,1,0,0,0,181,186,3,26,13,0,182,183,5,2,0,0,183,
  	185,3,26,13,0,184,182,1,0,0,0,185,188,1,0,0,0,186,184,1,0,0,0,186,187,
  	1,0,0,0,187,25,1,0,0,0,188,186,1,0,0,0,189,190,3,8,4,0,190,202,5,36,0,
  	0,191,192,5,4,0,0,192,199,5,5,0,0,193,194,5,4,0,0,194,195,3,34,17,0,195,
  	196,5,5,0,0,196,198,1,0,0,0,197,193,1,0,0,0,198,201,1,0,0,0,199,197,1,
  	0,0,0,199,200,1,0,0,0,200,203,1,0,0,0,201,199,1,0,0,0,202,191,1,0,0,0,
  	202,203,1,0,0,0,203,27,1,0,0,0,204,208,5,7,0,0,205,207,3,30,15,0,206,
  	205,1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,211,1,
  	0,0,0,210,208,1,0,0,0,211,212,5,8,0,0,212,29,1,0,0,0,213,216,3,4,2,0,
  	214,216,3,32,16,0,215,213,1,0,0,0,215,214,1,0,0,0,216,31,1,0,0,0,217,
  	218,3,38,19,0,218,219,5,6,0,0,219,220,3,34,17,0,220,221,5,3,0,0,221,252,
  	1,0,0,0,222,252,5,3,0,0,223,224,3,34,17,0,224,225,5,3,0,0,225,252,1,0,
  	0,0,226,252,3,28,14,0,227,228,5,28,0,0,228,229,5,9,0,0,229,230,3,36,18,
  	0,230,231,5,10,0,0,231,234,3,32,16,0,232,233,5,29,0,0,233,235,3,32,16,
  	0,234,232,1,0,0,0,234,235,1,0,0,0,235,252,1,0,0,0,236,237,5,30,0,0,237,
  	238,5,9,0,0,238,239,3,36,18,0,239,240,5,10,0,0,240,241,3,32,16,0,241,
  	252,1,0,0,0,242,243,5,26,0,0,243,252,5,3,0,0,244,245,5,27,0,0,245,252,
  	5,3,0,0,246,248,5,31,0,0,247,249,3,34,17,0,248,247,1,0,0,0,248,249,1,
  	0,0,0,249,250,1,0,0,0,250,252,5,3,0,0,251,217,1,0,0,0,251,222,1,0,0,0,
  	251,223,1,0,0,0,251,226,1,0,0,0,251,227,1,0,0,0,251,236,1,0,0,0,251,242,
  	1,0,0,0,251,244,1,0,0,0,251,246,1,0,0,0,252,33,1,0,0,0,253,254,3,60,30,
  	0,254,35,1,0,0,0,255,256,3,60,30,0,256,37,1,0,0,0,257,264,5,36,0,0,258,
  	259,5,4,0,0,259,260,3,34,17,0,260,261,5,5,0,0,261,263,1,0,0,0,262,258,
  	1,0,0,0,263,266,1,0,0,0,264,262,1,0,0,0,264,265,1,0,0,0,265,39,1,0,0,
  	0,266,264,1,0,0,0,267,268,5,9,0,0,268,269,3,34,17,0,269,270,5,10,0,0,
  	270,274,1,0,0,0,271,274,3,38,19,0,272,274,3,42,21,0,273,267,1,0,0,0,273,
  	271,1,0,0,0,273,272,1,0,0,0,274,41,1,0,0,0,275,276,7,1,0,0,276,43,1,0,
  	0,0,277,288,3,40,20,0,278,279,5,36,0,0,279,281,5,9,0,0,280,282,3,48,24,
  	0,281,280,1,0,0,0,281,282,1,0,0,0,282,283,1,0,0,0,283,288,5,10,0,0,284,
  	285,3,46,23,0,285,286,3,44,22,0,286,288,1,0,0,0,287,277,1,0,0,0,287,278,
  	1,0,0,0,287,284,1,0,0,0,288,45,1,0,0,0,289,290,7,2,0,0,290,47,1,0,0,0,
  	291,296,3,34,17,0,292,293,5,2,0,0,293,295,3,34,17,0,294,292,1,0,0,0,295,
  	298,1,0,0,0,296,294,1,0,0,0,296,297,1,0,0,0,297,49,1,0,0,0,298,296,1,
  	0,0,0,299,304,3,44,22,0,300,301,7,3,0,0,301,303,3,44,22,0,302,300,1,0,
  	0,0,303,306,1,0,0,0,304,302,1,0,0,0,304,305,1,0,0,0,305,51,1,0,0,0,306,
  	304,1,0,0,0,307,312,3,50,25,0,308,309,7,4,0,0,309,311,3,50,25,0,310,308,
  	1,0,0,0,311,314,1,0,0,0,312,310,1,0,0,0,312,313,1,0,0,0,313,53,1,0,0,
  	0,314,312,1,0,0,0,315,320,3,52,26,0,316,317,7,5,0,0,317,319,3,52,26,0,
  	318,316,1,0,0,0,319,322,1,0,0,0,320,318,1,0,0,0,320,321,1,0,0,0,321,55,
  	1,0,0,0,322,320,1,0,0,0,323,328,3,54,27,0,324,325,7,6,0,0,325,327,3,54,
  	27,0,326,324,1,0,0,0,327,330,1,0,0,0,328,326,1,0,0,0,328,329,1,0,0,0,
  	329,57,1,0,0,0,330,328,1,0,0,0,331,336,3,56,28,0,332,333,5,23,0,0,333,
  	335,3,56,28,0,334,332,1,0,0,0,335,338,1,0,0,0,336,334,1,0,0,0,336,337,
  	1,0,0,0,337,59,1,0,0,0,338,336,1,0,0,0,339,344,3,58,29,0,340,341,5,24,
  	0,0,341,343,3,58,29,0,342,340,1,0,0,0,343,346,1,0,0,0,344,342,1,0,0,0,
  	344,345,1,0,0,0,345,61,1,0,0,0,346,344,1,0,0,0,347,348,3,52,26,0,348,
  	63,1,0,0,0,36,67,69,81,90,97,106,119,122,125,133,145,150,159,162,165,
  	171,179,186,199,202,208,215,234,248,251,264,273,281,287,296,304,312,320,
  	328,336,344
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

std::vector<MiniCParser::DefineDirectiveContext *> MiniCParser::CompUnitContext::defineDirective() {
  return getRuleContexts<MiniCParser::DefineDirectiveContext>();
}

MiniCParser::DefineDirectiveContext* MiniCParser::CompUnitContext::defineDirective(size_t i) {
  return getRuleContext<MiniCParser::DefineDirectiveContext>(i);
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
    setState(69);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64424509442) != 0)) {
      setState(67);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(64);
        defineDirective();
        break;
      }

      case 2: {
        setState(65);
        decl();
        break;
      }

      case 3: {
        setState(66);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(71);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(72);
    match(MiniCParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefineDirectiveContext ------------------------------------------------------------------

MiniCParser::DefineDirectiveContext::DefineDirectiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MiniCParser::DefineDirectiveContext::DEFINE() {
  return getToken(MiniCParser::DEFINE, 0);
}

std::vector<tree::TerminalNode *> MiniCParser::DefineDirectiveContext::Ident() {
  return getTokens(MiniCParser::Ident);
}

tree::TerminalNode* MiniCParser::DefineDirectiveContext::Ident(size_t i) {
  return getToken(MiniCParser::Ident, i);
}

tree::TerminalNode* MiniCParser::DefineDirectiveContext::IntConst() {
  return getToken(MiniCParser::IntConst, 0);
}

tree::TerminalNode* MiniCParser::DefineDirectiveContext::FloatConst() {
  return getToken(MiniCParser::FloatConst, 0);
}

tree::TerminalNode* MiniCParser::DefineDirectiveContext::StringConst() {
  return getToken(MiniCParser::StringConst, 0);
}


size_t MiniCParser::DefineDirectiveContext::getRuleIndex() const {
  return MiniCParser::RuleDefineDirective;
}


std::any MiniCParser::DefineDirectiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<MiniCVisitor*>(visitor))
    return parserVisitor->visitDefineDirective(this);
  else
    return visitor->visitChildren(this);
}

MiniCParser::DefineDirectiveContext* MiniCParser::defineDirective() {
  DefineDirectiveContext *_localctx = _tracker.createInstance<DefineDirectiveContext>(_ctx, getState());
  enterRule(_localctx, 2, MiniCParser::RuleDefineDirective);
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
    setState(74);
    match(MiniCParser::T__0);
    setState(75);
    match(MiniCParser::DEFINE);
    setState(76);
    match(MiniCParser::Ident);
    setState(77);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1030792151040) != 0))) {
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
  enterRule(_localctx, 4, MiniCParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(81);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::CONST: {
        _localctx = _tracker.createInstance<MiniCParser::ConstDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(79);
        constDecl();
        break;
      }

      case MiniCParser::INT:
      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::VarDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(80);
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
  enterRule(_localctx, 6, MiniCParser::RuleConstDecl);
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
    setState(83);
    match(MiniCParser::CONST);
    setState(84);
    bType();
    setState(85);
    constDef();
    setState(90);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__1) {
      setState(86);
      match(MiniCParser::T__1);
      setState(87);
      constDef();
      setState(92);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(93);
    match(MiniCParser::T__2);
   
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
  enterRule(_localctx, 8, MiniCParser::RuleBType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(97);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::INT: {
        _localctx = _tracker.createInstance<MiniCParser::IntTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(95);
        match(MiniCParser::INT);
        break;
      }

      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::FloatTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(96);
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
  enterRule(_localctx, 10, MiniCParser::RuleConstDef);
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
    setState(99);
    match(MiniCParser::Ident);
    setState(106);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__3) {
      setState(100);
      match(MiniCParser::T__3);
      setState(101);
      constExp();
      setState(102);
      match(MiniCParser::T__4);
      setState(108);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(109);
    match(MiniCParser::T__5);
    setState(110);
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
  enterRule(_localctx, 12, MiniCParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__8:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::T__12:
      case MiniCParser::Ident:
      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        _localctx = _tracker.createInstance<MiniCParser::ScalarConstInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(112);
        constExp();
        break;
      }

      case MiniCParser::T__6: {
        _localctx = _tracker.createInstance<MiniCParser::ArrayConstInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(113);
        match(MiniCParser::T__6);
        setState(122);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 481036352128) != 0)) {
          setState(114);
          constInitVal();
          setState(119);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MiniCParser::T__1) {
            setState(115);
            match(MiniCParser::T__1);
            setState(116);
            constInitVal();
            setState(121);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(124);
        match(MiniCParser::T__7);
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
  enterRule(_localctx, 14, MiniCParser::RuleVarDecl);
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
    setState(127);
    bType();
    setState(128);
    varDef();
    setState(133);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__1) {
      setState(129);
      match(MiniCParser::T__1);
      setState(130);
      varDef();
      setState(135);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(136);
    match(MiniCParser::T__2);
   
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
  enterRule(_localctx, 16, MiniCParser::RuleVarDef);
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
    setState(138);
    match(MiniCParser::Ident);
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__3) {
      setState(139);
      match(MiniCParser::T__3);
      setState(140);
      constExp();
      setState(141);
      match(MiniCParser::T__4);
      setState(147);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(150);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T__5) {
      setState(148);
      match(MiniCParser::T__5);
      setState(149);
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
  enterRule(_localctx, 18, MiniCParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__8:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::T__12:
      case MiniCParser::Ident:
      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        _localctx = _tracker.createInstance<MiniCParser::ScalarInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(152);
        exp();
        break;
      }

      case MiniCParser::T__6: {
        _localctx = _tracker.createInstance<MiniCParser::ArrayInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(153);
        match(MiniCParser::T__6);
        setState(162);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 481036352128) != 0)) {
          setState(154);
          initVal();
          setState(159);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == MiniCParser::T__1) {
            setState(155);
            match(MiniCParser::T__1);
            setState(156);
            initVal();
            setState(161);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(164);
        match(MiniCParser::T__7);
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
  enterRule(_localctx, 20, MiniCParser::RuleFuncDef);
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
    setState(167);
    funcType();
    setState(168);
    match(MiniCParser::Ident);
    setState(169);
    match(MiniCParser::T__8);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::INT

    || _la == MiniCParser::FLOAT) {
      setState(170);
      funcFParams();
    }
    setState(173);
    match(MiniCParser::T__9);
    setState(174);
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
  enterRule(_localctx, 22, MiniCParser::RuleFuncType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(179);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::VOID: {
        _localctx = _tracker.createInstance<MiniCParser::VoidReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(176);
        match(MiniCParser::VOID);
        break;
      }

      case MiniCParser::INT: {
        _localctx = _tracker.createInstance<MiniCParser::IntReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(177);
        match(MiniCParser::INT);
        break;
      }

      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::FloatReturnTypeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(178);
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
  enterRule(_localctx, 24, MiniCParser::RuleFuncFParams);
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
    funcFParam();
    setState(186);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__1) {
      setState(182);
      match(MiniCParser::T__1);
      setState(183);
      funcFParam();
      setState(188);
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
  enterRule(_localctx, 26, MiniCParser::RuleFuncFParam);
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
    setState(189);
    bType();
    setState(190);
    match(MiniCParser::Ident);
    setState(202);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MiniCParser::T__3) {
      setState(191);
      match(MiniCParser::T__3);
      setState(192);
      match(MiniCParser::T__4);
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == MiniCParser::T__3) {
        setState(193);
        match(MiniCParser::T__3);
        setState(194);
        exp();
        setState(195);
        match(MiniCParser::T__4);
        setState(201);
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
  enterRule(_localctx, 28, MiniCParser::RuleBlock);
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
    setState(204);
    match(MiniCParser::T__6);
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 514792110728) != 0)) {
      setState(205);
      blockItem();
      setState(210);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(211);
    match(MiniCParser::T__7);
   
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
  enterRule(_localctx, 30, MiniCParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::CONST:
      case MiniCParser::INT:
      case MiniCParser::FLOAT: {
        _localctx = _tracker.createInstance<MiniCParser::BlockDeclarationContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(213);
        decl();
        break;
      }

      case MiniCParser::T__2:
      case MiniCParser::T__6:
      case MiniCParser::T__8:
      case MiniCParser::T__10:
      case MiniCParser::T__11:
      case MiniCParser::T__12:
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
        setState(214);
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
  enterRule(_localctx, 32, MiniCParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::AssignmentStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(217);
      lVal();
      setState(218);
      match(MiniCParser::T__5);
      setState(219);
      exp();
      setState(220);
      match(MiniCParser::T__2);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::EmptyStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(222);
      match(MiniCParser::T__2);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::ExpressionStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(223);
      exp();
      setState(224);
      match(MiniCParser::T__2);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<MiniCParser::NestedBlockStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(226);
      block();
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<MiniCParser::IfElseStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(227);
      match(MiniCParser::IF);
      setState(228);
      match(MiniCParser::T__8);
      setState(229);
      cond();
      setState(230);
      match(MiniCParser::T__9);
      setState(231);
      stmt();
      setState(234);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
      case 1: {
        setState(232);
        match(MiniCParser::ELSE);
        setState(233);
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
      setState(236);
      match(MiniCParser::WHILE);
      setState(237);
      match(MiniCParser::T__8);
      setState(238);
      cond();
      setState(239);
      match(MiniCParser::T__9);
      setState(240);
      stmt();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<MiniCParser::BreakStatementContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(242);
      match(MiniCParser::BREAK);
      setState(243);
      match(MiniCParser::T__2);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<MiniCParser::ContinueStatementContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(244);
      match(MiniCParser::CONTINUE);
      setState(245);
      match(MiniCParser::T__2);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<MiniCParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(246);
      match(MiniCParser::RETURN);
      setState(248);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 481036352000) != 0)) {
        setState(247);
        exp();
      }
      setState(250);
      match(MiniCParser::T__2);
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
  enterRule(_localctx, 34, MiniCParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(253);
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
  enterRule(_localctx, 36, MiniCParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
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
  enterRule(_localctx, 38, MiniCParser::RuleLVal);
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
    setState(257);
    match(MiniCParser::Ident);
    setState(264);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__3) {
      setState(258);
      match(MiniCParser::T__3);
      setState(259);
      exp();
      setState(260);
      match(MiniCParser::T__4);
      setState(266);
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
  enterRule(_localctx, 40, MiniCParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(273);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MiniCParser::T__8: {
        enterOuterAlt(_localctx, 1);
        setState(267);
        match(MiniCParser::T__8);
        setState(268);
        exp();
        setState(269);
        match(MiniCParser::T__9);
        break;
      }

      case MiniCParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(271);
        lVal();
        break;
      }

      case MiniCParser::IntConst:
      case MiniCParser::FloatConst: {
        enterOuterAlt(_localctx, 3);
        setState(272);
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
  enterRule(_localctx, 42, MiniCParser::RuleNumber);
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
    setState(275);
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
  enterRule(_localctx, 44, MiniCParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(287);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryExpPrimaryContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(277);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryExpFuncCallContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(278);
      match(MiniCParser::Ident);
      setState(279);
      match(MiniCParser::T__8);
      setState(281);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 481036352000) != 0)) {
        setState(280);
        funcRParams();
      }
      setState(283);
      match(MiniCParser::T__9);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MiniCParser::UnaryOpUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(284);
      unaryOp();
      setState(285);
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
  enterRule(_localctx, 46, MiniCParser::RuleUnaryOp);
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
    setState(289);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14336) != 0))) {
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
  enterRule(_localctx, 48, MiniCParser::RuleFuncRParams);
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
    exp();
    setState(296);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__1) {
      setState(292);
      match(MiniCParser::T__1);
      setState(293);
      exp();
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
  enterRule(_localctx, 50, MiniCParser::RuleMulExp);
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
    unaryExp();
    setState(304);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 114688) != 0)) {
      setState(300);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 114688) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(301);
      unaryExp();
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
  enterRule(_localctx, 52, MiniCParser::RuleAddExp);
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
    mulExp();
    setState(312);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__10

    || _la == MiniCParser::T__11) {
      setState(308);
      _la = _input->LA(1);
      if (!(_la == MiniCParser::T__10

      || _la == MiniCParser::T__11)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(309);
      mulExp();
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
  enterRule(_localctx, 54, MiniCParser::RuleRelExp);
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
    addExp();
    setState(320);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1966080) != 0)) {
      setState(316);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1966080) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(317);
      addExp();
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
  enterRule(_localctx, 56, MiniCParser::RuleEqExp);
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
    relExp();
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__20

    || _la == MiniCParser::T__21) {
      setState(324);
      _la = _input->LA(1);
      if (!(_la == MiniCParser::T__20

      || _la == MiniCParser::T__21)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(325);
      relExp();
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
  enterRule(_localctx, 58, MiniCParser::RuleLAndExp);
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
    eqExp();
    setState(336);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__22) {
      setState(332);
      match(MiniCParser::T__22);
      setState(333);
      eqExp();
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
  enterRule(_localctx, 60, MiniCParser::RuleLOrExp);
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
    setState(339);
    lAndExp();
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == MiniCParser::T__23) {
      setState(340);
      match(MiniCParser::T__23);
      setState(341);
      lAndExp();
      setState(346);
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
  enterRule(_localctx, 62, MiniCParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
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
