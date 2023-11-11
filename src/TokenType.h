#ifndef TOKENTYPE
#define TOKENTYPE

enum class TokenType {
    CONST,
    IDENT,
    ASSIGN_OP,
    ADD_OP,
    MULT_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMI_COLON,
    UNDEFINED,
    END_OF_FILE
};

#endif //TOKENTYPE
