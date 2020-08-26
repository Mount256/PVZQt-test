#ifndef PAPERZOMBIE_H
#define PAPERZOMBIE_H
#include "zombie.h"

class PaperZombie : public Zombie
{
public:
    PaperZombie(QPointF point);
    ~PaperZombie();
    void advance(int phase);
    QRectF boundingRect() const;

private:
    int paperHP;
    bool isPaper;
    void paperMovie(QString pic);
};

#endif // PAPERZOMBIE_H
