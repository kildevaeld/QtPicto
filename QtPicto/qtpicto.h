#pragma once

#include <QString>
#include <QFont>
#include <QColor>
#include <QHash>

#include <memory>
#include <typeindex>

#include "singleton.h"

namespace picto {

struct PictoTheme {
    QColor color;
    QString text;
    QColor disabledColor;
    QString disabledText;
    QColor activeColor;
    QString activeText;
    QColor selectedColor;
    QString selectedText;
};

class PictoProvider {
public:
    virtual ~PictoProvider () {}
    virtual bool initialize() = 0;
    virtual QFont font(int size) = 0;
    virtual QString name(int code) = 0;
    virtual int code(const QString &name) = 0;
    virtual QString providerName() = 0;
};

class PictoPainter {
public:
    virtual ~PictoPainter() { }
    virtual void paint(PictoProvider *p, QPainter *painter, const QRect &rect, const QColor &color, const QString &text) = 0;

};

class PictoGenerator {

public:
    PictoGenerator(PictoProvider *p, PictoPainter *painter);
    QIcon icon(int code, const PictoTheme &theme = PictoTheme()) const;
    QIcon icon(const QString &name, const PictoTheme &theme = PictoTheme()) const;
    QPixmap pixmap(int character, const QSize &size, const QColor &color = QColor("black")) const;
    QPixmap pixmap(const QString &name, const QSize &size, const QColor &color = QColor("black")) const;
    QImage image(int character, const QSize &size, const QColor &color = QColor("black")) const;
    QImage image(const QString &name, const QSize &size, const QColor &color = QColor("black")) const;

    PictoProvider *provider() const {
        return this->m_provider;
    }

private:
    PictoProvider *m_provider;
    PictoPainter *m_painter;
    PictoTheme m_theme;
};


class Picto: public Patterns::LazySingleton<Picto> {
    friend class Patterns::LazySingleton<Picto>;

public:
    template<class T>
    std::unique_ptr<PictoGenerator> provider() {
        std::type_index ti(typeid(T));
        size_t hash = ti.hash_code();
        PictoProvider *p;

        if (has(hash)) {
            p = get_provider(hash);
        } else {
            p = T::provider();
            if (!add_provider(hash, p)) {
                return nullptr;
            }
        }

        return std::unique_ptr<PictoGenerator>(new PictoGenerator(p, m_painter));
    }

    std::unique_ptr<PictoGenerator>provider(const QString &name);

    QStringList providers() const;

private:
    Picto();
    ~Picto() {
        qDeleteAll(m_providers);
        delete m_painter;
    }

    bool has(size_t hash) const;
    bool add_provider(size_t hash, PictoProvider *p);
    PictoProvider *get_provider(size_t hash) const;

    QHash<size_t, PictoProvider*> m_providers;
    PictoPainter *m_painter;
};


template<class T>
std::unique_ptr<PictoGenerator> provider() {
    return Picto::instance().provider<T>();
}

}

