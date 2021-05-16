#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, M; // N : ¼¼·Î y , M : °¡·Î x
int passedTurns = 0;
string map[101][101];
string s_move;
pair<int, int>firstLocation;
pair<int, int>bossLocation;

struct monster {
	int x;
	int y;
	string name;
	int ATT;
	int DEF;
	int HP;
	int EXP;
	monster(int x, int y, string name, int ATT, int DEF, int HP, int EXP) {
		this->x = x;
		this->y = y;
		this->name = name;
		this->ATT = ATT;
		this->DEF = DEF;
		this->HP = HP;
		this->EXP = EXP;
	}
};
struct item {
	int x;
	int y;
	char T;
	int S;
	item(int x, int y, char T, int S) {
		this->x = x;
		this->y = y;
		this->T = T;
		this->S = S;
	}
};

vector<monster>v_monster;
vector<item>v_item;

struct hero {
	int x; int y;
	int LV;
	int REM_HP; int CUR_HP;
	int ATT; int W_ATT;
	int DEF; int A_DEF;
	int EXP; int MAX_EXP;
	bool accessory[7];
	hero(int x,int y) {
		this->x = x; this->y = y;
		this->LV = 1;
		this->REM_HP = 20; this->CUR_HP = 20;
		this->ATT = 2; this->W_ATT = 0;
		this->DEF = 2; this->A_DEF = 0;
		this->EXP = 0; this->MAX_EXP = 5;
		memset(accessory, false, sizeof(accessory));
	}
	void GainEXP(int exp) {
		if (accessory[3])
			EXP += exp * 1.2;
		else
			EXP += exp;

		if (EXP >= MAX_EXP) { 
			LV++;				// ·¹º§¾÷
			ATT += 2; DEF += 2;			
			EXP = 0; MAX_EXP = LV * 5;	
			CUR_HP += 5; REM_HP = CUR_HP;
		}
	}
	void GainItem(int X, int Y) {
		string tempItem = map[Y][X];
		int temp = 0;
		for (int i = 1; i < tempItem.length(); i++) {
			temp *= 10;
			temp += tempItem[i] - '0';
		}
		switch (v_item[temp].T) {
		case 'W': W_ATT = v_item[temp].S; break;
		case 'A': A_DEF = v_item[temp].S; break;
		case 'O':
			if (accessory[v_item[temp].S]) // ÀÌ¹Ì ÀåÂøÇÑ°æ¿ì
				break;
			int count = 0;
			for (int i = 0; i < 7; i++)
				if (accessory[i])
					count++;
			if (count >= 4) // 4°³ ÀÌ»ó ¾Ç¼¼¼­¸® ÀåÂøÁßÀÎ°æ¿ì
				break;
			int idx = v_item[temp].S;
			accessory[idx] = true;
		}
	}
	void FightMonster(int X, int Y) {
		string tempMonster = map[Y][X];
		int temp = 0;
		for (int i = 1; i < tempMonster.length(); i++) {
			temp *= 10;
			temp += tempMonster[i] - '0';
		}
		int HERO_HP = REM_HP;
		int HERO_ATT = ATT + W_ATT;
		int HERO_DEF = DEF + A_DEF;

		int MON_HP = v_monster[temp].HP;
		int MON_ATT = v_monster[temp].ATT;
		int MON_DEF = v_monster[temp].DEF;

		if (Y == bossLocation.first && X == bossLocation.second ) {
			if (accessory[5]) // HU ÀåÂø½Ã
				HERO_HP = CUR_HP;
		}
		for (int i = 0;; i++) {
			int DMG = HERO_ATT;
			if (i == 0 && accessory[2]) {	// CO ÀåÂø½Ã
				if (accessory[4])		// DX ÀåÂø½Ã
					DMG *= 3;
				else
					DMG *= 2;
			}
			MON_HP -= max(1,DMG - MON_DEF);
			if (MON_HP <= 0) {
				REM_HP = HERO_HP;
				if (accessory[0]) {
					REM_HP += 3;
					if(REM_HP > CUR_HP)
						REM_HP = CUR_HP;
				}
				GainEXP(v_monster[temp].EXP);
				map[Y][X] = ".";
				if (Y == bossLocation.first && X == bossLocation.second) {
					map[Y][X] = "@";
					GameOver("YOU WIN!");
				}
				return;
			}

			DMG = MON_ATT;
			if (i == 0 && accessory[5] && Y == bossLocation.first && X == bossLocation.second)
				continue;
		
			HERO_HP -= max(1,DMG-HERO_DEF);
			if (HERO_HP <= 0) {
				REM_HP = 0;
				if (Y == bossLocation.first && X == bossLocation.second)
					map[y][x] = "M";
				else
					map[y][x] = "&";
				GameOver("YOU HAVE BEEN KILLED BY " + v_monster[temp].name + "..");
				return;
			}
		}
	}
	void FallTrap() {
		if (accessory[4])
			REM_HP -= 1;
		else
			REM_HP -= 5;

		if (REM_HP <= 0) {
			REM_HP = 0;
			GameOver("YOU HAVE BEEN KILLED BY SPIKE TRAP..");
		}
	}
	void MoveHero(char dir) {
		passedTurns++;
		int temp_x = x;
		int temp_y = y;
		switch (dir) {
		case 'U': temp_y--; break;
		case 'R': temp_x++; break;
		case 'D': temp_y++; break;
		case 'L': temp_x--; break;
		}
		if (1 > temp_x || temp_x > M || 1 > temp_y || temp_y > N || map[temp_y][temp_x][0] == '#') {
			if (map[y][x] == "^")
				FallTrap();
			return;
		}
		x = temp_x;
		y = temp_y;
		if (map[y][x][0] == 'B') {
			GainItem(x, y);
			map[y][x] = ".";
		}
		else if (map[y][x][0] == '^')
			FallTrap();
		else if (map[y][x][0] == '&' || map[y][x][0]=='M')
			FightMonster(x, y);
		else if (map[y][x][0] == '.')
			return;
	}
	void GameOver(string overText) {
		if ( REM_HP == 0 && accessory[1]) {
			accessory[1] = false;
			REM_HP = CUR_HP;
			y = firstLocation.first;
			x = firstLocation.second;
			return;
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				cout << map[i][j][0];
			}
			cout << endl;
		}
		cout << "Passed Turns : " << passedTurns << endl;
		cout << "LV : " << LV << endl;
		cout << "HP : " << REM_HP << "/"<<CUR_HP << endl;
		cout << "ATT : " << ATT << "+"<<W_ATT << endl;
		cout << "DEF : " << DEF << "+"<<A_DEF << endl;
		cout << "EXP : " << EXP << "/"<<MAX_EXP << endl;
		cout << overText << endl;
		exit(0);
	}
};

