TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    appsettings.cpp \
    room.cpp

LIBS += -lGL -lglut

HEADERS += \
    appsettings.hpp \
    room.hpp
