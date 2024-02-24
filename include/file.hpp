#include <iostream>
#include <string>
#include <vector>
#include <glob.h>
#include "exif.hpp"
#include <omp.h>

using namespace std;

struct Input {
    string input_dir;
    string file_extension;
    vector<string> files;
};

Input get_input_attributes(string input_dir) {
    Input input;

    glob_t globbuf;
    vector<string> files;
    
    glob((input_dir + "*.jpg").c_str(), 0, NULL, &globbuf);
    for (long unsigned int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.jpeg").c_str(), 0, NULL, &globbuf);
    for (long unsigned int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.JPG").c_str(), 0, NULL, &globbuf);
    for (long unsigned int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.JPEG").c_str(), 0, NULL, &globbuf);
    for (long unsigned int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    globfree(&globbuf);
    
    input.input_dir = input_dir;

    map<string, int> files_map = {};
    #pragma omp parallel for
    for (auto file : files) {
        files_map[file] = getDateTimeOriginalUnix(file);
    }
    sort(files.begin(), files.end(), [&files_map](const string& a, const string& b) {
        return files_map[a] < files_map[b];
    });
    input.files = files;

    input.file_extension = files[0].substr(files[0].find_last_of(".") + 1);

    return input;
}
