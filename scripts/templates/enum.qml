pragma Singleton

import QtQuick 2.5

QtObject {
{{#each icons}}
	property string {{name}}: "{{../enum}}/{{name}}"; // "image://{{../enum}}/{{name}}";
{{/each}}
}