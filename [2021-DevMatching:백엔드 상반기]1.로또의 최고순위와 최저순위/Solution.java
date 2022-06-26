import java.util.*;

class Solution {
    public int[] solution(int[] lottos, int[] win_nums) {
        int[] answer = new int[2];

        Set<Integer> set = new HashSet<Integer>();
        for(int num : win_nums){
            set.add(num);
        }

        for(int num : lottos){
            if(num == 0){
                answer[0]++;
            }
            else if(set.contains(num)){
                answer[0]++;
                answer[1]++;
            }
        }

        for(int i = 0 ; i < 2; i++){
            if(answer[i] == 0)
                answer[i] = 6;
            else{
                answer[i]= 7 - answer[i];
            }
        }
        return answer;
    }
}