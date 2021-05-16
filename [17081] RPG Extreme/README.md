# 17081. RPG Extreme

## 작성자 : Hwa-ning

## [문제 링크](https://www.acmicpc.net/problem/17081)

<br/>

풀어본 문제 중에 규모가 가장 컸던 구현 문제, 문제가 재밌어 보여서 덤볐는데 시간을 정말 많이 잡아먹었다. 단순히 코드를 구현하는데만 3시간 걸렸고 생각지 못한 버그들을 잡는데 한 2시간은 쓴 것 같다. 구조체로 멤버 변수와 멤버 함수로 구현하긴 했는데 마음에 들지않아서 나중에 시간이 남을때 좀 많이 다듬어야겠다.

### <풀이>

- vector\<item>과 vector\<monster>를 이용하여 아이템과 몬스터들의 정보를 저장해두는데 이를 빠르게 찾아주기 위해 map을 2차원 char가 아닌 2차원 string으로 선언했다.<br> 예를 들어 아이템이라면 vector에 넣어준 순서를 뒤에 붙여 13번째라면 "B13"과 같이 저장해뒀다.<br> (_나중에 고칠 것_ vector를 바로 찾아 사용하려고 생각했으나 전혀 효율적인 방법이 아닌 것 같다.)
  <br>
- MoveHero함수를 통해 주인공의 위치를 옮기고 도착한 칸에 해당하는 함수들을 실행 시켜주자.<br>
  \*\*\* 경계 밖을 벗어나거나 벽에 막혀 제자리인 경우 '^' 위치라면 FallTrap을 한 번 더 적용해야함 \*\*\*

1. 'B'인 경우 GetItem<br>
   무기나 방어구는 현재 장비의 공격력과 방어력과 상관없이 현재 획득한 장비로 무조건 바꿔줘야한다.<br>
   장신구의 경우는 이미 장착한 장신구의 경우 아무일도 생기지 않으며 이미 4개를 장착중이라면 새로운 장신구여도 장착 불가능하다.<br>
   장착 후 빈칸으로 바꿔야함!
2. '^'인 경우 FallTrap<br>
   현재 칸이 가시 함정인 경우 체력을 5 줄이고 장신구 DX를 착용중인 경우 체력을 1 줄이자.<br>
   가시 함정으로 체력이 0이하가 되는 경우 GameOver함수로 프로그램을 종료해주자.
3. '&'나 'M'인 경우 FightMonster<br>
   항상 선공을 하는 것을 잊지말고 장신구에 따른 추가적인 요소들을 꼼꼼히 확인하며 구현해야 함.<br>
   만약 방금 전투에서 승리한 몬스터가 'M'(보스)인 경우 게임을 승리했으므로 GetEXP를 통해 경험치를 획득하고 장신구 효과를 모두 적용한 후 GameOver함수로 프로그램을 종료.<br>
   전투에서 패배한다면 GameOver함수로 프로그램을 종료.<br>

- GameOver함수에서 체력이 0이 되어 죽은 경우 장신구 RE가 있다면 부활시켜줌.<br>
  게임을 승리하거나 끝이 나지 않은 경우에도 이 함수를 사용하여 프로그램을 종료하므로 체력을 꼭 확인해야 함.<br>
  \*\*\* RE가 있어 부활한다면 장신구 RE를 다시 없애줘야 함 \*\*\*

### <코드>

```C++
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int N, M;
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
	void GetEXP(int exp) {
		if (accessory[3])
			EXP += exp * 1.2;
		else
			EXP += exp;

		if (EXP >= MAX_EXP) {
			LV++;				// 레벨업
			ATT += 2; DEF += 2;
			EXP = 0; MAX_EXP = LV * 5;
			CUR_HP += 5; REM_HP = CUR_HP;
		}
	}
	void GetItem(int X, int Y) {
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
			if (accessory[v_item[temp].S]) // 이미 장착한경우
				break;
			int count = 0;
			for (int i = 0; i < 7; i++)
				if (accessory[i])
					count++;
			if (count >= 4) // 4개 이상 악세서리 장착중인경우
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
			if (accessory[5]) // HU 장착시
				HERO_HP = CUR_HP;
		}
		for (int i = 0;; i++) {
			int DMG = HERO_ATT;
			if (i == 0 && accessory[2]) {	// CO 장착시
				if (accessory[4])		// DX 장착시
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
				GetEXP(v_monster[temp].EXP);
				map[Y][X] = ".";
				if (Y == bossLocation.first && X == bossLocation.second) {
					map[Y][X] = "@";
					GameOver("YOU WIN!");
				}
				return;
			}

			if (i == 0 && accessory[5] && Y == bossLocation.first && X == bossLocation.second)
				continue;

			HERO_HP -= max(1,MON_ATT-HERO_DEF);
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
		accessory[4] ? REM_HP -= 1 : REM_HP -= 5;

		if (REM_HP <= 0) {
			REM_HP = 0;
			GameOver("YOU HAVE BEEN KILLED BY SPIKE TRAP..");
		}
	}
	void MoveHero(char dir) {
		passedTurns++;
		int next_x = x;
		int next_y = y;
		switch (dir) {
		case 'U': next_y--; break;
		case 'R': next_x++; break;
		case 'D': next_y++; break;
		case 'L': next_x--; break;
		}
		if (1 > next_x || next_x > M || 1 > next_y || next_y > N || map[next_y][next_x][0] == '#') {
			if (map[y][x] == "^")
				FallTrap();
			return;
		}
		x = next_x;
		y = next_y;
		if (map[y][x][0] == 'B') {
			GetItem(x, y);
			map[y][x] = ".";
		}
		else if (map[y][x][0] == '^') FallTrap();
		else if (map[y][x][0] == '&' || map[y][x][0]=='M') FightMonster(x, y);
	}
	void GameOver(string overText) {
		if ( REM_HP == 0 && accessory[1]) { // RE 부활
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
```
