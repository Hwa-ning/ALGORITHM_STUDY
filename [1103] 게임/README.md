# 1103. 게임

[문제 링크](https://www.acmicpc.net/problem/1103)

## <풀이>

전형적인 DFS + DP 문제, 문제에서 H로 빠지거나 맵 밖을 나가게 된다면 게임이 종료된다. DP 2차원 배열과 visited 2차원 배열로 방문여부를 확인하면서 풀이하면 된다.

- visited[][]는 현재의 싸이클을 확인하기 위해 사용
- DP[][]는 현재 (x,y) 좌표에서 움직일 수 있는 최대 칸을 확인하기 위해 사용

1. DFS 재귀로 4방향중 한 방향으로 이동시킨다. 
2. 당연하게 범위를 초과하거나 구멍(H)인 경우 DFS를 진행하지 않는다.
3. 이동하면서 visited 2차원 배열을 통해 방문을 기록, 방문했던적이 있는 곳이라면 무한히 반복할 수 있으므로 -1을 출력하고 종료한다.
4. 이동하면서 DP가 -1이면 한 번도 방문한 적이 없으므로 DFS를 진행하여 해당 좌표의 움직일 수 있는 횟수를 연산한다.<br>
4-1. -1이 아닌데 visited가 true라면 싸이클이 생기므로 -1을 출력하고 종료한다.<br>
4-2. visited가 false라면 싸이클이 생기지않고 DP배열에 그 칸의 이동 가능한 횟수가 저장되어있으므로 해당 칸의 이동 횟수를 return 

### <코드>

```JAVA
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main{
   static int height;
   static int width;

   static int[] dx = {0,0,-1,1};
   static int[] dy = {1,-1,0,0};
   static int[][] DP;
   static char[][] map;
   static boolean[][] visited;
   static void input() throws IOException {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

      String [] input = br.readLine().split(" ");

      height = Integer.parseInt(input[0]);
      width = Integer.parseInt(input[1]);

      DP = new int[height][width];
      map = new char[height][width];
      visited = new boolean[height][width];

      for(int i=0; i<height;i++) {
         String temp = br.readLine();
         for(int j=0; j<temp.length();j++){
            map[i][j] = temp.charAt(j);
            DP[i][j] = -1;
         }
      }
   }

   static int dfs(int y, int x)
   {
      if (DP[y][x] == -1) {
         DP[y][x] = 0;
         visited[y][x] = true;

         for (int i = 0; i < 4; i++) {
            char temp = map[y][x];
            if (temp == 'H') {
               break;
            }
            int now = (temp - '0');
            int ny = y + now * dy[i];
            int nx = x + now * dx[i];

            if (0 > ny || ny >= height || 0 > nx || nx >= width || map[ny][nx] == 'H') {
               continue;
            }
            DP[y][x] = Math.max(DP[y][x], dfs(ny, nx) + 1);
         }
         visited[y][x] = false;
      }
      else {
         if(visited[y][x]) {
            System.out.println(-1);
            System.exit(0);
         }
      }
      return DP[y][x];
   }
   public static void main(String[] args) throws Exception {
      input();
      int result = dfs(0,0) + 1;
      System.out.println(result);
   }
}
```
