CXX	 = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
app: main.cpp threadfuncs.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
run: app
	./app
clean:
	rm -f app producer_consumer output.log trace.log
	rm -f app output.log trace.log
.PHONY:	run clean
producer_consumer: producer_consumer.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
