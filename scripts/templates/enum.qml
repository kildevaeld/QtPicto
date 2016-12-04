pragma Singleton

import QtQuick 2.5
import QmlPicto 0.1

KeyTable {
{{#each icons}}
	property string {{name}}: "image://{{../enum}}/{{name}}";
{{/each}}
}