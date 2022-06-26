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
```
