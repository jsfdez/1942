ROOT_PATH = $$PWD

OBJECTS_DIR = .obj
CONFIG(debug, debug|release) {
    OBJECTS_DIR = .obj/debug
} else {
    OBJECTS_DIR = .obj/release
}
MOC_DIR = $$OBJECTS_DIR
UI_DIR = $$OBJECTS_DIR
RCC_DIR = $$OBJECTS_DIR

QMAKE_CXXFLAGS += /FS
