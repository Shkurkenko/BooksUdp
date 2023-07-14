#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "udpclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new UDPClient)
{
    ui->setupUi(this);
    connect(client, SIGNAL(DataRecieved(QJsonObject&)), this, SLOT(SetData(QJsonObject&)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}

void MainWindow::SetData(QJsonObject &data)
{
    ui->name->setText(data["name"].toString());
    ui->author->setText(data["author"].toString());
    ui->number_of_copies->setText(QString::number(data["number_of_copies"].toInt()));
    ui->price->setText(QString::number(data["price"].toInt()));
}

void MainWindow::on_searchBook_clicked()
{
    if(ui->book_line->text() == "") {
        ui->line_error->setText("Input is empty!");
        return;
    } else {
        ui->line_error->setText("");
    }
    QByteArray Data;
    QString name = ui->book_line->text();
    Data = name.toUtf8();
    client->SendBookName(Data);
}

