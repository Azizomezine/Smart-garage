#ifndef DSIKSTAT_H
#define DSIKSTAT_H

#include <QDialog>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>
#include <QGridLayout>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class DsikStat;
}

class DsikStat : public QDialog
{
    Q_OBJECT

public:
    explicit DsikStat(QWidget *parent = nullptr);
    void afficherStatDisk(QStringList Services,int freq[]);
    ~DsikStat();

private:
    Ui::DsikStat *ui;
};

#endif // DSIKSTAT_H
