/*
    Name: Phillip Kobylinski
    File: main.cpp
    Date: 05/11/2022
    Assignment: Final Project
    Description: Entry point for the ray-tracing program.
    License: See LICENSE.txt
*/

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include "bmp.h"
#include "scene.h"

using namespace std;

enum Resolution
{
    Resolution_64x64 = 1,
    Resolution_128x128 = 2,
    Resolution_256x256 = 3,
    Resolution_512x512 = 4,
    Resolution_1024x1024 = 5,
};

static int ResToDim(Resolution res);
static std::string ResToString(Resolution res);

int main()
{
    Scene scene;
    string scenePath;

    // Load the scene
    cout << "Enter a file name scene you'd like to render: ";
    getline(cin, scenePath);
    scenePath.erase(remove(scenePath.begin(), scenePath.end(), '\"'), scenePath.end());
    ifstream sceneFile;
    sceneFile.open(scenePath);
    if (!sceneFile.is_open()) {
        cerr << "Error: Could not read file " << scenePath << endl;
        return -2;
    }
    if (!scene.LoadFromFile(sceneFile)) {
        cerr << "Error: Could not parse scene " << scenePath << endl;
        return -2;
    }
    sceneFile.close();

    // Select a resolution
    Resolution res;
    cout << "Resolutions:" << endl;
    for (int i = 1; i <= 5; ++i) {
        cout << "\t" << i << " - " << ResToString(Resolution(i)) << endl;
    }
    int choice;
    while (true) {
        cout << "What resolution do you wish to render at? ";
        cin >> choice;
        if (choice < 1 || choice > 6) {
            cout << "Invalid resolution, choose a number 1 through 5." << endl;
        } else {
            break;
        }
    }
    res = Resolution(choice);

    // Render the scene
    int w = ResToDim(res);
    int h = w;
    cout << "Rendering scene at " << ResToString(res) << "..." << endl;
    unique_ptr<uint32_t[]> bitmap(new uint32_t[size_t(w) * size_t(h)]);
    scene.Render(bitmap.get(), w, h);

    // Output to BMP file
    string bmpPath = scenePath.substr(0, scenePath.find_last_of(".")) + "_" + ResToString(res) + ".bmp";
    cout << "Outputting result to " << bmpPath << "..." << endl;
    ofstream bmpFile(bmpPath, ios_base::binary);
    if (!bmpFile.is_open()) {
        cerr << "Error: Could not open " << bmpPath << " for writing" << endl;
        return -2;
    }
    WriteBMP(bmpFile, bitmap.get(), w, h);
    bmpFile.close();

    cout << "Finished!" << endl;
    return 0;
}

//
// Function:    ResToDim
// Parameters:  Resolution
// Returns:     Dimension
// Description: Convert Resolution enum to integer dimension
//
static int ResToDim(Resolution res)
{
    return int(pow(2, 5 + int(res)));
}

//
// Function:    ResToString
// Parameters:  Resolution
// Returns:     Resolution string
// Description: Convert Resolution enum to human readable string
//
static std::string ResToString(Resolution res)
{
    string str;
    switch (res) {
        case Resolution_64x64:
            str = "64x64";
            break;
        case Resolution_128x128:
            str = "128x128";
            break;
        case Resolution_256x256:
            str = "256x256";
            break;
        case Resolution_512x512:
            str = "512x512";
            break;
        case Resolution_1024x1024:
            str = "1024x1024";
            break;
        default:
            str = "<INVALID>";
            break;
    }
    return str;
}

/*
    Sample output:

    Enter a file name scene you'd like to render: data\scene1.txt
    Resolutions:
            1 - 64x64
            2 - 128x128
            3 - 256x256
            4 - 512x512
            5 - 1024x1024
    What resolution do you wish to render at? 4
    Rendering scene at 512x512...
    Outputting result to scene1_512x512.bmp...
    Finished!
*/
