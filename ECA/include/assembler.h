#ifndef ASM_H
#define ASM_H

#include <initializer_list>

#include "utils.h"

#define ASM_INC_PATH "\\..\\..\\lib\\wos32\\asm\\"

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;

/// Converts string to number
/// @param literal  string literal
/// @return numeric value
inline long long int stringToNum(string literal) {
    int mult = 1;
    long long int value;

    for (long long int i=static_cast<long long int>(literal.length())-1; i>=0; i--) {
        value += (literal[static_cast<size_type>(i)]-'0')*mult;
        mult *= 10;
    }

    return value;
}

/// Converts number to literal
/// @param num  number
/// @return string repr
inline string numToString(long long int num) {
    char * buf = static_cast<char*>(malloc(20));
    sprintf_s(buf, 100, "%I64u", num);
    string res = buf;
    return res;
}

enum Mnemonic {
    HLT,
    RET,
    MOV,
    JMP,
    PUSH,
    POP,
    AND,
    OR,
    LGDT,
    NULL_INS,
};

enum DataType {
    NULL_T,
    BYTE_T,
    WORD_T,
    DWORD_T,
    QWORD_T
};

class Token {
private:
    string stringLiteral_;

public:
    Token() {}

    Token(string stringLiteral) {
        this->stringLiteral_ = stringLiteral;
    }

    /// Literal form of value
    /// @return string literal
    string literal() const {
        return this->stringLiteral_;
    }
};



class InstructionToken : public Token {
private:
    Mnemonic value_;

public:
    InstructionToken() {}

    InstructionToken(Mnemonic value) {
        this->value_ = value;
    }

    InstructionToken(string value) {
        string val_l = lower(value);

        if (val_l == "hlt") {
            this->value_ = Mnemonic(HLT);
        } else if (val_l == "jmp") {
            this->value_ = Mnemonic(JMP);
        } else if (val_l == "lgdt") {
            this->value_ = Mnemonic(LGDT);
        } else if (val_l == "mov") {
            this->value_ = Mnemonic(MOV);
        } else if (val_l == "ret") {
            this->value_ = Mnemonic(RET);
        } else {
            this->value_ = Mnemonic(NULL_INS);
        }
    }

    /// Token value
    /// @return instruction
    Mnemonic value() const {
        return this->value_;
    }
};

class NumberToken : public Token {
private:
    long long int value_;
    string stringLiteral_;
    DataType type_;

public:
    NumberToken() {}

    NumberToken(string stringLiteral, DataType type) {
        this->stringLiteral_ = stringLiteral;
        this->value_ = stringToNum(stringLiteral);
        this->type_ = type;
    }

    NumberToken(long long int value, DataType type) {
        this->value_ = value;
        this->stringLiteral_ = numToString(value);
        this->type_ = type;
    }

    /// Token value
    /// @return number
    long long int value() const {
        return this->value_;
    }
};

inline DataType FindDataType(string stringLiteral) {
    string str_l = lower(stringLiteral);

    if (str_l == "byte") return DataType::BYTE_T;
    if (str_l == "word") return DataType::WORD_T;
    if (str_l == "dword") return DataType::DWORD_T;
    if (str_l == "qword") return DataType::QWORD_T;
    return DataType::NULL_T;
}

class PointerToken : public Token {
private:
    int value_;
    string stringLiteral_;

public:
    PointerToken() {}

    PointerToken(string stringLiteral) {
        this->stringLiteral_ = stringLiteral;
        this->value_ = static_cast<int>(stringToNum(stringLiteral));
    }

    PointerToken(int value) {
        this->value_ = value;
        this->stringLiteral_ = numToString(value);
    }

    /// Token value
    /// @return int
    int value() const {
        return this->value_;
    }
};

class Statement {
private:
    vector<Token> tokens_;

public:
    Statement() {}

    Statement(std::initializer_list<Token> tokens) {
        this->tokens_ = tokens;
    }

    /// Gets token at index
    /// @param i    index
    /// @return token at index i
    Token token(size_type i) const {
        return this->tokens_[i];
    }

    /// Gets string representation of tokens
    /// @return concatenation of token reprs
    string str_repr() const {
        string tmp;

        for (size_type i=0; i<this->tokens_.size(); i++) {
            tmp += this->tokens_[i].literal();
        }

        return tmp;
    }

    Token operator[](size_type n) const {
        return this->token(n);
    }
};

class Instruction : public Statement {
private:
    InstructionToken ins_;
    vector<Token> tokens_;

public:
    Instruction() {}

    Instruction(std::initializer_list<Token> tokens) {
        this->tokens_ = tokens;
    }

    InstructionToken GetIns() const {
        return this->ins_;
    }

    Token GetParam(size_type n) const {
        return this->tokens_[n];
    }
};

class AsmStruct {
private:
    map<string, Token> members_;

public:
    AsmStruct() {}

    void addMember(string name, DataType type, Token value) {
        this->members_.insert(std::make_pair(name, value));
    }
};

class Assembler {
private:
    /// Handles single include statement tree
    /// @param filename filename
    /// @param path     include path (relative)
    /// @return string concatenation of include result (usually header file)
    string resolveInclude(const string& filename, const string& path);

public:
    Assembler() {}

    /// Assembles files
    /// @param files    filenames
    /// @param source   code
    /// @param optimize optimize flag
    /// @param path     include path (relative)
    /// @return binary data
    vector<byte> DoAll(const vector<string>& files, const vector<string>& source, int optimize, const string& path);

    /// Preprocessed assembly
    /// @param files    filenames
    /// @param source   code
    /// @param path     include path (relative)
    /// @return string concatenation of files
    string PreProcess(const vector<string>& files, const vector<string>& source, const string& path);

    /// Assembles preprocessed code into statements
    /// @param code         source code
    /// @param optimize     optimize flag
    /// @return resulting statements generated from source
    vector<Statement> Assemble(const string& code, int optimize);

    /// Disassembles statements into bytes
    /// @param statements   statements
    /// @return binary data
    vector<byte> Disassemble(const vector<Statement>& statements);

    /// Calculates the size of an instruction (in bytes)
    /// @param instruction  statement containing instruction & operands
    /// @param optimize     optimization level (for instruction compacting)
    /// @return size in bytes of the instruction
    int calcInstructionSize(const Instruction& instruction, const int optimize);
};

#endif
