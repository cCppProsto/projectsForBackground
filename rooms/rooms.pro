TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    appsettings.cpp \
    room.cpp \
    roomobjects.cpp \
    barrelobj.cpp

LIBS += -lGL -lglut -lSOIL

HEADERS += \
    appsettings.hpp \
    room.hpp \
    roomobjects.hpp \
    barrelobj.hpp
