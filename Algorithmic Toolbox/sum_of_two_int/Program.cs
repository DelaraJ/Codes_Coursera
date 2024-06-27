using System;
class Program
{
    static void Main(string[] args)
    {
        var toks = Console.ReadLine().Split(" ");
        int sum = int.Parse(toks[0])+ int.Parse(toks[1]);
        Console.WriteLine(sum);
    }
}