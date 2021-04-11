/**
 * Perform text censorship and record matches information
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * newspeak.cpp
 * 2021-04-08
 */

#include <string>
#include <vector>
#include "newspeak.h"

using namespace std;
using namespace sweary;


// Get number of partial (substring) matches of last censor job for a certain bad word
int NewspeakEngine::getPartialMatches(string key)
{
  return partialMatches[key];
}

// Get number of full matches of last censor job for a certain bad word
int NewspeakEngine::getCompleteMatches(string key)
{
  return completeMatches[key];
}

// Get number of matches of last censor job for a certain bad word
int NewspeakEngine::getTotalMatches(string key)
{
  return getCompleteMatches(key) + getPartialMatches(key);
}

// Censor words from a text
string NewspeakEngine::censor(vector<string> bannedWords, string text, char censorChar, long unsigned int edgeChars)
{
    // Make lowercase copy of text to search no-no words
    string lowerCaseText = text;

    for (char &c : lowerCaseText)
    {
        c = tolower(c);
    }

    // Search each banned word in the lowercase copy
    for (string banned : bannedWords)
    {
      bool hasSearched = false;
      size_t searchStart = 0;

      partialMatches[banned] = 0;
      completeMatches[banned] = 0;

      while (searchStart != string::npos)
      {
        if (hasSearched)
        {
          // Arriving at this point means a match was found in the previous iteration of this while loop

          // Redact word with desired character
          for (long unsigned int i = edgeChars; i < banned.size() - edgeChars; i++)
          {
            text[searchStart + i] = censorChar;
          }

          // If any of neighbouring chars are alphanumeric, count match as partial, otherwise as complete
          bool prevCharAlnum = searchStart > 0 && isalnum(text[searchStart - 1]);

          unsigned int nextCharPos = searchStart + banned.size();
          bool nextCharAlnum = nextCharPos < text.size() && isalnum(text[nextCharPos]);

          if (prevCharAlnum || nextCharAlnum)
          {
            ++partialMatches[banned];
          }
          else
          {
            ++completeMatches[banned];
          }

          // Set start of search to end of current match
          searchStart += banned.size();
        }

        // Find next instance of substring in text
        size_t nextMatch = lowerCaseText.find(banned, searchStart);
        searchStart = nextMatch;
        hasSearched = true;
      }
    }

    return text;
}
