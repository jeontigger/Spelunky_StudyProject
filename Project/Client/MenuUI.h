#pragma once
#include "UI.h"


class MenuUI :
    public UI
{
public:
    virtual void render() override;
    virtual void render_update() override;

private:
    void File();
    void Window();
    void Level();
    void GameObject();
    void Asset();
    void Animation();
    void TileMaker();


public:
    MenuUI();
    ~MenuUI();
};

