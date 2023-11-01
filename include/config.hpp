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

void print_one_attribute(string key, string value, long unsigned int max_length) {
    // if value is string, print with quotation marks
    cout << key << value;
    for (long unsigned int n = 0; n < max_length - value.length() + 1; n++) cout << " ";
    cout << "|" << endl;
}

void print_one_attribute(string key, int value, long unsigned int max_length) {
    cout << key << value;
    for (long unsigned int n = 0; n < max_length - to_string(value).length() + 1; n++) cout << " ";
    cout << "|" << endl;
}

void config_printer(Config config) {
    // get the longest string length of values
    long unsigned int max_length = 0;
    if (config.input_folder.length() > max_length) max_length = config.input_folder.length();
    if (config.output_file.length() > max_length) max_length = config.output_file.length();
    if (to_string(config.mode).length() > max_length) max_length = to_string(config.mode).length();
    if (to_string(config.width).length() > max_length) max_length = to_string(config.width).length();
    if (to_string(config.height).length() > max_length) max_length = to_string(config.height).length();
    if (to_string(config.num_of_frames).length() > max_length) max_length = to_string(config.num_of_frames).length();
    if (to_string(config.fps).length() > max_length) max_length = to_string(config.fps).length();
    if (to_string(config.threshold).length() > max_length) max_length = to_string(config.threshold).length();
    if (to_string(config.alpha).length() > max_length) max_length = to_string(config.alpha).length();

    for (long unsigned int n = 0; n < 20 + max_length; n++) cout << "-";
    cout << endl;

    print_one_attribute("| input_folder  | ", config.input_folder, max_length);
    print_one_attribute("| output_file   | ", config.output_file, max_length);
    print_one_attribute("| mode          | ", config.mode, max_length);
    print_one_attribute("| width         | ", config.width, max_length);
    print_one_attribute("| height        | ", config.height, max_length);
    print_one_attribute("| num_of_frames | ", config.num_of_frames, max_length);
    print_one_attribute("| fps           | ", config.fps, max_length);
    if (config.threshold != 0) {
        print_one_attribute("| threshold     | ", config.threshold, max_length);
    }
    if (config.alpha != 0.0) {
        print_one_attribute("| alpha         | ", config.alpha, max_length);
    }
    for (long unsigned int n = 0; n < 20 + max_length; n++) cout << "-";
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
