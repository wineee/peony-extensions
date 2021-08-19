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
    previewpage/audio-preview-page.cpp \
    previewpage/base-preview-page.cpp \
    components/icon-button.cpp \
    components/slider.cpp \
    content-preview-page-factory.cpp \
    content-preview-page.cpp \
    previewpage/doc-preview-page.cpp \
    previewpage/image-preview-page.cpp \
    previewpage/pdf-preview-page.cpp \
    previewpage/video-preview-page.cpp \
    previewpage/other-preview-page.cpp \
    previewpage/text-preview-page.cpp

HEADERS += \
    preview-page-manger.h \
    previewpage/audio-preview-page.h \
    previewpage/base-preview-page.h \
    components/icon-button.h \
    components/slider.h \
    content-preview-page-factory.h \
    previewpage/doc-preview-page.h \
    previewpage/image-preview-page.h \
    previewpage/other-preview-page.h \
    previewpage/pdf-preview-page.h \
    peony-qt-preview-file-content-plugin_global.h \
    previewpage/video-preview-page.h \
    content-preview-page.h \
    previewpage/text-preview-page.h

target.path = $$[QT_INSTALL_LIBS]/peony-extensions
INSTALLS += target

RESOURCES += \
    resources/resources.qrc

