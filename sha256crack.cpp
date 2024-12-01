#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <thread>
#include <vector>
#include <mutex>
#include <fstream>
#include <sstream>

std::mutex printMutex;

std::string sha256(const std::string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, data.c_str(), data.length());
    SHA256_Final(hash, &sha256_ctx);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

void bruteForceThreaded(const std::string& targetHash, const std::string& charset, const std::string& prefix, int maxLen, int startIdx, int step) {
    if (prefix.length() == maxLen) {
        std::string passwordHash = sha256(prefix);
        if (passwordHash == targetHash) {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "!!password found!!: " << prefix << std::endl;
        }
        return;
    }

    for (int i = startIdx; i < charset.size(); i += step) {
        bruteForceThreaded(targetHash, charset, prefix + charset[i], maxLen, startIdx, step);
    }
}

void startBruteForce(const std::string& targetHash, const std::string& charset, int maxLen, int totalThreads) {
    std::vector<std::thread> threads;
    for (int i = 0; i < totalThreads; ++i) {
        threads.push_back(std::thread(bruteForceThreaded, targetHash, charset, "", maxLen, i, totalThreads));
    }

    for (auto& t : threads) {
        t.join();
    }
}

void dictionaryAttack(const std::string& targetHash, const std::string& dictionaryFile) {
    std::ifstream file(dictionaryFile);
    if (!file.is_open()) {
        std::cout << "could not open dictionary file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string hash = sha256(line);
        if (hash == targetHash) {
            std::lock_guard<std::mutex> lock(printMutex);
            std::cout << "!!password found (dictionary)!!: " << line << std::endl;
            file.close();
            return;
        }
    }

    file.close();
    std::cout << "password not found in dict." << std::endl;
}

int main() {
    std::string targetHash;
    std::cout << "enter target sha256 hash: ";
    std::getline(std::cin, targetHash);

    std::string defaultCharset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()";
    int defaultMaxLen = 10;

    std::cout << "do you want to use default charset and maxlen 10? (y/n): ";
    char useDefault;
    std::cin >> useDefault;

    std::string charset;
    int maxLen;

    if (useDefault == 'y' || useDefault == 'Y') {
        charset = defaultCharset;
        maxLen = defaultMaxLen;
        std::cout << "using default charset and maxLen of " << maxLen << std::endl;
    } else {
        std::cout << "enter your custom charset (or press enter to use the default): ";
        std::cin.ignore();
        std::getline(std::cin, charset);

        if (charset.empty()) {
            charset = defaultCharset;
        }

        std::cout << "enter the maxLen for the password: ";
        std::cin >> maxLen;

        std::cout << "using charset: " << charset << " and maxLen: " << maxLen << std::endl;
    }

    int totalThreads = std::thread::hardware_concurrency();
    std::cout << "using " << totalThreads << " threads based on your system's CPU cores." << std::endl;

    char attackMode;
    std::cout << "choose attack mode (b for brute-force, d for dictionary): ";
    std::cin >> attackMode;

    if (attackMode == 'b' || attackMode == 'B') {
        std::cout << "starting bruteforce attack..." << std::endl;
        startBruteForce(targetHash, charset, maxLen, totalThreads);
    } else if (attackMode == 'd' || attackMode == 'D') {
        std::string dictionaryFile;
        std::cout << "enter dictionary file path: ";
        std::cin >> dictionaryFile;
        std::cout << "starting dictionary attack..." << std::endl;
        dictionaryAttack(targetHash, dictionaryFile);
    } else {
        std::cout << "invalid attack mode. exiting." << std::endl;
    }

    return 0;
}
