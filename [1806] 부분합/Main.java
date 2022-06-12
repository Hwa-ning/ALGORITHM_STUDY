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