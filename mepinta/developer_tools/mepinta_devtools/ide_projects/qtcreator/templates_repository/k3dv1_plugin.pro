#-------------------------------------------------
#-------------------------------------------------

QT -= core gui

TARGET = ${TARGET}
TEMPLATE = lib

OBJECTS_DIR=built_objects/
DESTDIR=${DESTDIR}

DEFINES += k3d="k3dv1"

CFLAGS+=-c -fmessage-length=0 -fPIC -fvisibility=hidden -shared

include( sources.pri )
