SOURCES += main.cpp \
    dialog.cpp

FORMS += \
    dialog.ui

HEADERS += \
    dialog.h


CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# Compile with high warning levels, a warning is an error
# Qt does not go well with -Weffc++
QMAKE_CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror

# Qt
QT += core gui widgets

# Boost Graph
LIBS += -lboost_graph

# Poppler
LIBS += -lpoppler-qt5

# Debug and release settings
CONFIG += debug_and_release
CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}
