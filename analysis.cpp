/**
 * Text analysis
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * analysis.cpp
 * 2021-04-08
 */

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "analysis.h"

#include <iostream>

using namespace std;
using namespace sweary;

// Divides a string into words
vector<string> TextAnalysis::extractWords(string text)
{
    vector<string> allWords;
    string buffer;
    bool bufferActive = false;

    buffer = "";

    for (char c : text)
    {
        if (isalnum(c))
        {
            // ;)
            bufferActive = true;
            buffer.append(true, c);
        } else
        {
            if (bufferActive)
            {
              if (c != '\'')
              {
                bufferActive = false;
                allWords.push_back(buffer);
                buffer = "";
              }
            }
        }
    }
    if (buffer != "")
      allWords.push_back(buffer);
    return allWords;
}

// Get map of word frequency
wordmap TextAnalysis::getWordMap(vector<string> wordlist)
{
  wordmap w;

  for (string word : wordlist)
  {
    for (char& c : word)
    {
      c = tolower(c);
    }

    // Create key if it doesn't exist
    if (!w.count(word))
    {
      w[word] = 0;
    }

    ++w[word];
  }

  return w;
}

// Get vector of word frequency sorted by frequency, then alphabetically
vector<TextAnalysis::WordFrequency> TextAnalysis::wordMapToSortedVector(wordmap wordlist)
{
  vector<TextAnalysis::WordFrequency> wf;

  for (auto const &word : wordlist)
  {
    wf.push_back({ word.first, word.second });
  }

  // Sort by descending order, frequency as main criteria and alphabetical order as second
  sort(wf.begin(), wf.end(), greater<TextAnalysis::WordFrequency>());
  return wf;
}

// Get map of word length frequency
wordLengthMap TextAnalysis::analyseWordLength(vector<string> wordlist)
{
  wordLengthMap lengthMap;

  for (string word : wordlist)
  {
    // Create key if it doesn't exist
    if (!lengthMap.count(word.size()))
    {
      lengthMap[word.size()] = 0;
    }

    ++lengthMap[word.size()];
  }


  return lengthMap;
}

// Average word length of word list
double TextAnalysis::averageWordLength(vector<string> wordlist)
{
  int sum = 0;

  for (string word : wordlist)
  {
    sum += word.size();
  }

  return (sum / (double) wordlist.size());
}

// Get map of char frequency
charmap TextAnalysis::getCharMap(vector<string> wordlist)
{
  charmap cm;

  for (string word : wordlist)
  {
    for (char& c : word)
    {
      // Treat upper and lower case versions as a single letter
      c = tolower(c);

      // Create key if it doesn't exist
      if (!cm.count(c))
      {
        cm[c] = 0;
      }

      // Increase times that letter was found
      ++cm[c];
    }
  }


  return cm;
}
