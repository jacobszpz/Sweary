/**
 * Helper class for easy access to files
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * files.cpp
 * 2021-04-07
 */

#include <string>
#include <iostream>
#include <fstream>
#include "files.h"

using namespace std;
using namespace sweary;

// Retrieves contents from file in disk as a string
string Files::getContentsFromFile(string filename)
{
  string line;
  ifstream inputFile(filename);
  string fileContents = "";

  // Open text file and copy all lines
  if (inputFile.is_open())
  {
    while (getline(inputFile, line))
    {
      fileContents.append(line + '\n');
    }
  }
  else
  {
    cout << "File IO error when opening " << filename << endl;
  }

  // Remove last newline
  fileContents.pop_back();
  return fileContents;
}

// Writes string to file in disk
void Files::writeContentsToFile(string filename, string contents)
{
  ofstream outputFile(filename);

  if (outputFile.is_open())
  {
    outputFile << contents;
    outputFile.close();
  }
  else
  {
    cout << "File IO error when opening " << filename << endl;
  }
}
