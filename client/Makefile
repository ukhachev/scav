TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one

SRCS = \
       project/src/action.cpp \
       project/src/connector.cpp \
       project/src/gamefield.cpp \
       project/src/game_object.cpp\
       project/src/action_constructor.cpp\
       project/src/box2d.cpp \
       project/src/physics_object.cpp \
       project/src/textures.cpp \
       project/src/map_constructor.cpp \
       project/src/physics_action.cpp \
       project/src/contact_listener.cpp \
       project/src/menu.cpp \
       project/src/animation.cpp \
       project/src/cursor.cpp \
       project/src/inventor.cpp \
       project/src/main.cpp
HDRS = \
	   ./project/include

CFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lpthread -lsfml-audio

.PHONY: all clean

all: $(SRCS)
	$(CXX)  -std=gnu++11 $(addprefix -I,$(HDRS)) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -rf $(TARGET)
