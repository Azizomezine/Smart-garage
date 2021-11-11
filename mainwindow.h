#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "client.h"
#include "avis.h"
#include "QrCode.hpp"
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

    void on_pushButtonAjouter_clicked();

    void on_pushButtonSupprimer_clicked();

    void on_pushButtonModifier_clicked();

    void on_pushButtonActualiser_clicked();

    void on_pushButtonRechercher_clicked();

    void on_pushButtontrier_clicked();

    void on_pushButtonClient_clicked();

    void on_pushButtonAvis_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonAjouteravis_clicked();





  void on_qrcodegen_clicked();

  void on_pushButtonActualiser_2_clicked();

  void on_pushButtonSupprimer_2_clicked();



  void on_pushButtonModifieravis_clicked();





  void on_cin_comboBox2_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Client Etmp;
    avis at;
};

#endif // MAINWINDOW_H
