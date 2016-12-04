#pragma once

#include "qtpicto.h"

namespace picto {

class {{enum}}: public QObject {

    friend class Picto;

    Q_OBJECT

    class Provider : public PictoProvider {
        friend class {{enum}};
    public:
        
        virtual ~Provider () {}
        virtual bool initialize();
        virtual QFont font(int size);
        virtual QString name(int code);
        virtual int code(const QString &name);
        virtual QString providerName();

        

    private:
        Provider() {}
        
        QString m_fontName;

    };


public:
    enum icon { 
    {{#each icons}} 
        {{name}} = {{code}}, 
    {{/each}} 
    };

    Q_ENUM({{enum}}::icon)

    static PictoProvider *provider() {
        return new Provider();
    }

private:
    {{enum}}(): QObject() {}
    ~{{enum}}() {}
};



}