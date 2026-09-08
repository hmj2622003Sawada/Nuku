#pragma once

// \‘¢‘Ì‚ÌéŒ¾
struct OBJECT
{

};

// ŠÖ”éŒ¾
void InitGame(void);
int LoadGraphWithCheck(const char* file);
int LoadSoundMemWithCheck(const char* file);
void DrawTextC(int x, int y, const char* txt, int col, int siz);
void DrawParameter(void);
void DrawTimer(void);
void DrawText_C(int x, int y, const char* txt, int val, int col, int siz);
void UpdateKey(void);