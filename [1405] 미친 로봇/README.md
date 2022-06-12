# 1405 미친 로봇

## [문제 링크](https://www.acmicpc.net/problem/1405)

<br/>

### <풀이>

그냥 전형적인 DFS 문제, 처음에 아무생각없이 방문한 곳을 Set에 저장했는데 당연히 메모리 초과로 실패

```JAVA
import java.util.HashSet;
import java.util.Objects;
import java.util.Scanner;
import java.util.Set;

class Loc{
    int x;
    int y;
    Loc(int x, int y){
        this.x = x;
        this.y = y;
    }
}
public class Main{
    static int N;
    static double allPercent = 0.0;
    static boolean [][] visited = new boolean [30][30];
    static int [] percent = new int [4];
    static int [] dx = {0,0,1,-1};
    static int [] dy = {1,-1,0,0};
    static void input() {
        Scanner sc = new Scanner(System.in);

        N = sc.nextInt();

        for(int i=0;i<4;i++) {
            percent[i] = sc.nextInt();
        }
    }
    static void solve(int now, Loc nowLoc, double nowPercent){
        if(nowPercent == 0)
            return;

        if(now == N){
            allPercent += nowPercent;
            return;
        }
        for(int i=0;i<4;i++){
            if(percent[i] == 0){
                continue;
            }
            int next_x = nowLoc.x + dx[i];
            int next_y = nowLoc.y + dy[i];
            Loc nextLoc = new Loc(next_x, next_y);
            if(visited[next_y][next_x]){
                continue;
            }
            visited[next_y][next_x] = true;
            solve(now+1, nextLoc, nowPercent * percent[i] / 100 );
            visited[next_y][next_x] = false;
        }
    }
    public static void main(String[] args){
        input();
        visited[15][15] = true;
        solve(0, new Loc(15,15),1.0);
        System.out.println(allPercent);
    }
}
```
