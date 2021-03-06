//
// Created by dion on 16/12/2020.
//

#ifndef SFML_FRAMEWORK_CARD_H
#define SFML_FRAMEWORK_CARD_H
#include <SFML/Graphics.hpp>
#include "../Util/NonCopyable.h"
#include "../Util/Maths.h"
#include "../ResourceManager/ResourceManager.h"
#include <iostream>
class Card// : public NonCopyable
{
private:
    char kind;
    int value;
public:

    Card(char kind, int value,bool face);

    Card(const Card& other) = delete;
    Card& operator=(const Card& other) = delete;

    Card(Card&& other) noexcept = default;
    Card& operator=(Card&& other) noexcept = default;

    ~Card() = default;

    void setPosition(sf::Vector2f pos);
    void setPosition(float x,float y);
    void setTargetPosition(sf::Vector2f pos);
    void setTargetPosition(float x,float y);
    void setTargetRotation(float r);
    void setHighlight(bool state);
    void scale(float k);

    sf::Vector2f getPosition();
    sf::Vector2f getTargetPosition();
    void render(sf::RenderTarget& renderer);

    void updatePosition();
    void setRotation(float r);
    void rotate(float r);
    float getRotation();

    int getValue() const;
    char getKind() const;

    void setTexture(const sf::Texture& front_texture, const sf::Texture& back_texture, const sf::Texture& highlight_texture);

    void faceUp();
    void faceDown();
    bool isFaceUp();

    bool operator == ( const Card& b);
    void select();
    sf::FloatRect getGlobalBounds();
    float getTargetRotation();
private:
    //sprites
    sf::Sprite front_sprite,back_sprite,highlight_sprite;
    sf::Vector2f targetPosition;
    float target_rotation;
    float rotation;
    bool is_highlighted;
    bool is_selected;
    bool face_up;

};


#endif //SFML_FRAMEWORK_CARD_H
