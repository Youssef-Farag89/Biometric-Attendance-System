QT += core gui widgets sql multimedia

CONFIG += c++17

TARGET = BiometricAttendance
TEMPLATE = app

SOURCES += \
    main.cpp \
    sources/MainWindow.cpp \
    sources/DatabaseManager.cpp \
    sources/User.cpp \
    sources/Attendance.cpp \
    sources/Fingerprint.cpp \
    sources/ScannerDevice.cpp

HEADERS += \
    headers/MainWindow.h \
    headers/DatabaseManager.h \
    headers/User.h \
    headers/Attendance.h \
    headers/Fingerprint.h \
    headers/ScannerDevice.h

FORMS += \
    forms/MainWindow.ui

win32: {
    QMAKE_CXXFLAGS += -std=c++17
}
unix: {
    QMAKE_CXXFLAGS += -std=c++17
}

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    resources.qrc
