SOURCES += main.cpp \
 bant.cpp \
 bantsmell.cpp \
 bfield.cpp \
 barea.cpp \
 bwidget.cpp \
 bhomefield.cpp \
 bfoodfield.cpp
TEMPLATE = app
CONFIG += warn_on \
	  qt \
 opengl
TARGET = ../bin/bant

HEADERS += bant.h \
 bantsmell.h \
 bfield.h \
 brand.h \
 barea.h \
 bwidget.h \
 bhomefield.h \
 bfoodfield.h \
 bdebug.h

OBJECTS_DIR = .lib


MOC_DIR = .moc

CONFIG -= stl \
thread
FORMS += bantviewwidget.ui

QT += opengl

UI_DIR = .ui

