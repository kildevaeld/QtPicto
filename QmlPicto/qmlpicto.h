#ifndef QMLPICTO_H
#define QMLPICTO_H

#include "pictoimageprovider.h"
#include <QQmlEngine>
#include <QQuickImageProvider>
#include <QQuickItem>
#include <QtPicto/QtPicto>

namespace picto {

template <class T>
PictoImageProvider *imageProvider(
    QQmlImageProviderBase::ImageType imageType = QQmlImageProviderBase::Pixmap,
    QQmlImageProviderBase::Flags flags = QQmlImageProviderBase::Flags()) {

  auto provider = picto::provider<T>();

  if (!provider)
    return nullptr;

  return new PictoImageProvider(provider.release(), imageType, flags);
}

template <class T>
void imageProvider(
    QQmlEngine *engine,
    QQmlImageProviderBase::ImageType imageType = QQmlImageProviderBase::Pixmap,
    QQmlImageProviderBase::Flags flags = QQmlImageProviderBase::Flags()) {

  std::unique_ptr<picto::PictoGenerator> provider = picto::provider<T>();

  if (!provider)
    return;

  QString name = provider->provider()->providerName();

  auto p = new PictoImageProvider(provider.release(), imageType, flags);

  engine->addImageProvider("picto-" + name, p);
}
}

#endif // QMLPICTO_H
