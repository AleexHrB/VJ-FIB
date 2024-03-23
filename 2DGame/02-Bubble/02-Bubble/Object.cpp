#include "Object.h"

void Object::update(int deltaTime)
{
    sprite->update(deltaTime);
    if (position.y  < 370) {
        t += deltaTime / 100.0;
        position.x = initPos.x + t * speed.x;
        position.y = initPos.y + t * speed.y;
        sprite->setPosition(position);
    }
}

Effects Object::applyEffect()
{
    return this -> eff;
}

unsigned int Object::getBonus()
{
    if (this -> eff != Effects::GET_BONUS) return 0;

    //Poner las frutas bien
    else {
        switch (this->f) {
        case Fruit::APPLE:
            return 100;

        case Fruit::BANNANA:
            return 200;

        case Fruit::CHERRY:
            return 300;

        default:
            return 400;
        }
    }
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const glm::vec2& pos)
{
    this->texProgram = shaderProgram;
    sizeQuad = glm::ivec2(20, 20);
    eff = Effects(rand() % SIZE_EFF);
    //eff = Effects::FREEZE;
    if (eff == Effects::GET_BONUS) loadFruit();
    else loadPowerUp();
    this->speed = glm::ivec2(0, 3*g);
    this->position = this -> initPos = pos;
    sprite->setPosition(pos);
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
}

void Object::loadFruit()
{
    spritesheet.loadFromFile("images/Fruit.png", TEXTURE_PIXEL_FORMAT_RGBA);
    this -> f = Fruit(rand() % 10);
    sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 5.0, 0.5), &spritesheet, &texProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, glm::vec2(f % 5 / 5.0, f / 5 * 0.5));
    sprite->changeAnimation(0);

}

void Object::loadPowerUp()
{
    spritesheet.loadFromFile("images/PowerUpsMin.png", TEXTURE_PIXEL_FORMAT_RGBA);
    unsigned int fr;
    switch (this->eff) {
    case Effects::GUN:
        fr = 12;
        break;
    case Effects::DOUBLE:
        fr = 6;
        break;
    case Effects::STICK:
        fr = 0;
        break;
    case Effects::DYNAMITE:
        fr = 7;
        break;
    case Effects::FREEZE:
        fr = 2;
        break;
    case Effects::SLOW:
        fr = 8;
        break;
    default:
        fr = 0;
    }
    sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 6.0, 1.0 / 3.0), &spritesheet, &texProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, glm::vec2(fr % 6 / 6.0, fr / 6 / 3.0));
    sprite->changeAnimation(0);
}
