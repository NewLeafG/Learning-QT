#include "wallpapermanager.h"
#include <QFile>
#include <QProcess>
#include <QDebug>

WallpaperManager::WallpaperManager(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this))
{
    connect(networkManager, &QNetworkAccessManager::finished, this, &WallpaperManager::onNetworkReply);
}

void WallpaperManager::fetchWallpaper()
{
    QNetworkRequest request(QUrl("https://www.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1"));
    networkManager->get(request);
    qDebug()<<QSslSocket::sslLibraryBuildVersionString();

}

void WallpaperManager::onNetworkReply(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QString xml(response);
        QString imageUrl = "https://www.bing.com" + xml.section("<url>", 1, 1).section("</url>", 0, 0);

        QUrl url(imageUrl);
        QNetworkRequest request(url);
        QNetworkReply *imageReply = networkManager->get(request);
        // qDebug()<<QSslSocket::supportsSsl();
        connect(imageReply, &QNetworkReply::finished, [=]() {
            if (imageReply->error() == QNetworkReply::NoError) {
                QByteArray imageData = imageReply->readAll();
                QFile file("bing_wallpaper.jpg");
                if (file.open(QIODevice::WriteOnly)) {
                    file.write(imageData);
                    file.close();
                    setWallpaper();
                }
            }
            imageReply->deleteLater();
        });
    }
    reply->deleteLater();
}

void WallpaperManager::setWallpaper()
{
    // Platform-specific code to set wallpaper (example for Windows)
    // QProcess::startDetached("powershell.exe", QStringList() << "-command" << "Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; public class Wallpaper { [DllImport(\"user32.dll\")] public static extern int SystemParametersInfo(int uAction, int uParam, string lpvParam, int fuWinIni); }'; Wallpaper.SystemParametersInfo(20, 0, 'bing_wallpaper.jpg', 3)");
}
