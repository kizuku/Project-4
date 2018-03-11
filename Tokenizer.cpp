#include "provided.h"
#include <string>
#include <vector>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
	string m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
	m_separators = separators;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
	vector<string> words;
	string temp;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < m_separators.size(); j++) {
			if (s[i] == m_separators[j]) { // if char is a separator
				if (temp != "") {  // if temp is not empty
					// add temp to vector
					words.push_back(temp);
				}
				break;
			}
		}
		temp += s[i];
	}
    return words;  
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
