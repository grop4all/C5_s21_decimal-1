using System;

class Decimal_testing {
  static void Main() {
      
    int Noper = 5;
    
    string[] Ops = {"ADD" , "SUB", "MUL", "DIV", "MOD", "GREAT", "LESS"};
    string[] Ops1 = {"add" , "sub", "mul", "div", "mod", "is_greater", "is_less"};
    
    int[] num1 = {0,777,8888,0,28};
    int[] num2 = {10,5454,5454,1,15};
    
    bool b1;
    if (num1[3]==0) b1 = false;
        else b1 = true;
    bool b2;
    if (num2[3]==0) b2 = false;
        else b2 = true;
        
    //decimal max_dec = Decimal.MaxValue;
    
    decimal number1 =  new Decimal(num1[0], num1[1], num1[2], b1, (byte)num1[4]);
    decimal number2 = new Decimal(num2[0], num2[1], num2[2], b2, (byte)num2[4]);
    
    decimal num_result = new Decimal(0,0,0,false,0);
    
    if (Noper==0) num_result = number1 + number2;
    if (Noper==1) num_result = number1 - number2;
    if (Noper==2) num_result = number1 * number2;
    if (Noper==3) num_result = number1 / number2;
    if (Noper==4) num_result = number1 % number2;

    int[] bits0 = decimal.GetBits(number1);
    int[] bits1 = decimal.GetBits(number2);
    int[] bits2 = decimal.GetBits(num_result);
    
    bool func_res = false;
    if (Noper==5) func_res = number1 > number2;
    
    int func_res_int = 0;
    if (func_res) func_res_int = 1;
    
    Console.WriteLine($"START_TEST({Ops[Noper]}Test00) {{");
    if (Noper<5) {
        Console.WriteLine($"s21_decimal num1 = new_decimal({(uint)num1[0]}, {(uint)num1[1]}, {(uint)num1[2]}, {(uint)num1[3]}, {(uint)num1[4]});");
        Console.WriteLine($"s21_decimal num2 = new_decimal({(uint)num2[0]}, {(uint)num2[1]}, {(uint)num2[2]}, {(uint)num2[3]}, {(uint)num2[4]});");
        Console.WriteLine($"s21_decimal result;");
        Console.WriteLine($"ck_assert_uint_eq(s21_{Ops1[Noper]}(num1, num2, &result), 0);");
        Console.WriteLine($"ck_assert_uint_eq(result.bits[0], {(uint)bits2[0]});");
        Console.WriteLine($"ck_assert_uint_eq(result.bits[1], {(uint)bits2[1]});");
        Console.WriteLine($"ck_assert_uint_eq(result.bits[2], {(uint)bits2[2]});");
        Console.WriteLine($"ck_assert_uint_eq(result.bits[3], {(uint)bits2[3]});\n");
        Console.WriteLine($"// --- C# operation <{Ops[Noper]}> testing result:");
        Console.WriteLine($"// num1: {number1}");
        Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits0[3], (uint)bits0[2], (uint)bits0[1], (uint)bits0[0]);
        Console.WriteLine($"// num2: {number2}");
        Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits1[3], (uint)bits1[2], (uint)bits1[1], (uint)bits1[0]);
        Console.WriteLine($"// res : {num_result}");
        Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits2[3], (uint)bits2[2], (uint)bits2[1], (uint)bits2[0]);
        Console.WriteLine("}");
        Console.WriteLine("END_TEST");
    }
    if (Noper >=5) {
        Console.WriteLine($"s21_decimal num1 = new_decimal({(uint)num1[0]}, {(uint)num1[1]}, {(uint)num1[2]}, {(uint)num1[3]}, {(uint)num1[4]});");
        Console.WriteLine($"s21_decimal num2 = new_decimal({(uint)num2[0]}, {(uint)num2[1]}, {(uint)num2[2]}, {(uint)num2[3]}, {(uint)num2[4]});");
        Console.WriteLine($"ck_assert_uint_eq(s21_{Ops1[Noper]}(num1, num2), {func_res_int});\n");
        Console.WriteLine($"// --- C# operation <{Ops[Noper]}> testing result:");
        Console.WriteLine($"// num1: {number1}");
        Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits0[3], (uint)bits0[2], (uint)bits0[1], (uint)bits0[0]);
        Console.WriteLine($"// num2: {number2}");
        Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits1[3], (uint)bits1[2], (uint)bits1[1], (uint)bits1[0]);
        Console.WriteLine($"// res : {func_res} {func_res_int}");
        Console.WriteLine("}");
        Console.WriteLine("END_TEST");
    }
  }
}
