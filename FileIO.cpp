#include "FileIO.h"

bool compareScores(const Score& a, const Score& b) {
    return a.score > b.score;
}

void FileIO::saveScore(const std::string& name, int score) {
    // Step 1: Read all the scores from the file
    std::vector<Score> scores = loadScores();

    // Step 2: Find the index of the score for the user with the given name in the vector
    int index = -1;
    for (int i = 0; i < scores.size(); i++) {
        if (scores[i].name == name) {
            index = i;
            break;
        }
    }

    // Step 3: Update the score if the new score is greater than the old score
    if (index != -1 && score > scores[index].score) {
        scores[index].score = score;
    }

    // Step 4: Add a new score for the user to the vector if the user does not exist in the vector
    if (index == -1) {
        scores.push_back({ name, score });
    }

    // Step 5: Sort the vector based on the score in descending order
    std::sort(scores.begin(), scores.end(), compareScores);

    // Step 6: Write all the scores in the vector to the file
    std::ofstream file("Resources/Users.txt");
    if (file.is_open()) {
        for (const auto& score : scores) {
            file << score.name << "," << score.score << std::endl;
        }
        file.close();
    }
}

std::vector<Score> FileIO::loadScores() {
    std::vector<Score> scores;

    std::ifstream file("Resources/Users.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::string name;
            int score;
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            ss >> score;
            scores.push_back({ name, score });
        }
        file.close();
    }
    else {
        std::cout << "ERROR::GAME::COULD NOT OPEN SCORES FILE" << "\n";
    }

    std::sort(scores.begin(), scores.end(), compareScores);

    return scores;
}
