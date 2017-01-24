#ifndef QMLPICTOVIEW_H
#define QMLPICTOVIEW_H

#include <QQuickPaintedItem>

class PictoResolver : public QObject {
  Q_OBJECT
public:
  PictoResolver(QObject *parent = 0);
  ~PictoResolver() {}

  static QObject *qmlResolverRegister(QQmlEngine *engine,
                                      QJSEngine *scriptEngine) {
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    PictoResolver *o = new PictoResolver();
    return o;
  }

public slots:
  QString icon(const QString &name, const QColor &color = QColor("black"),
               const int size = 32);
  QString image(const QString &name, const QColor &color = QColor("black"));
};

class QmlPictoView : public QQuickPaintedItem {
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
  void setName(QString name) {
    if (m_name == name)
      return;

    m_name = name;
    update();
    emit nameChanged(name);
  }

  void setColor(QColor color) {
    if (m_color == color)
      return;

    m_color = color;
    update();
    emit colorChanged(color);
  }

public:
  virtual void paint(QPainter *painter);
  QString name() const { return m_name; }
  QColor color() const { return m_color; }
};

#endif // QMLPICTOVIEW_H
