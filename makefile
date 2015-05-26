CC := g++
SRCDIR := src
BUILDDIR := build
BINDIR := bin
TARGET := main.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -c -pthread -std=c++0x
INC := -I include

.PHONY: run clean all

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -o $@ $<

$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) $^ -o $(BINDIR)/$(TARGET)

all: $(TARGET)

clean:
	-rm -rf $(BUILDDIR)
	-rm -rf $(BINDIR)

run: $(TARGET)
	./$(BINDIR)/$(TARGET)
