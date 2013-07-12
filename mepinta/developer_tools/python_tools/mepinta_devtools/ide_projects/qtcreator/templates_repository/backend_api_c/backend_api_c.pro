#-------------------------------------------------
#-------------------------------------------------

QT -= core gui

TARGET = backend_api_c
TEMPLATE = lib

OBJECTS_DIR=built_objects/
DESTDIR=built_objects/
#${MEPINTA_LIBS_PATH}

INCLUDEPATH += src/

CFLAGS+=-c -fmessage-length=0 -fPIC -fvisibility=hidden -shared

include( sources.pri )
