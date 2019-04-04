#include "Logger.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

Logger::Logger() : _level(Error) {
  _logFilename = std::string("gbmu.log");
  _file.open(_logFilename, std::ios::app);
}

std::string make_log_entry(Logger::LogLevel level, std::string const &message) {
  std::stringstream ss;
  char str[32] = {0};
  time_t current = std::time(nullptr);

  std::pair<Logger::LogLevel, std::string> level_str[] = {
      {Logger::Debug, "DEBUG"},
      {Logger::Warning, "WARNING"},
      {Logger::Error, "ERROR"}};

  for (int i = 0; i < 3; i++) {
    if (level_str[i].first == level) {
      ss << "[" << level_str[i].second << "]";
      break;
    }
  }

  std::strftime(str, sizeof(str), "%H:%M:%S", std::localtime(&current));
  ss << "[" << std::string(str) << "] " << message;

  return ss.str();
}

void Logger::log_to_console(std::string const &message) {
  std::cout << message << std::endl;
}

void Logger::log_to_file(std::string const &message) {
  if (!_file.is_open())
    return;
  _file << message << std::endl;
}

void Logger::log(LogLevel level, LogOutput output, std::string const &message) {
  void (Logger::*f[2])(const std::string &) = {&Logger::log_to_console,
                                               &Logger::log_to_file};
  LogOutput outputs[2] = {Console, File};

  if (_level < level)
    return;
  for (int i = 0; i < 2; i++) {
    if (output == outputs[i])
      (this->*f[i])(make_log_entry(level, message));
  }
}
