#pragma once
#include "Weapon.h"

class Missile : public Weapon {
public:
    explicit Missile(AbstractPlayer* player);
    Projectile* activateWeapon(const std::vector<Enemy*>& enemies) override;
    void levelUp() override;
};

class MissileProjectile : public Projectile {
    const int size = 20;
public:
    MissileProjectile(int damage, double speed, int pierce) : Projectile(damage, speed, 0, pierce) {};
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};
