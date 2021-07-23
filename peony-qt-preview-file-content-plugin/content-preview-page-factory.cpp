/*
 * Peony-Qt's Library
 *
 * Copyright (C) 2019, Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: Yue Lan <lanyue@kylinos.cn>
 *
 */

#include "content-preview-page-factory.h"
#include "content-preview-page.h"

#include "peony-qt/controls/preview-page/preview-page-factory/preview-page-factory-manager.h"

using Peony::PreviewPageFactoryManager;

ContentPreviewPageFactory::ContentPreviewPageFactory(QObject *parent) : QObject (parent)
{
     auto manager = PreviewPageFactoryManager::getInstance();
     manager->registerFactory(this->name(), static_cast<PreviewPagePluginIface*>(this));
}

ContentPreviewPageFactory::~ContentPreviewPageFactory()
{

}

static ContentPreviewPageFactory *globalInstance = nullptr;

ContentPreviewPageFactory* ContentPreviewPageFactory::getInstance() {
    if (!globalInstance) {
        globalInstance = new ContentPreviewPageFactory;
    }
    return globalInstance;
}

Peony::PreviewPageIface *ContentPreviewPageFactory::createPreviewPage()
{
    return new ContentPreviewPage;
}
