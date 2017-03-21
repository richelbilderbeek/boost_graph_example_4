SOURCES += main.cpp \
    dialog.cpp

FORMS += \
    dialog.ui

HEADERS += \
    dialog.h

# C++14
CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14

# Compile with high warning levels, a warning is an error
# Qt does not go well with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror

# Qt
QT += core gui widgets

# Boost Graph
LIBS += -lboost_graph

# Poppler
LIBS += -lpoppler-qt5

message(Host name: $$QMAKE_HOST.name)
contains(QMAKE_HOST.name,fwn-biol-132-102) {
  message("Host is university computer in my office")
  QMAKE_CXX = g++-5
  QMAKE_LINK = g++-5
  QMAKE_CC = gcc-5
}
