# 1806 부분합

## [문제 링크](https://www.acmicpc.net/problem/1806)

<br/>

### <풀이>

두 포인터 left, right를 이용한 문제 처음부터 끝까지 순회하면 됨.
1. left ~ right까지의 합이 S보다 작은 경우
 - right를 오른쪽으로 한 칸 이동(현재 합계에 right 값을 더해줌)
2. 합이 S보다 큰 경우
 - 현재까지의 최소 길이와 지금 합이 S보다 큰 상황의 길이를 비교
 - left를 오른쪽으로 한 칸 이동(현재 합계에 left 값을 빼줌)

arr를 N+1 만큼 할당하여 while 문에서 index N인 경우, 해당하는 index가 0으로 초기화 되있으므로 0을 더하고 다음 while문 조건에서 종료되도록 함.
```JAVA
import java.util.Scanner;

public class Main{
    static int N;
    static int S;
    static int [] arr;
    static void input() {
        Scanner sc = new Scanner(System.in);

        N = sc.nextInt();
        S = sc.nextInt();

        arr = new int[N+1];
        for(int i=0;i<N;i++){
            arr[i] = sc.nextInt();
        }
    }
    static int solve() {
        int left = 0;
        int right = 0;
        int sum = arr[0];
        int result = N + 1;
        while( left <= right && right < N){
            if( sum < S){
                sum += arr[++right];
            }
            else{
                result = Math.min(result, right - left + 1);
                sum -= arr[left++];
            }
        }
        if(result == N +1)
            return 0;
        return result;
    }
    public static void main(String[] args){
        input();
        System.out.println(solve());
    }
}
```
