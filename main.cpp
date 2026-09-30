#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <string>

#include "threadfuncs.h"

int main() {
  about();

  // Open log file
  Logger logger("output.log");

{
	std::ostringstream oss;
	oss << "main: pid = " << getProcessID()
	<< " thread_id = " << std::this_thread::get_id();
	logger.writeLine(oss.str());
}

  // args for threads
  std::vector<ThreadArgs> args(COUNT_THREADS);

for (int i = 0; i< COUNT_THREADS; ++i) {
	args[i].id = i;
	args[i].tag = "T" + std::to_string(i);
}


  // thread are starting
  std::vector<std::thread> threads;
  threads.reserve(COUNT_THREADS);

  for (int i = 0; i < COUNT_THREADS; ++i) {
    threads.emplace_back(funcThread, std::cref(args[i]), std::ref(logger));
  }

  // wait for stop all thread
 	 for (auto& t : threads) {
	  if (t.joinable()) t.join();
  }

  // close file automatically
{
	std::ostringstream oss;
	oss << "main:pid = " << getProcessID()
	<< " thread_id = " << std::this_thread::get_id();
	logger.writeLine(oss.str());
} 
  return 0;
}
