#include "Framework.h"

Button::Button(wstring file)
    : ImageRect(file)
{
    normalTexture = texture;
}

Button::Button(Texture* texture)
    : ImageRect(texture), normalTexture(texture)
{
}

Button::~Button()
{
}

void Button::Update()
{
    if (!isActive) return;
    
    Vector2 normalSize = { size.x + 4, size.y + 3 };
    Vector2 overSize = { size.x + 4, size.y + 3 };

    if (IsCollision(mousePos))
    {
        state = OVER;

        if (overevent)
            overevent();

        if (KEY_UP(VK_LBUTTON) && isClick)
        {
            if (event)
                event();

            isClick = false;
        }

        if (KEY_DOWN(VK_LBUTTON))
        {
            isClick = true;
        }

        if (KEY_PRESS(VK_LBUTTON))
        {
            state = DOWN;

            if (downevent)
                downevent();
        }
    }
    else
    {
        state = NORMAL;

        if (KEY_UP(VK_LBUTTON))
            isClick = false;
    }

    switch (state)
    {
    case Button::NORMAL:
        texture = normalTexture;
        break;
    case Button::OVER:
        if(overTexture)
            texture = overTexture;
        break;
    case Button::DOWN:
        if(downTexture)
            texture = downTexture;
        break;
    default:
        break;
    }

}

void Button::Render(HDC hdc)
{
    ImageRect::Render(hdc);

    if (font)
    {
        oldFont = (HFONT)SelectObject(hdc, font);
    }

    COLORREF oldColor = SetTextColor(hdc, fontColor);

    RECT rect = { Left(), Top() + fontSize * 0.25f,
        Right(), Bottom() + fontSize * 0.25f };
    DrawTextA(hdc, text.c_str(), text.length(), &rect, DT_CENTER);

    if (font)
        SelectObject(hdc, oldFont);

    SetTextColor(hdc, oldColor);
}

void Button::SetFont(HFONT font, int fontSize, COLORREF fontColor)
{
    this->font = font;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
}

void Button::CreateAnimations()
{
}
