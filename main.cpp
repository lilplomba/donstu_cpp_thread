#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <string>
#include <future>
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
	std::thread::id mainId = std::this_thread::get_id();
	if(!threads.empty() && threads[0].get_id() == mainId) {
	std::cout << " thread 0 == main (не должно случиться)" << std::endl;
}	else {
	std::cout << " thread 0 != main (ожидаемо) " << std::endl;
} 
	std::cout << "atomicCounter = " << atomicCounter.load() << std::endl;
	std::cout << "plainCounter = " << plainCounter << std::endl;

{
	std::promise<std::string> prom;
	std::future<std::string> fut = prom.get_future();
	ThreadArgs arg;
	arg.id = 100;
	arg.tag = "PROMISE";
	arg.message = "returning value via promise";

	std::thread t([&arg, p = std:: move(prom)]() mutable {
	std::ostringstream oss;
	oss << "thread " << arg.tag << "finished";
	p.set_value(oss.str());
});
	std::string result = fut.get();
	std::cout << "[promise/future] result = " << result << std::endl;
	logger.writeLine("[promise/future] result = " + result);
	t.join();
}
	{
	ThreadArgs arg;
	arg.id = 101;
	arg.tag = "ASYNC";
	arg.message = "returning value via async";
	auto fut2 = std::async(std::launch::async, [&arg]() -> std::string {
	std::ostringstream oss;
	oss << "async thread " << arg.tag << "done" ;
	return oss.str();
});
	std::string result2 = fut2.get();
	std::cout << "[async] result = " << result2 << std::endl;
	logger.writeLine("[async] result = " + result2);
}
	
  return 0;
}
