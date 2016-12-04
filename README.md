# QtPicto
Qt and Qml icons fonts,


```c++
import <QtPicto/QtPicto>

using picto::awesome;
using picto::material;

int main () {
    
    auto p = picto::provider<awesome>(); 
    
    auto pixmap = p->pixmap(awesome::gear, QSize(100,100));
    auto image = p->image("gear", QSize(60,60));
    
    auto icon = p->icon(awesome::plus, QSize(100, 100));
    
    
    auto pm = picto::provider<material>();
    
    auto button = new QButton();
    button->setIcon(pm->icon(material::add));
    
}

```


```qml

import QtQuick 2.5
import QmlPicto 0.1

Image {
  source: Awesome.gears // or Material
}


```
