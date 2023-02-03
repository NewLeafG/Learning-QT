#ifndef PIESLICE_H
#define PIESLICE_H

#include <QtQuick/QQuickPaintedItem>
#include <QColor>

class PieSlice : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor FINAL)
    QML_ELEMENT

public:
    PieSlice(QQuickItem *parent = nullptr);

    QColor color() const;
    void setColor(const QColor &color);

    void paint(QPainter *painter) override;

private:
    QColor m_color;
};

#endif // PIESLICE_H
