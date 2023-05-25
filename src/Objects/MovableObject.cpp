#include "MovableObject.h"

void MovableObject::setSpeed(double speed) {
    speed_ = speed;
}

void MovableObject::setDirection(const QPointF& direction) {
    direction_ = direction;
    if (!direction_.isNull())
        sightDirection_ = direction;
}

double MovableObject::getSpeed() const {
    return speed_;
}

const QPointF& MovableObject::getDirection() const {
    return direction_;
}

void MovableObject::move() {
    move(speed_, direction_);
}

MovableObject::MovableObject() : speed_(), direction_() { }

void MovableObject::move(double speed, const QPointF& direction, bool animate) {
    auto length = vecLength(direction);
    if (length == 0) {
        return;
    }
    setPosition(
        {pos_.x() + speed * direction.x() / length, pos_.y() + speed * direction.y() / length}
    );
    if (animation_.isActive() && animate)
        animation_.nextFrame();
}

const QPointF& MovableObject::getSightDirection() const {
    return sightDirection_;
}

void MovableObject::setAnimation(AnimationManager& anim) {
    animation_ = std::move(anim);
}
