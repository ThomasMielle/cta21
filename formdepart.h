#ifndef FORMDEPART_H
#define FORMDEPART_H

#include <QDialog>

#include <QDebug>

namespace Ui {
class FormDepart;
}

class FormDepart : public QDialog
{
    Q_OBJECT

public:
    explicit FormDepart(QWidget *parent = 0);
    ~FormDepart();

private slots:
    void on_comboBoxTypeInter1_currentIndexChanged(const QString &arg1);

private:
    Ui::FormDepart *ui;
};

#endif // FORMDEPART_H
