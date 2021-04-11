/**
 * Sweary: An Overzealous Profanity Checker
 * Contains information about Sweary
 *
 * Jacob Sanchez Perez (G20812080) <jsanchez-perez@uclan.ac.uk>
 * University of Central Lancashire
 *
 * sweary.h
 * 2021-04-07
 */

#ifndef SWEARY_H
#define SWEARY_H

#include <string>

namespace sweary
{
  const std::string title = "Sweary";
  const std::string description = "An Overzealous Profanity Checker";
  const std::string version = "v0.2";
  const std::string author = "Jacob Sanchez Perez";
  const std::string email = "jsanchez-perez@uclan.ac.uk";
  const std::string copyright = "Copyright (C) 2021";
  const std::string disclaimer = title + " " + version + ", " + copyright + " " + author + "\n"
                                 "" + title + " comes with ABSOLUTELY NO WARRANTY;\n"
                                 "This is free software, and you are welcome\n"
                                 "to redistribute it under certain conditions.";
}

#endif
