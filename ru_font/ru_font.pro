TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    rus_font.cpp

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CFLAGS += -std=c11

LIBS += -lGL -lGLU -lglut
LIBS += -lglfw
LIBS += -lX11 -lXrandr -lXinerama -lXxf86vm -lXcursor -lpthread -ldl

DISTFILES +=

HEADERS += \
    rus_font.hpp

