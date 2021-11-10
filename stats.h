#ifndef STATS_H
#define STATS_H

#include <QDialog>
#include "connection.h"
#include "qcustomplot.h"
#include <QWidget>

namespace Ui {
class stats;
}

class stats : public QDialog
{
    Q_OBJECT

public:
    explicit stats(QWidget *parent = nullptr);
    ~stats();
    void plot();
private:
    Ui::stats *ui;
};

#endif // STATS_H

