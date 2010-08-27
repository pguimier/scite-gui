CC           = g++           # use GNU C++ compiler
CC-FLAGS     = -Wall -c      # warn all
LINKER       = g++           # use GNU C++ as linker 
LINKER-FLAGS = -shared -o   # flags for linker (-o must be last)
RM           = rm -f         # how to remove files
MAKE         = make          # name of make utility 
OBJS         = lgui.o LuaControl.o PageControl.o LuaControls.o
TARGET       = gui.so        # name of executable
LUA_PATH     = /usr/src/scite/scite_ru_older/src/scite/lua
LUA_INCS     = -I$(LUA_PATH)/include -I$(LUA_PATH)/src
GTK_INC      = `pkg-config --cflags --libs gtk+-2.0`

INC          = $(LUA_INCS) $(GTK_INC)

$(TARGET): $(OBJS)
	$(LINKER) $(INC) $(LINKER-FLAGS) $@ $(OBJS)

#create from all *.cxx the .o with same basename
#.cxx.o:
%.o : %.cxx
	$(CC) $(INC) $(CC-FLAGS) $<
	
clean:
	$(RM) *.o

