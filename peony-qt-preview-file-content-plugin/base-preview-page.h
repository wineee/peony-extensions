#ifndef BASEPREVIEWPAGE_H
#define BASEPREVIEWPAGE_H

#include <QFrame>
#include <QObject>

class ContentPreviewPage;

class BasePreviewPage : public QFrame
{
    friend class ContentPreviewPage;
    Q_OBJECT
public:
    explicit BasePreviewPage(QWidget *parent = nullptr);
    ~BasePreviewPage();
};

#endif // BASEPREVIEWPAGE_H
