#include "selectbox.h"

SelectBox::SelectBox()
{

}

QRectF SelectBox::boundingRect() const
{
    return QRectF(330, 0, 600, 90);
}

void SelectBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QImage image(":/graphics/Screen/ChooserBackground.png");
    painter->drawImage(boundingRect(), image);
    //--------------
    QFont font;
    font.setPointSize(12);
    painter->setBrush(QColor(128, 128, 0, 250));
    painter->drawRect(QRect(343, 63, 63, 25));
    painter->setFont(font);
    painter->drawText(360, 83, QString::number(Cards::sunTotal));
    //--------------
    painter->setBrush(QColor(128, 128, 0, 250));
    painter->drawRect(QRect(390, 570, 400, 25));
    painter->setFont(font);
    painter->drawText(425, 590, "胜 利 目 标 ：收 集 满 2000 点 阳 光 ！");
}

void SelectBox::advance(int phase)
{
    if(!phase)
        return;
    update();
}
