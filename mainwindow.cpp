#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // when the current directory changes, update it in GUI
    connect(this, this->g_directory_changed, this, this->on_g_directory_changed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addFilesToList(QDir directory){
    ui->list->clear();
    for(auto entry :  directory.entryInfoList()){
        if(entry.fileName() == "." || entry.fileName() == ".."){
            continue;
        }
        ui->list->addItem(entry.fileName());
    }
}

void MainWindow::on_actionChoose_Directory_triggered()
{
    g_directory = QFileDialog::getExistingDirectory(this,"Choose Directory","");
    if(g_directory != ""){
        QDir directory(g_directory);
        emit g_directory_changed(g_directory);
        addFilesToList(directory);
    }
}

void MainWindow::openFileInTextEdit(QString path){
    QFile file(path);
    if (file.open(QFile::ReadOnly)){
        QTextStream inStream(&file);
        ui->content->setText(inStream.readAll());
        file.close();
    }
}

void MainWindow::on_list_currentTextChanged(const QString &currentText)
{
    QString absPath = g_directory + "/" + currentText;
    QFileInfo finfo(absPath);

    // if user chooses a file
    if(finfo.isFile()){
        openFileInTextEdit(absPath);
    }
    // if user chooses a directory
    else if(finfo.isDir()){
        g_directory = absPath;
        emit g_directory_changed(g_directory);
        QDir directory(absPath);
        addFilesToList(directory);
    }
}


void MainWindow::on_prevDir_clicked()
{
    if(g_directory == ""){
        return;
    }
    QFileInfo f(g_directory);
    g_directory = f.absolutePath(); // get the directory of the current directory
    emit g_directory_changed(g_directory);
    addFilesToList(f.absoluteDir());
}

void MainWindow::on_g_directory_changed(QString new_g_dir)
{
    ui->g_dir->setText(new_g_dir);
}
