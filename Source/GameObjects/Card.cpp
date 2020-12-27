//
// Created by dion on 16/12/2020.
//

#include "Card.h"
Card::Card(char kind,int value, bool face)
:   is_highlighted(false),
    kind(kind),
    value(value),
    face_up(face)
{

}


void Card::render(sf::RenderTarget &renderer) {
    if(face_up)
        renderer.draw(front_sprite);
    else
        renderer.draw(back_sprite);

    if(is_highlighted)
        renderer.draw(highlight_sprite);
}
void Card::setPosition(float x, float y) {
    setPosition(sf::Vector2f(x,y));
}
void Card::setPosition(sf::Vector2f pos){
    front_sprite.setPosition(pos);
    back_sprite.setPosition(pos);
    highlight_sprite.setPosition(pos);
}
void Card::setHighlight(bool state){
    is_highlighted = state;
}
sf::Vector2f Card::getPosition(){
    return front_sprite.getPosition();
}

void Card::setTargetPosition(sf::Vector2f pos)
{
    targetPosition = pos;
}
void Card::setTargetPosition(float x, float y) {
    setTargetPosition(sf::Vector2f(x,y));
}
sf::Vector2f Card::getTargetPosition() {
    return targetPosition;
}

void Card::setRotation(float r)
{
    float rot = r*180/acosf(-1);
    front_sprite.setRotation(rot);
    back_sprite.setRotation(rot);
    highlight_sprite.setRotation(rot);
}
void Card::setTargetRotation(float r)
{
   target_rotation = r;
}
float Card::getRotation()
{
    return front_sprite.getRotation()*acosf(-1)/180;
}

int Card::getValue() const
{
    return value;
}
char Card::getKind() const
{
    return kind;
}

void Card::scale(float k){
    front_sprite.scale(k,k);
    back_sprite.scale(k,k);
    highlight_sprite.scale(k,k);
}

void Card::updatePosition()
{
    float e;
    const float k = 0.15;
    if((e=EuclideanDistance(getPosition(),targetPosition))>=0.000001)
    {
       setPosition(getPosition()+(targetPosition-getPosition())*k);
    }
    if((e=target_rotation-getRotation())>=0.00001)
    {
       setRotation(getRotation()+e*k);
    }


//    std::cout<<"error "<<e<<" x "<<getPosition().x<<std::endl;
}
void Card::setTexture(const sf::Texture &front_texture, const sf::Texture &back_texture,
                      const sf::Texture &highlight_texture) {
    front_sprite.setTexture(front_texture);
    back_sprite.setTexture(back_texture);
    highlight_sprite.setTexture(highlight_texture);
}

void Card::faceUp()
{
    face_up = true;
}
void Card::faceDown()
{
    face_up = false;
}
sf::FloatRect Card::getGlobalBounds()
{
   if(face_up)
       return front_sprite.getGlobalBounds();
   else
       return back_sprite.getGlobalBounds();
}

bool Card::operator==(const Card& b)
{
   return (b.getKind()==kind)&&(b.getValue()==value);
}

bool Card::isFaceUp()
{
    return face_up;
}