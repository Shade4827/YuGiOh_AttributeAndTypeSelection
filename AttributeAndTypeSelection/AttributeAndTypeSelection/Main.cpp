#include <Siv3D.hpp> // OpenSiv3D v0.4.3
#include "GUI.hpp"

void Main(){
	// 背景を水色にする
	Scene::SetBackground(ColorF(1, 1, 1));
	Window::Resize(Size(800, 600));

	/*
	種族のデータと属性のデータを用意
	設定切替
	　同じものが出ないようにする(6人までの場合有効)
	人数を入力してその分フィールドを用意
	　名前、属性、種族のフィールド
	全体やり直しボタン
	フィールドの追加・削除ボタン
	スクロール機能
	*/

	const Array<String> ALL_ATTRIBUTES = { U"炎",U"水",U"風",U"地",U"光",U"闇" };
	const Array<String> ALL_TYPES = { U"ドラゴン族",U"魔法使い族",U"アンデット族",U"戦士族",U"獣戦士族",U"獣族",U"鳥獣族",U"悪魔族",U"天使族",U"昆虫族",U"恐竜族"
								,U"爬虫類族",U"魚族",U"海竜族",U"機械族",U"雷族",U"水族",U"炎族",U"岩石族",U"植物族",U"サイキック族",U"幻竜族",U"サイバース族" };
	
	Array<String> monsterAttributes = ALL_ATTRIBUTES;
	Array<String> monsterTypes = ALL_TYPES;

	bool isSameDischarge = true;
	bool isStarted = false;
	Font buttonFont(30);

	BackGround bg(Rect(10, 10, 780, 580), 1);
	RectButton plusButton(U"+", Rect(680, 200, 100, 60));
	RectButton resetButton(U"Reset", Rect(680, 300, 100, 60));

	while (System::Update()){
		bg.Draw(ColorF(1, 1, 1), ColorF(0, 0, 1));

		SimpleGUI::CheckBox(isSameDischarge, U"Same", Vec2(680, 100), unspecified, !isStarted);

		while (!isSameDischarge && bg.inputFields.size() > 6) {
			bg.Delete();
		}

		plusButton.Update();
		if (plusButton.GetRect().leftClicked()) {
			if (!(!isSameDischarge && bg.inputFields.size() >= 6)) {
				bg.Add();
			}
		}
		plusButton.Draw();
		buttonFont(plusButton.GetLabel()).drawAt(plusButton.GetRect().center(), ColorF(0.2, 0.4, 0.6));

		resetButton.Update();
		if (resetButton.GetRect().leftClicked()) {
			bg.Reset();
			monsterAttributes = ALL_ATTRIBUTES;
			monsterTypes = ALL_TYPES;
			isStarted = false;
		}
		resetButton.Draw();
		buttonFont(resetButton.GetLabel()).drawAt(resetButton.GetRect().center(), ColorF(0.2, 0.4, 0.6));

		for (int i = 0; i < bg.inputFields.size(); i++) {
			if (bg.inputFields[i].Clicked(isSameDischarge, monsterAttributes, monsterTypes)) {
				isStarted = true;
			}
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
