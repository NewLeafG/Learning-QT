/*
 * @Author: WYJ
 * @Date: 2024-08-11 18:44:19
 * @LastEditors: WYJ
 * @LastEditTime: 2024-08-13 20:19:47
 * @FilePath: \BingDesk_QT\wallpapermanager.cpp
 * @Description:
 *
 * KH.
 */
#include "wallpapermanager.h"
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <windows.h>
#include <QDir>
#include <QDate>
#include <QTimer>

WallpaperManager::WallpaperManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    // connect(networkManager, &QNetworkAccessManager::finished, this, &WallpaperManager::onNetworkReply);
    setNotificationStr("BingDesk_QT initializing...");
    m_getImgSuccess = 0;

    m_timer_2s = new QTimer(this);
    connect(m_timer_2s, &QTimer::timeout, this, &WallpaperManager::onTimeout_2s);
    m_timer_2s->start(2000); // 定时器每2000毫秒触发一次
}

void WallpaperManager::fetchWallpaper()
{
    // QNetworkRequest request(QUrl("https://www.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1"));
    QNetworkRequest request(QUrl("http://www.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1&mkt=zh-CN"));
    QSharedPointer<QNetworkReply> reply(networkManager->get(request));
    qDebug() << QSslSocket::sslLibraryBuildVersionString();
    QtFuture::connect(reply.get(), &QNetworkReply::finished).then([=]
                                                                  {
                                                                      if (reply->error() == QNetworkReply::NoError)
                                                                      {
                                                                          QByteArray response = reply->readAll();
                                                                          QString xml(response);
                                                                          QString imageUrl = "https://www.bing.com" + xml.section("<url>", 1, 1).section("</url>", 0, 0);
                                                                          QString imageCopyright=xml.section("<copyright>", 1, 1).section("</copyright>", 0, 0);
                                                                          imageCopyright.replace(QString("/"), QString("-"));
                                                                          imageCopyright.replace(QString("("), QString("-"));
                                                                          imageCopyright.replace(QString(")"), QString("-"));
                                                                          setNotificationStr(imageCopyright);
                                                                          m_getImgSuccess=1;

                                                                          QUrl url(imageUrl);
                                                                          QNetworkRequest request(url);
                                                                          QNetworkReply *imageReply = networkManager->get(request);
                                                                          // qDebug()<<QSslSocket::supportsSsl();
                                                                          connect(imageReply, &QNetworkReply::finished, [=]()
                                                                                  {
            if (imageReply->error() == QNetworkReply::NoError) {
                QByteArray imageData = imageReply->readAll();
QDate currentDate = QDate::currentDate();
                QString fileName=QDir::currentPath()+"/BingDesk_QT_img/"+ QString::number(currentDate.year())+"/";
               
                QDir dir(fileName);
                if(!dir.exists())
                {
                    dir.mkpath(fileName);
                }
                                   fileName=fileName+ QString::number(currentDate.month())+"-"+ QString::number(currentDate.day())+"-"+imageCopyright+".jpg";
                // QFile file("bing_wallpaper.jpg");
                QFile file(fileName);
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(imageData);
                    file.close();
                    setWallpaper(fileName);
                }
            }
            imageReply->deleteLater(); });
                                                                      }
                                                                      reply->deleteLater(); });
}

void WallpaperManager::setWallpaper(QString imagePath)
{
    // Convert the QString to a wide string
    std::wstring wsImagePath = imagePath.toStdWString();
    // Call the Windows API to set the wallpaper
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void *)wsImagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}
//! [8]

QString WallpaperManager::getNotificationStr()
{
    return m_notificationStr;
}

void WallpaperManager::setNotificationStr(QString str)
{
    m_notificationStr=str;
    emit statusChanged();
}

void WallpaperManager::onTimeout_2s()
{
    if (!m_getImgSuccess)
    {
        // Clean previous state
        replies.clear();
        fetchWallpaper();
    }
    else
    {
        m_timer_2s->stop();
    }
}
