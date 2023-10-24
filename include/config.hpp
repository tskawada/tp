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
    int threshold;
    float alpha;
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
        cerr << "Error: input_folder is not set. Please set input_folder in config.txt." << endl;
        exit(1);
    }
    if (config.output_file == "") {
        cerr << "Error: output_file is not set. Please set output_file in config.txt." << endl;
        exit(1);
    }
    if (config.num_of_frames == 0) {
        cout << "Info: num_of_frames is not set. All images in input_folder will be used." << endl;
    }
    if (config.fps == 0.0) {
        cerr << "Error: fps is not set or invalid. Please set fps as a float number in config.txt." << endl;
        exit(1);
    }
    if (config.mode == 1) {
        if (config.threshold == 0) {
            cerr << "Error: threshold is not set or invalid. Please set threshold as a positive integer in config.txt." << endl;
            exit(1);
        }
        if (config.alpha == 0.0) {
            cerr << "Error: alpha is not set or invalid. Please set alpha as a float number in config.txt." << endl;
            exit(1);
        }
    } else if (config.mode != 0) {
        cerr << "Error: mode is invalid. mode must be 0 or 1." << endl;
        exit(1);
    }
    return 0;
}

void config_printer(Config config) {
    // get the longest string length of values
    int max_length = 0;
    if (config.input_folder.length() > max_length) max_length = config.input_folder.length();
    if (config.output_file.length() > max_length) max_length = config.output_file.length();
    if (to_string(config.mode).length() > max_length) max_length = to_string(config.mode).length();
    if (to_string(config.width).length() > max_length) max_length = to_string(config.width).length();
    if (to_string(config.height).length() > max_length) max_length = to_string(config.height).length();
    if (to_string(config.num_of_frames).length() > max_length) max_length = to_string(config.num_of_frames).length();
    if (to_string(config.fps).length() > max_length) max_length = to_string(config.fps).length();
    if (to_string(config.threshold).length() > max_length) max_length = to_string(config.threshold).length();
    if (to_string(config.alpha).length() > max_length) max_length = to_string(config.alpha).length();

    for (int n = 0; n < 20 + max_length; n++) cout << "-";
    cout << endl;
    cout << "| input_folder  | " << config.input_folder;
    for (int n = 0; n < max_length - config.input_folder.length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| output_file   | " << config.output_file;
    for (int n = 0; n < max_length - config.output_file.length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| mode          | " << config.mode;
    for (int n = 0; n < max_length - to_string(config.mode).length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| width         | " << config.width;
    for (int n = 0; n < max_length - to_string(config.width).length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| height        | " << config.height;
    for (int n = 0; n < max_length - to_string(config.height).length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| num_of_frames | " << config.num_of_frames;
    for (int n = 0; n < max_length - to_string(config.num_of_frames).length() + 1; n++) cout << " ";
    cout << "|" << endl;
    cout << "| fps           | " << config.fps;
    for (int n = 0; n < max_length - to_string(config.fps).length() + 8; n++) cout << " ";
    cout << "|" << endl;
    if (config.threshold != 0) {
        cout << "| threshold     | " << config.threshold;
        for (int n = 0; n < max_length - to_string(config.threshold).length() + 1; n++) cout << " ";
        cout << "|" << endl;
    }
    if (config.alpha != 0.0) {
        cout << "| alpha         | " << config.alpha;
        for (int n = 0; n < max_length - to_string(config.alpha).length() + 8; n++) cout << " ";
        cout << "|" << endl;
    }
    for (int n = 0; n < 20 + max_length; n++) cout << "-";
    cout << endl;
}

Config config_loader(string path) {
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
        .threshold = 0,
        .alpha = 0.0
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
        } else if (key == "num_of_frames") {
            config.num_of_frames = stoi(value);
        } else if (key == "fps") {
            config.fps = stod(value);
        } else if (key == "threshold") {
            config.threshold = stoi(value);
        } else if (key == "alpha") {
            config.alpha = stod(value);
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
