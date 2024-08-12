#ifndef WALLPAPERMANAGER_H
#define WALLPAPERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtConcurrent>

class WallpaperManager : public QObject
{
    Q_OBJECT
public:
    explicit WallpaperManager(QObject *parent = nullptr);

public slots:
    void fetchWallpaper();

private slots:
    void setWallpaper(QString fileName);

private:
    QNetworkAccessManager *networkManager;
    QList<QSharedPointer<QNetworkReply>> replies;
};

#endif // WALLPAPERMANAGER_H
