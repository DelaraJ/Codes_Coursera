def findGCD(a,b):
    if min(a,b)==0: print(max(a,b))
    elif a%b==0: print(b)
    else: findGCD(b,a%b)
x,y = map(int, input().split())
findGCD(x,y)