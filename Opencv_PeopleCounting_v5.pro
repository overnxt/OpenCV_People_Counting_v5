QT -= gui

CONFIG += c++14 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    package_bgs/PBAS/PBAS.cpp \
    package_bgs/PBAS/PixelBasedAdaptiveSegmenter.cpp \
    package_tracking/cvblob/cvaux.cpp \
    package_tracking/cvblob/cvblob.cpp \
    package_tracking/cvblob/cvcolor.cpp \
    package_tracking/cvblob/cvcontour.cpp \
    package_tracking/cvblob/cvlabel.cpp \
    package_tracking/cvblob/cvtrack.cpp \
    package_tracking/BlobTracking.cpp \
    Demo.cpp \
    package_analysis/ObjectCouting.cpp

HEADERS += \
    package_bgs/PBAS/PBAS.h \
    package_bgs/PBAS/PixelBasedAdaptiveSegmenter.h \
    package_bgs/IBGS.h \
    package_tracking/cvblob/cvblob.h \
    package_tracking/BlobTracking.h \
    package_analysis/ObjectCouting.h
PKGCONFIG += opencv3
CONFIG += link_pkgconfig
