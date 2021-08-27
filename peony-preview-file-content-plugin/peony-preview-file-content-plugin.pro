QT += core gui widgets multimedia multimediawidgets webengine webenginewidgets pdf pdfwidgets

TARGET = peony-qt-preview-file-content-plugin videographicsitem
TEMPLATE = lib

DEFINES += PEONYQTPREVIEWFILECONTENTPLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PEONYADMIN_LIBRARY
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../common.pri)

CONFIG += debug c++11 link_pkgconfig plugin no_keywords


PKGCONFIG += peony

SOURCES += \
    preview-page-manger.cpp \
    previewpage/audio.cpp \
    previewpage/base.cpp \
    components/icon-button.cpp \
    components/slider.cpp \
    content-preview-page-factory.cpp \
    content-preview-page.cpp \
    previewpage/onlyoffice.cpp \
    previewpage/html.cpp \
    previewpage/image.cpp \
    previewpage/pdf.cpp \
    previewpage/video.cpp \
    previewpage/other.cpp \
    previewpage/text.cpp

HEADERS += \
    preview-page-manger.h \
    previewpage/audio.h \
    previewpage/base.h \
    components/icon-button.h \
    components/slider.h \
    content-preview-page-factory.h \
    previewpage/onlyoffice.h \
    previewpage/html.h \
    previewpage/image.h \
    previewpage/other.h \
    previewpage/pdf.h \
    peony-qt-preview-file-content-plugin_global.h \
    previewpage/video.h \
    content-preview-page.h \
    previewpage/text.h

target.path = $$[QT_INSTALL_LIBS]/peony-extensions
INSTALLS += target

RESOURCES += \
    resources/resources.qrc

