#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../QtPicto/QtPicto"

using picto::awesome;
using picto::material;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    auto pr = picto::provider<material>();


    auto pix = pr->pixmap(material::add, ui->label->size(), QColor("red"));

    ui->label->setPixmap(pix);

    ui->pushButton->setIcon(pr->icon(material::settings));



}

MainWindow::~MainWindow()
{
    delete ui;
}
