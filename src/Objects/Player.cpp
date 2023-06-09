#include "Player.h"
#include "HpBar.h"
#include "Missile.h"
#include "Whip.h"
#include "Knife.h"
#include "Lightning.h"
#include <QPainter>

Player::Player() : AbstractPlayer() {
    speed_ = 2;

    weapons_.push_back(std::make_shared<Whip>(this));
    weapons_.push_back(std::make_shared<Lightning>(this));
    weapons_.push_back(std::make_shared<Knife>(this));
    weapons_.push_back(std::make_shared<Missile>(this));
    weapons_.front()->levelUp();


    for (int i = 0; i < 4; ++i) {
        passives_.push_back(std::make_shared<PassiveUpgrade>(static_cast<UpgradeType>(i), this));
    }

    AnimationManager anim(QPixmap(":/Antonio.png"), 4, speed_, 32, 34, 4);
    setAnimation(anim);

    auto* hpBar = new HpBar(this);
    hpBar->setPos(0, -boundingRect().height() / 2 - hpBar->boundingRect().height() / 2 - 5);
}

void Player::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    //    painter->setPen({Qt::black, 2});
    //    painter->drawRect(boundingRect());
    painter->scale(1, -1);
    painter->drawPixmap(
        boundingRect().topLeft(), animation_.getCurrentFrame().transformed(QTransform::fromScale(sightDirection_.x() >= 0 ? 1 : -1, 1)).scaled(47, 50)
    );
}

QRectF Player::boundingRect() const {
    return QRectF(-47. / 2, -25, 47, 50);
}

const std::vector<std::shared_ptr<Weapon>>& Player::getWeapons() {
    return weapons_;
}

const std::vector<std::shared_ptr<PassiveUpgrade>>& Player::getPassives() {
    return passives_;
}

std::vector<Upgrade*> Player::getPossibleUpgrades() {
    std::vector<Upgrade*> possibleUpgrades;
    for (auto& weapon : weapons_) {
        if (weapon->getLevel() < weapon->maxLevel) {
            possibleUpgrades.push_back(weapon.get());
        }
    }
    for (auto& passive : passives_) {
        if (passive->getLevel() < passive->maxLevel) {
            possibleUpgrades.push_back(passive.get());
        }
    }
    return possibleUpgrades;
}
