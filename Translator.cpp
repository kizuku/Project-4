#include "provided.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class TranslatorImpl
{
public:
	bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
	vector<map<char, char>> mapping; // maps ciphertext to plaintext
};

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
	// check for syntactically invalid arguments
	if (ciphertext.size() != plaintext.size())
		return false;
	for (int i = 0; i < ciphertext.size(); i++) {
		if (!isalpha(ciphertext[i]) || !isalpha(plaintext[i]))
			return false;
	}

	for (int i = 0; i < ciphertext.size(); i++) {
		ciphertext[i] = tolower(ciphertext[i]);
		plaintext[i] = tolower(plaintext[i]);
	}

	// check for repeated chars within the strings
	for (int i = 0; i < ciphertext.size(); i++) {
		for (int j = 0; j < i; j++)
			if (ciphertext[i] == ciphertext[j] || plaintext[i] == plaintext[j])
				return false;
	}

	map<char, char> newTable;
	if (!mapping.empty())
		newTable = mapping.back();

	// check for duplicates in the mapping
	map<char, char>::iterator it;
	for (it = newTable.begin(); it != newTable.end(); it++) {
		for (int i = 0; i < ciphertext.size(); i++) {
			if (it->first == ciphertext[i] || it->second == plaintext[i])
				return false;
		}
	}

	// add new mappings 
	for (int i = 0; i < ciphertext.size(); i++) {
		newTable[ciphertext[i]] = plaintext[i];
	}

	// add mapping to the vector 
	mapping.push_back(newTable);
	return true;
}

bool TranslatorImpl::popMapping()
{
	if (mapping.empty())
		return false;

	mapping.pop_back();
	return true;
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
	string translation;
	string temp = ciphertext;

	map<char, char> currentTable;
	if (!mapping.empty())
		currentTable = mapping.back();

	bool uppercase;
	for (int i = 0; i < temp.size(); i++) {
		uppercase = false;
		if (!isalpha(temp[i])) {
			translation += temp[i];
			continue;
		}
		uppercase = isupper(temp[i]);
		temp[i] = tolower(temp[i]);
		map<char, char>::const_iterator it = currentTable.find(temp[i]);
		if (it == currentTable.end()) 
			temp[i] = '?';	
		else
			temp[i] = it->second;
		if (uppercase)
			temp[i] = toupper(temp[i]);
		translation += temp[i];
	}
	return translation;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
