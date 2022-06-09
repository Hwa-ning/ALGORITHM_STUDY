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