#include <bits/stdc++.h>

using namespace std;

enum TokenType
{
    LEFT_PAREN,
    RIGHT_PAREN,
    MINUS,
    PLUS,
    SLASH,
    STAR,
    SEMICOLON,
    EQUAL,
    IDENTIFIER,
    NUMBER,
    OUTPUT,
    END
};

string type_to_string(TokenType tokenType)
{
    switch (tokenType)
    {
    case LEFT_PAREN:
        return "LEFT_PAREN";
    case RIGHT_PAREN:
        return "RIGHT_PAREN";
    case MINUS:
        return "MINUS";
    case PLUS:
        return "PLUS";
    case SLASH:
        return "SLASH";
    case STAR:
        return "STAR";
    case SEMICOLON:
        return "SEMICOLON";
    case EQUAL:
        return "EQUAL";
    case IDENTIFIER:
        return "IDENTIFIER";
    case NUMBER:
        return "NUMBER";
    case OUTPUT:
        return "OUTPUT";
    case END:
        return "END";
    }
    return "UNKNOWN";
}

class Token
{
    TokenType type;
    string lexeme;
    int line;

public:
    Token(TokenType type, string lexeme, int line)
    {
        this->type = type;
        this->lexeme = lexeme;
        this->line = line;
    }

public:
    string to_string()
    {
        return "Token(" + type_to_string(type) + ", " + lexeme + ", " + std::to_string(line) + ")";
    }
};

class Scanner
{
    map<string, TokenType> keyword;
    string source;
    vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

public:
    Scanner()
    {
        keyword.insert(make_pair("output", OUTPUT));
    }

    Scanner(string source)
    {
        Scanner();
        this->source = source;
    }

    vector<Token> scan_tokens()
    {
        while (!is_at_end())
        {
            start = current;
            scan_token();
        }
        tokens.push_back(Token(END, "", line));
        return tokens;
    }

    void scan_token()
    {
        char c = advance();
        switch (c)
        {
        case '(':
            add_token(LEFT_PAREN);
            break;
        case ')':
            add_token(RIGHT_PAREN);
            break;
        case '-':
            add_token(MINUS);
            break;
        case '+':
            add_token(PLUS);
            break;
        case '/':
            add_token(SLASH);
            break;
        case '*':
            add_token(STAR);
            break;
        case ';':
            add_token(SEMICOLON);
            break;
        case '=':
            add_token(EQUAL);
            break;
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
            line++;
            break;
        default:
            if (isdigit(c))
            {
                number();
            }
            else if (isalpha(c))
            {
                identifier();
            }
            else
            {
                cout << "Unexpected character: " << c << endl;
            }
            break;
        }
    }

    void identifier()
    {
        while (isalnum(peek()))
            advance();
        string text = source.substr(start, current - start);
        TokenType type = keyword[text];
        if (type == TokenType::OUTPUT)
        {
            add_token(OUTPUT);
        }
        else
        {
            add_token(IDENTIFIER);
        }
    }

    void number()
    {
        while (isdigit(peek()))
            advance();
        if (peek() == '.' && isdigit(peek_next()))
        {
            advance();
            while (isdigit(peek()))
                advance();
        }
        add_token(NUMBER);
    }

    char peek()
    {
        if (is_at_end())
            return '\0';
        return source[current];
    }

    char peek_next()
    {
        if (current + 1 >= source.length())
            return '\0';
        return source[current + 1];
    }

    bool is_at_end()
    {
        return current >= source.length();
    }

    char advance()
    {
        current++;
        return source[current - 1];
    }

    void add_token(TokenType type)
    {
        string text = source.substr(start, current - start);
        tokens.push_back(Token(type, text, line));
    }
};

int main()
{
    string source;
    while (cin >> source)
    {
        Scanner scanner(source);
        vector<Token> tokens = scanner.scan_tokens();
        for (Token token : tokens)
        {
            cout << token.to_string() << endl;
        }
    }
    return 0;
}