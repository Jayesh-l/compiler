#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>

using namespace std;

enum class TokenType
{
    _return,
    int_literal,
    semicolon
};

struct Token
{
    TokenType type;
    optional<string> value {};
};
string tokens_to_asm(const vector<Token>& tokens)
{
    stringstream output;
    output << " global _start\n_start:\n";
    for (int i = 0;i<tokens.size();i++)
    {
        auto token = tokens[i];
        if (token.type == TokenType::_return)
        {
            if (i+1<tokens.size() && tokens[i+1].type == TokenType::int_literal)
            {
                if (i+2<tokens.size() && tokens[i+2].type == TokenType::semicolon)
                {
                    output<<"   mov rax,60\n";
                    output<<"   mov rdi, "<<tokens[i+1].value.value()<<"\n";
                    output<<"   syscall";
                }
            }
        }
    }
    return output.str();

}
vector<Token> tokenize(const string &str)
{
    vector<Token> tokens;
    string buf;
    for (int i=0;i<str.length();i++)
    {
        char c = str[i];
        if (isalpha(c))
        {
            buf.push_back(c);
            i++;
            while (i<str.size() && isalpha(str[i]))
            {
                buf.push_back(str[i]);
                i++;
            }
            i--;
            if (buf == "return")
            {
                // Token t;
                // t.type = TokenType::_return;
                // t.value = std::nullopt;
                // tokens.push_back(t);

                tokens.push_back({.type = TokenType::_return});
                buf.clear();
                continue;
            }
            else
            {
                cerr<<"Kar diya kaand"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (isdigit(c))
        {
            buf.push_back(c);
            i++;
            while (i<str.size() && isdigit(str[i]))
            {
                buf.push_back(str[i]);
                i++;
            }
            i--;
            tokens.push_back({.type = TokenType::int_literal,.value = buf});
            buf.clear();
        }
        else if (c == ';')
        {
            tokens.push_back({.type = TokenType::semicolon});
        }
        else if (isspace(c))
        {
            continue;
        }
        else
        {
            cout<<"kar diya kaand";
        }
    }
    return tokens;
}

int main(int argc,char* argv[])
{
    if (argc != 2)
    {
        cerr<<"Incorrectly done. Do it like..."<<endl;
        cerr<<"ltn <input.lango>"<<endl;
        return EXIT_FAILURE;
    }
    string contents;
    {
        stringstream contents_stream;
        fstream input(argv[1],ios::in);
        contents_stream<<input.rdbuf();
        contents = contents_stream.str();
    }
    {
        vector <Token> tokens = tokenize(contents);
        fstream file("out.asm",ios::out);
        file<<tokens_to_asm(tokens);
    }
    system("nasm -felf64 out.asm");
    system("ld -o out out.o");
    return EXIT_SUCCESS;
}