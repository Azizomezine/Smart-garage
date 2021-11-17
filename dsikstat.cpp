#include "dsikstat.h"
#include "ui_dsikstat.h"
#include <QPieSeries>
DsikStat::DsikStat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DsikStat)
{
    ui->setupUi(this);
}

DsikStat::~DsikStat()
{
    delete ui;
}

void DsikStat::afficherStatDisk(QStringList Services,int freq[])
{
    // 4. Pie Chart Example
    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    QGridLayout* mainLayout = new QGridLayout;
    for(int i=0;i<Services.length();i++)
    {
        series->append(Services.at(i),freq[i]);
    }
    /*
    series->append("urgence",1);
    series->append("psychiatrie",2);
    series->append("neurologie",3);
    series->append("Seeds/Nuts",10);
    series->append("Whole Grains",15);*/

    // Add label to 1st slice
    QVector<QPieSlice*> slice;
    for (int i = 0; i < Services.length(); ++i) {
        slice.push_back(NULL);
    }
    slice[0]=series->slices().at(0);
    slice.at(0)->setLabelVisible();
    slice[1]=series->slices().at(1);
    slice.at(1)->setExploded();
    slice.at(1)->setLabelVisible();
    slice.at(1)->setPen(QPen(Qt::darkGreen, 2));
    slice.at(1)->setBrush(Qt::green);

    // Add label, explode and define brush for 2nd slice
    for (int i = 2; i < Services.length(); ++i) {
        slice[i]=series->slices().at(i);
        slice.at(i)->setLabelVisible();
    }


    // Add labels to rest of slices

    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("What Derek Ate this Week");
    chart->legend()->hide();

    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    // Set the main window widget
    mainLayout->addWidget(chartView,0,0);
    setLayout(mainLayout);
}
