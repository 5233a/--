# 排序算法分析（算法的优劣由占用空间与花费时间共同决定）

## 选择排序

### 分析

最贴近人类思想的排序方式。依次找到子列表中最符合条件的数据放在应该被放置的位置上。

### 优化

问题: 在通常情况下，若定义一个新的数组，则要花费两倍的内存空间。优化算法，仅采用一个列表。

方法：使用交换的方法，将被选中的合适的的数据与它应该被放置的位置上的数据进行交换。

代价: 仅需一个列表，但是也多占用了一个数据的空间，用来存放交换时的临时变量，且在时间上花费更多（每次进行交换都要进行两次赋值操作）。

### 伪代码实现

list = {Sue, Cora, Beth, Ann, June}

FOR i from 0 to list.length-2 DO

Find index of the smallest item in list[i..list.length-1]

IF index <> i THEN

list.swap (i, index)

END IF

END FOR list = {Sue, Cora, Beth, Ann, June}

FOR i from 0 to list.length-2 DO

index = i

FOR j from i+1 to list.length-1 DO

IF list[j] < list[index] THEN index=j

END FOR …

END FOR 
