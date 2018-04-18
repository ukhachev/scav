TARGET = server

HDRS = \
	   project/include

SRCS = \
	project/src/game_field.cpp \
	project/src/action_container.cpp \
	project/src/client_action.cpp \
	project/src/game_object.cpp \
	project/src/client_action_constructor.cpp \
	project/src/network.cpp \
	project/src/main.cpp

CFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lpthread

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++11 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(SRCS) $(CFLAGS)

test: test_client.cpp
	c++  -std=gnu++11 -Wall -Wextra -Werror -o test test_client.cpp $(CFLAGS)

clean:
	rm -rf $(TARGET)
