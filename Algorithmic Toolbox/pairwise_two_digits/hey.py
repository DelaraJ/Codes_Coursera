n = int(input())
ns= list(map(int, input().split()))
max1 = -1
max2 = -1
for num in ns:
    if(num>max1) :
        max2=max1
        max1=num
    elif(num>max2):
        max2=num
res = max1*max2
print(res)