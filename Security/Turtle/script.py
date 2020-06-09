import timeit

start = timeit.default_timer()

ans = 0
for i in range(2 ** 31):
    ans += 1

stop = timeit.default_timer()

print('Time: ', stop - start)  
