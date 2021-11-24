#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"voiture.h"
#include <QDialog>
#include<QWidget>
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
    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();
    //void on_pb_exit_clicked();


    void on_pb_exit_clicked();

    void on_radioButton_croissant_clicked();

    void on_radioButton_dcroissant_clicked();

    void on_rechercher_button_clicked();

    void on_statsmed_clicked();

    void on_btn_export_clicked();


    void on_btn_imp_clicked();


private:
    Ui::MainWindow *ui;
    voiture v;
};

#endif // MAINWINDOW_H



