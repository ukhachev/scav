TARGET = main.out

HDRS = \
	   project/include

SRCS = \
	project/src/game_field.cpp \
	project/src/action_container.cpp \
	project/src/client_action.cpp \
	project/src/game_object.cpp \
	project/src/client_action_constructor.cpp

CFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network

.PHONY: all clean

all: $(SRCS)
	$(CXX) -std=gnu++11 -Wall -Wextra -Werror $(addprefix -I,$(HDRS)) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -rf $(TARGET)
