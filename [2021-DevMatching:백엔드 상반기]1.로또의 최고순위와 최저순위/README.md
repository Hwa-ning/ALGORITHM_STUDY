[2021-DevMatching:백엔드 상반기]
#1.로또의 최고순위와 최저순위

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/77484)

<br/>

### <풀이>
단순한 문제 Set을 이용해서 풀이</br>
1. lottos[]의 수가 0이면 최고 순위의 갯수에만 ++
2. 0이 아니고 win_nums[]에 포함되는 수라면 최고 순의 갯수와 최저 순위의 갯수에 ++ 
3. 그 이후 answer에 저장된 수를 이용한 계산 후 return
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
