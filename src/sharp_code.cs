using System;

class Decimal_testing {
  static void Main() {
    
    decimal number1 =  new Decimal(102,0,0,false,0);
    decimal number2 = new Decimal(4,0,0,false,0);
    
    //decimal num_sum = Decimal.Divide(number1, number2);
    //decimal num_sum = Decimal.Add(number1, number2);
    
    decimal num_div = number1 / number2;
    decimal num_mod = number1 % number2;
    
    Console.WriteLine("C# testing result:");
    Console.WriteLine($"decimal_num1: {number1}");
    Console.WriteLine($"decimal_num2: {number2}");
    Console.WriteLine($"decimal_num_div: {num_div}");
    Console.WriteLine($"decimal_num_mod: {num_mod}");
    
    int[] bits = decimal.GetBits(num_div);
    int[] bits2 = decimal.GetBits(num_mod);

    Console.WriteLine("result bits: {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                         (uint)bits[3], (uint)bits[2], (uint)bits[1], (uint)bits[0]);
    Console.WriteLine("result bits: {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                         (uint)bits2[3], (uint)bits2[2], (uint)bits2[1], (uint)bits2[0]);
    
  }
}
