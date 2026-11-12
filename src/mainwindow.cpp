#include "mainwindow.h"
#include "./parser.h"
#include "./ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringList>
#include <QString>
#include <iostream>
#include <exception>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actionAdd_File_triggered()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        tr("Seleccione el archivo"),
        "./",
        tr("Archivos de texto(*.txt)"));

    if(path.isEmpty()) {
        QMessageBox::critical(this, "Error", "No selecciono un archivo");
        return;
    }

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    filePath = path;

    ui->inputFileText->setPlainText(QTextStream(&file).readAll());
    ui->inputFileText->setReadOnly(true);

    //QTextStream stream(&file);
    //ui->addFileText->setPlainText(stream.readAll());
    //file.close();

    //filename = path;

    //ui->plainTextEdit->setPlainText("Hello World");
}


void MainWindow::on_actionCalculate_triggered()
{
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Choose an input file"));
        return;
    }

    QStringList options = {"Brute Force", "Greedy", "Dynamic Programming"};
    bool ok;
    QString algorithm = QInputDialog::getItem(this, "Algorithm", "Choose the algorithm", options, 0, false, &ok);

    if(!ok) return;

    try {
        Network rs = inputParser(filePath.toStdString());
        const string alg = algorithm.toStdString();
        string output;

        if (alg == "Brute Force") {
            output = outputParser(modexFB(rs));
        }
        else if (alg == "Greedy") {
            output = outputParser(modexV(rs));
        }
        else if (alg == "Dynamic Programming") {
            output = outputParser(modexPD(rs));
        }
        else {
            QMessageBox::critical(this, tr("Error"), tr("Bad algotithm"));
            return;
        }

        const QString answer = QString::fromStdString(output);
        ui->outputFileText->setPlainText(answer);

        const QFileInfo inputInfo(filePath);
        const QString outputPath = inputInfo.dir().filePath(
            inputInfo.completeBaseName() + "out.txt");
        QFile outputFile(outputPath);
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("No se pudo crear el archivo de salida:\n%1")
                                      .arg(outputFile.errorString()));
            return;
        }

        const QByteArray outputBytes = answer.toUtf8();
        if (outputFile.write(outputBytes) != outputBytes.size()) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("No se pudo escribir el archivo de salida:\n%1")
                                      .arg(outputFile.errorString()));
            return;
        }

        QMessageBox::information(this, tr("Salida guardada"),
                                 tr("La salida se guardó en:\n%1").arg(outputPath));
    }
    catch (const std::exception &error) {
        QMessageBox::critical(this, tr("Error"),
                              tr("No se pudo calcular la salida:\n%1")
                                  .arg(QString::fromLocal8Bit(error.what())));
    }

    ui->outputFileText->setReadOnly(true);
}
