# 很懶惰的題解

1. 把左右兩邊分成 pair 和 distinct, 然後做一些greedy
2. 能把 distinct 先消掉就先消掉
3. 先消左右兩邊的 Distinct
4. 再來拿左邊的Pair消右邊的distinct
5. 再來拿右邊的Pair消左邊的distinct
6. 最後Pair內部互消 distinct兩兩互消

靈感來自 @Yi Kuo
