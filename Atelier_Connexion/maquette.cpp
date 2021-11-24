#include "maquette.h"
#include<iostream>
#include "ui_maquette.h"
#include"voiture.h"
#include<QMessageBox>
#include<QTextStream>
#include<QIntValidator>
#include"modifier.h"
#include<QFile>
#include<QTextStream>
#include<QPixmap>
#include <QPrinter>
#include <QPrintDialog>


#include<QTextDocument>

#include<QDebug>
#include <QtPrintSupport/QPrinter>




using namespace std;
maquette::maquette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maquette)
{
    ui->setupUi(this);
    ui->tab_voiture->setModel(V.afficher());

        ui->heure_E->setValidator(new QIntValidator(0, 23, this));
         ui->heure_S->setValidator(new QIntValidator(0, 23, this));
}

maquette::~maquette()
{
    delete ui;
}

void maquette::on_pb_ajouter_clicked()
{

    QString  NOM=ui->NOM->text();
    QString Modele=ui->Modele->text();
    QString Categorie=ui->Categorie-> text();
    QString Matricule=ui->Matricule-> text();



    voiture v(NOM, Modele, Categorie, Matricule) ;

bool test=v.ajouter();

if(test)
{
    //refresh
    ui->tab_voiture->setModel(v.afficher());
    QMessageBox::information( nullptr, QObject::tr("OK"),
                QObject::tr("Ajout successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
else
    QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("Ajout failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);





}

void maquette::on_PB_supp_clicked()
{
    Voiture V;
    QString MATRICULE=ui->M_supp->text();
    bool test=V.supprimer(MATRICULE);
            QMessageBox msgBox;
            if(test)
            {
                ui->tab_voiture->setModel(V.afficher());
                msgBox.setText("Suppression avec succes.");
            }


            else
                    msgBox.setText("echec de suppression.");
            msgBox.exec();
}


 void maquette::on_btn_edit_clicked()
{
    modifier W;
    W.show();
    W.exec();

}

void maquette::on_btn_afficher_clicked()
{
    ui->tab_voiture->setModel(V.afficher());
}

void maquette::on_btn_calculer_clicked()
{
    Voiture V;
    int nbr_v;
    nbr_v=V.calculer();
    ui->res_calc->display(nbr_v);
}


void maquette::on_btn_stat_clicked()
{

    QSqlQueryModel * model= new QSqlQueryModel();
                        model->setQuery("select * from VOITURE where HRE < 10 ");
                        float heure1=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE  between 10 and 14 ");
                        float heure2=model->rowCount();
                        model->setQuery("select * from VOITURE where HRE >14 ");
                        float heure3=model->rowCount();
                        float total=heure1+heure2+heure3;
                        QString a=QString("moins de 10 hr "+QString::number((heure1*100)/total,'f',2)+"%" );
                        QString b=QString("entre 10 et 14 hr "+QString::number((heure2*100)/total,'f',2)+"%" );
                        QString c=QString("+14 hr "+QString::number((heure3*100)/total,'f',2)+"%" );
                        QPieSeries *series = new QPieSeries();
                        series->append(a,heure1);
                        series->append(b,heure2);
                        series->append(c,heure3);
                if (heure1!=0)
                {QPieSlice *slice = series->slices().at(0);
                 slice->setLabelVisible();
                 slice->setPen(QPen());}
                if ( heure2!=0)
                {
                         // Add label, explode and define brush for 2nd slice
                         QPieSlice *slice1 = series->slices().at(1);
                         //slice1->setExploded();
                         slice1->setLabelVisible();
                }
                if(heure3!=0)
                {
                         // Add labels to rest of slices
                         QPieSlice *slice2 = series->slices().at(2);
                         //slice1->setExploded();
                         slice2->setLabelVisible();
                }
                        // Create the chart widget
                        QChart *chart = new QChart();
                        // Add data to chart with title and hide legend
                        chart->addSeries(series);
                        chart->setTitle("Pourcentage Par heure :Nombre Des voiture "+ QString::number(total));
                        chart->legend()->hide();
                        // Used to display the chart
                        QChartView *chartView = new QChartView(chart);
                        chartView->setRenderHint(QPainter::Antialiasing);
                        chartView->resize(1000,500);
                        chartView->show();


}


void maquette::on_btn_export_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        exportExcel obj(fileName, "mydata", ui->tab_voiture);

        //colums to export
        obj.addField(0, "MATRICULE", "char(20)");
        obj.addField(1, "ANNONCE", "char(20)");
        obj.addField(2, "DOMAINE", "char(20)");
        obj.addField(3, "EXPERIENCE", "char(20)");
        obj.addField(4, "SALAIRE", "char(20)");




        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

void maquette::on_btn_imp_clicked()
{
    QString strStream;
                             QTextStream out(&strStream);

                             const int rowCount = ui->tab_voiture->model()->rowCount();
                             const int columnCount = ui->tab_voiture->model()->columnCount();
                             QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                             out <<"<html>\n"
                                   "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                 << "<title>ERP - COMmANDE LIST<title>\n "
                                 << "</head>\n"
                                 "<body bgcolor=#ffffff link=#5000A0>\n"
                                 "<h1 style=\"text-align: center;\"><strong> ******LISTE DES  licence commerciale ******"+TT+" </strong></h1>"
                                 "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                                   "</br> </br>";
                             // headers
                             out << "<thead><tr bgcolor=#d6e5ff>";
                             for (int column = 0; column < columnCount; column++)
                                 if (!ui->tab_voiture->isColumnHidden(column))
                                     out << QString("<th>%1</th>").arg(ui->tab_voiture->model()->headerData(column, Qt::Horizontal).toString());
                             out << "</tr></thead>\n";

                             // data table
                             for (int row = 0; row < rowCount; row++) {
                                 out << "<tr>";
                                 for (int column = 0; column < columnCount; column++) {
                                     if (!ui->tab_voiture->isColumnHidden(column)) {
                                         QString data =ui->tab_voiture->model()->data(ui->tab_voiture->model()->index(row, column)).toString().simplified();
                                         out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                     }
                                 }
                                 out << "</tr>\n";
                             }
                             out <<  "</table>\n"
                                 "</body>\n"
                                 "</html>\n";

                             QTextDocument *document = new QTextDocument();
                             document->setHtml(strStream);

                             QPrinter printer;

                             QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                             if (dialog->exec() == QDialog::Accepted) {
                                 document->print(&printer);
                             }

                             delete document;


}

void maquette::on_btn_upload_2_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "", tr("image (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            ui->image->setPixmap(QPixmap::fromImage(image));
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Image non effectué.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}
