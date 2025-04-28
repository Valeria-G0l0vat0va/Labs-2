#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>

bool createFileWithRandomNumbers(const std::string& fileName, const int numberCount, const int maxNumberCount) {
    srand(time(0));
    std::ofstream f(fileName);
    if (!f) {
        std::cerr << "Error when opening a file for writing." << std::endl;
        return false;
    }
    for (int i = 0; i < numberCount; i++) {
        int random = std::rand() % (maxNumberCount + 1);
        f << random << " ";
    }
    f.close();
    return true;
}

bool isFileContainsSortedArray(const std::string& fileName) {
    std::ifstream f(fileName);
    if (!f.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
        return false;
    }
    int currentValue;
    int previousValue;
    f >> previousValue;
    while (f >> currentValue) {
        if (currentValue < previousValue) {
            return false;
        }
        previousValue = currentValue;
    }
    return true;
}

int Empty(const std::string& fileName) {
    std::ifstream f(fileName);

    if (!f) {
        std::cerr << "Error open a file" << fileName << std::endl;
        return -1;
    }

    int x;
    if (f >> x) {
        return 1;
    }
    else {
        return 0;
    }
}

bool splitSort(const std::string& inputFile, const std::string& outputFile1, const std::string& outputFile2) {
    std::ifstream f(inputFile);
    std::ofstream fa(outputFile1);
    std::ofstream fb(outputFile2);

    if (!f.is_open() || !fa.is_open() || !fb.is_open()) {
        std::cerr << "Unable to open file: " << std::endl;
        return false;
    }
    int x1, x2, n;

    f >> x1;
    n = 0;
    while (!f.eof())
    {
        if (n == 0)
        {
            fa << x1 << " ";
        }
        else {
            fb << x1 << " ";
        }
        f >> x2;
        if (x1 > x2) {
            n = 1 - n;
        }
        x1 = x2;
    }
    f.close();
    fa.close();
    fb.close();
    return true;
}

bool mergeSort(const std::string& inputFile1, const std::string& inputFile2, const std::string& outputFile1, const std::string& outputFile2) {
    std::ifstream srcFiles[2] = {
        std::ifstream(inputFile1),
        std::ifstream(inputFile2)
    };
    std::ofstream dstFiles[2] = {
        std::ofstream(outputFile1),
        std::ofstream(outputFile2)
    };

    for (int i = 0; i < 2; i++) {

        if (!srcFiles[i].is_open() || !dstFiles[i].is_open()) {
            std::cerr << "Unable to open some work files." << std::endl;
            return false;
        }
    }

    int x[2], y[2];

    srcFiles[0] >> x[0];
    srcFiles[1] >> x[1];

    int n = 0, m = 0;
    while (!srcFiles[0].eof() && !srcFiles[1].eof())
    {
        if (x[m] > x[1 - m])
            m = 1 - m;
        dstFiles[n] << x[m] << " ";
        srcFiles[m] >> y[m];
        if (srcFiles[m].eof() || x[m] > y[m])
        {
            m = 1 - m;
            dstFiles[n] << x[m] << " ";
            srcFiles[m] >> y[m];
            while (!srcFiles[m].eof() && x[m] <= y[m])
            {
                x[m] = y[m];
                dstFiles[n] << x[m] << " ";
                srcFiles[m] >> y[m];
            }
            x[1 - m] = y[1 - m];
            n = 1 - n;
        }
        x[m] = y[m];
    }
    while (!srcFiles[0].eof())
    {
        dstFiles[n] << x[0] << " ";
        srcFiles[0] >> y[0];
        if (x[0] > y[0])
            n = 1 - n;
        x[0] = y[0];
    }
    while (!srcFiles[1].eof())
    {
        dstFiles[n] << x[1] << " ";
        srcFiles[1] >> y[1];
        if (x[1] > y[1])
            n = 1 - n;
        x[1] = y[1];
    }
    for (int i = 0; i < 2; i++) {
        srcFiles[i].close();
        dstFiles[i].close();
    }
    return true;
}

bool fileSort(const std::string& inputFile, const std::string& outputFile)
{
    std::ifstream f(inputFile);
    std::string srcFiles[2] = {
        "FileA.txt",
        "FileB.txt"
    };
    std::string dstFiles[2] = {
        "FileC.txt",
        "FileD.txt"
    };

    if (!splitSort(inputFile, srcFiles[0], srcFiles[1])) {
        std::cerr << "Error during splitting." << std::endl;
        return false;
    }

    while (Empty(srcFiles[1]) == 1) {
        if (!mergeSort(srcFiles[0], srcFiles[1], dstFiles[0], dstFiles[1])) {
            std::cerr << "Error during merging." << std::endl;
            return false;
        }

        std::swap(srcFiles[0], dstFiles[0]);
        std::swap(srcFiles[1], dstFiles[1]);
    }

    std::remove(outputFile.c_str());
    std::rename(srcFiles[0].c_str(), outputFile.c_str());
    return true;

}

int main()
{
    createFileWithRandomNumbers("File.txt", 15000, 15000);

    if (!fileSort("File.txt", "SortedFile.txt")) {
        std::cerr << "Sorting failed." << std::endl;
        return -1;
    }

    if (isFileContainsSortedArray("SortedFile.txt")) {
        std::cout << "The file contains a sorted array." << std::endl;
    }
    else {
        std::cerr << "The file does not contain a sorted array." << std::endl;
    }

    return 0;
}