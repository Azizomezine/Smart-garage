#ifndef CHANGETHEME_H
#define CHANGETHEME_H

#include <QDialog>

namespace Ui {
class Changetheme;
}

class Changetheme : public QDialog
{
    Q_OBJECT

public:
    explicit Changetheme(QWidget *parent = nullptr);
    ~Changetheme();

private slots:
    void on_Applytheme_clicked();

    void on_cancel_clicked();

private:
    Ui::Changetheme *ui;
};

#endif // CHANGETHEME_H
