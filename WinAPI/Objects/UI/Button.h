#pragma once

class Button : public ImageRect
{
protected:
    enum State
    {
        NORMAL, OVER, DOWN
    };

public:
    Button(wstring file);
    Button(Texture* texture);
    ~Button();

    void Update();
    void Render(HDC hdc);

    void SetFont(HFONT font, int fontSize = 20, COLORREF fontColor = BLACK);

    void SetEvent(Event event) { this->event = event; }
    void SetOverEvent(Event overevent) { this->overevent = overevent; }
    void SetDownEvent(Event downevent) { this->downevent = downevent; }

    void SetNormalTexture(Texture* texture) { normalTexture = texture; }
    void SetOverTexture(Texture* texture) { overTexture = texture; }
    void SetDownTexture(Texture* texture) { downTexture = texture; }

    void SetText(string text) { this->text = text; }

    void CreateAnimations();

protected:
    State state = NORMAL;

    bool isClick = false;
    bool isOver = false;

    Event event = nullptr;
    Event overevent = nullptr;
    Event downevent = nullptr;

    Texture* normalTexture = nullptr;
    Texture* overTexture = nullptr;
    Texture* downTexture = nullptr;

    string text;

    HFONT font = nullptr, oldFont = nullptr;
    int fontSize = 20;
    COLORREF fontColor = BLACK;
};