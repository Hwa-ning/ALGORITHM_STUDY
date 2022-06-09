# 16954. 움직이는 미로탈출

[문제 링크](https://www.acmicpc.net/problem/16954)

## <풀이>

전형적인 BFS 문제, 특이한 점이 있다면 방문한 곳에 대한 처리와 가만히 있는 경우가 존재한다는 것인 것 같다.

1. 현재 위치 x : 0, y : 7에서 시작 movingQueue에 add
2. 한 번 움직인 후에 벽이 움직여야하기 때문에 항상 현재 movingQueue의 size만큼만 BFS 진행
3. BFS 진행, 고려사항은 다음과 같음
- 현재 좌표가 벽인 경우
- 현재 좌표가 x : 7, y : 0인 경우 return 1
- 다음 좌표가 벽이거나 맵을 벗어나는 경우
- 이 때, <strong>visited(HashSet\<Loc\>)을 이용</strong>해서 현재 좌표와 현재 몇 칸 움직였는지를 기록해서 무한 반복되는 경우는 Queue에 넣지 않음 
4. moveWall() 벽을 한 칸씩 내려준다.
- 2~4 반복

## <주의>
- 방문한 곳에 대해 처리할 때, C++에서 사용하듯이 visited 2차원 배열의 HashSet을 사용하려고 했는데 Java에선 불가능함
- 사용하려고 한다면 ArrayList<>로 감싸면 사용 가능함.
- 오랜만에 푸는 코딩테스트 문젠데 BFS의 경우 x,y좌표에 항상 조심하자
## <코드>
```JAVA
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

class Loc {
    int x;
    int y;
    int now;
    Loc(int x, int y, int now){
        this.x = x;
        this.y = y;
        this.now = now;
    }
}
public class Main{
    static char [][] map = new char[8][8];
    static Set<Loc> visited = new HashSet<Loc>();
    static Queue<Loc> wallQueue = new ArrayDeque<>();
    static Queue<Loc> movingQueue = new ArrayDeque<>();

    static int [] dx = {0,0,0,1,1,1,-1,-1,-1};
    static int [] dy = {0,1,-1,0,1,-1,0,1,-1};

    static void input() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        for(int i=0;i<8;i++) {
            String input = br.readLine();
            for(int j=0;j<8;j++){
                map[i][j] = input.charAt(j);
                if(map[i][j] == '#'){
                    wallQueue.add(new Loc(j,i,0));
                }
            }
        }
    }
    static void moveWall(){
        for(int i=0;i<8;i++) {
            for (int j = 0; j < 8; j++) {
                map[i][j] = '.';
            }
        }
        int wallQueueSize = wallQueue.size();
        for(int i=0;i<wallQueueSize;i++){
            Loc wall = wallQueue.poll();
            if(wall.y >= 7){
                continue;
            }
            map[wall.y + 1][wall.x] = '#';
            wallQueue.add(new Loc(wall.x, wall.y+1, wall.now));
        }
    }
    static int solve(){
        Loc init = new Loc(0,7,0);
        movingQueue.add(init);
        visited.add(init);

        while(!movingQueue.isEmpty()) {
            int movingQueueSize = movingQueue.size();
            for (int i = 0; i < movingQueueSize; i++) {
                Loc nowLoc = movingQueue.poll();
                if (map[nowLoc.y][nowLoc.x] == '#') {
                    continue;
                }
                else if(nowLoc.x == 7 && nowLoc.y == 0){
                    return 1;
                }

                for(int j=0;j<9;j++) {
                    Loc nextLoc = new Loc(nowLoc.x + dx[j], nowLoc.y + dy[j], nowLoc.now + 1);
                    if (0 > nextLoc.x || nextLoc.x >= 8 || 0 > nextLoc.y || nextLoc.y >= 8 || visited.contains(nextLoc) || map[nextLoc.y][nextLoc.x] =='#') {
                        continue;
                    }
                    movingQueue.add(nextLoc);
                }
            }
            moveWall();
        }
        return 0;
    }
    public static void main(String[] args) throws Exception {
        input();
        System.out.println(solve());
    }
}
```
