# 5639. 이진 검색 트리

[문제 링크](https://www.acmicpc.net/problem/5639)

## <풀이>
이진검색트리 BST 문제</br>
문제에서 전위 순회의 결과가 입력으로 주어지기 때문에 들어온 순서이므로 순서대로 insert한 후, 후위 순회를 출력하면 끝

## <코드>
```JAVA
import java.io.BufferedReader;
import java.io.InputStreamReader;

class Node {
    int value;
    Node left = null;
    Node right = null;

    Node(int value){
        this.value = value;
    }
    void insert(int value){
        if( value < this.value){
            if(this.left == null){
                this.left = new Node(value);
            }
            else{
                this.left.insert(value);
            }
        }
        else{
            if(this.right == null){
                this.right = new Node(value);
            }
            else{
                this.right.insert(value);
            }
        }
    }
}
public class Main{
    static Node root;
    static void input() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        root = new Node(Integer.parseInt(br.readLine()));

        String input;
        while(true){
            input = br.readLine();
            if(input.isEmpty() || input == null)
                break;
            root.insert(Integer.parseInt(input));
        }
    }
    static void postOrder(Node node){
        if(node.left != null ) {
            postOrder(node.left);
        }
        if(node.right != null){
            postOrder(node.right);
        }
        System.out.println(node.value);
    }
    public static void main(String[] args) throws Exception {
        input();
        postOrder(root);
    }
}
```
