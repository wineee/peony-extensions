#include "previewpage/base.h"

BasePreviewPage::BasePreviewPage(QWidget *parent) : QFrame(parent)
{
    base_layout = new QVBoxLayout(this);
    setLayout(base_layout);
}
