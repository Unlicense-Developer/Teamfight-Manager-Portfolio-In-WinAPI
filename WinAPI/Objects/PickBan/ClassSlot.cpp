#include "Framework.h"

ClassSlot::ClassSlot(ClassData data)
	:Button(data.file), data(data)
{
	hfont_12 = CreateFont(12, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_18 = CreateFont(18, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_21 = CreateFont(21, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	hfont_24 = CreateFont(24, 0, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"Galmuri14 Regular");
	
	previewTexture = new ImageRect();
	skillTexture = new ImageRect();
	ultTexture = new ImageRect();

	Texture* texture = Texture::Add(this->data.previewtexture);
	previewTexture->SetTexture(texture);
	texture = Texture::Add(this->data.skilltexture);
	skillTexture->SetTexture(texture);
	texture = Texture::Add(this->data.ulttexture);
	ultTexture->SetTexture(texture);
}

ClassSlot::~ClassSlot()
{
	delete previewTexture;
}

void ClassSlot::Update()
{
	Button::Update();

}

void ClassSlot::Render(HDC hdc)
{
	Button::Render(hdc);
	ShowClassInfo(hdc);
	PrintPickOrder(hdc);
}

void ClassSlot::ShowClassInfo(HDC hdc)
{
	SelectObject(hdc, hfont_18);
	SetTextColor(hdc, WHITE);
	
	Vector2 textpos;

	if (data.jobname.size() == 4) // 이름 두글자
	{
		textpos = { pos.x - 12, pos.y + 27 };
	}
	else if (data.jobname.size() == 6) // 이름 세글자
	{
		textpos = { pos.x - 19, pos.y + 27 };
	}
	else if (data.jobname.size() == 8) // 이름 네글자
	{
		textpos = { pos.x - 25, pos.y + 27 };
	}

	TextOutA(hdc, textpos.x, textpos.y, data.jobname.c_str(), data.jobname.size());
}

void ClassSlot::PrintPickOrder(HDC hdc)
{
	SelectObject(hdc, hfont_24);

	if (isPicked)
		TextOutA(hdc, pos.x + 20, pos.y - 54, to_string(pickOrder).c_str(), to_string(pickOrder).size());
}

void ClassSlot::AddPlayer()
{
	if (isAdded)
		return;

	isAdded = true;
	Texture* bluetexture = Texture::Add(data.pick_bluetexture);
	SetNormalTexture(bluetexture);
	SetOverTexture(bluetexture);
	SetDownTexture(bluetexture);
	
}

void ClassSlot::AddComputer()
{
	if (isAdded)
		return;

	isAdded = true;
	Texture* redtexture = Texture::Add(data.pick_redtexture);
	SetNormalTexture(redtexture);
	SetOverTexture(redtexture);
	SetDownTexture(redtexture);
}

void ClassSlot::CheckBanEnd() // 밴이 되었는지 체크
{
	Audio::Get()->Play("Ban", 0.1f);
	isBaned = true;
	Texture* bantexture = Texture::Add(data.bantexture);
	SetNormalTexture(bantexture);
	SetOverTexture(bantexture);
	SetDownTexture(bantexture);
}

void ClassSlot::CheckPickEnd()
{
	Audio::Get()->Play("Pick", 0.2f);
	isPicked = true;
}
