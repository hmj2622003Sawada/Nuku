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