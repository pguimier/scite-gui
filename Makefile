CC           = g++           # use GNU C++ compiler
CC-FLAGS     = -Wall -c      # warn all
LD       = g++           # use GNU C++ as linker 
LD-FLAGS = -shared -o   # flags for linker (-o must be last)
RM           = rm -f         # how to remove files
MAKE         = make          # name of make utility 
OBJS         = lgui.o LuaControls.o LuaControl.o GTKControl.o PageControl.o ListView.o Buttons.o Splitter.o Menu.o Dialogs.o TextControls.o Container.o
TARGET       = gui.so        # name of executable
LUA_PATH     = ./lua
LUA_INCS     = -I$(LUA_PATH)/include -I$(LUA_PATH)/src
GTK_INC      = `pkg-config --cflags --libs gtk+-2.0`

INC          = $(LUA_INCS) $(GTK_INC)

$(TARGET): $(OBJS)
	$(LD) $(INC) $(LD-FLAGS) $@ $(OBJS)

debug.so: $(OBJS)
	$(LD) $(INC) -llua5.1 $(LD-FLAGS) $@ $(OBJS)>/dev/null  #maybe needed (if lua not found): sudo ln -s /usr/lib/liblua5.1.so.0 /usr/lib/liblua5.1.so
	ldd -r $@ >/dev/null
	$(RM) $@ >/dev/null

#create from all *.cxx the .o with same basename
#.cxx.o:
%.o : %.cxx
	$(CC) $(INC) $(CC-FLAGS) $<
	
clean:
	$(RM) *.o

