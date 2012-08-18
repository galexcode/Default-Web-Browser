QT += core gui webkit

TARGET = MyBrowser
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    Application.cpp \
    RegistryEntry.cpp

HEADERS += MainWindow.h \
    Application.h \
    RegistryEntry.h

FORMS += MainWindow.ui

mac {
    SOURCES += UtilitiesMac.cpp
    HEADERS += UtilitiesMac.h
    LIBS += -framework ApplicationServices
	ICON = Icon.icns
}

win32 {
    SOURCES += UtilitiesWin.cpp
    HEADERS += UtilitiesWin.h
    LIBS += Ole32.lib
    LIBS += Shell32.lib
	RC_FILE = MyBrowser.rc
}
