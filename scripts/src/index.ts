import * as request from 'orange.request';
import * as hbs from 'handlebars';
import * as fs from 'mz/fs';
import * as Path from 'path';


const faRe = /^\$fa-var-/;
const nrRe = /^\d+/;
const outPath = Path.resolve("../QtPicto");


interface Options {
    icons: {name:string,code:number}[];
    provider: string;
    enum:string;
    font: string;
}
const excludes = [
    'try', 'linux', 'font', 'code', 'name', 'explicit', 'class', 'delete', 'public', 'print'
]


async function generate_fontawesome () {


    let str = await request.get('https://raw.githubusercontent.com/FortAwesome/' +
                            'Font-Awesome/master/scss/_variables.scss').text(null, true);


    let icons = [];

    for (const line of str.split('\n')) {
        
        if (!faRe.test(line)) continue;

        let line_a = line.substr(8).trim().split(': ');
       
        let name = line_a[0].replace(/-/gm, '_').trim();
        let code = line_a[1].replace(/[;"\\]*/g,'');

        if (nrRe.test(name) || excludes.indexOf(name) > -1) name = 'fa_' + name;

        icons.push({name:name, code: "0x" + code});

    }

    let Name = "Awesome";
    let name = "awesome";

    let options: Options = {
        icons: icons,
        provider: Name,
        enum: name,
        font: "fontawesome.ttf"
    }

    let buf = await fs.readFile(Path.join(__dirname,"../templates/icon.cpp"));

    let template = hbs.compile(buf.toString());

    let out = template(options);

    await fs.writeFile(Path.join(outPath, `${name}.cpp`), out);


    buf = await fs.readFile(Path.join(__dirname,"../templates/icon.h"));

    template = hbs.compile(buf.toString());

    out = template(options);

    await fs.writeFile(Path.join(outPath, `${name}.h`), out);


    let ret = await request.get('https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/fonts/fontawesome-webfont.ttf').end();
    let blob = await ret.blob();

    await fs.writeFile(Path.join(outPath,"fonts/fontawesome.ttf"), blob);

    await generate_qml(options)
    

}

async function generate_qml(options:Options) {

    let buf = await fs.readFile(Path.join(__dirname,"../templates/enum.qml"));

    let template = hbs.compile(buf.toString());

    let out = template(options);

    await fs.writeFile(Path.resolve(`../QmlPicto/${options.provider}.qml`), out);

}



async function generate_material () {


    let str = await request.get('https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/codepoints').text(null, true);


    let icons = [];
    
    for (const line of str.split('\n')) {
        if (!line) continue;

        let line_a = line.split(' ');
       
        let name = line_a[0] //.replace(/-/gm, '_').trim();
        let code = line_a[1] //.replace(/[;"\\]*/g,'');
        
        if (nrRe.test(name) || excludes.indexOf(name) > -1) name = 'ma_' + name;

        icons.push({name:name, code: "0x" + code});

    }

    let Name = "Material";
    let name = "material";

    let options ={
        icons: icons,
        provider: Name,
        enum: name,
        font: "material.ttf"
    }

    let buf = await fs.readFile(Path.join(__dirname,"../templates/icon.cpp"));

    let template = hbs.compile(buf.toString());

    let out = template(options);

    await fs.writeFile(Path.resolve(outPath,`${name}.cpp`), out);


    buf = await fs.readFile(Path.join(__dirname,"../templates/icon.h"));

    template = hbs.compile(buf.toString());

    out = template(options);

    await fs.writeFile(Path.join(outPath, `${name}.h`), out);


    let ret = await request.get('https://raw.githubusercontent.com/google/material-design-icons/master/iconfont/MaterialIcons-Regular.ttf').end();
    let blob = await ret.blob();

    await fs.writeFile(Path.join(outPath,"fonts/material.ttf"), blob);
    
    await generate_qml(options)

}

async function generate_qrc () {
    let fonts = await fs.readdir(Path.join(outPath,'fonts'))

    let out = [];
    for (let font of fonts) {
        let ext = Path.extname(font)
        if (ext == '.ttf' || ext == '.oft') {
            out.push(`<file>fonts/${font}</file>`);
        } 
    }

    let str = `<RCC>
    <qresource prefix="/">
        ${out.join('\n\t')}
    </qresource>
</RCC>
    `

    await fs.writeFile(Path.join(outPath,`qtpicto.qrc`), str);
}

async function generate_sources() {

    await generate_fontawesome();
    
    

}

function generate() {

    return Promise.all([
        generate_fontawesome(),
        generate_material()
    ])
    .then( () => {
        return generate_qrc();
    });

}


generate().catch( e => {
    console.log(e)
})