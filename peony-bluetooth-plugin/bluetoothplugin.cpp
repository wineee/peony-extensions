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
 * Authors: tang guang <tangguang@kylinos.cn>
 *
 */

#include "bluetoothplugin.h"

#include <QFileInfo>
#include <QProcess>

using namespace Peony;

BluetoothPlugin::BluetoothPlugin(QObject *parent)
{
    QTranslator *t = new QTranslator(this);
    qDebug()<<"system().name:"<<QLocale::system().name();
    qDebug()<<"\n\n\n\n\n\n\ntranslate:"<<t->load(":/translations/peony-bluetooth-plugin_"+QLocale::system().name());
    QApplication::installTranslator(t);
}

QList<QAction *> BluetoothPlugin::menuActions(Peony::MenuPluginInterface::Types types, const QString &uri, const QStringList &selectionUris)
{
    qDebug() << Q_FUNC_INFO << uri << selectionUris;
    QList<QAction*> actions;
    QStringList target;
    for (auto str : selectionUris) {
        qDebug() << Q_FUNC_INFO << str << "   =   " << Peony::FileUtils::urlEncode(str);
        target << Peony::FileUtils::urlEncode(str);
    }

    QProcess process;
    process.start("rfkill list");
    process.waitForFinished();
    QByteArray output = process.readAllStandardOutput();
    QString str_output = output;
    if(!str_output.contains(QString("bluetooth"), Qt::CaseInsensitive))
        return actions;

    if(!QFileInfo::exists("/usr/bin/ukui-bluetooth")){
        return actions;
    }
    if (types == MenuPluginInterface::DirectoryView || types == MenuPluginInterface::DesktopWindow)
    {
        if (! selectionUris.isEmpty()) {
            auto info = FileInfo::fromUri(selectionUris.first());
            //special type mountable, return
            qDebug()<<"info isVirtual:"<<info->isVirtual()<<info->mimeType();
            if (!selectionUris.first().startsWith("file:///"))
                  return actions;
            else{
                if(info->mimeType().split("/").at(1) != "directory"){
                    QAction *compress = new QAction(QIcon::fromTheme("blueman-tray"), tr("Send from bluetooth to..."), nullptr);
                    actions << compress;
                    connect(compress, &QAction::triggered, [=](){
                        QString path = selectionUris.at(0);
                        QDBusMessage m = QDBusMessage::createMethodCall("org.ukui.bluetooth","/org/ukui/bluetooth","org.ukui.bluetooth","file_transfer");
                        m << target;
                        qDebug() << Q_FUNC_INFO << m.arguments().at(0).value<QString>() <<__LINE__;
                        // 发送Message
                        QDBusConnection::sessionBus().call(m);
                    });
                }
            }
        }
    }

    return actions;
}
