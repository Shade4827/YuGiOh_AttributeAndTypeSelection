#pragma once
#include <Siv3D.hpp>

class RectButton {
private:
	RectF rect;
	String label;
	Transition transition;

public:
	RectButton() = default;
	RectButton(const String& _label, const RectF& _rect);
	void Update();
	void Draw(const ColorF& colorBase = ColorF(0.9, 0.92, 0.94), const ColorF& colorPressed = ColorF(1.0), const ColorF& colorFrame = ColorF(0.9, 0.92, 0.94));
	const RectF& GetRect();
	const String& GetLabel();
};

class InputField {
private:
	String monsterAttribute;
	String monsterType;
	const Font uiFont = Font(30);
	const Font dataFont = Font(30);
	TextEditState nameTes;
	RectButton lotteryButton;
	bool isDone;

public:
	InputField();
	InputField(const RectF& _rect);
	void Draw(const Vec2 pos);
	void SetRect(const RectF& _rect);
	bool Clicked(bool isSameLottery, Array<String>& monsterAttribute, Array<String>& monsterType);
};

class BackGround {
private:
	const Font uiFont = Font(30);
	RectF rect;
	const String attributeText = U"ëÆê´";
	const String typeText = U"éÌë∞";

public:
	Array<InputField> inputFields;
	BackGround() = default;
	BackGround(const Rect& _rect, const int& num);
	void Draw(const ColorF& colorBase = ColorF(0.9, 0.92, 0.94), const ColorF& colorFrame = ColorF(0.9, 0.92, 0.94));
	void Add();
	void Delete();
	void Reset();
};