TEMPLATE = app
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -LC:\Includes\SFML\READY_SFML-2.0\LIBS\

INCLUDEPATH += C:\Includes\SFML\SFML-2.0\include
DEPENDPATH += C:\Includes\SFML\SFML-2.0\include

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

SOURCES += Source.cpp

HEADERS += map.h
