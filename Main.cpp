#include "DxLib.h"
#include <stdlib.h>
#include "Mainheader.h"

// 定数の定義
const int WIDTH = 444, HEIGHT = 340; // 画面サイズ
const int FPS = 60; // フレームレート
enum{TITLE, RULE, PLAY, RESULT};



// グローバル変数
int distance = 0;

int imgBG;
int timer = 0;
int timer1 = 2;
int timer2 = 4;
int timer3 = 6;
int stimer = 0;
int mtimer = 0;
int scene = TITLE;
int rank = 4;
int timers = 0;
int timerm = 0;
int second = 0;
int minute = 0;
int spacepush = 0;
bool firstflag = false;
bool secondflag = false;
bool thirdflag = false;
bool fourthflag = true;
bool pushflag = false;

int E1X = 1000;
int E2X = 750;
int E3X = 500;

int KeyFrame[256];




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
	int PlayerX = 30, PlayerY = 115;

	int imgEnemy1[6] = {
		LoadGraph("image/runE11.png"),
		LoadGraph("image/runE12.png"),
		LoadGraph("image/runE13.png"),
		LoadGraph("image/runE14.png"),
		LoadGraph("image/runE15.png"),
		LoadGraph("image/runE16.png")
	};

	int imgEnemy2[6] = {
		LoadGraph("image/runE21.png"),
		LoadGraph("image/runE22.png"),
		LoadGraph("image/runE23.png"),
		LoadGraph("image/runE24.png"),
		LoadGraph("image/runE25.png"),
		LoadGraph("image/runE26.png")
	};

	int imgEnemy3[6] = {
		LoadGraph("image/runE31.png"),
		LoadGraph("image/runE32.png"),
		LoadGraph("image/runE33.png"),
		LoadGraph("image/runE34.png"),
		LoadGraph("image/runE35.png"),
		LoadGraph("image/runE36.png")
	};


	while (1) // メインループ
	{
		ClearDrawScreen(); // 画面をクリアにする

		
		if (PlayerX > WIDTH) PlayerX = -100;
		
		timer++;
		timer1++;
		timer2++;
		timer3++;
		

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
			timers = 0;
			timers++;
			timerm = 0;
			
			
			
			DrawGraph(0, 0, imgBG, FALSE);// 背景表示
			DrawGraph(E1X, 15 ,imgEnemy1[(timer1 / 7) % 6],TRUE);
			DrawGraph(E2X, 45 ,imgEnemy2[(timer2 / 7) % 6],TRUE);
			DrawGraph(E3X, 75 ,imgEnemy3[(timer3 / 7) % 6],TRUE);
			DrawGraph(PlayerX, PlayerY, imgPlayer[(timer / 7) % 6], TRUE);
			if (rank == 4 && fourthflag == true)
			{
				DrawTextC(20, 10,"4位", 0xffffff, 20);
			}
			if (rank == 3 && thirdflag == true)
			{
				DrawTextC(20,10,"3位", 0xB87333, 20);
			}
			if (rank == 2 && secondflag == true)
			{
				DrawTextC(20,10,"2位", 0xc0c0c0, 20);
			}
			if (rank == 1 && firstflag == true)
			{
				DrawTextC(20,10,"1位", 0xffd700, 20);
			}
			DrawParameter();
			
			if (PlayerX <= E3X)
			{
				fourthflag = true;
				thirdflag = false;
				rank = 4;
			}
			if (PlayerX >= E3X)
			{
				fourthflag = false;
				thirdflag = true;
				secondflag = false;
				rank = 3;
			}
			if (PlayerX >= E2X)
			{
				thirdflag = false;
				secondflag = true;
				firstflag = false;
				rank = 2;
			}
			if (PlayerX >= E1X)
			{
				secondflag = false;
				firstflag = true;
				rank = 1;
			}

			if (timers / 60 == 1)
			{
				second = second + 1;
				if (second == 60)
				{
					second = 0;
					minute = minute + 1;
				}
			}

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				E1X -= 1;
				E2X -= 1;
				E3X -= 1;
			}
			
			if (CheckHitKey(KEY_INPUT_SPACE) == 0)
			{
				spacepush++;
			}
			if (spacepush / 3 == 0)
			{
				E1X += 1;
				E2X += 1;
				E3X += 1;
			}

			if (CheckHitKey(KEY_INPUT_0))
			{
				scene = RESULT;
			}
			break;
		case RESULT:
			int x = 222;
			int y = 200;
			DrawText_C(WIDTH * 0.5, HEIGHT * 0.5, "%1d位",rank, 0xffffff, 15);
			DrawTimer();
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
	int staminabox = 0;
	int x = 20, y = HEIGHT - 30; // 表示位置
	DrawBox(x, y, 421, y + 20, 0x000000, TRUE);
	for (int i = 0; i < stamina; i++)
	{
		int r = 255 - i; // RGB計算
		int g = i *2;
		int b = 0;
		DrawBox(x + 1, y + 1, x + 300 + i, y + 19, GetColor(r, g, b), TRUE);
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		staminabox++;
		DrawBox(420, y, 420 - 4 *  staminabox, y + 20, GetColor(0, 0, 0), TRUE);
	}
	else
	{
		staminabox--;
	}

	if (staminabox >= 100)
	{
		staminabox == 100;
	}
	if (0 >= staminabox)
	{
		staminabox == 0;
	}


}

void DrawTimer(void)
{
	int x = 150;
	int y = HEIGHT - 140;
	DrawText_C(x,y,"TIME: %02d", minute, 0xffffff, 20);
	DrawText_C(x + 90, y, ":%02d", second, 0xffffff, 20);
}

void DrawText_C(int x, int y, const char* txt, int val, int col, int siz)
{
	SetFontSize(siz);
	DrawFormatString(x + 1, y + 1, 0xffffff, txt, val);
	DrawFormatString(x, y, col, txt, val);
}






// 背景のサイズH444×W340

/*
やることリスト
・スペースキーを連打して、スタミナを消費させる(スタミナが0になると連打しても動けなくする)機構
・リザルト画面での順位とタイム発表の仕組み

優先度低め
・ゴール時、走っている最中、タイトル画面等で流すBGMを探す、流す

*/