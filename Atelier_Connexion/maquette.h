#ifndef MAQUETTE_H
#define MAQUETTE_H

#include <QDialog>
#include<voiture.h>
#include<QWidget>

namespace Ui {
class maquette;
}

class maquette : public QDialog
{
    Q_OBJECT

public:
    explicit maquette(QWidget *parent = nullptr);
    ~maquette();

private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_btn_edit_clicked();

    void on_btn_afficher_clicked();

    void on_btn_edit_2_triggered(QAction *arg1);

    //void on_btn_calculer_clicked();

    void on_btn_stat_clicked();




    //void on_btn_export_clicked();

//    void on_btn_imp_clicked();


   // void on_btn_upload_2_clicked();

private:
    Ui::maquette *ui;
    voiture V;
};

#endif // MAQUETTE_H
