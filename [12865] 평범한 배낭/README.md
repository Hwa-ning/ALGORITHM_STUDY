# 12865. 평범한 배낭

[문제 링크](https://www.acmicpc.net/problem/12865)

## <풀이>

DP 문제 중에 기본인 배낭 문제
- 이중 for문을 돌리면서 최대 가치를 찾는다. i는 현재 넣고자 하는 물건의 번호, j는 현재 들 수 있는 무게를 의미한다.
- DP[i][j]는 무게 j까지 들 수 있을 때 물건 i번 까지를 이용한 최대 가치
- DP[i-1][j]는 물건 i를 넣지 않았을 때 최대 가치
- i번 물건을 넣었을 때와 넣지않았을 때의 가치를 비교하며 2차원 DP 배열을 완성해가며 최대 가치를 계산해나간다.

1. i는 현재 넣고자 하는 물건, j는 현재 넣을 수 있는 배낭의 무게로 이중 for문을 돌면서 확인한다.
2. 현재 넣으려고 하는 물건(i)의 무게와 arr_weight[i-1]이 들 수 있는 무게(j)를 비교한다.</br>
2-1. 들 수 없다면(물건 i가 j보다 무겁다면), i를 들지 않은 가치인 DP[i-1][j]가 현재 최댓값이 됨.</br>
2-2. 들 수 있다면 물건 i를 가방에 넣었을 때와 넣지 않았을 때의 가치를 비교한다. </br>
i번을 들고자 하면 (물건 i를 들지 않은 무게에서 최대 가치 + 물건 i의 가치)와 현재 까지 물건 i를 들지 않은 최대 가치를 비교한다.

![스크린샷 2022-06-01 오후 10 13 55](https://user-images.githubusercontent.com/69469529/171413212-6dba2fe1-5adf-4520-8946-46159d62fe3f.png)
<br>ex) DP[2][6] : 물건 2를 들었을 때 vs 물건 2를 들지 않았을 때 <br>
물건 2를 들었을 때 DP[ i-1 (2-1, 현재 들고자 하는 물건)] [ j (6,현재 들 수 있는 무게) - arr_weight[ i-1 (4, 물건 2의 무게) ] + arr_value[ i-1 (8, 물건 2의 가치) vs DP[1][6] (13, 물건 1까지 확인했을 때 무게 6일 때 최대 가치)
## <코드>
```JAVA
import java.io.IOException;
import java.util.Scanner;

public class Main{

   static int item_count;
   static int weight;

   static int[] arr_weight;
   static int[] arr_value;
   static int[][] DP;

   static void input() throws IOException {
      Scanner sc = new Scanner(System.in);

      item_count = sc.nextInt();
      weight = sc.nextInt();

      arr_weight = new int[item_count];
      arr_value = new int[item_count];
      DP = new int[item_count+1][weight+1];

      for(int i=0;i<item_count;i++){
         arr_weight[i] = sc.nextInt();
         arr_value[i] = sc.nextInt();
      }
   }

   static void solve(){
      for(int i=1; i <= item_count; i++){
         for(int j=1;j <= weight; j++){
            if(arr_weight[i-1] <= j){
               DP[i][j] = Math.max(DP[i-1][j-arr_weight[i-1]] + arr_value[i-1] ,DP[i-1][j]);
            }
            else{
               DP[i][j] = DP[i-1][j];
            }
         }
      }
   }
   public static void main(String[] args) throws IOException {
      input();
      solve();
      System.out.println(DP[item_count][weight]);
   }
}
```
