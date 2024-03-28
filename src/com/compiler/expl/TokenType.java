package com.compiler.expl;

enum TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN,
    MINUS, PLUS, SLASH, STAR, SEMICOLON, EQUAL,

    // Literals
    IDENTIFIER, NUMBER,

    // Keyword
    OUTPUT,

    EOF
}
