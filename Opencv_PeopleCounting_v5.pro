QT -= gui
QT += network
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
    backgroundsub_algorithms/PBAS/PBAS.cpp \
    backgroundsub_algorithms/PBAS/PixelBasedAdaptiveSegmenter.cpp \
    tracking_algorithms/cvblob/cvaux.cpp \
    tracking_algorithms/cvblob/cvblob.cpp \
    tracking_algorithms/cvblob/cvcolor.cpp \
    tracking_algorithms/cvblob/cvcontour.cpp \
    tracking_algorithms/cvblob/cvlabel.cpp \
    tracking_algorithms/cvblob/cvtrack.cpp \
    tracking_algorithms/BlobTracking.cpp \
    Demo.cpp \
    analysis_algorithms/ObjectCouting.cpp \
    communication_api/serverapi.cpp

HEADERS += \
    backgroundsub_algorithms/PBAS/PBAS.h \
    backgroundsub_algorithms/PBAS/PixelBasedAdaptiveSegmenter.h \
    backgroundsub_algorithms/IBGS.h \
    tracking_algorithms/cvblob/cvblob.h \
    tracking_algorithms/BlobTracking.h \
    analysis_algorithms/ObjectCouting.h \
    communication_api/serverapi.h
PKGCONFIG += opencv3
CONFIG += link_pkgconfig
