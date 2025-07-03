#include "dialog.h"
#include "ui_dialog.h"

#include "resim.h"
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);


    //---------------dosya okuma işlemleri-----------------
    QFile gecenlerOku("C:/Users/Acer/OneDrive/Belgeler/odevdeneme/konumlar.txt");
    if(!gecenlerOku.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Hata!",gecenlerOku.errorString());
        return ;
    }
    QTextStream stream(&gecenlerOku);

    while(!stream.atEnd()) //stream nesnesi henüz dosya sonuna gelmediyse
    {
        koordinatBol += stream.readLine().split(" "); //("100", "200", "200", ...) şeklinde şu an
    }
    gecenlerOku.close();


    //---------------------bağlama işlemleri------------------------

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::karpuzKoy);
    timer->start(800); //karpuz oluşma hızı

    zamanlayiciZaman = new QTimer(this);
    connect(zamanlayiciZaman, &QTimer::timeout, this, &Dialog::zamanlayici);
    zamanlayiciZaman->start(1000); //zamanlayici geri sayma hızı

    kaymaZaman = new QTimer(this);
    connect(kaymaZaman, &QTimer::timeout, this, &Dialog::kay);
    kaymaZaman->start(100); //kayarkenki hızı kontrol


    kesmeZaman = new QTimer(this);
    connect(kesmeZaman, &QTimer::timeout, this, &Dialog::kes);
    kesmeZaman->start(30);



}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::karpuzKoy()
{
    //--------------rasgele koordinat oluşturma ve karpuzları koordinatlara yerleştirme----------


    randomKoordinat = QRandomGenerator::global()->bounded(0,29);

    if( randomKoordinat % 2 == 0)
    {
        randomx = koordinatBol[randomKoordinat].toInt(); //x i ürettiyse +1 ini y olarak alsın
        randomy = koordinatBol[randomKoordinat+1].toInt();
    }
    else
    {
        randomy = koordinatBol[randomKoordinat].toInt();
        randomx = koordinatBol[randomKoordinat-1].toInt();
    }

    resim *etiket= new resim(this);
    etiket->setGeometry(randomx, randomy, 80, 80);

    QPixmap pixmap(":/imegines/images/1.png");
    QPixmap boyutPix = pixmap.scaled(QSize(80,80));
    etiket->setIcon(QIcon(boyutPix)); //karpuz resmini koysun diye
    etiket->setIconSize(boyutPix.size());
    etiket->setStyleSheet("QPushButton { background-color: transparent; border: none; }"); //butonu görünmez yapsın arka planı
    yerlesenKarpuzList.append(etiket);
    etiket->show();

}


void Dialog::zamanlayici()
{
    static int syc = 30;
    if(syc!=-1)
    {
        ui->lbl_sure->setText(QString::number(syc));
        syc--;
    }
    else
    {
        dosyaYaz();
        bilgilendirme();
        close();
    }


}

void Dialog::kes()
{
    kesilenSay=0;
    kacirilanSay=0;

    for(int i=0; i<yerlesenKarpuzList.size(); ++i)
    {
        if(yerlesenKarpuzList[i]->tiklamaKontrol)
        {
            QPixmap pixmap2(":/imegines/images/2.png");

            QPixmap boyutPix2 = pixmap2.scaled(QSize(80,80));
            yerlesenKarpuzList[i]->setIcon(QIcon(boyutPix2)); //fotoğrafı kesilen karpuz olarak güncelledik tıklandığı için
            yerlesenKarpuzList[i]->setIconSize(boyutPix2.size());
            yerlesenKarpuzList[i]->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
            kesilenKarpuzList.append(yerlesenKarpuzList[i]);

            if(kesilenKarpuzList.contains(yerlesenKarpuzList[i]))
            {
                kesilenSay++;
            }
        }

        ui->ln_kesilen->setText(QString::number(kesilenSay));

        if(yerlesenKarpuzList[i]->y() > 800 && !yerlesenKarpuzList[i]->tiklamaKontrol)//bu y uzunluğunu normal karpuz resmi ile geçince kesemedi sayılır
        {kacirilanSay++;}
        ui->ln_kacirilan->setText(QString::number(kacirilanSay));

    }

}

void Dialog::dosyaYaz()
{

    QFile dosyayaYaz("C:/Users/Acer/OneDrive/Belgeler/odevdeneme/skorlar.txt");
    if(!dosyayaYaz.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return;
    }

    QTextStream yaz(&dosyayaYaz);
    QString varOlanVeri = yaz.readAll(); //dosyadaki verileri aldık ki üstüne yazabilelim
    dosyayaYaz.seek(0); //imleç başa
    yaz << kesilenSay <<Qt::endl;
    yaz << varOlanVeri <<Qt::endl;
    dosyayaYaz.close();
}

void Dialog::bilgilendirme()
{
    QFile dosyadanOku("C:/Users/Acer/OneDrive/Belgeler/odevdeneme/skorlar.txt");
    if(!dosyadanOku.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QList<int> okunanlarListe;
    while(!dosyadanOku.atEnd())
    {
        QString okunan = dosyadanOku.readLine();
        int okunanInt = okunan.toInt();
        okunanlarListe.append(okunanInt);
    }
    dosyadanOku.close();

    int maxSkor=0;
    for(int i=0; i<okunanlarListe.size(); ++i)
    {
        if(okunanlarListe[i] > maxSkor)
        {
            maxSkor = okunanlarListe[i]; //maxskor başta 0 belirlendi ve döngü ile gelen eleman maxskor dan büyükse yeni maxskor olarak atanadı
        }
    }

    if(kesilenSay == maxSkor)
    {

        QMessageBox::information(this, "Bilgi!", "Tebrikler Maximum Skor Sizde!"
                                                 "\nKesilen Karpuz Sayısı: "+QString::number(kesilenSay)+
                                                     "\nKaçırılan Karpuz Sayısı: "+QString::number(kacirilanSay)+
                                                     "\nMaximum Skor: "+QString::number(maxSkor));
    }
    else
    {
        QMessageBox::information(this, "Bilgi!", "Maksimum Skoru Geçemediniz!"
                                                 "\nKesilen Karpuz Sayısı: "+QString::number(kesilenSay)+
                                                     "\nKaçırılan Karpuz Sayısı: "+QString::number(kacirilanSay)+
                                                     "\nMaximum Skor: "+QString::number(maxSkor));
    }
}
void Dialog::kay()
{
    for(int i=0; i<yerlesenKarpuzList.size(); ++i)
    {
        if(!kesilenKarpuzList.contains(yerlesenKarpuzList[i])) //kesilenler dursun diye
        {
            yerlesenKarpuzList[i]->setGeometry(yerlesenKarpuzList[i]->x(),
                                               yerlesenKarpuzList[i]->y()+10,
                                               yerlesenKarpuzList[i]->width(),
                                               yerlesenKarpuzList[i]->height());

        }

    }

}
