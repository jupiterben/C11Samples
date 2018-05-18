#pragma once
#include <functional>

 class RenderWindow
 {
public:
    virtual void run(){}  

    std::function<void()> OnInit;
    std::function<void()> OnDraw;
    std::function<void(int,int)>  onSize;
	std::function<void()> OnDestroy;
 };