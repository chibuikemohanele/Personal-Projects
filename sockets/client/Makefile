TARGET = client
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GPP = g++ -std=c++98 -g $(WARNING) $(ERROR) 

TESTFLAGS = #put testflags here
SRCS = client.cpp
OBJS = $(SRCS:%.cpp=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --leak-check=full --log-file=valgrind.log #put first testcase here

$(TARGET): $(OBJS) 
	$(GPP) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.cpp.o: 
	$(GPP) $(TESTFLAGS) -c $*.cpp 

testmemory: $(TARGET)
	$(VALGRIND)

#put testcases here
testall: test1 

#example of how to write code for a testcase
test1: $(TARGET)
	./client localhost 2000

test2: $(TARGET)
	./client cnn.com 80

clean: # remove all machine generated files
	rm -f $(TARGET) $(OBJS) -f -r  .vscode ../.vscode