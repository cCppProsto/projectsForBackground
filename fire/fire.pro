TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    globaldata.cpp \
    rgbcolor.cpp \
    hsvcolor.cpp \
    fireplace.cpp

LIBS += -lGL -lglut

HEADERS += \
    globaldata.hpp \
    rgbcolor.hpp \
    hsvcolor.hpp \
    fireplace.hpp
