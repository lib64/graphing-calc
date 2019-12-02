#include "lexer.h"

const vector<string> Lexer::OPERATORS = {
    "+","-","*","/",
    "(",")","|","^"
};

const vector<string> Lexer::FUNCTIONS = {
    "sqrt","sin","cos","tan",
    "acos","asin","atan"
};

const std::string Lexer::REGEX_IDENTIFIER = "[a-zA-Z_]+[a-zA-Z0-9_]*";

const std::string Lexer::REGEX_INT_LITERAL = "[-]?\\d+";

const std::string Lexer::REGEX_FLOAT_LITERAL = "[0-9]+\\.[0-9]+";

Lexer::Lexer(const std::string &expr)
{
    _expr = expr;
    _index = 0;

    _intRegex = new std::regex(REGEX_INT_LITERAL);
    _floatRegex = new std::regex(REGEX_FLOAT_LITERAL);
    _identifierRegex = new std::regex(REGEX_IDENTIFIER);
}

Lexer::~Lexer()
{
    delete  _intRegex;
    delete _floatRegex;
    delete _identifierRegex;
}

static bool check_for(const std::string &line, size_t start, const std::string &match) {
    if(match.length() <= line.length() - start) {
        long st = static_cast<long>(start);
        long ml = static_cast<long>(match.length());
        std::string s1(line.begin() + st, line.begin()+ st + ml);
        if(s1 == match) {
            return true;
        }
    }
    return false;
}

static long check_for_each(const std::string &line, size_t start, const std::vector<std::string> &arr) {
    for(size_t i = 0; i < arr.size(); i++) {
        if(check_for(line, start, arr[i])) {
            return static_cast<long>(i);
        }
    }
    return -1;
}

static long check_regex(const std::string& line, size_t start, std::regex *reg) {
      std::smatch matches;
      std::regex_search ( line.begin()+static_cast<long>(start),line.end(), matches, *reg );
      if(!matches.empty()) {
          if(matches.position(0) == 0) {
              return matches[0].length();
          }
      }
      return 0;
}

vector<LexerToken> Lexer::lex()
{
    vector<LexerToken> tokens;

    while(_index < _expr.size()) {

        if(isspace(_expr.at(_index))) {
            ++_index;
            continue;
        }

        // operators
        long op = check_for_each(_expr, _index, OPERATORS);
        if(op != -1) {

            LexerToken::Type type;
            switch(op) {
            case 0: type = LexerToken::Type::OP_ADD; break;
            case 1: type = LexerToken::Type::OP_SUB; break;
            case 2: type = LexerToken::Type::OP_MUL; break;
            case 3: type = LexerToken::Type::OP_DIV; break;
            case 4: type = LexerToken::Type::LPAREN; break;
            case 5: type = LexerToken::Type::RPAREN; break;
            case 6: type = LexerToken::Type::OP_ABS; break;
            case 7: type = LexerToken::Type::OP_POW; break;
            default:
                throw std::invalid_argument("bad lexerTokenType for operator");
            }

            LexerToken tok(type,OPERATORS[static_cast<size_t>(op)], _index);
            tokens.push_back(tok);
            _index += OPERATORS[static_cast<size_t>(op)].size();
            continue;
        }

        // functions
        long func = check_for_each(_expr, _index, FUNCTIONS);
        if(func != -1) {

            LexerToken::Type type;
            switch(func) {
            case 0: type = LexerToken::Type::SQRT; break;
            case 1: type = LexerToken::Type::SIN; break;
            case 2: type = LexerToken::Type::COS; break;
            case 3: type = LexerToken::Type::TAN; break;
            case 4: type = LexerToken::Type::ASIN; break;
            case 5: type = LexerToken::Type::ACOS; break;
            case 6: type = LexerToken::Type::ATAN; break;
            default:
                throw std::invalid_argument("bad lexerTokenType for function");
            }

            LexerToken tok(type, FUNCTIONS[static_cast<size_t>(func)], _index);
            tokens.push_back(tok);
            _index += FUNCTIONS[static_cast<size_t>(func)].size();
            continue;
        }

        long len;

        // float literals
        len = check_regex(_expr,_index,_floatRegex);
        if(len > 0) {
            std::string match = std::string(_expr.begin()+static_cast<long>(_index),
                                            _expr.begin()+static_cast<long>(_index)+len);
            LexerToken tok(LexerToken::Type::FLOAT_LIT,match, _index);
            tokens.push_back(tok);
            _index += static_cast<size_t>(len);
            continue;
        }

        // int literals
        len = check_regex(_expr,_index,_intRegex);
        if(len > 0) {
            std::string match = std::string(_expr.begin()+static_cast<long>(_index),
                                            _expr.begin()+static_cast<long>(_index)+len);
            LexerToken tok(LexerToken::Type::INT_LIT,match, _index);
            tokens.push_back(tok);
            _index += static_cast<size_t>(len);
            continue;
        }

        // identifiers
        len = check_regex(_expr,_index,_identifierRegex);
        if(len > 0) {
            std::string match = std::string(_expr.begin()+static_cast<long>(_index),
                                            _expr.begin()+static_cast<long>(_index)+len);

            if(match != "x") {
                throw std::invalid_argument("Unknown variable:" + match + ". use x.");
            }

            LexerToken tok(LexerToken::Type::IDENTIFIER,match, _index);
            tokens.push_back(tok);
            _index += static_cast<size_t>(len);
            continue;

        }
        throw std::invalid_argument("bad token");
    }
    return tokens;
}
