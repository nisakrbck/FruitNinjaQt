#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QStringList>
#include <QList>
#include <QRandomGenerator>  //random konum için
#include "resim.h"
#include <QTimer>
#include <QVector> //liste de append kullanmak için
#include <QPixmap>
#include <QWidget>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void karpuzKoy();
    void kay();
    void zamanlayici();
    void kes();
    void dosyaYaz();
    void bilgilendirme();

private:
    Ui::Dialog *ui;
    int randomKoordinat;
    QStringList koordinatBol;

    int randomx,randomy;

    QList<resim*> yerlesenKarpuzList;
    QList<resim*> kesilenKarpuzList;

    int kesilenSay,kacirilanSay;
    QTimer *timer;
    QTimer *kaymaZaman;
    QTimer *kesmeZaman;
    QTimer *zamanlayiciZaman;

};
#endif // DIALOG_H
