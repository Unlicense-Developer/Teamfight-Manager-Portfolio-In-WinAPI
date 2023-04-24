#pragma once
class Waterfall : public ImageRect
{
public:
	Waterfall();
	~Waterfall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	Animation* animation;
};