#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include "client.h"
#include "avis.h"
#include "QrCode.hpp"
#include "personnel.h"
#include "carte.h"
#include"voiture.h"
#include "finance.h"
#include "fournisseur.h"
#include <QDialog>
#include<QWidget>
#include <QSslSocket>
#include "SmtpMime"
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include "SmtpMime"
#include "notif.h"
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

void on_pushButtonActualiser_3_clicked();



void on_excel_clicked();

void on_pushButtonfichierpdf_clicked();




void on_Applytheme_clicked();

void on_pushButtoninderx4_clicked();

void on_cancel_clicked();

void on_pb_ajouter_clicked();

void on_tri_clicked();

void on_pb_supprimer_clicked();

void on_pbmodifier_clicked();

void on_pb_rechercher_clicked();
void on_tri2_clicked();
void on_pushButtonAvis_2_clicked();

void on_pushButton_5_clicked();

void on_pb_ajouter_2_clicked();

void on_pb_modifier_clicked();

void on_pb_supprimer_2_clicked();

void on_pb_exit_clicked();

void on_radioButton_croissant_clicked();

void on_radioButton_dcroissant_clicked();

void on_rechercher_button_clicked();

void on_btn_export_clicked();

void on_btn_imp_clicked();

void on_statsmed_clicked();

void on_pushButton_7_clicked();

void on_pushButton_6_clicked();

void on_pushbutton_finance_clicked();

void on_pushButton_14_clicked();



void on_pb_supprimer2_clicked();

void on_pushButton_13_clicked();

void on_pushButton_11_clicked();

void on_pushButton_8_clicked();

void on_pushButton_12_clicked();

void on_baj_clicked();

void on_statperso_clicked();

void on_radioButton_clicked();

void on_radioButton_2_clicked();

void on_radioButton_3_clicked();

void on_radioButton_4_clicked();

void on_pushButton_15_clicked();

void on_exportperso_clicked();

//chkmbo


void on_supp_clicked();

void on_Mod_2_clicked();

// void on_rechercher_button_clicked();

//void on_trier_button_clicked();

//void on_envoyer_clicked();

void on_trierc_currentTextChanged(const QString &arg1);



void on_return_2_clicked();

void on_pushbutton_fournisseur_clicked();

void on_pushButtonAjouter_2_clicked();

void on_Login_clicked();

void on_pushButtonClient_3_clicked();

void on_pushButtonAvis_5_clicked();

void on_pb_exit_3_clicked();



void on_theme_clicked();

void on_pb_exit_4_clicked();

private:
    Ui::MainWindow *ui;


    Client Etmp;
        FOURNISSEUR F;
    avis at;
    Carte ct;
int cinc;
 personnel p;
 voiture v;
 Finance f;
  QPieSeries *series = new QPieSeries();
};

#endif // MAINWINDOW_H
