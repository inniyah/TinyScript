#include <cassert>
#include <sstream>
#include <string>

#include "lexer.hpp"

int main() {
    using namespace tiny;

    std::string str{"Hello world 0 10.0 'a' \"hello\""};
    std::istringstream s{str};

    Lexer lexer{s, "test"};

    assert(lexer.next_token() == TokenKind::IDENT);
    assert(lexer.str() == "Hello");

    assert(lexer.next_token() == TokenKind::IDENT);
    assert(lexer.str() == "world");

    assert(lexer.next_token() == TokenKind::INT_VALUE);
    assert(lexer.i_value() == 0);

    assert(lexer.next_token() == TokenKind::FLOAT_VALUE);
    assert(std::abs(lexer.f_value() - 10.0f) < 0.001f);

    assert(lexer.next_token() == TokenKind::CHAR_VALUE);
    assert(lexer.c_value() == 'a');

    assert(lexer.next_token() == TokenKind::STRING_VALUE);
    assert(lexer.str() == "hello");

    assert(lexer.next_token() == TokenKind::SUB);

    return 0;
}
