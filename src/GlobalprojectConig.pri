CONFIG += c++17

CONFIG += debug_and_release
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG(debug,debug|release){
    UI_DIR  = $$PWD/../tmp/$${TARGET}d
    RCC_DIR  = $$PWD/../tmp/$${TARGET}d
    MOC_DIR  = $$PWD/../tmp/$${TARGET}d
    OBJECTS_DIR = $$PWD/../tmp/$${TARGET}d
}
CONFIG(release,debug|release){
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    OBJECTS_DIR = $$PWD/../tmp/$${TARGET}
}

VCPKG_BIN_PATH = C:/vcpkg

INCLUDEPATH += $${VCPKG_BIN_PATH}/installed/x64-windows/include

CONFIG(debug, debug|release){
    LIBS += -L$${VCPKG_BIN_PATH}/installed/x64-windows/debug/lib
}

CONFIG(release, debug|release){
    LIBS += -L$${VCPKG_BIN_PATH}/installed/x64-windows/lib
}

