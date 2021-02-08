CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

VCPKG_BIN_PATH = C:/vcpkg

INCLUDEPATH += $${VCPKG_BIN_PATH}/installed/x64-windows/include

CONFIG(debug, debug|release){
    LIBS += -L$${VCPKG_BIN_PATH}/installed/x64-windows/debug/lib
}

CONFIG(release, debug|release){
    LIBS += -L$${VCPKG_BIN_PATH}/installed/x64-windows/lib
}

