#include "Framework.h"

ProgressBar::ProgressBar(Texture* frontTexture, Texture* backTexture1, Texture* backTexture2)
    : fronttexture(frontTexture), backtexture1(backTexture1), backtexture2(backTexture2)
{
    size = frontTexture->GetSize();
    backsize1 = backTexture1->GetSize();
    backsize2 = backTexture2->GetSize();
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Render(HDC hdc)
{
    if (backtexture1)
        backtexture1->Render(hdc, this);

    GdiTransparentBlt( // HP
        hdc,
        (int)Left(), (int)Top() + 50,
        (int)(size.x * value), (int)size.y,
        fronttexture->GetMemDC(),
        0, 0, (int)(backsize1.x), (int)backsize1.y,
        MAGENTA
    );

    //if (backtexture2)
    //    backtexture2->Render(hdc, this);

    //GdiTransparentBlt( // ½ºÅ³
    //    hdc,
    //    (int)Left(), (int)Top() + 5,
    //    (int)(size.x * value), (int)size.y,
    //    fronttexture->GetMemDC(),
    //    0, 0, (int)(size.x * value), (int)size.y,
    //    MAGENTA
    //);
}
