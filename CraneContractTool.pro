QT       += core gui widgets
CONFIG   += c++17

# 整个项目只需要这一个主源文件，彻底避免文件丢失
SOURCES  += main.cpp

TARGET   = CraneContractTool
TEMPLATE = app

win32-msvc {
    CONFIG += release
    # 强制放宽新版 MSVC 编译器的非标审查，完美解决 stdext 报错
    QMAKE_CXXFLAGS += /permissive
}
