/**
 * Analysis of texts
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * analysis.h
 * 2021-04-07
 */

#ifndef SWEARY_ANALYSIS_H
#define SWEARY_ANALYSIS_H

#include <string>
#include <vector>
#include <map>

typedef std::map<std::string, int> wordmap;
typedef std::map<int, int> wordLengthMap;
typedef std::map<char, int> charmap;

namespace sweary
{
  class TextAnalysis
  {
  public:
    struct WordFrequency {
      std::string word;
      int frequency;

      // Overload operators for sorting structs
      bool operator<(const WordFrequency& other) const
      {
          if (frequency == other.frequency)
            return word > other.word;
          return frequency < other.frequency;
      }

      bool operator>(const WordFrequency& other) const
      {
          if (frequency == other.frequency)
            return word < other.word;
          return frequency > other.frequency;
      }
    };

    // Divides a string into words (basically groups of alphanum chars)
    static std::vector<std::string> extractWords(std::string text);
    // Get map of word-frequency from vector of words
    static wordmap getWordMap(std::vector<std::string> wordlist);
    // Order word-frequency map by frequency into vector
    static std::vector<TextAnalysis::WordFrequency> wordMapToSortedVector(wordmap wm);
    // Get map of word length-frequency
    static wordLengthMap analyseWordLength(std::vector<std::string> wordlist);
    // Simple average, nothing to see here
    static double averageWordLength(std::vector<std::string> wordlist);
    // Get map of char-frequency
    static charmap getCharMap(std::vector<std::string> wordlist);
  };
}

#endif
