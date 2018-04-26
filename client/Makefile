TARGET = main.out

# XXX: Don't forget backslash at the end of any line except the last one

SRCS = \
       action.cpp \
       connector.cpp \
       gamefield.cpp \
       game_object.cpp\
       action_constructor.cpp\
       box2d.cpp \
       physics_object.cpp \
       main.cpp \
       view.cpp
HDRS = \
	   .

CFLAGS =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lpthread

.PHONY: all clean

all: $(SRCS)
	$(CXX)  -std=gnu++11 $(addprefix -I,$(HDRS)) -o $(TARGET) $(SRCS) $(CFLAGS)

clean:
	rm -rf $(TARGET)
