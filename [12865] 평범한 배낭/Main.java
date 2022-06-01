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