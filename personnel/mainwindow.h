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

private:
    Ui::MainWindow *ui;
    personnel p;
};

#endif // MAINWINDOW_H
