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