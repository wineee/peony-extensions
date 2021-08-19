#ifndef BASEPREVIEWPAGE_H
#define BASEPREVIEWPAGE_H

#include <QFrame>
#include <QObject>
#include <QWidget>
#include <QLayout>

#include "file-info.h"
#include "file-info-job.h"

using Peony::FileInfoJob;
using Peony::FileInfo;

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
    virtual void updateInfo(FileInfo *info) = 0;
};

#endif // BASEPREVIEWPAGE_H
