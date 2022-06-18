# 1167 트리의지름

## [문제 링크](https://www.acmicpc.net/problem/1967)

<br/>

### <풀이>
[BOJ 1967](https://github.com/Hwa-ning/ALGORITHM_STUDY/tree/main/%5B1967%5D%20%ED%8A%B8%EB%A6%AC%EC%9D%98%20%EC%A7%80%EB%A6%84) 과 입력 외에 동일

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
      int dist;

      for(int i=0;i<N;i++) {
         parent = sc.nextInt();
         while (true) {
            child = sc.nextInt();
            if(child == -1)
               break;
            dist = sc.nextInt();
            nodes[parent].add(new Node(child,dist));
         }
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
