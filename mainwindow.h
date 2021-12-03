#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "personnel.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pbmodifier_clicked();

     void on_pb_rechercher_clicked();


     void on_tri_clicked();

     void on_tri2_clicked();

     void on_present_clicked();

     void on_present_2_clicked();

     void on_present_3_clicked();

     void on_present_4_clicked();

     void on_pushButton_clicked();

     void on_radioButton_clicked();

     void on_radioButton_2_clicked();

     void on_radioButton_3_clicked();

     void on_radioButton_4_clicked();


private:
    Ui::MainWindow *ui;
    personnel p;
};

#endif // MAINWINDOW_H
