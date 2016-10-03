#pragma once
#include <functional>

 class RenderWindow
 {
public:
    virtual void run(){}

    std::function<void()> fInit;
    std::function<void()> fDraw;
 };