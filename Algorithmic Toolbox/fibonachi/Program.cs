using System;
class Program
{
    static long f1 = 1;
    static long f2 = 1;
    public static long fib(int n)
    {
        if(n<1)
            return 0;
        if (n<=2)
            return 1;
        if (n%2 == 1)
        {
            n+=1;
            for ( int i=2; i<n; i+=2 )
            {
                f1=f1+f2;
                f2=f1+f2;
            }
            return f1;
        }
        else
        {
            for ( int i=2; i<n; i+=2 )
            {
                f1=f1+f2;
                f2=f1+f2;
            }
            return f2;

        }
    }
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        Console.WriteLine(fib(n));
    }
}