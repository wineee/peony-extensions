QT += core gui widgets multimedia # multimediawidgets network webengine webenginewidgets webkit webkitwidgets

TARGET = peony-qt-preview-file-content-plugin
TEMPLATE = lib

DEFINES += PEONYQTPREVIEWFILECONTENTPLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PEONYADMIN_LIBRARY

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../common.pri)

CONFIG += debug c++11 link_pkgconfig plugin no_keywords

PKGCONFIG += peony

SOURCES += \
    audio-preview-page.cpp \
    base-preview-page.cpp \
    content-preview-page-factory.cpp \
    content-preview-page.cpp \
  #  doc-preview-page.cpp \
  #  image-preview-page.cpp \
  #  pdf-preview-page.cpp \
  #  video-preview-page.cpp \
    other-preview-page.cpp \
    text-preview-page.cpp

HEADERS += \
    audio-preview-page.h \
    base-preview-page.h \
    content-preview-page-factory.h \
  #  doc-preview-page.h \
  #  image-preview-page.h \
    other-preview-page.h \
  #  pdf-preview-page.h \
    peony-qt-preview-file-content-plugin_global.h \
  #  video-preview-page.h \
    content-preview-page.h \
    text-preview-page.h

target.path = $$[QT_INSTALL_LIBS]/peony-extensions
INSTALLS += target

