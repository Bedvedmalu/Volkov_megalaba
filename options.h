#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unordered_set>
#include "pipeline.h"
#include "compressorstation.h"
#include "utils.h"
#include <chrono>

void option1(std::unordered_map<int, pipeline>& pipelines);

void option2(std::unordered_map<int, compressorstation>& css);

void option3(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);

void option4(std::unordered_map<int, pipeline>& pipelines);

void option5(std::unordered_map<int, compressorstation>& css);

void option6(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);

void option7(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);

void option8(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);

void option9(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css, std::unordered_set<int>& keys);