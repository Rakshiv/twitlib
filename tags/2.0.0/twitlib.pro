######################################################################
# Automatically generated by qmake (2.01a) Fri Jul 18 22:57:32 2008
######################################################################

unix:TEMPLATE = lib
win32:TEMPLATE = vclib

CONFIG += debug_and_release
DEPENDPATH += include generated
INCLUDEPATH += include generated
QT = core network xml
TARGET = QTwitLib
MOC_DIR = generated
OBJECTS_DIR = intermediates
DESTDIR = release
CONFIG += build_all

# Input
HEADERS += include/Core.h \
		   include/Server.h \
		   include/QTwitLib.h \
           include/Decipher.h \
           include/Returnables.h
		   
SOURCES += src/Core.cpp \
		   src/QTwitLib.cpp \
           src/Decipher.cpp
