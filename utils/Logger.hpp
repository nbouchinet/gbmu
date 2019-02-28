#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <string>
# include <fstream>

class Logger {
	public:
		enum LogOutput {
			Console,
			File
		};
		enum LogLevel {
			Error = 0,
			Warning = 1,
			Debug = 2
		};

		static Logger &getInstance() {
			static Logger instance;
			return instance;
		}

	private:
		Logger();

		void logToConsole(std::string const &message);
		void logToFile(std::string const &message);
		std::string makeLogEntry(LogLevel level, std::string const &message);

		std::string _logFilename;
		std::ofstream _file;
		LogLevel _level;

	public:
		Logger(Logger const &) = delete;
		void operator=(Logger const &) = delete;

		void log(LogLevel level, LogOutput output, std::string const &message);
		void setLogLevel(LogLevel lvl) { _level = lvl; }
};

#endif
