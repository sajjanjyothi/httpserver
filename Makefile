 CPP = g++
 RM = rm -f 
 CFLAGS = -std=c++17
 
  # compiler flags:
  #  -g     - this flag adds debugging information to the executable file
  #  -Wall  - this flag is used to turn on most compiler warnings
 
  # The build target 
TARGET = server
OBJS = server.o http_server.o
LIBS = -lpthread
all: $(TARGET)
 
$(TARGET): $(OBJS)
	$(CPP) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
%.o : %.cpp 
	$(CPP) $(CFLAGS) -c -o $@ $< 

clean:
	$(RM) $(TARGET) $(OBJS)