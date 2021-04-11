/**
 * Sweary: An Overzealous Profanity Checker
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * main.cpp
 * 2021-04-07
 */

 /* Divide and conquer */

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "files.h"
#include "newspeak.h"
#include "analysis.h"
#include "sweary.h"

using namespace std;
using namespace sweary;

// Display a series of data about a text through the console
void statisticalAnalysis(string textFileName, vector<string> words);

// Take all the words from all texts and sort them alphabetically into a string with newlines
string getSortedTextContents(vector<string> combined);

int main()
{
    const string textFileExtension = ".txt";
    const string textFilesPrefix = "text";
    const int textFilesNo = 4;
    const string bannedWordsFile = "banned" + textFileExtension;
    const string outputSuffix = "Filtered" + textFileExtension;
    const string sortedWordsFilename = "sorted" + textFileExtension;
    const bool fileOutputEnabled = true;
    const string quitKey = "q";

    string command;

    cout << sweary::title << " " << sweary::version << endl;
    cout << sweary::description << endl;
    cout << "by " << sweary::author << " <" << sweary::email << ">" << endl << endl;

    cout << sweary::disclaimer << endl << endl;

    do
    {
      cout << "Press ENTER to start file analysis (or 'q' to exit)" << endl << endl;
      getline(cin, command);

      if (command == quitKey)
      {
        return 0;
      }
    } while (command != "");

    vector<string> textFileNames;

    //  prev 4
    for (int i = 1; i <= textFilesNo; i++)
    {
        textFileNames.push_back(textFilesPrefix + to_string(i));
    }

    //textFileNames.push_back("tests");

    vector<string> banned = TextAnalysis::extractWords(Files::getContentsFromFile(bannedWordsFile));
    vector<vector<string>> allWords;

    for (string textFileName : textFileNames)
    {
        cout << "PROCESSING FILE " << textFileName << endl << endl;

        // Get text from file
        string contents = Files::getContentsFromFile(textFileName + textFileExtension);

        // Extract all words from text
        vector<string> textWords = TextAnalysis::extractWords(contents);
        allWords.push_back(textWords);

        // Perform analysis
        statisticalAnalysis(textFileName, textWords);

        // Censor the text
        cout << "Censoring Text" << endl << endl;
        NewspeakEngine engine = NewspeakEngine();
        string censoredText = engine.censor(banned, contents);

        // Display matches information
        for (string badWord : banned)
        {
          if (engine.getTotalMatches(badWord))
          {
            cout << "Matches for " << badWord << endl;
            cout << "Complete: " << engine.getCompleteMatches(badWord) << "  ";
            cout << "Partial: " << engine.getPartialMatches(badWord) << endl << endl;
          }
        }

        // Not outputing filtered text to screen
        //cout << censoredText << endl << endl;

        // Finally, write the censored version to text files
        if (fileOutputEnabled)
        {
          string outputFilename = textFileName + outputSuffix;
          cout << "Writing filtered text to file " << outputFilename << endl;
          Files::writeContentsToFile(outputFilename, censoredText);
        }

        // Pause so user can better read whatever's going on
        cout << endl << "End of analysis of file " << textFileName << endl;
        cout << "Press ENTER to continue" << endl;
        cout.clear();
        getchar();
        cout << endl;
    }

    // Combined analysis
    cout << "Showing analysis of combined texts" << endl;
    vector<string> combined;

    // Merge all words vectors into a single vector
    for (vector<string> &words : allWords)
    {
      combined.insert( combined.end(), words.begin(), words.end() );
    }

    statisticalAnalysis("COMBINED", combined);

    // Write sorted words to file
    cout << endl << "Writing alphabetically sorted word set of all texts to " << sortedWordsFilename << endl;
    Files::writeContentsToFile(sortedWordsFilename, getSortedTextContents(combined));
    getchar();
    return 0;
}

void statisticalAnalysis(string textFileName, vector<string> words)
{
  const char barUnit = '|';
  const int maxWordLengthDigits = 2;

  // Set to 0 to disable
  unsigned int topFrequentWords = 0;

  string command;

  // Now, perform analysis
  cout << "Performing text analysis..." << endl;

  wordmap w = TextAnalysis::getWordMap(words);
  vector<TextAnalysis::WordFrequency> wf = TextAnalysis::wordMapToSortedVector(w);

  cout << "Word Frequency for " << textFileName << endl << endl;
  cout << "Print top how many words? (ENTER to skip, 0 to show all)" << endl;
  getline(cin, command);

  if (command != "")
  {
    try
    {
      topFrequentWords = stoi(command);
    } catch (const invalid_argument&)
    {
      cout << "Invalid input, defaulting to showing all words." << endl;
    }

    wordmap topWords;
    for (unsigned int i = 0; (!topFrequentWords || i < topFrequentWords) && i < wf.size(); i++)
    {
      topWords[wf[i].word] = wf[i].frequency;
    }

    for (auto const &word : topWords)
    {
      cout << "\"" << word.first << "\" appeared " << word.second << " times." << endl;
    }
  }

  cout << endl << "GRAPHS FOR " << textFileName << endl;

  cout << "Output graphs? (Y/n)" << endl;

  if (tolower(getchar()) != 'n')
  {
    cout << endl << "Word Frequency By Number Of Characters" << endl << endl;
    wordLengthMap lengthMap = TextAnalysis::analyseWordLength(words);

    string bar = "";
    for (auto const &length : lengthMap)
    {
      cout.width(maxWordLengthDigits);
      cout.fill('0');

      cout << length.first << ": " << bar.append(length.second, barUnit) << endl;
      bar = "";
    }

    cout << endl << "AVG: " << TextAnalysis::averageWordLength(words) << endl;


    cout << endl << "Character frequency" << endl << endl;
    charmap charMap = TextAnalysis::getCharMap(words);

    for (auto const &letter : charMap)
    {
      cout << letter.first << ": " << bar.append(letter.second, barUnit) << endl;
      bar = "";
    }
  }

  cout << endl;
}

string getSortedTextContents(vector<string> combined)
{
  sort(combined.begin(), combined.end());
  string sortedTextOutput = "";

  for (string word: combined)
  {
    sortedTextOutput.append(word + "\n");
  }

  return sortedTextOutput;
}
