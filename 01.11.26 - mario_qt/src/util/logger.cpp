/**
	- Почему instance является статической локальной переменной?
	- Как реализовать getInstance() без многопоточности?
*/

#include "logger.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

using biv::Logger;

Logger::Logger() {
	log_file.open("super_mario_log.log", std::ios::out | std::ios::trunc);
	if (!log_file.is_open()) {
		std::cerr << "[ERROR] Failed to create/open super_mario_log.log" << std::endl;
	} else {
		log_info("Logger initialized. Game started.");
	}
}

Logger::~Logger() {
	if (log_file.is_open()) {
		log_info("Logger shutting down. Game finished.");
		log_file.close();
	}
}

Logger& Logger::getInstance() {
	static Logger instance;
	return instance;
}

void Logger::log_info(const std::string& message) {
	std::lock_guard<std::mutex> lock(log_mutex);
	
	if (log_file.is_open()) {
		auto now = std::chrono::system_clock::now();
		std::time_t now_c = std::chrono::system_clock::to_time_t(now);
		std::tm* local_time = std::localtime(&now_c);

		if (local_time) {
			log_file 
				<< "[" 
				<< std::put_time(local_time, "%Y-%m-%d %H:%M:%S") 
				<< "] [INFO] " 
				<< message 
				<< "\n";
			log_file.flush(); 
		}
	} else {
		std::cerr << "[ERROR] Log file is not open!" << std::endl;
	}
}
