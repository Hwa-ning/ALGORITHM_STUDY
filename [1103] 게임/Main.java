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