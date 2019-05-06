TARGET = #put executable name here
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c98 -g $(WARNING) $(ERROR) 

TESTFLAGS = #put testflags here

SRCS = #put .c srcs here
OBJS = $(SRCS:%.c=%.o)

VALGRIND = valgrind --tool=memcheck --verbose --leak-check=full --log-file=valgrind.log #put first testcase here

$(TARGET): $(OBJS) 
	$(GCC) $(TESTFLAGS) $(OBJS) -o $(TARGET)

.c.o: 
	$(GCC) $(TESTFLAGS) -c $*.c 

testmemory: $(TARGET)
	$(VALGRIND)

#put testcases here
testall: test1 test2 test3 test4 test5 test6 test7 test8

#example of how to write code for a testcase
test1: $(TARGET)
	./huff input/input1.bin output1.txt
	diff -i -w expected/expected1.txt output1.txt

clean: # remove all machine generated files
	rm -f $(TARGET) $(OBJS)