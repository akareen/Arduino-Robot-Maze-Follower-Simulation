CC := gcc
CFLAGS := -std=c17 -Wall #-Werror
LIBFLAGS :=  -ISDL2/include/SDL2  -ISDL2 -ISDL2/include 
LINKFLAGS := `sdl2-config --cflags --libs` -lm
WINFLAGS :=  -lmingw32 -LSDL2/lib -lSDL2main -lSDL2

###############################################
# Detect files and set paths accordingly
###############################################

TARGET := main

LIBDIR := lib
SRCDIR := src
BUILDDIR := build

SRCFILES := $(wildcard $(SRCDIR)/*.c)
OBJFILES := $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCFILES))

###############################################
# Compile files
###############################################

.PHONY: all
.PHONY: clean

# Windows version
ifeq ($(OS), Windows_NT)
all: ${TARGET}.exe

clean:
	rmdir /s /q ${BUILDDIR} 2> nul & del /f /q $(TARGET) $(TARGET).exe 2> nul

run: ${TARGET}.exe
	./${TARGET}.exe

# Linux/Mac Version
else
all: ${TARGET}

clean:
	rm -rf ${BUILDDIR}; rm -f $(TARGET); rm -f $(TARGET).exe

run: ${TARGET}
	./${TARGET}

endif


#################


$(TARGET): $(OBJFILES)
	$(CC) $^ $(LINKFLAGS) -o $@ 

$(TARGET).exe: $(OBJFILES)
	$(CC) $^  $(WINFLAGS) -o $@ 

$(BUILDDIR)/%.o : $(SRCDIR)/%.c $(LIBDIR)/%.h | $(BUILDDIR)
	$(CC) $(CFLAGS) $(LIBFLAGS) -I$(LIBDIR) -c $< -o $@ 

$(BUILDDIR): 
	mkdir build

#################
