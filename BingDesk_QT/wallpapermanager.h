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

    Q_PROPERTY(QString notificationStr READ getNotificationStr WRITE setNotificationStr NOTIFY statusChanged)

    QString getNotificationStr();
    void setNotificationStr(QString str);

    signals:
    void statusChanged();

public slots:
    void fetchWallpaper();

private slots:
    void setWallpaper(QString fileName);

private:
    QNetworkAccessManager *networkManager;
    QList<QSharedPointer<QNetworkReply>> replies;
    QString m_notificationStr;
    bool m_getImgSuccess;
    QTimer *m_timer_2s;

    void onTimeout_2s();
};

#endif // WALLPAPERMANAGER_H
