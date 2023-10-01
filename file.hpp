#include <iostream>
#include <string>
#include <vector>
#include <glob.h>

using namespace std;

struct Input {
    string input_dir;
    string file_extension;
    int file_num;
};

Input get_input_attributes(string input_dir) {
    Input input;

    glob_t globbuf;
    vector<string> files;
    
    glob((input_dir + "*.jpg").c_str(), 0, NULL, &globbuf);
    for (int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.jpeg").c_str(), 0, NULL, &globbuf);
    for (int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.JPG").c_str(), 0, NULL, &globbuf);
    for (int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    glob((input_dir + "*.JPEG").c_str(), 0, NULL, &globbuf);
    for (int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    globfree(&globbuf);
    
    input.input_dir = input_dir;
    input.file_num = files.size();
    input.file_extension = files[0].substr(files[0].find_last_of(".") + 1);

    return input;
}
