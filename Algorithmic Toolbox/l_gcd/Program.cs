using System;
class Program
{
    static long f1 = 1;
    static long f2 = 1;
    static long s = 2;
    public static long fib(long n, long mod)
    {
        if(n<1)
            return 0;
        if (n==1)
            return 1;
        if (n==2)
            return 2;
        if (n%2 == 1)
        {
            n+=1;
            for (long i=2; i<n; i+=2 )
            {
                f1=(f1+f2)%mod;
                f2=(f1+f2)%mod;
                s+=f1+f2;
            }
            return (s-f2)%mod;
        }
        else
        {
            for (long i=2; i<n; i+=2 )
            {
                f1=(f1+f2)%mod;
                f2=(f1+f2)%mod;
                s+=f1+f2;
            }
            return s%mod;

        }
    }
    static void Main(string[] args)
    {
        // var toks = Console.ReadLine().Split();
        // long n = long.Parse(toks[0]);
        // long m = long.Parse(toks[1]);
        // long n = long.Parse(Console.ReadLine());
        int[] ns=new int[] {1,2,3,4,5,6,7,8,9,10};
        for (int i =0; i<ns.Length; i++)
        {
            Console.WriteLine(fib(ns[i], 5));

        }
    }
}