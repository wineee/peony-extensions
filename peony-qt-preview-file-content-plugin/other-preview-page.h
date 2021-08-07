#ifndef OTHERPREVIEWPAGE_H
#define OTHERPREVIEWPAGE_H

#include <QLabel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QIcon>
#include <QWidget>

#include <QFile>
#include <QFileInfo>
#include <QUrl>

#include "base-preview-page.h"
#include "controls/icon-container.h"
#include <QPushButton>

class OtherPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit OtherPreviewPage(QWidget *parent = nullptr);
    ~OtherPreviewPage() = default;

public Q_SLOTS:
    void updateInfo(FileInfo *info) override;
    void resizeIcon(QSize size);

private:
    QPushButton *m_icon;
    QFormLayout *m_form;
    QLabel *m_display_name_label;
    QLabel *m_type_label;
    QLabel *m_time_modified_label;
    QLabel *m_time_access_label;

public:
    void cancel() override;
};

#endif // OTHERPREVIEWPAGE_H
