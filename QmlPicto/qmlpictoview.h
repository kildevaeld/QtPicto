#ifndef QMLPICTOVIEW_H
#define QMLPICTOVIEW_H

#include <QQuickPaintedItem>

class QmlPictoView : public QQuickPaintedItem
{
    Q_OBJECT
    QString m_name;

    QColor m_color;

public:

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    QmlPictoView(QQuickItem *parent = 0);

signals:

    void nameChanged(QString name);

    void colorChanged(QColor color);

public slots:

// QQuickPaintedItem interface
void setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}

void setColor(QColor color)
{
    if (m_color == color)
    return;

m_color = color;
emit colorChanged(color);
}

public:
virtual void paint(QPainter *painter);
QString name() const
{
    return m_name;
}
QColor color() const
{
    return m_color;
}
};

#endif // QMLPICTOVIEW_H
