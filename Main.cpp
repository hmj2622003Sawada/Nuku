#include "DxLib.h"
#include <stdlib.h>
#include "Mainheader.h"

// 定数の定義
const int WIDTH = 444, HEIGHT = 340; // 画面サイズ
const int FPS = 60; // フレームレート
enum{TITLE, RULE, PLAY, RESULT};



// グローバル変数
int distance = 0;
// int imgPlayer, imgCPU;
int imgBG;
int timer = 0;
int scene = TITLE;





int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("Nuku Game");	// ウィンドウのタイトル
	SetGraphMode(WIDTH, HEIGHT, 32);	// ウィンドウの大きさとカラー指定
	ChangeWindowMode(TRUE);	// ウィンドウモードで起動
	if (DxLib_Init() == -1) return -1;	// ライブラリの初期化、エラーが起きたら終了
	SetBackgroundColor(0, 0, 0);	// 背景色の指定
	SetDrawScreen(DX_SCREEN_BACK);	// 描画面を裏画面に

	InitGame(); // 初期化用の関数


	int imgPlayer[6] = {
	LoadGraph("image/run1.png"),
	LoadGraph("image/run2.png"),
	LoadGraph("image/run3.png"),
	LoadGraph("image/run4.png"),
	LoadGraph("image/run5.png"),
	LoadGraph("image/run6.png")
	};
	int PlayerX = 30, PlayerY = 75;

	/*int imgEnemy1[6] = {
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png")
	}*/

	/*int imgEnemy2[6] = {
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png")
	}*/

	/*int imgEnemy3[6] = {
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png"),
		LoadGraph("image/.png")
	}*/


	while (1) // メインループ
	{
		ClearDrawScreen(); // 画面をクリアにする

		
		if (PlayerX > WIDTH) PlayerX = -100;
		timer++;


		switch (scene)
		{
		case TITLE:
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.3, "Overtake Game", 0xffffff, 50);
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.75, "Press SPACE to Next.", 0xffffff, 20);
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				scene = RULE;
			}
			break;
		case RULE:
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.3, "スペースキーを連打すると速く走ります",0xffffff,15);
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.55, "スタミナがなくなると速度が遅くなります", 0xffffff,13);
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.7, "Press Enter to Start", 0xffffff,20);
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				scene = PLAY;
			}
			break;
		case PLAY:
			DrawGraph(0, 0, imgBG, FALSE);// 背景表示
			DrawGraph(PlayerX, PlayerY, imgPlayer[(timer / 7) % 6], TRUE);
			DrawParameter();
			


			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				scene = RESULT;
			}
			break;
		case RESULT:
			DrawTextC(WIDTH * 0.5, HEIGHT * 0.5, "１位", 0xffffff, 15);
			if (CheckHitKey(KEY_INPUT_5))
			{
				scene = TITLE;
			}
		}



		ScreenFlip();	// 裏画面の内容を表画面に反映
		WaitTimer(1000 / FPS);	// 一定時間待機
		if (ProcessMessage() == -1) break;	// エラーが起きたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;	// Escが押されたら終了
	}

	DxLib_End(); // DXライブラリの終了
	return 0;	// 終了
}


// 自作の関数

// 初期化用の関数
void InitGame(void)
{
	// 背景、画像の読み込み 
	imgBG = LoadGraphWithCheck("image/haikei.jpeg");
	// プレイヤーの画像
	
	// サウンドの読み込みと音量設定
//  bgm = LoadSoundMemWithCheck("sound/bgm.wav");

}

// 画像、音声の読み込み失敗通知
int LoadGraphWithCheck(const char* file)
{
	int res = LoadGraph(file);
	if (res == -1)
	{
		MessageBox(GetMainWindowHandle(), file, "画像読み込みに失敗", MB_OK | MB_ICONSTOP);
	}
	return res;
}

int LoadSoundMemWithCheck(const char* file)
{
	int res = LoadSoundMem(file);
	if (res == -1)
	{
		MessageBox(GetMainWindowHandle(), file, "音声の読み込みに失敗", MB_OK | MB_LEN_MAX);
		return res;
	}
}

void DrawTextC(int x, int y, const char* txt, int col, int siz)
{
	SetFontSize(siz);
	int strWidth = GetDrawStringWidth(txt, strlen(txt));
	x -= strWidth / 2;
	y -= siz / 2;
	DrawString(x + 1, y + 1, txt, 0x000000);
	DrawString(x, y, txt, col);
}

// スタミナ用のパラメーター
void DrawParameter(void)
{
	int stamina = 100;
	int x = 30, y = HEIGHT - 30; // 表示位置
	DrawBox(x, y, 400, y + 20, 0x000000, TRUE);
	for (int i = 0; i < stamina; i++)
	{
		int r = 255 - i; // RGB計算
		int g = i *2;
		int b = 0;
		DrawBox(x + 1 + i , y + 1, x + 270 + i , y + 19, GetColor(r, g, b), TRUE);
	}
}



// 背景のサイズH444×W340

/*
やることリスト
・順位の変動する機構
・スペースキーを連打して、スタミナを消費させる(スタミナが0になると連打しても動けなくする)機構
・敵画像の配置(3人)
・リザルト画面での順位とタイム発表の仕組み

優先度低め
・ゴール時、走っている最中、タイトル画面等で流すBGMを探す、流す

*/