TARGET = main.out

HDRS = \
	   project/include

SRCS = \
       project/src/HelloWorld.cpp \
       project/src/box2d.cpp

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++11 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf $(TARGET)
