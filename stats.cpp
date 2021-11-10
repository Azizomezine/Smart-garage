#include "stats.h"
#include "ui_stats.h"
#include "qcustomplot.h"
#include"QSqlRecord"
#include"QSqlQuery"
stats::stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stats)
{
    ui->setupUi(this);
    this->setWindowTitle("Stats");
    plot();
}

stats::~stats()
{
    delete ui;
}





void stats::plot()
{
    //set-up
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->widget->setBackground(QBrush(gradient));
    QCPBars *regen = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
    regen->setAntialiased(false);
    regen->setStackingGap(1);
    regen->setName("Quantité");
    regen->setPen(QPen(QColor(255, 170, 0).lighter(130)));
    regen->setBrush(QColor(255, 170, 0));

    //x axis
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3;
    labels << "Seringue" << "Comprime" << "Autre..." ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);

    ui->widget->xAxis->setTicker(textTicker);
    ui->widget->xAxis->setTickLabelRotation(60);
    ui->widget->xAxis->setSubTicks(false);
    ui->widget->xAxis->setTickLength(0, 4);
    ui->widget->xAxis->setRange(0, 8);
    ui->widget->xAxis->setBasePen(QPen(Qt::white));
    ui->widget->xAxis->setTickPen(QPen(Qt::white));
    ui->widget->xAxis->grid()->setVisible(true);
    ui->widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setLabelColor(Qt::white);

    //y axis

    ui->widget->yAxis->setRange(0,5000);//intervale de x
    ui->widget->yAxis->setPadding(5); // a bit more space to the left border
    ui->widget->yAxis->setBasePen(QPen(Qt::white));
    ui->widget->yAxis->setTickPen(QPen(Qt::white));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
    ui->widget->yAxis->grid()->setSubGridVisible(true);
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setLabelColor(Qt::white);
    ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

//data
    QVector<double> regenData;

    QSqlQuery query1("select SUM(QUANTITE)from MEDICAMENT where TYPE='Seringue'  ");

    while (query1.next()) {
                int  nbr_faute=0;
                 int nbr_fauteee=0;
                            int  nbr_fautee = query1.value(0).toInt();

              QSqlQuery query2("select SUM(QUANTITE)from MEDICAMENT where TYPE='Comprime'");
              while (query2.next()) {

                                      nbr_faute = query2.value(0).toInt();
                                      QSqlQuery query3("select SUM(QUANTITE)from MEDICAMENT where TYPE='Autre...'");
                                      while (query3.next()) {
                                          nbr_fauteee = query3.value(0).toInt();
                                          break;
                                      }
                                     }
              regenData<< nbr_fautee << nbr_faute<< nbr_fauteee;
                            break;
                           }

    regen->setData(ticks, regenData);

    //legend


    ui->widget->legend->setVisible(true);
    ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
    ui->widget->legend->setBorderPen(Qt::NoPen);

    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget->legend->setFont(legendFont);
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);





}
