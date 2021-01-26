# SCC-2021 Day2 HW-Report
Author: Lawrence Wu, 109062328

# Original v.s. std::multiset
According to the experiment, the differences between the original Red Black Tree and the implementation of Red Black Tree from Cplusplus standard library is not significant. The amount of instruction from std::multiset is a little bit less than the original one. But, the cache-references of the original implementation is signicantly greater than the standard library implementation, which indicates the orignal implementation is frequently accessing memory. Overall, the performance of standard library implementation is slightly better than the orignal implementation, with or without Ofast optimization.

# std::multiset::emplace\_hint
Emplace hint allows an additional parameter `hint` being sent while calling the `insert` function. If `hint` is the greatest element that is smaller than the inserted element, then emplace hint would immidietly insert the element after `hint`, which considerably increases the performance of `insert`. Since the initial loop monotonously insert element to the data structure, by simply recording the previous element being insert as the new `hint`, we may take advantage of emplace hint. Such measure has significantly increased performance by 39%. Not only the CPU instruction has decreased, the memory access has also significatly decreased.

# Comparisions
![](https://i.imgur.com/iCKkh3i.jpg)


