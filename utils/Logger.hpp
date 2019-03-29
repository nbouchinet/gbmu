#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <fstream>
#include <string>

class Logger {
 public:
  enum LogOutput { Console, File };
  enum LogLevel { Error = 0, Warning = 1, Debug = 2 };

  static Logger &instance() {
    static Logger instance;
    return instance;
  }

  static void log(const std::string &message, LogLevel level = Error,
                  LogOutput out = Console) {
    instance().log(level, out, message);
  }

 private:
  Logger();

  void log_to_console(const std::string &message);
  void log_to_file(const std::string &message);

  std::string _logFilename;
  std::ofstream _file;
  LogLevel _level;

 public:
  Logger(const Logger &) = delete;
  void operator=(const Logger &) = delete;

  void log(LogLevel level, LogOutput output, const std::string &message);
  void setLogLevel(LogLevel lvl) { _level = lvl; }
};

#endif
