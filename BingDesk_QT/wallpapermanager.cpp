#include "wallpapermanager.h"
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <windows.h>
#include <QDir>

WallpaperManager::WallpaperManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    // Clean previous state
    replies.clear();
    // connect(networkManager, &QNetworkAccessManager::finished, this, &WallpaperManager::onNetworkReply);
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

                                                                          QUrl url(imageUrl);
                                                                          QNetworkRequest request(url);
                                                                          QNetworkReply *imageReply = networkManager->get(request);
                                                                          // qDebug()<<QSslSocket::supportsSsl();
                                                                          connect(imageReply, &QNetworkReply::finished, [=]()
                                                                                  {
            if (imageReply->error() == QNetworkReply::NoError) {
                QByteArray imageData = imageReply->readAll();
                QString fileName=QDir::currentPath()+"/BingDesk_QT_img/";
                QDir dir(fileName);
                if(!dir.exists())
                {
                    dir.mkpath(fileName);
                }
                                   fileName=fileName+imageCopyright+".jpg";
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
                                                                      reply->deleteLater();
                                                                  });
}


void WallpaperManager::setWallpaper(QString imagePath)
{
    // Convert the QString to a wide string
    std::wstring wsImagePath = imagePath.toStdWString();
    // Call the Windows API to set the wallpaper
    SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)wsImagePath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}
//! [8]
