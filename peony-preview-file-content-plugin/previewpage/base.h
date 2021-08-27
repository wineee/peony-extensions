#ifndef BASEPREVIEWPAGE_H
#define BASEPREVIEWPAGE_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QDebug>

#include "file-info.h"
#include "file-info-job.h"

class BasePreviewPage : public QFrame
{
    Q_OBJECT
public:
    BasePreviewPage(QWidget *parent = nullptr);
    BasePreviewPage() = delete;
    ~BasePreviewPage() = default;
    virtual void cancel() = 0;

protected:
    QVBoxLayout *m_layout = nullptr;

public Q_SLOTS:
    virtual void updateInfo(Peony::FileInfo *info) = 0;
};

#endif // BASEPREVIEWPAGE_H
