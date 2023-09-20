#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Config {
    string input_folder;
    string output_file;
    int mode;
    int width;
    int height;
    int num_of_frames;
    double fps;
    int level;
};

void split_string(const string& input, char delimiter, string& key, string& value) {
    size_t delimiterPos = input.find(delimiter);
    if (delimiterPos != string::npos) {
        key = input.substr(0, delimiterPos);
        value = input.substr(delimiterPos + 1);
    } else {
        cerr << "Error: key and value delimiter(" << delimiter << ") not found." << endl;
        cerr << "Invalid config file format." << endl;
        exit(1);
    }
}

int config_checker(Config config) {
    if (config.input_folder == "") {
        cerr << "Error: input_folder is not set." << endl;
        cerr << "Please set input_folder in config.txt." << endl;
        exit(1);
    }
    if (config.output_file == "") {
        cerr << "Error: output_file is not set." << endl;
        cerr << "Please set output_file in config.txt." << endl;
        exit(1);
    }
    if (config.width == 0) {
        cerr << "Error: width is not set or invalid." << endl;
        cerr << "Please set width as a postive integer in config.txt." << endl;
        exit(1);
    }
    if (config.height == 0) {
        cerr << "Error: height is not set or invalid." << endl;
        cerr << "Please set height as positive integer in config.txt." << endl;
        exit(1);
    }
    if (config.num_of_frames == 0) {
        cerr << "Error: num_of_frames is not set or invalid." << endl;
        cerr << "Please set num_of_frames as a positive integer in config.txt." << endl;
        exit(1);
    }
    if (config.fps == 0.0) {
        cerr << "Error: fps is not set or invalid." << endl;
        cerr << "Please set fps as a float number in config.txt." << endl;
        exit(1);
    }
    if (config.mode == 1) {
        if (config.level == 0) {
            cerr << "Error: level is not set or invalid." << endl;
            cerr << "Please set level as a positive integer in config.txt." << endl;
            exit(1);
        }    
    } else if (config.mode != 0) {
        cerr << "Error: mode is invalid." << endl;
        cerr << "mode must be 0 or 1." << endl;
        exit(1);
    }
    return 0;
}

void config_printer(Config config) {
    cout << "********************************************" << endl;
    cout << "input_folder: " << config.input_folder << endl;
    cout << "output_file: " << config.output_file << endl;
    cout << "mode: " << config.mode << endl;
    cout << "width: " << config.width << endl;
    cout << "height: " << config.height << endl;
    cout << "num_of_frames: " << config.num_of_frames << endl;
    cout << "fps: " << config.fps << endl;
    cout << "level: " << config.level << endl;
    cout << "********************************************" << endl;
}

Config config_loader(string path) {
    if (path == "") {
        path = "./assets/example.cfg";
    }
    ifstream ifs(path);
    string str;
    string key, value;

    Config config = {
        .input_folder = "",
        .output_file = "",
        .mode = -1,
        .width = 0,
        .height = 0,
        .num_of_frames = 0,
        .fps = 0.0,
        .level = 0,
    };

    if (ifs.fail()) {
        cerr << "Failed to open file." << endl;
        exit(1);
    }

    while (getline(ifs, str)) {
        split_string(str, '=', key, value);

        if (str[0] == '#') {
            continue;
        }

        if (key == "input_folder") {
            config.input_folder = value;
        } else if (key == "output_file") {
            config.output_file = value;
        } else if (key == "width") {
            config.width = stoi(value);
        } else if (key == "height") {
            config.height = stoi(value);
        } else if (key == "num_of_frames") {
            config.num_of_frames = stoi(value);
        } else if (key == "fps") {
            config.fps = stod(value);
        } else if (key == "level") {
            config.level = stoi(value);
        } else if (key == "mode") {
            config.mode = stoi(value);
        }
    }

    if(!config_checker(config)) {
        cout << "Config file loaded successfully." << endl;
    } else {
        exit(1);
    };

    ifs.close();
    return config;
}
