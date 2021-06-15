#include <iostream>
#include <string>

using namespace std;

struct Backup {
	int minoRow;
	int minoColumn;
	int theseusRow;
	int theseusColumn;
};

void maze_1(int mino[], int theseus[], int i, int xpos, int ypos);
void maze_2(int mino[], int theseus[], int i, int xpos, int ypos);
void maze_3(int mino[], int theseus[], int i, int xpos, int ypos);
void maze_4(int mino[], int theseus[], int i, int xpos, int ypos);
void maze_5(int mino[], int theseus[], int i, int xpos, int ypos);
bool promising(int mino[], int theseus[], int i);
bool moveMino_1(int mino[], int theseus[]);
bool moveMino_2(int mino[], int theseus[]);
bool moveMino_3(int mino[], int theseus[]);
bool moveMino_4(int mino[], int theseus[]);
bool moveMino_5(int mino[], int theseus[]);

string* str;
bool isMinoMove;
bool samePlace;
Backup* backup;
bool isPrint;

int upPos_1[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
	{0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0}, //2
	{0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0}, //3
	{0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0}, //4
	{0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0}, //5
	{0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0}, //6
	{0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0}, //7
	{0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int downPos_1[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0}, //1
	{0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0}, //2
	{0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0}, //3
	{0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0}, //4
	{0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0}, //5
	{0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0}, //6
	{0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0}, //7
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int leftPos_1[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0}, //1
	{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0}, //2
	{0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0}, //3
	{0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0}, //4
	{0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0}, //5
	{0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0}, //6
	{0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}, //7
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rightPos_1[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0}, //1
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0}, //2
	{0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0}, //3
	{0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0}, //4
	{0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0}, //5
	{0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0}, //6
	{0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, //7
	{0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int upPos_2[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, //1
	{0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //2
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //3
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //4
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}, //6
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //7
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int downPos_2[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //1
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //2
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //3
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //4
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //6
	{0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int leftPos_2[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //1
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //2
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //3
	{0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, //4
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0}, //5
	{0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0}, //6
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //7
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rightPos_2[10][11] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //1
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //2
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //3
	{0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0}, //4
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //5
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //6
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //7
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int upPos_3[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
	{0, 1, 1, 1, 1, 1, 0, 1, 0, 0}, //2
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //3
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //4
	{0, 1, 0, 1, 1, 1, 0, 1, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //6
	{0, 0, 1, 1, 1, 1, 1, 0, 1, 0}, //7
	{0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int downPos_3[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0, 1, 0, 0}, //1
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //2
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //3
	{0, 1, 0, 1, 1, 1, 0, 1, 1, 0}, //4
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //5
	{0, 0, 1, 1, 1, 1, 1, 0, 1, 0}, //6
	{0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int leftPos_3[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 0}, //1
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0}, //2
	{0, 0, 1, 1, 1, 1, 0, 1, 1, 0}, //3
	{0, 0, 1, 1, 1, 0, 1, 1, 1, 0}, //4
	{0, 0, 1, 1, 0, 1, 1, 1, 1, 0}, //5
	{0, 0, 0, 0, 1, 1, 1, 0, 1, 0}, //6
	{0, 0, 1, 0, 1, 0, 1, 1, 1, 0}, //7
	{0, 0, 1, 1, 1, 1, 0, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rightPos_3[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0}, //1
	{0, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //2
	{0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, //3
	{0, 1, 1, 1, 0, 1, 1, 1, 0, 0}, //4
	{0, 1, 1, 0, 1, 1, 1, 1, 0, 0}, //5
	{0, 0, 0, 1, 1, 1, 0, 1, 0, 0}, //6
	{0, 1, 0, 1, 0, 1, 1, 1, 0, 0}, //7
	{0, 1, 1, 1, 1, 0, 1, 1, 0, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int upPos_4[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}, //2
	{0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, //3
	{0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0}, //4
	{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //6
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //7
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //8
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int downPos_4[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0}, //1
	{0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0}, //2
	{0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0}, //3
	{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0}, //4
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //6
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //7
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int leftPos_4[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0}, //1
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0}, //2
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //3
	{0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0}, //4
	{0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, //5
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0}, //6
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, //7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, //8
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rightPos_4[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0}, //1
	{0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0}, //2
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //3
	{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0}, //4
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, //5
	{0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0}, //6
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, //7
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}, //8
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int upPos_5[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //1
	{0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0}, //2
	{0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0}, //3
	{0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0}, //4
	{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //5
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //6
	{0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //7
	{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0}, //8
	{0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int downPos_5[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0}, //1
	{0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0}, //2
	{0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0}, //3
	{0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0}, //4
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, //5
	{0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, //6
	{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0}, //7
	{0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0}, //8
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int leftPos_5[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0}, //1
	{0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, //2
	{0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0}, //3
	{0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0}, //4
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0}, //5
	{0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, //6
	{0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0}, //7
	{0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0}, //8
	{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int rightPos_5[11][16] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0}, //1
	{0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0}, //2
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0}, //3
	{0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, //4
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0}, //5
	{0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, //6
	{0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0}, //7
	{0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0}, //8
	{0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0}, //9
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int main() {
	int mino_1[] = { 3, 3 };
	int theseus_1[] = { 1, 1 };

	int mino_2[] = { 1, 1 };
	int theseus_2[] = { 1, 9 };

	int mino_3[] = { 1, 1 };
	int theseus_3[] = { 2, 2 };

	int mino_4[] = { 5, 14 };
	int theseus_4[] = { 5, 1 };

	int mino_5[] = { 4, 7 };
	int theseus_5[] = { 6, 13 };

	str = new string[1000];
	for (int i = 0; i < 1000; i++)
		str[i] = "";


	//1번에 해당하는 부분
	backup = new Backup[1000];
	samePlace = false;
	int i = 0;
	isMinoMove = true;
	isPrint = false;

	cout << "Puzzle1" << endl;
	maze_1(mino_1, theseus_1, i, 9, 2);



	//2번에 해당하는 부분
	i = 0;
	samePlace = false;
	isMinoMove = true;
	isPrint = false;
	backup = new Backup[1000];
	for (int i = 0; i < 1000; i++)
		str[i] = "";

	cout << "Puzzle2" << endl;
	maze_2(mino_2, theseus_2, i, 0, 4);



	//3번에 해당하는 부분
	i = 0;
	samePlace = false;
	isMinoMove = true;
	isPrint = false;
	backup = new Backup[1000];
	for (int i = 0; i < 1000; i++)
		str[i] = "";

	cout << "Puzzle3" << endl;
	maze_3(mino_3, theseus_3, i, 1, 0);



	//4번에 하당하는 부분
	i = 0;
	samePlace = false;
	isMinoMove = true;
	isPrint = false;
	backup = new Backup[1000];
	for (int i = 0; i < 1000; i++)
		str[i] = "";

	cout << "Puzzle4" << endl;
	maze_4(mino_4, theseus_4, i, 2, 15);



	//5번에 해당하는 부분
	i = 0;
	samePlace = false;
	isMinoMove = true;
	isPrint = false;
	backup = new Backup[1000];
	for (int i = 0; i < 1000; i++)
		str[i] = "";

	cout << "Puzzle5" << endl;
	maze_5(mino_5, theseus_5, i, 6, 15);

	return 0;
}

void maze_1(int mino[], int theseus[], int i, int xpos, int ypos) {
	if (promising(mino, theseus, i)) {
		if (theseus[0] == xpos && theseus[1] == ypos) {
			for (int k = 0; k < i; k++) {
				if (str[k] == "") {
					cout << endl;
					break;
				}
				cout << str[k];
			}
			cout << endl;
			isPrint = true;
			return;
		}
		else {
			backup[i].minoRow = mino[0];
			backup[i].minoColumn = mino[1];
			backup[i].theseusRow = theseus[0];
			backup[i].theseusColumn = theseus[1];

			for (int d = 1; d <= 5; d++) {
				if (d == 1) {
					if (leftPos_1[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]--;
						str[i] = "L";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_1(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 2) {
					if (rightPos_1[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]++;
						str[i] = "R";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_1(mino, theseus);
					}
					else continue;
				}
				else if (d == 3) {
					if (upPos_1[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]--;
						str[i] = "U";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_1(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 4) {
					if (downPos_1[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]++;
						str[i] = "D";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_1(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 5) {
					mino[0] = backup[i].minoRow;
					mino[1] = backup[i].minoColumn;
					theseus[0] = backup[i].theseusRow;
					theseus[1] = backup[i].theseusColumn;
					str[i] = "S";
					moveMino_1(mino, theseus);

				}
				if (isPrint)
					return;
				maze_1(mino, theseus, i + 1, xpos, ypos);
			}
		}
	}
}

void maze_2(int mino[], int theseus[], int i, int xpos, int ypos) {
	if (promising(mino, theseus, i)) {
		if (theseus[0] == xpos && theseus[1] == ypos) {
			for (int k = 0; k < i; k++) {
				if (str[k] == "") {
					cout << endl;
					break;
				}
				cout << str[k];
			}
			cout << endl;
			isPrint = true;
			return;
		}
		else {
			backup[i].minoRow = mino[0];
			backup[i].minoColumn = mino[1];
			backup[i].theseusRow = theseus[0];
			backup[i].theseusColumn = theseus[1];

			for (int d = 1; d <= 5; d++) {
				if (d == 1) {
					if (leftPos_2[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]--;
						str[i] = "L";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_2(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 2) {
					if (rightPos_2[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]++;
						str[i] = "R";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_2(mino, theseus);
					}
					else continue;
				}
				else if (d == 3) {
					if (upPos_2[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]--;
						str[i] = "U";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_2(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 4) {
					if (downPos_2[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]++;
						str[i] = "D";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_2(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 5) {
					mino[0] = backup[i].minoRow;
					mino[1] = backup[i].minoColumn;
					theseus[0] = backup[i].theseusRow;
					theseus[1] = backup[i].theseusColumn;
					str[i] = "S";
					moveMino_2(mino, theseus);

				}
				if (isPrint)
					return;
				maze_2(mino, theseus, i + 1, xpos, ypos);
			}
		}
	}
}

void maze_3(int mino[], int theseus[], int i, int xpos, int ypos) {
	if (promising(mino, theseus, i)) {
		if (theseus[0] == xpos && theseus[1] == ypos) {
			for (int k = 0; k < i; k++) {
				if (str[k] == "") {
					cout << endl;
					break;
				}
				cout << str[k];
			}
			cout << endl;
			isPrint = true;
			return;
		}
		else {
			backup[i].minoRow = mino[0];
			backup[i].minoColumn = mino[1];
			backup[i].theseusRow = theseus[0];
			backup[i].theseusColumn = theseus[1];

			for (int d = 1; d <= 5; d++) {
				if (d == 1) {
					if (leftPos_3[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]--;
						str[i] = "L";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_3(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 2) {
					if (rightPos_3[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]++;
						str[i] = "R";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_3(mino, theseus);
					}
					else continue;
				}
				else if (d == 3) {
					if (upPos_3[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]--;
						str[i] = "U";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_3(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 4) {
					if (downPos_3[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]++;
						str[i] = "D";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_3(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 5) {
					mino[0] = backup[i].minoRow;
					mino[1] = backup[i].minoColumn;
					theseus[0] = backup[i].theseusRow;
					theseus[1] = backup[i].theseusColumn;
					str[i] = "S";
					moveMino_3(mino, theseus);

				}
				if (isPrint)
					return;
				maze_3(mino, theseus, i + 1, xpos, ypos);
			}
		}
	}
}

void maze_4(int mino[], int theseus[], int i, int xpos, int ypos) {
	if (promising(mino, theseus, i)) {
		if (theseus[0] == xpos && theseus[1] == ypos) {
			for (int k = 0; k < i; k++) {
				if (str[k] == "") {
					cout << endl;
					break;
				}
				cout << str[k];
			}
			cout << endl;
			isPrint = true;
			return;
		}
		else {
			backup[i].minoRow = mino[0];
			backup[i].minoColumn = mino[1];
			backup[i].theseusRow = theseus[0];
			backup[i].theseusColumn = theseus[1];

			for (int d = 1; d <= 5; d++) {
				if (d == 1) {
					if (leftPos_4[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]--;
						str[i] = "L";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_4(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 2) {
					if (rightPos_4[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]++;
						str[i] = "R";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_4(mino, theseus);
					}
					else continue;
				}
				else if (d == 3) {
					if (upPos_4[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]--;
						str[i] = "U";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_4(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 4) {
					if (downPos_4[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]++;
						str[i] = "D";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_4(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 5) {
					mino[0] = backup[i].minoRow;
					mino[1] = backup[i].minoColumn;
					theseus[0] = backup[i].theseusRow;
					theseus[1] = backup[i].theseusColumn;
					str[i] = "S";
					moveMino_4(mino, theseus);

				}
				if (isPrint)
					return;
				maze_4(mino, theseus, i + 1, xpos, ypos);
			}
		}
	}
}

void maze_5(int mino[], int theseus[], int i, int xpos, int ypos) {
	if (promising(mino, theseus, i)) {
		if (theseus[0] == xpos && theseus[1] == ypos) {
			for (int k = 0; k < i; k++) {
				if (str[k] == "") {
					cout << endl;
					break;
				}
				cout << str[k];
			}
			cout << endl;
			isPrint = true;
			return;
		}
		else {
			backup[i].minoRow = mino[0];
			backup[i].minoColumn = mino[1];
			backup[i].theseusRow = theseus[0];
			backup[i].theseusColumn = theseus[1];

			for (int d = 1; d <= 5; d++) {
				if (d == 1) {
					if (leftPos_5[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]--;
						str[i] = "L";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_5(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 2) {
					if (rightPos_5[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[1]++;
						str[i] = "R";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_5(mino, theseus);
					}
					else continue;
				}
				else if (d == 3) {
					if (upPos_5[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]--;
						str[i] = "U";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_5(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 4) {
					if (downPos_5[backup[i].theseusRow][backup[i].theseusColumn]) {
						mino[0] = backup[i].minoRow;
						mino[1] = backup[i].minoColumn;
						theseus[0] = backup[i].theseusRow;
						theseus[1] = backup[i].theseusColumn;
						theseus[0]++;
						str[i] = "D";
						if (theseus[0] == xpos && theseus[1] == ypos) {
							for (int k = 0; k < i + 1; k++) {
								if (str[k] == "") {
									cout << endl;
									break;
								}
								cout << str[k];
							}
							cout << endl;
							isPrint = true;
							return;
						}
						moveMino_5(mino, theseus);
					}
					else
						continue;
				}
				else if (d == 5) {
					mino[0] = backup[i].minoRow;
					mino[1] = backup[i].minoColumn;
					theseus[0] = backup[i].theseusRow;
					theseus[1] = backup[i].theseusColumn;
					str[i] = "S";
					moveMino_5(mino, theseus);

				}
				if (isPrint)
					return;
				maze_5(mino, theseus, i + 1, xpos, ypos);
			}
		}
	}
}

bool promising(int mino[], int theseus[], int i) {
	if (!isMinoMove && str[i - 1] == "S") {
		isMinoMove = true;
		return false;
	}

	if (i == 0) {
		return true;
	}

	if (samePlace) {
		samePlace = false;
		return false;
	}


	for (int m = 1; m <= (i / 2); m++) {
		if (backup[i - (2 * m)].minoRow == mino[0] && backup[i - (2 * m)].minoColumn == mino[1] && 
			backup[i - (2 * m)].theseusRow == theseus[0] && backup[i - (2 * m)].theseusColumn == theseus[1]) {
			return false;
		}
	}

	return true;
}

bool moveMino_1(int mino[], int theseus[]) {
	if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
		samePlace = true;
		return false;
	}

	int rowDiffer = mino[0] - theseus[0]; //0보다 크면 left, 작으면 right
	int colDiffer = mino[1] - theseus[1]; //0보다 크면 mino 아래로, 작으면 위로

	int k = 2;

	int num = 0;

	while (k != 0) {
		if (colDiffer > 0 && leftPos_1[mino[0]][mino[1]] == 1) {
			mino[1]--;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (colDiffer < 0 && rightPos_1[mino[0]][mino[1]] == 1) {
			mino[1]++;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
			}

			continue;
		}
		else if (rowDiffer < 0 && downPos_1[mino[0]][mino[1]] == 1) {
			mino[0]++;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (rowDiffer > 0 && upPos_1[mino[0]][mino[1]] == 1) {
			mino[0]--;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		k--;
		num++;
	}

	if (num == 2)
		isMinoMove = false;
	else
		isMinoMove = true;

	return true;
}

bool moveMino_2(int mino[], int theseus[]) {
	if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
		samePlace = true;
		return false;
	}

	int rowDiffer = mino[0] - theseus[0]; //0보다 작으면 left, 크면 right
	int colDiffer = mino[1] - theseus[1]; //0보다 작으면 down, 크면 up

	int k = 2;

	int num = 0;

	while (k != 0) {
		if (colDiffer > 0 && leftPos_2[mino[0]][mino[1]] == 1) {
			mino[1]--;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (colDiffer < 0 && rightPos_2[mino[0]][mino[1]] == 1) {
			mino[1]++;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
			}

			continue;
		}
		else if (rowDiffer < 0 && downPos_2[mino[0]][mino[1]] == 1) {
			mino[0]++;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (rowDiffer > 0 && upPos_2[mino[0]][mino[1]] == 1) {
			mino[0]--;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		k--;
		num++;
	}

	if (num == 2)
		isMinoMove = false;
	else
		isMinoMove = true;

	return true;
}

bool moveMino_3(int mino[], int theseus[]) {
	if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
		samePlace = true;
		return false;
	}

	int rowDiffer = mino[0] - theseus[0]; //0보다 작으면 left, 크면 right
	int colDiffer = mino[1] - theseus[1]; //0보다 작으면 down, 크면 up

	int k = 2;

	int num = 0;

	while (k != 0) {
		if (colDiffer > 0 && leftPos_3[mino[0]][mino[1]] == 1) {
			mino[1]--;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (colDiffer < 0 && rightPos_3[mino[0]][mino[1]] == 1) {
			mino[1]++;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
			}

			continue;
		}
		else if (rowDiffer < 0 && downPos_3[mino[0]][mino[1]] == 1) {
			mino[0]++;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}


			continue;
		}
		else if (rowDiffer > 0 && upPos_3[mino[0]][mino[1]] == 1) {
			mino[0]--;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		k--;
		num++;
	}

	if (num == 2)
		isMinoMove = false;
	else
		isMinoMove = true;

	return true;
}

bool moveMino_4(int mino[], int theseus[]) {
	if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
		samePlace = true;
		return false;
	}

	int rowDiffer = mino[0] - theseus[0]; //0보다 작으면 left, 크면 right
	int colDiffer = mino[1] - theseus[1]; //0보다 작으면 down, 크면 up

	int k = 2;

	int num = 0;

	while (k != 0) {
		if (colDiffer > 0 && leftPos_4[mino[0]][mino[1]] == 1) {
			mino[1]--;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (colDiffer < 0 && rightPos_4[mino[0]][mino[1]] == 1) {
			mino[1]++;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
			}

			continue;
		}
		else if (rowDiffer < 0 && downPos_4[mino[0]][mino[1]] == 1) {
			mino[0]++;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (rowDiffer > 0 && upPos_4[mino[0]][mino[1]] == 1) {
			mino[0]--;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		k--;
		num++;
	}

	if (num == 2)
		isMinoMove = false;
	else
		isMinoMove = true;

	return true;
}

bool moveMino_5(int mino[], int theseus[]) {
	if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
		samePlace = true;
		return false;
	}

	int rowDiffer = mino[0] - theseus[0]; //0보다 작으면 left, 크면 right
	int colDiffer = mino[1] - theseus[1]; //0보다 작으면 down, 크면 up

	int k = 2;

	int num = 0;

	while (k != 0) {
		if (colDiffer > 0 && leftPos_5[mino[0]][mino[1]] == 1) {
			mino[1]--;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (colDiffer < 0 && rightPos_5[mino[0]][mino[1]] == 1) {
			mino[1]++;
			k--;
			colDiffer = mino[1] - theseus[1];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
			}

			continue;
		}
		else if (rowDiffer < 0 && downPos_5[mino[0]][mino[1]] == 1) {
			mino[0]++;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		else if (rowDiffer > 0 && upPos_5[mino[0]][mino[1]] == 1) {
			mino[0]--;
			k--;
			rowDiffer = mino[0] - theseus[0];

			if (mino[0] == theseus[0] && mino[1] == theseus[1]) {
				samePlace = true;
				return false;
			}

			continue;
		}
		k--;
		num++;
	}

	if (num == 2)
		isMinoMove = false;
	else
		isMinoMove = true;

	return true;
}