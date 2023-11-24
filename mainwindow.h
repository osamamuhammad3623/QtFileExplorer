#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QFileInfo>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void g_directory_changed(QString new_g_dir);

private slots:
    void on_actionChoose_Directory_triggered();

    void on_list_currentTextChanged(const QString &currentText);

    void addFilesToList(QDir directory);
    void on_prevDir_clicked();
    void on_g_directory_changed(QString new_g_dir);
    void openFileInTextEdit(QString path);
    void writeFile(QString path, QString data);

    void on_save_clicked();

private:
    Ui::MainWindow *ui;
    QString g_directory = "";
};
#endif // MAINWINDOW_H
