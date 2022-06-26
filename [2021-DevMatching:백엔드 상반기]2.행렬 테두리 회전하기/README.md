[2021-DevMatching:백엔드 상반기]
#2.행렬 테두리 회전하기

## [문제 링크](https://programmers.co.kr/learn/courses/30/lessons/77485)

<br/>

### <풀이>
단순한 구현 문제 2차원 배열에서 changer 변수로 직전 행렬에 있던 숫자를 저장해서 행렬을 밀면서 진행</br>
```JAVA
class Solution {
    public int[] solution(int rows, int columns, int[][] queries) {
        int[][] nums = new int[rows][columns];
        int[] result = new int[queries.length];

        int num = 1;
        for(int i=0 ; i<rows ; i++) {
            for(int j=0 ; j<columns ; j++) {
                nums[i][j] = num++;
            }
        }

        for(int i=0 ; i<queries.length ; i++) {
            int[] query = queries[i];

            int sx=query[0]-1;
            int sy=query[1]-1;

            int ex=query[2]-1;
            int ey=query[3]-1;

            int changer = nums[sx][sy];
            int min = changer;

            for(int x=sx+1 ; x<=ex ; x++) {
                min = Math.min(min, nums[x][sy]);
                nums[x-1][sy] = nums[x][sy];
            }

            for(int y=sy+1 ; y<=ey ; y++) {
                min = Math.min(min, nums[ex][y]);
                nums[ex][y-1] = nums[ex][y];
            }

            for(int x=ex-1 ; x>=sx ; x--) {
                min = Math.min(min, nums[x][ey]);
                nums[x+1][ey] = nums[x][ey];
            }

            for(int y=ey-1 ; y>sy ; y--) {
                min = Math.min(min, nums[sx][y]);
                nums[sx][y+1] = nums[sx][y];
            }
            nums[sx][sy+1] = changer;
            result[i] = min;
        }
        return result;
    }
}
```
