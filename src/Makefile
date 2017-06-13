TARGET=engine
OBJDIR = obj/
OBJS = $(OBJDIR)dungeon.o $(OBJDIR)main.o $(OBJDIR)Logger.o $(OBJDIR)Settings.o $(OBJDIR)Timer.o $(OBJDIR)Texture.o $(OBJDIR)Audio.o $(OBJDIR)Mesh.o $(OBJDIR)glHelper.o $(OBJDIR)Model.o $(OBJDIR)WakeEngine.o  $(OBJDIR)Camera.o $(OBJDIR)PhysicsModel.o $(OBJDIR)Text.o $(OBJDIR)entity.o
CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS= -g -std=gnu++11 -Wall -c  -I/usr/include/freetype2  
CPPFLAGSNOWARNING = -g -std=gnu++11 -c
LDFLAGS = -Wall -g
LDLIBS= -lSDL2 -lSDL2_image -lSDL2_mixer -lGL -lglut -lGLU -lGLEW -lassimp -lpng -lfreetype
ODIR = -o $(OBJDIR)
SRCS = $(wildcard *.cpp)
ESRCS = $(wildcard wakeEngine/*.cpp);

#all: $(SRCS)
#	$(CXX) $(CPPFLAGS) $(ESRCS) $(SRCS) -g -Wall $(LDLIBS) -o $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) $(LDFLAGS) -o ../$@

$(OBJDIR)dungeon.o: dungeon.cpp dungeon.h
		$(CXX) $(CPPFLAGS) $(LDLIBS) dungeon.cpp -o $@

$(OBJDIR)main.o: main.cpp
	$(CXX) $(CPPFLAGS) $(LDLIBS) main.cpp -o $@

# wakeEngine makes
$(OBJDIR)Logger.o: wakeEngine/Logger.cpp wakeEngine/Logger.h
	$(CXX) $(CPPFLAGSNOWARNING) $(LDLIBS) wakeEngine/Logger.cpp -o $@

$(OBJDIR)Settings.o: wakeEngine/Settings.cpp wakeEngine/Settings.h wakeEngine/Logger.h wakeEngine/includes.h
	$(CXX) $(CPPFLAGSNOWARNING) $(LDLIBS) wakeEngine/Settings.cpp -o $@

$(OBJDIR)Timer.o: wakeEngine/Timer.cpp wakeEngine/Timer.h wakeEngine/Logger.h
	$(CXX) $(CPPFLAGSNOWARNING) $(LDLIBS) wakeEngine/Timer.cpp -o $@

$(OBJDIR)WakeEngine.o: wakeEngine/WakeEngine.cpp wakeEngine/WakeEngine.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/WakeEngine.cpp -o $@

$(OBJDIR)Texture.o: wakeEngine/Texture.cpp wakeEngine/Texture.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Texture.cpp -o $@

$(OBJDIR)Audio.o: wakeEngine/Audio.cpp wakeEngine/Audio.cpp
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Audio.cpp -o $@

$(OBJDIR)Mesh.o: wakeEngine/Mesh.cpp wakeEngine/Mesh.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Mesh.cpp -o $@

$(OBJDIR)glHelper.o: wakeEngine/glHelper.cpp wakeEngine/glHelper.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/glHelper.cpp -o $@

$(OBJDIR)Camera.o: wakeEngine/Camera.cpp wakeEngine/Camera.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Camera.cpp -o $@

$(OBJDIR)PhysicsModel.o: wakeEngine/PhysicsModel.cpp wakeEngine/PhysicsModel.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/PhysicsModel.cpp -o $@

$(OBJDIR)Model.o: wakeEngine/Model.cpp wakeEngine/Model.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Model.cpp -o $@

$(OBJDIR)Text.o: wakeEngine/Text.cpp wakeEngine/Text.h
	$(CXX) $(CPPFLAGS) $(LDLIBS) wakeEngine/Text.cpp -o $@

$(OBJDIR)entity.o: entity.cpp entity.h
		$(CXX) $(CPPFLAGS) $(LDLIBS) entity.cpp -o $@


clean:
	rm -f obj/*.o
