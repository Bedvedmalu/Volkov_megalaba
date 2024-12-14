#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
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

void option10(std::unordered_map<int, pipeline>& pipelines, std::unordered_map<int, compressorstation>& css);


template<typename T>
std::vector<T> Kan_by_Volkov(std::unordered_map<T, std::unordered_set<T>>& graph)
{
	std::unordered_map<T, int> inDegree;

	for (const auto& pair : graph) {
		const T& vertex = pair.first;
		inDegree[vertex] = 0;
	}

	for (const auto& pair : graph) {
		const T& vertex = pair.first;
		for (const T& neighbor : pair.second) {
			inDegree[neighbor]++;
		}
	}

	std::queue<T> zero;

	for (const auto& pair : inDegree) {
		if (pair.second == 0) {
			zero.push(pair.first);
		}
	}

	std::vector<T> sort;
	while (!zero.empty()) {
		T vertex = zero.front();
		zero.pop();
		sort.push_back(vertex);

		for (const T& neighbor : graph.at(vertex)) {
			inDegree[neighbor]--;
			if (inDegree[neighbor] == 0) {
				zero.push(neighbor);
			}
		}
	}

	if (sort.size() != inDegree.size()) {
		return {  };
	}

	else {
		return sort;
	}
}
