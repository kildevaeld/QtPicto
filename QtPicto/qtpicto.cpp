#include "qtpicto.h"
#include <QIconEngine>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>


inline void initMyResource() { Q_INIT_RESOURCE(qtpicto); }


namespace picto {

class PictoCharPainter: public PictoPainter {


    // QtPictoPainter interface
public:
    void paint(PictoProvider *p, QPainter *painter, const QRect &rect, const QColor &color, const QString &text) {
        painter->save();


        painter->setPen(color);

        // add some 'padding' around the icon
        //int drawSize = qRound(rect.height()*options.value("scale-factor").toFloat());

        painter->setFont( p->font(rect.height()) );
        painter->drawText( rect, text, QTextOption( Qt::AlignCenter|Qt::AlignVCenter ) );
        painter->restore();
    }
};


class PictoIconPainterIconEngine : public QIconEngine
{

public:

    PictoIconPainterIconEngine( PictoProvider* provider, PictoPainter* painter, const PictoTheme& options  )
        : provider_m (provider)
        , painter_m (painter)
        , theme_m (options)
    {
    }

    virtual ~PictoIconPainterIconEngine() {}

    PictoIconPainterIconEngine* clone() const
    {
        return new PictoIconPainterIconEngine( provider_m, painter_m, theme_m );
    }

    virtual void paint(QPainter* painter, const QRect& rect, QIcon::Mode mode, QIcon::State state)
    {


        QColor color = theme_m.color;
        QString text = theme_m.text;

        if( mode == QIcon::Disabled ) {
            if (theme_m.disabledColor.isValid()) {
                color = theme_m.disabledColor;
            }
            if( !theme_m.disabledText.isEmpty() ) {
                text = theme_m.disabledText;
            }
        } else if( mode == QIcon::Active ) {
            if (theme_m.activeColor.isValid()) {
                color = theme_m.activeColor;
            }
            if( !theme_m.activeText.isEmpty() ) {
                text = theme_m.activeText;
            }
        } else if( mode == QIcon::Selected ) {
            if (theme_m.selectedColor.isValid()) {
                color = theme_m.selectedText;
            }
            if( !theme_m.selectedText.isEmpty() ) {
                text = theme_m.selectedText;
            }
        }

        painter_m->paint(provider_m, painter, rect, color, text);

    }

    virtual QPixmap pixmap(const QSize& size, QIcon::Mode mode, QIcon::State state)
    {
        QPixmap pm(size);
        pm.fill( Qt::transparent ); // we need transparency
        {
            QPainter p(&pm);
            paint(&p, QRect(QPoint(0,0),size), mode, state);
        }
        return pm;
    }

private:

    PictoProvider* provider_m;                  ///< a reference to the QtAwesome instance
    PictoPainter* painter_m;   ///< a reference to the icon painter
    PictoTheme theme_m;                    ///< the options for this icon painter
};






PictoGenerator::PictoGenerator(PictoProvider *p, PictoPainter *painter): m_provider(p),m_painter(painter) {
    m_theme = PictoTheme{QColor("black")};
}

QIcon PictoGenerator::icon(int character, const PictoTheme &theme) const {

    auto t = m_theme;
    t.text = QString(QChar(static_cast<int>(character)));

    PictoIconPainterIconEngine *engine = new PictoIconPainterIconEngine(m_provider, m_painter, t);

    return QIcon(engine);
}

QIcon PictoGenerator::icon(const QString &name, const PictoTheme &theme) const {
    int code = m_provider->code(name);

    if (code == 0) return QIcon();

    return icon(code, theme);
}

QPixmap PictoGenerator::pixmap(int character, const QSize &size, const QColor &color) const {



    QPixmap pm(size *::QGuiApplication::primaryScreen()->devicePixelRatio());
    pm.setDevicePixelRatio(::QGuiApplication::primaryScreen()->devicePixelRatio());
    QString text(QChar(static_cast<int>(character)));

    pm.fill( Qt::transparent ); // we need transparency
    {
        QPainter p(&pm);
        //p.setRenderHint(QPainter::TextAntialiasing);
        //p.setRenderHint(QPainter::Antialiasing);
        m_painter->paint(m_provider, &p, QRect(QPoint(0,0),pm.size() / pm.devicePixelRatio()),color, text);
    }
    return pm;
}

QPixmap PictoGenerator::pixmap(const QString &name, const QSize &size, const QColor &color) const {
    int code = m_provider->code(name);
    if (code == 0) return QPixmap();
    return pixmap(code, size, color);
}

QImage PictoGenerator::image(int character, const QSize &size, const QColor &color) const {
    QImage pm(size, QImage::Format_ARGB32_Premultiplied);
    QString text(QChar(static_cast<int>(character)));
    pm.fill( Qt::transparent ); // we need transparency
    {
        QPainter p(&pm);
        p.setRenderHint(QPainter::TextAntialiasing);
        //paint(&p, QRect(QPoint(0,0),size), mode, state);
        m_painter->paint(m_provider, &p, QRect(QPoint(0,0),size),color, text);
    }
    return pm;
}

QImage PictoGenerator::image(const QString &name, const QSize &size, const QColor &color) const {
    int code = m_provider->code(name);
    if (code == 0) return QImage();
    return image(code, size, color);
}


Picto::Picto(): m_painter(new PictoCharPainter()) {
    initMyResource();
}


std::unique_ptr<PictoGenerator> Picto::provider(const QString &name) {
    auto values = m_providers.values();

    auto p = std::find_if(values.begin(), values.end(), [&](PictoProvider *p) {
        return p->providerName() == name;
    });

    if (p != std::end(values)) {
        return std::unique_ptr<PictoGenerator>(new PictoGenerator(p[0], m_painter));
    }

    return nullptr;
}

QStringList Picto::providers() const {
    auto keys = m_providers.values();

    QStringList out;
    std::transform(keys.begin(), keys.end(),std::back_inserter(out),[](PictoProvider *p) {
        return p->providerName();
    });

    return out;
}

bool Picto::has(size_t hash) const {
    return this->m_providers.contains((hash));
}

bool Picto::add_provider(size_t hash, PictoProvider *p) {

    if (!p->initialize()) {
        return false;
    }
    this->m_providers.insert(hash, p);
    return true;
}

PictoProvider *Picto::get_provider(size_t hash) const
{
    return m_providers.value(hash, nullptr);
}

}
