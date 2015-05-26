CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -pthread -std=c++0x
INC := -I include

.PHONY: run clean all

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) -c -Wall $(CFLAGS) $(INC) -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(CFLAGS)

all: $(TARGET)

clean:
	-rm -rf $(BUILDDIR)

run: $(TARGET)
	./$(TARGET)
