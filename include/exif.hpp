#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>

std::time_t convertDateTimeToUnixTime(const std::string& dateTimeStr) {
    std::tm tmStruct = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tmStruct, "%Y:%m:%d %H:%M:%S");
    return std::mktime(&tmStruct);
}

int getDateTimeOriginalUnix(const std::string path) {
    char command[256];
    std::snprintf(command, sizeof(command), "identify -format '%%[exif:DateTimeOriginal]' %s", path.c_str());

    FILE* identifyProcess = popen(command, "r");
    
    if (identifyProcess == nullptr) {
        std::cerr << "failed to open identify process" << std::endl;
        return 1;
    }

    char buffer[256];
    std::string result;

    while (fgets(buffer, sizeof(buffer), identifyProcess) != nullptr) {
        result += buffer;
    }
    pclose(identifyProcess);

    if (result.empty()) {
        std::cerr << "failed to get exif data" << std::endl;
        return 1;
    }

    std::time_t dateTimeOriginalUnix = convertDateTimeToUnixTime(result);
    return dateTimeOriginalUnix;

    return 0;
}
