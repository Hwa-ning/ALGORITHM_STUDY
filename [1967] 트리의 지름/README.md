# 1967 트리의지름

## [문제 링크](https://www.acmicpc.net/problem/1967)

<br/>

### <풀이>
이진 트리가 아닌 그냥 트리에 관한 문제<br>
트리에서 노드와 노드 사이의 가중치 중 가장 긴 거리를 찾아야 하는데 처음 2차원 배열의 Node를 사용했을 때 메모리초과가 발생했다. 따라서 ArrayList의 배열을 이용해서 필요한만큼의 Node를 저장해주었음.

1. DFS를 이용해서 가장 긴 지름을 만들 수 있는 하나의 노드를 찾음<br>
 -> 지름 중 한 개의 노드를 찾음
2. 1.에서 나온 하나의 노드를 이용해서 DFS를 한 번더 진행해서 가장 긴 지름을 찾음. 
```JAVA
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
```
