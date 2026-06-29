QT       += core gui widgets
CONFIG   += c++17

SOURCES += main.cpp \
           mainwindow.cpp

HEADERS += mainwindow.h

TARGET   = CraneContractTool
TEMPLATE = app

win32-msvc {
    CONFIG += release
    # 核心修复：强行放宽新版 MSVC 编译器的非标审查，挽回 stdext，彻底修复 qvarlengtharray.h 报错
    QMAKE_CXXFLAGS += /permissive
}
