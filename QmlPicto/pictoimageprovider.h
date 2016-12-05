#ifndef PICTOIMAGEPROVIDER_H
#define PICTOIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <memory>

namespace picto {
    class PictoGenerator;
}



class PictoImageProvider: public QQuickImageProvider
{
public:
    PictoImageProvider(picto::PictoGenerator *generator, QQmlImageProviderBase::ImageType imageType, QQmlImageProviderBase::Flags flags);

    // QQuickImageProvider interface
public:
    virtual QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
    std::unique_ptr<picto::PictoGenerator> m_gen;
    void get_options(QList<QPair<QString, QString> > &list, QColor *color, QSize *size);

};

#endif // PICTOIMAGEPROVIDER_H
