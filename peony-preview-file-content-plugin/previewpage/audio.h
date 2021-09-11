#ifndef AUDIOPREVIEWPAGE_H
#define AUDIOPREVIEWPAGE_H

#include <QMediaPlayer>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QFormLayout>

#include "previewpage/base.h"
#include "components/slider.h"
#include "components/icon-button.h"

class AudioPreviewPage : public BasePreviewPage
{
    Q_OBJECT
public:
    explicit AudioPreviewPage(QWidget *parent = nullptr);
    ~AudioPreviewPage() = default;

private:
    QPushButton *m_button;
    QPushButton *volume_button;
    Slider *m_progress;
    QTimer *timer;
    QMediaPlayer *m_player;

    QIcon m_base_icon;
    IconButton *m_icon;
    QFormLayout *m_form;
    QLabel *m_title_label;
    QLabel *m_author_label;
//    QLabel *m_time_modified_label;
//    QLabel *m_time_access_label;

    void updateMeta();

    // BasePreviewPage interface
public Q_SLOTS:
    void updateInfo(Peony::FileInfo *info) override;
public:
    void cancel() override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent* size) override;
};

#endif // AUDIOPREVIEWPAGE_H
