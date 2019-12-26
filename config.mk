# See LICENSE file for license and copyright information

VERSION = 0.1.0

# minimum required zathura version
ZATHURA_MIN_VERSION = 0.1.1
ZATHURA_VERSION_CHECK ?= $(shell pkg-config --atleast-version=$(ZATHURA_MIN_VERSION) zathura; echo $$?)

# paths
PREFIX ?= /usr
LIBDIR ?= ${PREFIX}/lib

# libs
CAIRO_INC ?= $(shell pkg-config --cflags cairo)
CAIRO_LIB ?= $(shell pkg-config --libs cairo)

GTK_INC ?= $(shell pkg-config --cflags gtk+-3.0)
GTK_LIB ?= $(shell pkg-config --libs   gtk+-3.0)

WEBKIT_INC ?= $(shell pkg-config --cflags webkitgtk-3.0)
WEBKIT_LIB ?= $(shell pkg-config --libs   webkitgtk-3.0)

ZATHURA_INC ?= $(shell pkg-config --cflags zathura)

INCS = ${GIRARA_INC} ${GTK_INC} ${WEBKIT_INC} ${ZATHURA_INC}
LIBS = ${GIRARA_LIB} ${GTK_LIB} ${WEBKIT_LIB}

# plugindir
PLUGINDIR ?= $(shell pkg-config --variable=plugindir zathura)
ifeq (,${PLUGINDIR})
PLUGINDIR = ${LIBDIR}/zathura
endif

# flags
CFLAGS += -std=c99 -fPIC -pedantic -Wall -Wno-format-zero-length $(INCS)

# debug
DFLAGS ?= -g

# build with cairo support?
WITH_CAIRO ?= 1

# compiler
CC ?= gcc
LD ?= ld

# set to something != 0 if you want verbose build output
VERBOSE ?= 0
