#include "GUI.hpp"

RectButton::RectButton(const String& _label, const RectF& _rect)
	: rect(_rect)
	, label(_label)
	, transition(Transition(0.0s, 0.5s)) {}

//毎ループ呼び出して色の調整を行う
void RectButton::Update() {
	transition.update(rect.leftPressed());
}

//GUIを描く
//Updateのたびに呼び出す必要がある
//arg1:基本色 arg2:ボタンを押した時の色 arg3:外枠の色
void RectButton::Draw(const ColorF& colorBase, const ColorF& colorPressed, const ColorF& colorFrame) {
	const ColorF color = colorBase.lerp(colorPressed, transition.easeIn());

	rect.draw(color).drawFrame(1, 1, colorFrame);

	if (rect.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
}

const RectF& RectButton::GetRect() {
	return rect;
}

const String& RectButton::GetLabel() {
	return label;
}

InputField::InputField() {
	monsterAttribute = U"";
	monsterType = U"";
	isDone = false;
}

InputField::InputField(const RectF& _rect){
	monsterAttribute = U"";
	monsterType = U"";
	isDone = false;
	lotteryButton = RectButton(U"✅", _rect);
}

void InputField::Draw(const Vec2 pos) {
	SimpleGUI::TextBox(nameTes, pos, 200);
	
	if (monsterAttribute != U"") {
		dataFont(monsterAttribute).drawAt(pos + Vec2(280, 20), ColorF(0, 0, 0));
	}

	if (monsterType != U"") {
		dataFont(monsterType).drawAt(pos + Vec2(430, 20), ColorF(0, 0, 0));
	}
	
	lotteryButton.Update();
	lotteryButton.Draw();
	uiFont(lotteryButton.GetLabel()).drawAt(lotteryButton.GetRect().center(), ColorF(0.2, 0.4, 0.6));
}

void InputField::SetRect(const RectF& _rect){
	lotteryButton = RectButton(U"✅", _rect);
}

bool InputField::Clicked(bool isSameDischarge, Array<String>& monsterAttributes, Array<String>& monsterTypes){
	if (!isDone && lotteryButton.GetRect().leftClicked()) {
		int attributeNum = Random(monsterAttributes.size() - 1);
		int typeNum = Random(monsterTypes.size() - 1);

		monsterAttribute = monsterAttributes[attributeNum];
		monsterType = monsterTypes[typeNum];

		if (!isSameDischarge) {
			monsterAttributes.remove_if([monsterAttributes, attributeNum](String str) {return str == monsterAttributes[attributeNum]; });
			monsterTypes.remove_if([monsterTypes, typeNum](String str) {return str == monsterTypes[typeNum]; });
		}

		isDone = true;

		return true;
	}

	return false;
}

BackGround::BackGround(const Rect& _rect, const int& num): rect(_rect){
	for (int i = 0; i < num; i++) {
		Add();
	}
}

void BackGround::Draw(const ColorF& colorBase, const ColorF& colorFrame){
	rect.draw(colorBase).drawFrame(1, 1, colorFrame);
	
	uiFont(attributeText).drawAt(rect.pos + Vec2(330, 30), ColorF(0, 0, 0));
	uiFont(typeText).drawAt(rect.pos + Vec2(480, 30), ColorF(0, 0, 0));

	for (int i = 0; i < inputFields.size();i++) {
		uiFont(ToString(i + 1) + U".").drawAt(rect.pos + Vec2(30, 50 + 40 * (i + 1)), ColorF(0, 0, 0));
		inputFields[i].Draw(rect.pos + Vec2(55, 35 + 40 * (i + 1)));
	}
}

void BackGround::Add(){
	inputFields << InputField();
	inputFields.back().SetRect(RectF(600, 50 + 40 * inputFields.size(), 50, 30));
}

void BackGround::Delete(){
	inputFields.pop_back();
}

void BackGround::Reset() {
	inputFields.clear();
	Add();
}

