#ifndef WALLPAPERMANAGER_H
#define WALLPAPERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WallpaperManager : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperManager(QObject *parent = nullptr);

public slots:
    void fetchWallpaper();

private slots:
    void onNetworkReply(QNetworkReply *reply);
    void setWallpaper();

private:
    QNetworkAccessManager *networkManager;
};

#endif // WALLPAPERMANAGER_H
