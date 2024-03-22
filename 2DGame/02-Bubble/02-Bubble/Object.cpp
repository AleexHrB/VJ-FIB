#include "Object.h"

void Object::update(int deltaTime)
{
    sprite->update(deltaTime);
    if (position.y + t * speed.y  < 370) {
        t += deltaTime / 100.0;
        float x = position.x + t * speed.x;
        float y = position.y + t * speed.y;
        sprite->setPosition(glm::vec2(x,y));
    }
}

Effects Object::applyEffect()
{
    return f;
}

unsigned int Object::getBonus()
{
    return 0;
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Effects f, const glm::vec2& pos)
{
    this->texProgram = shaderProgram;
    sizeQuad = glm::ivec2(20, 20);
    if (f == Effects::GET_BONUS) loadFruit();
    else loadPowerUp();
    this->speed = glm::ivec2(0, 3*g);
    this->position = pos;
    sprite->setPosition(pos);
    this->f = f;
}

pair<glm::ivec2, glm::ivec2> Object::getHitbox()
{
    return {sizeQuad, glm::vec2(position.x + t * speed.x, position.y + t * speed.y)};
}

void Object::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
}

void Object::loadFruit()
{
    spritesheet.loadFromFile("images/Fruit.png", TEXTURE_PIXEL_FORMAT_RGBA);
    unsigned int fr = rand() % 10;
    sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 5.0, 0.5), &spritesheet, &texProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, glm::vec2(fr % 5 / 5.0, fr / 5 * 0.5));
    sprite->changeAnimation(0);

}

void Object::loadPowerUp()
{
    spritesheet.loadFromFile("images/powerup.png", TEXTURE_PIXEL_FORMAT_RGBA);
    unsigned int fr = rand() % 3;
    sprite = Sprite::createSprite(sizeQuad, glm::vec2(1.0 / 3.0, 1.0), &spritesheet, &texProgram);
    sprite->setNumberAnimations(1);
    sprite->setAnimationSpeed(0, 1);
    sprite->addKeyframe(0, glm::vec2(fr / 3.0, 0.0));
    sprite->changeAnimation(0);
}
