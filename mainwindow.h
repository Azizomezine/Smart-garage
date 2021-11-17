#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "client.h"
#include "avis.h"
#include "QrCode.hpp"
#include "carte.h"
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

  void on_pushButton_3_clicked();

 void on_pushButton_4_clicked();



void on_Button_croissant_clicked();

void on_Button_dcroissant_clicked();




void on_stat_clicked();

void on_carte_client_clicked();

void on_stat_avis_clicked();

void on_pushButtonreturn_clicked();

void on_pushButtonajouter_clicked();


void on_ajouter_pts_clicked();

void on_Actualiser_clicked();

private:
    Ui::MainWindow *ui;
    Client Etmp;
    avis at;
    Carte ct;
int cinc;
};

#endif // MAINWINDOW_H
