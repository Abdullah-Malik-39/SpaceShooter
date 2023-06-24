#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

struct Score {
    std::string name;
    int score;
};

class FileIO {
public:
    void saveScore(const std::string& name, int score);
    std::vector<Score> loadScores();
};

#endif
