//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2013
//
//

#ifndef _LOGGER
#define _LOGGER

#include <string>

namespace imaging
{

	// Stateless logger: Opens and closes the file stream each time a new entry is written. 
	// All entries are appended after the first time the log is opened.
	// This is a single-instance object (singleton) and is shared by all logger-aware objects
	// (see implementation of the "Logged" base class below
	//
	class Logger
	{
	private:
		std::string log_filename;         // holds the filename of the log
		static Logger * logger_instance;  // holds the single instance of the logger

		Logger(std::string filename) :    // private constructor: you cannot create a new logger by calling "new"
		  log_filename(filename) {}       // but only by calling the "request()" or "create()" class member (see below) 
	public:
		
		static void create(std::string filename);  // Creates a Logger object and initializes the log file
		static Logger * request();                 // Returns a valid (the only) instance to a Logger object
		static void destroy();                     // Shuts down the logging facility and destroys the Logger object

		void write(std::string entry);             // Adds an entry to the log file. A timestamp is always inserted
		                                           // automatically with each entry (see Logger.cpp for the implementation)
	};


	// The Logger API used by the developer does not have to be aware of the above class. Instead, use the two 
	// initialization/destruction functions provided below, and derive your "log-enabled" class from the Logged class:


	//Use this function before starting any logging to create a global logger
	void createLogger(std::string logfile); 

	// Use this before the application closes to release the global logger
	void destroyLogger();

	// Generic class API to enable logging of objects' transactions to log files.
	// You can inherit this class (remember, multiple inheritance is allowed) in order to 
	// make your class logged. Then, you only have to call the member function "addLogEntry()"
	// from anywhere within the class code to report something to the log.
	class Logged
	{
	private:
		Logger *logger;

	protected:
		virtual /* (@) */ void addLogEntry(std::string entry); // Adds a log entry and prefixes it by the time stamp and the class id 
		                                                       // which added the entry to the log file
		
	public:
		Logged();
	};

	// (@) addLogEntry is declared as virtual in order for the typeid() operation to work (Logger.cpp)
	// See http://www.cplusplus.com/reference/typeinfo/type_info/
	// Do not trouble yourself with this (yet).


} //namespace imaging

#endif