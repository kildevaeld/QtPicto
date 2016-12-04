import QtQuick 2.5

Item {

    property string source;
    property color color;

    property alias asynchronous: __image.asynchronous
    property alias autoTransform: __image.autoTransform
    property alias cache: __image.cache
    property alias fillMode: __image.fillMode
    property alias horizontalAlignment: __image.horizontalAlignment
    property alias status: __image.status
    property alias progress: __image.progress


    onWidthChanged: {
        this._update()
    }

    onSourceChanged: {
        this._update()
    }

    Image {
        anchors.fill: parent
        id: __image

    }


    function _update () {
        if (!source.match(/^(image:\/)?awesome|material/)) {
            return __image.source = source;
        }



        var s = source;
        if (width == 0 || height == 0) return

        var args = width > 0 && height > 0 ? ['width='+width, 'height='+height] : [];
        if (color) {
            args.push('color=' + color);
        }

        __image.source = s + (args.length > 0 ? '?' + args.join('&') : '');

    }

}
