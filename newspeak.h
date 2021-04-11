/**
 * Perform text censorship and record matches information
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * newspeak.h
 * 2021-04-08
 */

#ifndef NEWSPEAK_H
#define NEWSPEAK_H

#include <map>
#include <string>
#include <vector>

namespace sweary
{
  class NewspeakEngine
  {
  public:
    /**
    * Censors words in a string with the desired char (by default '*')
    * Can also leave edge characters untouched, so that only the middle characters are affected
    * @param bannedWords A vector containing the words to redact
    * @param text The text to redact words from
    * @param censorChar The character to redact words with
    * @param edgeChars Number of characters from the edges of each word to leave untouched
    */
    std::string censor(std::vector<std::string> bannedWords, std::string text, char censorChar = '*', long unsigned int edgeChars = 1);

    // Getters for private vars
    int getCompleteMatches(std::string key);
    int getPartialMatches(std::string key);
    int getTotalMatches(std::string key);
  private:
    // Holds number of number of complete matches for each bad word
    std::map<std::string, int> completeMatches;
    // Holds number of number of partial matches (i.e. as a substring) for each bad word
    std::map<std::string, int> partialMatches;
  };
}

#endif
