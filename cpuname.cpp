//
// Created by andrew on 10/29/26.
//

#include <fstream>
#include <string>
#include <sstream>

#include "redux.hpp"

std::string getCpuNameFromProc() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.rfind("model name", 0) == 0 || line.rfind("Model", 0) == 0 || line.rfind("Hardware", 0) == 0) {
            auto colon = line.find(':');
            if (colon != std::string::npos) {
                // Skip colon and any leading whitespace
                size_t start = line.find_first_not_of(" \t", colon + 1);
                if (start != std::string::npos) {
                    return line.substr(start);
                }
            }
        }
    }
    return "Unknown CPU";
}