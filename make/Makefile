TARGET = IOMFB-dos-1

ARCH    ?= arm64
SDK     ?= iphoneos

CLANG    := $(shell xcrun --sdk $(SDK) --find clang)
ifeq ($(CLANG),)
$(error Could not find clang for SDK $(SDK))
endif
SYSROOT  := $(shell xcrun --sdk $(SDK) --show-sdk-path)
CC       := $(CLANG) -isysroot $(SYSROOT) -arch $(ARCH)
CODESIGN := codesign

CFLAGS = -O2 -Wall -Werror -Wpedantic -Wno-gnu -DSTANDALONE=1

FRAMEWORKS = -framework IOKit

SOURCES = ../IOMFB-DOS-1/IOMFB_DOS_1.c

HEADERS =

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(FRAMEWORKS) $(DEFINES) -o $@ $(SOURCES)
	$(CODESIGN) -s - $@

clean:
	rm -f -- $(TARGET)
