#-------------------------------------------------
#
#
#
#-------------------------------------------------

QT -= core gui

TARGET = ##pluginName
TEMPLATE = lib

OBJECTS_DIR=##projectDirectory/Debug
DESTDIR=##projectDirectory/Debug

DEFINES += k3d="k3dv1"
#DEFINES += ##pluginName_LIBRARY

SOURCES += src/##pluginName.cpp

#HEADERS +=

INCLUDEPATH += /usr/lib/glibmm-2.4/include
INCLUDEPATH += /usr/include/glibmm-2.4
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include/
INCLUDEPATH += /usr/lib/glib-2.0/include
INCLUDEPATH += /usr/include/glib-2.0
INCLUDEPATH += /usr/include/sigc++-2.0
INCLUDEPATH += /usr/lib/sigc++-2.0/include

INCLUDEPATH += /home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/Mepinta_SDK/include_new

INCLUDEPATH += /home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/Mepinta/Mepinta_k3dv1_DataTypes_Includes

INCLUDEPATH += /home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1_Libs/include
INCLUDEPATH += /home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1_Libs/boost
INCLUDEPATH += /home/jduo/Projects/Informatica/Mepinta/EclipseProjects_Basic_Data_Types/k3dv1/k3dv1MPExtension

CXXFLAGS+=##compilerArgs

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE6AAB5C7
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = PolyCone.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
