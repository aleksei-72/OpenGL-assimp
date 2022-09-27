TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt


DEFINES += enable-sjlj-exceptions fexceptions DSFML_DYNAMIC


INCLUDEPATH += \
    libs/assimp-5.2.5/include \
    libs/glew-2.1.0/include \
    libs/glfw-3.3.8.bin.WIN64/include \
    libs/glm \
    libs/SFML-2.5.0/include \
    libs/tinyxml/include \
    libs/inicpp-1.2.0/include


SOURCES += \
    src/3d/mesh/Mesh.cpp \
    src/3d/mesh/simpleMeshes.cpp \
    src/3d/model/Model.cpp \
    src/3d/object/GameObject.cpp \
    src/gl/pixelBuffer.cpp \
    src/gl/pixelBufferToTGA.cpp \
    src/gl/shader.cpp \
    src/gl/texture.cpp \
    src/input/keyboard.cpp \
    src/input/mouse.cpp \
    src/logger/logger.cpp \
    src/main.cpp \
    src/parsers/parseConfig.cpp \
    src/physics/player/playerPhysics.cpp \
    src/player/Player.cpp \
    src/public/public.cpp \
    src/timer/timer.cpp


HEADERS += \
    src/3d/mesh/Mesh.h \
    src/3d/mesh/Model.h \
    src/3d/mesh/simpleMeshes.h \
    src/3d/model/Model.h \
    src/3d/object/GameObject.h \
    src/constants.h \
    src/fpsCounter/fpsCounter.h \
    src/gl/pixelBuffer.h \
    src/gl/pixelBufferToTGA.h \
    src/gl/shader.h \
    src/gl/texture.h \
    src/input/keyboard.h \
    src/input/mouse.h \
    src/logger/logger.h \
    src/parsers/parseConfig.h \
    src/physics/player/playerPhysics.h \
    src/player/Player.h \
    src/public/public.h \
    src/timer/timer.h


win32: LIBS += -lopengl32 -lglu32
win32: LIBS += -L$$PWD/libs/glfw-3.3.8.bin.WIN64/lib-mingw-w64/ -lglfw3dll
win32: LIBS += -L$$PWD/libs/glew-2.1.0/lib/Release/x64 -lglew32
win32: LIBS += -L$$PWD/libs/assimp-5.2.5/lib/ -llibassimp.dll
win32: LIBS += -L$$PWD/libs/inicpp-1.2.0/bin/ -llibinicpp
win32: LIBS += -L$$PWD/libs/tinyxml/lib/ -lTinyXML
win32: LIBS += -L$$PWD/libs/SFML-2.5.0/lib/ -lsfml-system -lsfml-graphics -lsfml-window
