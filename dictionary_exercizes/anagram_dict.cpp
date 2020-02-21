/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) 
    {
        while (getline(wordsFile, word)) 
        {
            //sorts the word
            string word_sorted = word;
            std::sort(word_sorted.begin(), word_sorted.end());
            //pushes the word to the dict
            dict[word_sorted].push_back(word_sorted);       
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    //loops through all strings in a word
    for(auto & s : words)
    {
        //sorts each word
        string word_sorted = s;
        std::sort(word_sorted.begin(), word_sorted.end());
        //pushes it to dictionary 
        dict[word_sorted].push_back(s);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    //sorts the word
    string word_sorted = word;
    std::sort(word_sorted.begin(), word_sorted.end());
    //finds the sorted word in the dictionary
    auto sorted_lookup = dict.find(word_sorted);
    //we must not be at the end of the list
    if(sorted_lookup != dict.end())
    {
        //there must be more than one entry for anagrams
        if(dict.at(word_sorted).size() != 1)
        {
            //returns the vector of anagrams
            return dict.at(word_sorted);
        }
    }
    //returns an empty vector
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all_anagrams;
    //loops through each anagram vector in the dictionary
    for(auto & anagram_pair : dict)
    {
        //gets anagram vector from pair
        auto & anagram_vect = anagram_pair.second;
        //must have more than one entry
        if(anagram_vect.size() > 1)  all_anagrams.push_back(anagram_vect);
    }
    return all_anagrams;
}
