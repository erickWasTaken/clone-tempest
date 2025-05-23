#ifndef LEVELBOX_HPP
#define LEVELBOX_HPP

#include "UIElement.hpp"

class LevelBox : public UIElement{
private:
    u8 levelNum;

public:
    LevelBox(i32 x, i32 y, i32 w, i32 h) = delete;
    LevelBox(u8 level, i32 x, i32 y, i32 w, i32 h);
    ~LevelBox();
    
    void Update() override;
    void Render(SDL_Renderer* ren) const override;
    void Render(SDL_Renderer* ren, bool selected) const;
    
    inline void SetLevelNum(u8 level){ levelNum = level; };
    inline u8 GetLevelNum(){ return levelNum; };
};

#endif
