import java.util.*;

class Node {
    int idx;
    int dist;
    Node(int no, int dist){
        this.idx = no;
        this.dist = dist;
    }
}

public class Main{
    static ArrayList<Node>[] nodes;
    static int N;
    static int max_idx = 0;
    static int max = 0;
    static boolean visited[];
    static void input()  {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();

        nodes = new ArrayList[N+1];

        for(int i=0;i<N+1;i++){
            nodes[i] = new ArrayList<>();
        }

        int parent;
        int child;
        int length;
        for(int i=0;i<N-1;i++) {
            parent = sc.nextInt();
            child = sc.nextInt();
            length = sc.nextInt();

            nodes[parent].add(new Node(child,length));
            nodes[child].add(new Node(parent,length));
        }
    }
    static void solve(){
        visited = new boolean[N+1];
        visited[1] = true;
        dfs(1,0);

        visited = new boolean[N+1];
        visited[max_idx] = true;
        dfs(max_idx,0);
    }
    static void dfs(int now, int value) {
        if(value > max){
            max = value;
            max_idx = now;
        }
        for( Node n : nodes[now]){
            if(!visited[n.idx]){
                visited[n.idx] = true;
                dfs(n.idx, value + n.dist);
            }
        }
    }
    public static void main(String[] args) throws Exception {
        input();
        solve();
        System.out.println(max);
    }
}