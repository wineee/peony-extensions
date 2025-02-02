QT += core gui widgets multimedia multimediawidgets \
webengine webenginewidgets webenginecore webchannel

TARGET = peony-qt-preview-file-content-plugin videographicsitem
TEMPLATE = lib

#DEFINES += USE_QTPDF
DEFINES += USE_KSyntaxHighlighting
#DEFINES += USE_OnlyOffice

DEFINES += PEONYQTPREVIEWFILECONTENTPLUGIN_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += PEONYADMIN_LIBRARY
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../common.pri)
include(third_party/qpdflib/qpdflib.pri)

CONFIG += debug c++11 link_pkgconfig plugin no_keywords

PKGCONFIG += peony

if(contains(DEFINES, USE_KSyntaxHighlighting)) {
    QT += KSyntaxHighlighting
}

if(contains(DEFINES, USE_QTPDF)) {
    QT += pdf pdfwidgets
    SOURCES += previewpage/pdf.cpp
    HEADERS += previewpage/pdf.h
}

if(contains(DEFINES, USE_OnlyOffice)) {
    QT += KSyntaxHighlighting
    SOURCES += previewpage/onlyoffice.cpp
    HEADERS += previewpage/onlyoffice.h
}

SOURCES += \
    preview-file-type.cpp \
    preview-page-manger.cpp \
    previewpage/audio.cpp \
    previewpage/base.cpp \
    components/icon-button.cpp \
    components/slider.cpp \
    content-preview-page-factory.cpp \
    content-preview-page.cpp \
    previewpage/html.cpp \
    previewpage/image.cpp \
    previewpage/pdf2.cpp \
    previewpage/to-pdf.cpp \
    previewpage/video.cpp \
    previewpage/other.cpp \
    previewpage/text.cpp

HEADERS += \
    preview-file-type.h \
    preview-page-manger.h \
    previewpage/audio.h \
    previewpage/base.h \
    components/icon-button.h \
    components/slider.h \
    content-preview-page-factory.h \
    previewpage/html.h \
    previewpage/image.h \
    previewpage/other.h \
    peony-qt-preview-file-content-plugin_global.h \
    previewpage/pdf2.h \
    previewpage/to-pdf.h \
    previewpage/video.h \
    content-preview-page.h \
    previewpage/text.h

target.path = $$[QT_INSTALL_LIBS]/peony-extensions
INSTALLS += target

RESOURCES += \
    resources/resources.qrc

