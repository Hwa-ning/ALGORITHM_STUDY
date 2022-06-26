[2021-DevMatching:백엔드 상반기]
#3. 다단계 칫솔 판매

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/77486)

<br/>

### <풀이>
Map<String, Node> 을 이용해서 풀이 </br>
Node에는 현재의 이익인 profit과 추천인(부모)를 가리키는 parent를 둠.
1. enroll 배열로 Map에 판매원들을 집어넣고 넣음과 동시에 추천인(부모)를 가리키도록 한다.</br>
->문제에서 `즉, 어느 판매원의 이름이 enroll 의 i 번째에 등장한다면, 이 판매원을 조직에 참여시킨 사람의 이름, 즉 referral 의 i 번째 원소는 이미 배열 enroll 의 j 번째 (j < i) 에 등장했음이 보장됩니다.`로 인해 이 전에 항상 추천인(부모)가 등장하므로 문제 없음
2. seller 배열로 판매원을 map에서 찾고 setReward 함수를 통해 판매원들과 그 추천인들에게 재귀를 통해 이익을 분배한다.<br/>
3. 현재 금액에서 나누기 10을 하면서 현재 노드에 저장된 추천인(부모)에게 수익을 분배한다.</br>
->  소수점 계산에 유의
```JAVA
import java.util.*;

class Solution {

    static class Node{
        int profit = 0;
        Node parent = null;
    }

    static Map<String, Node> map = new HashMap<>();

    static void setReward(Node nowNode, int nowMoney){
        if(nowNode.parent == null || nowMoney < 10){
            nowNode.profit += nowMoney;
            return;
        }
        setReward(nowNode.parent, (int)(nowMoney/10.0));
        nowNode.profit+= nowMoney - (int)(nowMoney/10.0);
    }

    public int[] solution(String[] enroll, String[] referral, String[] seller, int[] amount) {
        int[] answer = new int[enroll.length];
        map.put("-",new Node());

        for(int i=0;i<enroll.length;i++){
            Node temp = new Node();
            Node parent = map.get(referral[i]);
            temp.parent = parent;
            map.put(enroll[i],temp);
        }

        for(int i=0;i<seller.length;i++){
            Node s = map.get(seller[i]);
            setReward(s,amount[i]*100);
        }

        for(int i=0;i<enroll.length;i++){
            answer[i] = map.get(enroll[i]).profit;
        }
        return answer;
    }
}
```