int main()
{
	int monsterCount = 0;
	int itemCount = 0;
	cin >> N >> M;
	string input;
	for (int i = 1; i <= N; i++) {
		cin >> input;
		for (int j = 1; j <= M; j++) {
			map[i][j] = input[j - 1];
			if (map[i][j] == "@") {
				firstLocation.first = i;
				firstLocation.second = j;
				map[i][j] = ".";
			}
			else if (map[i][j] == "&")
				monsterCount++;
			else if (map[i][j] == "M") {
				monsterCount++;
				bossLocation.first = i;
				bossLocation.second = j;
			}
			else if (map[i][j] == "B")
				itemCount++;
		}
	}
	hero HERO(firstLocation.second, firstLocation.first);
	cin >> s_move;
	for (int i = 0; i < monsterCount; i++) {
		int x, y, W, A, H, E;
		string monsterName;
		cin >> y >> x >> monsterName >> W >> A >> H >> E;
		v_monster.push_back(monster(y,x,monsterName,W,A,H,E));
		map[y][x] += to_string(i);
	}
	for (int i = 0; i < itemCount; i++) {
		int y, x;
		char T;
		string S;
		cin >> y >> x >> T >> S;
		if (T == 'O') {
			if (S == "HR") v_item.push_back(item(y, x, T, 0));
			else if (S == "RE") v_item.push_back(item(y, x, T, 1));
			else if (S == "CO") v_item.push_back(item(y, x, T, 2));
			else if (S == "EX") v_item.push_back(item(y, x, T, 3));
			else if (S == "DX") v_item.push_back(item(y, x, T, 4));
			else if (S == "HU") v_item.push_back(item(y, x, T, 5));
			else if (S == "CU") v_item.push_back(item(y, x, T, 6));
		}
		else 
			v_item.push_back(item(y, x, T,stoi(S)));
		map[y][x] += to_string(i);
	}

	for (passedTurns = 0; passedTurns < s_move.length();) 
		HERO.MoveHero(s_move[passedTurns]);
	
	map[HERO.y][HERO.x] = "@";
	HERO.GameOver("Press any key to continue.");
	return 0;
}
/*
8 10
M&&&&&&&&&
&&&&&&&&&&
@BBBBBBBB^
..........
..........
..........
..........
..........
RRRRRRRRRRURRRRRRRRRRRRRRRRRRRULLLLLLLLLLLLLLLLLLL
1 1 100 10 10 1 10
1 2 100 10 10 1 10
1 3 107 10 10 1 10
1 4 164 10 10 1 10
1 5 145 10 10 1 10
1 6 154 10 10 1 10
1 7 176 10 10 1 10
1 8 156 10 10 1 10
1 9 138 10 10 1 10
1 10 ac 100 100 100 10
2 1 186 1 1 1 10
2 2 186 1 1 1 10
2 3 1 1 1 1 10
2 4 1 1 1 1 10
2 5 1 1 1 1 10
2 6 1 1 1 1 10
2 7 1 1 1 1 10
2 8 1 1 1 1 10
2 9 1 1 1 1 10
2 10 1 1 1 1 10
3 2 O CU
3 3 O RE
3 4 O CO
3 5 O EX
3 6 O DX
3 7 O HU
3 8 O CU
3 9 O CU
*/