/*
 * MIT License
 * 
 * Copyright (c) 2026 Andrew Ellis Page
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * SPDX short identifier: MIT
 */

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