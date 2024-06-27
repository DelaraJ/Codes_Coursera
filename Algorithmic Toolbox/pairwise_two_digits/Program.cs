using System;
using System.Collections.Generic;
using System.Linq;
class Program
{
    static void Main(string[] args)
    {
        int n = int.Parse(Console.ReadLine());
        List<int> toks = Array.ConvertAll(Console.ReadLine().Split(" "), int.Parse).ToList();
        // // O(nLogn)
        // toks.Sort();
        // toks.Reverse();
        // Console.WriteLine(toks[0]*toks[1]);
        // O(n)
        long max1 = -1;
        long max2 = -1;
        foreach (int num in toks)
        {
            if(num>max1)
            {
                max2=max1;
                max1=num;
            }
            else if(num>max2)
            {
                max2=num;
            }
        }
        long res = max1*max2;
        Console.WriteLine(res);

    }
}