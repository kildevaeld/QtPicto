"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator.throw(value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments)).next());
    });
};
const request = require('orange.request');
const hbs = require('handlebars');
const fs = require('mz/fs');
const Path = require('path');
const faRe = /^\$fa-var-/;
const nrRe = /^\d+/;
const outPath = Path.resolve("../QtPicto");
function generate_fontawesome() {
    return __awaiter(this, void 0, void 0, function* () {
        let str = yield request.get('https://raw.githubusercontent.com/FortAwesome/' +
            'Font-Awesome/master/scss/_variables.scss').text(null, true);
        let icons = [];
        for (const line of str.split('\n')) {
            if (!faRe.test(line))
                continue;
            let line_a = line.substr(8).trim().split(': ');
            let name = line_a[0].replace(/-/gm, '_').trim();
            let code = line_a[1].replace(/[;"\\]*/g, '');
            if (nrRe.test(name) || name == 'try' || name == 'linux' || name == 'font' || name == 'code')
                name = 'fa_' + name;
            icons.push({ name: name, code: "0x" + code });
        }
        let Name = "Awesome";
        let name = "awesome";
        let options = {
            icons: icons,
            provider: Name,
            enum: name,
            font: "fontawesome.ttf"
        };
        let buf = yield fs.readFile(Path.join(__dirname, "../templates/icon.cpp"));
        let template = hbs.compile(buf.toString());
        let out = template(options);
        yield fs.writeFile(Path.join(outPath, `${name}.cpp`), out);
        buf = yield fs.readFile(Path.join(__dirname, "../templates/icon.h"));
        template = hbs.compile(buf.toString());
        out = template(options);
        yield fs.writeFile(Path.join(outPath, `${name}.h`), out);
        let ret = yield request.get('https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/fonts/fontawesome-webfont.ttf').end();
        let blob = yield ret.blob();
        yield fs.writeFile(Path.join(outPath, "fonts/fontawesome.ttf"), blob);
        yield generate_qml(options);
    });
}
function generate_qml(options) {
    return __awaiter(this, void 0, void 0, function* () {
        let buf = yield fs.readFile(Path.join(__dirname, "../templates/enum.qml"));
        let template = hbs.compile(buf.toString());
        let out = template(options);
        yield fs.writeFile(Path.resolve(`../QmlPicto/${options.provider}.qml`), out);
    });
}
const excludes = [
    'try', 'linux', 'font', 'code', 'name', 'explicit', 'class', 'delete', 'public'
];
function generate_material() {
    return __awaiter(this, void 0, void 0, function* () {
        let str = yield request.get('https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints').text(null, true);
        let icons = [];
        for (const line of str.split('\n')) {
            if (!line)
                continue;
            let line_a = line.split(' ');
            let name = line_a[0]; //.replace(/-/gm, '_').trim();
            let code = line_a[1]; //.replace(/[;"\\]*/g,'');
            if (nrRe.test(name) || excludes.indexOf(name) > -1)
                name = 'ma_' + name;
            icons.push({ name: name, code: "0x" + code });
        }
        let Name = "Material";
        let name = "material";
        let options = {
            icons: icons,
            provider: Name,
            enum: name,
            font: "material.ttf"
        };
        let buf = yield fs.readFile(Path.join(__dirname, "../templates/icon.cpp"));
        let template = hbs.compile(buf.toString());
        let out = template(options);
        yield fs.writeFile(Path.resolve(outPath, `${name}.cpp`), out);
        buf = yield fs.readFile(Path.join(__dirname, "../templates/icon.h"));
        template = hbs.compile(buf.toString());
        out = template(options);
        yield fs.writeFile(Path.join(outPath, `${name}.h`), out);
        let ret = yield request.get('https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/MaterialIcons-Regular.ttf').end();
        let blob = yield ret.blob();
        yield fs.writeFile(Path.join(outPath, "fonts/material.ttf"), blob);
        yield generate_qml(options);
    });
}
function generate_qrc() {
    return __awaiter(this, void 0, void 0, function* () {
        let fonts = yield fs.readdir(Path.join(outPath, 'fonts'));
        let out = [];
        for (let font of fonts) {
            let ext = Path.extname(font);
            if (ext == '.ttf' || ext == '.oft') {
                out.push(`<file>fonts/${font}</file>`);
            }
        }
        let str = `<RCC>
    <qresource prefix="/">
        ${out.join('\n\t')}
    </qresource>
</RCC>
    `;
        yield fs.writeFile(Path.join(outPath, `qtpicto.qrc`), str);
    });
}
function generate_sources() {
    return __awaiter(this, void 0, void 0, function* () {
        yield generate_fontawesome();
    });
}
function generate() {
    return Promise.all([
        generate_fontawesome(),
        generate_material()
    ])
        .then(() => {
        return generate_qrc();
    });
}
generate().catch(e => {
    console.log(e);
});
