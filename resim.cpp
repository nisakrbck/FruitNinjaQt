
#include "resim.h"
#include <QPixmap>
#include <QWidget>
resim::resim(QWidget *parent) : QPushButton(parent)
{
    tiklamaKontrol = false;
    connect(this, &QPushButton::clicked, this, &resim::tikla);
}

void resim:: tikla()
{
    tiklamaKontrol =!tiklamaKontrol;
}
