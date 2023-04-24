#pragma once

class ProgressBar : public Rect
{
public:
    ProgressBar(Texture* frontTexture, Texture* backTexture1 = nullptr, Texture* backTexture2 = nullptr);
    ~ProgressBar();

    void Render(HDC hdc);

    void SetValue(const float& value) { this->value = value; }

private:
    Texture* fronttexture;
    Texture* backtexture1;
    Texture* backtexture2;

    Vector2 backsize1;
    Vector2 backsize2;

    float value;
};