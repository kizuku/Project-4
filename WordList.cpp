#include "provided.h"
#include "MyHash.h"
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <cctype>
using namespace std;

class WordListImpl
{
public:
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
	string createPattern(string s) const;
	MyHash<string, list<string>> m_hashtable;
};

// use letters to create pattern keys
string WordListImpl::createPattern(string s) const{
	string pattern;
	// don't check first character
	pattern += 'A';
	for (int i = 1; i < s.size(); i++) {
		// if word is invalid, return "-1"
		if (!isalpha(s[i]) && s[i] != '\'') {
			pattern = "-1";
			break;
		}
		int increment = 0;
		for (int j = 0; j < i; j++) {
			if (s[i] != s[j])
				increment++;
		}
		pattern += 'A' + increment;
	}
	return pattern;
}

bool WordListImpl::loadWordList(string filename)
{
	m_hashtable.reset();
	ifstream infile(filename);
	
	if (!infile)  // file could not be opened
		return false;
	
	string word;
	list<string>* wordList;
	while (getline(infile, word)) {
		for (int i = 0; i < word.size(); i++)
			word[i] = tolower(word[i]);

		string pattern = createPattern(word);
		if (pattern == "-1")
			continue;
		wordList = m_hashtable.find(pattern);
		if (wordList == nullptr) {
			list<string> newList;
			newList.push_back(word);
			m_hashtable.associate(pattern, newList);
		}
		else {
			wordList->push_back(word);
		}
	}
	// all words loaded successfully
	return true;  
}

bool WordListImpl::contains(string word) const
{
	string temp = word;
	for (int i = 0; i < temp.size(); i++) 
		temp[i] = tolower(temp[i]);

	string key = createPattern(temp);
	const list<string> *wordList;
	wordList = m_hashtable.find(key);
	if (wordList == nullptr)
		return false;
	else {
		for (list<string>::const_iterator it = wordList->begin(); it != wordList->end(); it++) {
			if ((*it) == temp)
				return true;
		}
	}
	return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
	vector<string> possWords;

	// check for valid conditions
	if (cipherWord.size() != currTranslation.size())
		return possWords;

	for (int i = 0; i < cipherWord.size(); i++)
		if (!isalpha(cipherWord[i]) && cipherWord[i] != '\'')
			return possWords;

	for (int i = 0; i < currTranslation.size(); i++)
		if (!isalpha(currTranslation[i]) && currTranslation[i] != '\'' && currTranslation[i] != '?')
			return possWords;

	for (int i = 0; i < currTranslation.size(); i++) {
		cipherWord[i] = tolower(cipherWord[i]);
		currTranslation[i] = tolower(currTranslation[i]);
	}

	string cipherPattern = createPattern(cipherWord);
	const list<string> *words = m_hashtable.find(cipherPattern);
	if (words == nullptr)
		return possWords;
	else {
		bool match;
		for (list<string>::const_iterator it = words->begin(); it != words->end(); it++) {
			match = true;
			for (int i = 0; i < currTranslation.size(); i++) {
				if (currTranslation[i] != '?' && currTranslation[i] != (*it)[i]) {
					match = false;
					break;
				}
			}
			if (match)
				possWords.push_back(*it);
		}
	}
    return possWords; 
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}
