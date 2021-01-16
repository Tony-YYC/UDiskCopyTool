#pragma once
#include <sys/stat.h>
#include <string>

bool exist_test(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}