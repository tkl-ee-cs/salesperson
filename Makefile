TARGET = salesperson
CPPFLAGS = -Wall -std=c++11
SRC_DIR = src

$(TARGET) : $(SRC_DIR)/main.cpp
	g++ $(CPPFLAGS) $< -o $@ -lboost_program_options

clean :
	rm -f $(TARGET) *.o
