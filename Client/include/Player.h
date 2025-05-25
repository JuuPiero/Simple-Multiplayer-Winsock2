#pragma once
#include "GameObject.h"
#include <iostream>
#include "Math/Vector2.h"
#include "Color.h"
class Player : public JuuPiero::GameObject {
public:
    Player(int x, int y, int width, int height);
    Player() {}
    ~Player() = default;
    void Render() override;
    void Update(uint32_t deltaTime) override;
    void HandleInput(uint32_t deltaTime);
    void SetId(uint32_t id);

    inline uint32_t GetId() {
        return m_Id;
    }


public:
    Color color;
    
protected:
    uint32_t m_Id = 0;
    Vector2 m_Velocity;

};