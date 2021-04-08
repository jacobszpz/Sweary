/**
 * Helper class for easy access to files
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * files.h
 * 2021-04-07
 */

#ifndef SWEARY_FILES_H
#define SWEARY_FILES_H

#include <string>

namespace sweary
{
  class Files
  {
  public:
    static std::string getContentsFromFile(std::string filename);
    static void writeContentsToFile(std::string filename, std::string contents);
  };
}

#endif
