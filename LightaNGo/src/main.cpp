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
    optional<string> value;
};

vector<Token> tokenize(const string &str)
{
    for (char c:str)
    {
        cout<<c<<endl;
    }
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
    tokenize(contents);
    return EXIT_SUCCESS;
}