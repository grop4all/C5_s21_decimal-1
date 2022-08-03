using System;

class Decimal_testing {
  static void Main() {
    
    int Noper = 0;  
    
    string[] convert_ops = {"INT", "FLOAT"};
    string[] convert_ops1 = {"int", "float"};
    
    //int[] num1 = {0,0,0,0,5};
    //int[] num2 = {0,0,0,1,1};
    
    int int_number = -95452;
    
    decimal num_result = new decimal( int_number );
    
    // bool b1;
    // if (num1[3]==0) b1 = false;
    //     else b1 = true;
    // bool b2;
    // if (num2[3]==0) b2 = false;
    //     else b2 = true;
        
    //decimal max_dec = Decimal.MaxValue;
    
    //decimal number1 =  new Decimal(num1[0], num1[1], num1[2], b1, (byte)num1[4]);
   // decimal number2 = new Decimal(num2[0], num2[1], num2[2], b2, (byte)num2[4]);
    


    //int[] bits0 = decimal.GetBits(number1);
    //int[] bits1 = decimal.GetBits(number2);
    int[] bits2 = decimal.GetBits(num_result);

    
    Console.WriteLine($"START_TEST(CONVERT_FROM_{convert_ops[Noper]}_Test00) {{");
    Console.WriteLine($"int int_num = {int_number};");
    Console.WriteLine($"s21_decimal result;");
    Console.WriteLine($"ck_assert_uint_eq(s21_from_{convert_ops1[Noper]}_to_decimal(int_num, &result), 0);");
    Console.WriteLine($"ck_assert_uint_eq(result.bits[0], {(uint)bits2[0]});");
    Console.WriteLine($"ck_assert_uint_eq(result.bits[1], {(uint)bits2[1]});");
    Console.WriteLine($"ck_assert_uint_eq(result.bits[2], {(uint)bits2[2]});");
    Console.WriteLine($"ck_assert_uint_eq(result.bits[3], {(uint)bits2[3]});\n");
    Console.WriteLine($"// --- C# operation <CONVERT_FROM_INT> testing result:");
    Console.WriteLine($"// int_num: {int_number}");
    Console.WriteLine($"// res : {num_result}");
    Console.WriteLine("//       {0,10:d10} {1,10:D10} {2,10:D10} {3,10:D10}",
                             (uint)bits2[3], (uint)bits2[2], (uint)bits2[1], (uint)bits2[0]);
    Console.WriteLine($"}");
    Console.WriteLine($"END_TEST");
  }
}
