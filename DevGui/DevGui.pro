######################################################################
# Automatically generated by qmake (2.01a) Fri Aug 1 19:38:51 2008
######################################################################

unix:TEMPLATE = app
win32:TEMPLATE =vcapp
TARGET = DevGui
INCLUDEPATH += . include ../include
DEPENDPATH += . include ../include
MOC_DIR = generated
UI_DIR = generated
OBJECTS_DIR = intermediates
DESTDIR = release
unix:LIBS += -L../release -lQTwitLib
win32:LIBS += -L../debug -lQTwitLib

# Input
HEADERS += include/example.h
FORMS += ui/example.ui
SOURCES += src/example.cpp \
		   src/main.cpp

