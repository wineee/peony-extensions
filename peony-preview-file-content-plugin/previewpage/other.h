#ifndef OTHERPREVIEWPAGE_H
#define OTHERPREVIEWPAGE_H

#include <QLabel>
#include <QFormLayout>
#include <QIcon>

#include "previewpage/base.h"
#include "components/icon-button.h"

class OtherPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit OtherPreviewPage(QWidget *parent = nullptr);
    ~OtherPreviewPage() = default;

private:
    IconButton *m_icon;
    QFormLayout *m_form;
    QLabel *m_display_name_label;
    QLabel *m_type_label;
    QLabel *m_time_modified_label;
    QLabel *m_time_access_label;

    // BasePreviewPage interface
public:
    void cancel() override;

public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* size) override;
};

#endif // OTHERPREVIEWPAGE_H
