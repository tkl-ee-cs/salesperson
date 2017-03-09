TARGET = salesperson
CFLAGS = -Wall
SRC_DIR = src

$(TARGET) : $(SRC_DIR)/main.cpp
	g++ $< -o $@ -lboost_program_options

clean :
	rm -f $(TARGET) *.o
