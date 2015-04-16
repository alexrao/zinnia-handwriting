#############################################################################
## compiler and related, set or default

# CC
CC := $(CROSS_COMPILER)gcc

# CXX
CXX := $(CROSS_COMPILER)g++

# # AR
# AR ?= $(CROSS_COMPILER)ar

# # RANLIB
# RANLIB ?= $(CROSS_COMPILER)ranlib

# LINKER
LINKER ?= $(CXX)

# STRIP
STRIP := $(CROSS_COMPILER)strip

QT_MOC := $(QT_MOC)


#############################################################################
## CFLAGS, CXXFLAGS and LDFLAGS
#
BUILD_ROOT ?= .
PATH2INC ?= $(BUILD_ROOT)/include
CFLAGS += -I$(PATH2INC)
CFLAGS += -DUNICODE
CFLAGS += -Wall -Wno-unused-parameter
# deps
CFLAGS += -Wp,-MD,$@.d

CXXFLAGS += -I$(PATH2INC)
CXXFLAGS += -Wall -Wno-unused-parameter
CXXFLAGS += -DUNICODE
# deps
CXXFLAGS += -Wp,-MD,$@.d
ifneq ($(GCCONW),)
CXXFLAGS += -I../../../usr/qt-5.4.1-o-msw/5.4/mingw491_32/include
endif
CXXFLAGS += -DID_QT_VERSION=$(ID_QT_VERSION)

ifneq ($(MINGW32),)
CXXFLAGS += -DMINGW32=1
endif
# CXXFLAGS_MOC += -Iinclude
CXXFLAGS_MOC += -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED


# ##
# ARFLAGS = crv

## LDFLAGS
ifneq ($(MINGW32),)
  ifneq ($(QT4),)
    LDFLAGS += -L$(BUILD_ROOT)/lib
    LDFLAGS += -lQtCore4
    LDFLAGS += -lQtGui4
  else
    LDFLAGS += -L../../../usr/qt-5.4.1-o-msw/5.4/mingw491_32/lib
    LDFLAGS += -lQt5Core
    LDFLAGS += -lQt5Gui
    LDFLAGS += -lQt5Widgets
  endif # ifneq ($(QT4),)
  LDEXTRA += $(BUILD_ROOT)/lib/libzinnia.lib
else
  LDFLAGS += -L$(BUILD_ROOT)/lib
  LDFLAGS += -lQtCore
  LDFLAGS += -lQtGui
endif


#############################################################################
## VPATH
VPATH += $(BUILD_ROOT)/include


#############################################################################
## out
OUT ?= .

# out
VPATH += $(OUT)


## TARGET
#
ifneq ($(MINGW32),)
  TARGET1 ?= $(OUT)/simple-demo.exe
else
  TARGET1 ?= $(OUT)/simple-demo
endif

#
TARGET += $(TARGET1)
all: .ready $(TARGET)
	@echo "all done"


#############################################################################
## OBJS
#
SUFFIX_OBJ ?= .o

#
OBJS_COMMON +=

#
OBJS += $(OBJS_COMMON)
OBJS += $(OUT)/main$(SUFFIX_OBJ)
OBJS += $(OUT)/handwritor$(SUFFIX_OBJ)
# # moc_
OBJS += $(OUT)/moc_/handwritor$(SUFFIX_OBJ)


#############################################################################
## build
#
.ready:
	@mkdir -p $(OUT)

#
$(TARGET): $(OBJS)
	$(LINKER) -o $@ $^ $(LDFLAGS) $(LDEXTRA)
ifeq ($(MINGW32),)
	$(STRIP) $@
endif

$(OUT)/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
$(OUT)/%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OUT)/moc_%.cpp: include/%.h
	$(QT_MOC) -o $@ $< $(CXXFLAGS_MOC)


#############################################################################
## deps
eac_files := $(foreach f,$(OBJS),$(OUT)/.$(f).d) # each
dep_files := $(wildcard $(eac_files)) # depend
ifneq ($(dep_files),)
  include $(dep_files)
endif

# common


#############################################################################
## clean
clean:
	@rm -fv $(OBJS) $(TARGET)

distclean: clean
	@rm -fv $(OUT)/*.o.d
ifneq ($(OUT), .)
	@rmdir $(OUT)/
endif

# UPDATE_COMMON
UPDATE_COMMON:
	cd $(PWD)/common; ./update.gitrepo.sh $(PWD)/common

## install

install: .ready $(TARGET)
ifeq ($(PREFIX),)
	$(error "install: should provide a NOT-NULL PREFIX")
endif
	install -d $(PREFIX)/bin
	install -m 775 $(TARGET1) $(PREFIX)/bin

##
.PHONY: all install clean distclean .ready


## ========================================================================= #
#
#        Filename:  Makefile
#
#     Description:
#
# - Mode: 644
# - NOTE. NOT use "dos"
# - Updated: TODO
#
#         Version:  1.0.0
#         Created:  2015-04-16 13:38:17
#        Revision:	1.0.0
#
## ========================================================================= #
