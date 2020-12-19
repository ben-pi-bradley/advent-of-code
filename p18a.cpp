// Advent of Code December 18, 2020 Midnight.
// Ben Bradley


#include <iostream>
#include <string>

using namespace std;


uint64_t atou64 (string & in, int & inptr)
{

    uint64_t r = 0;
    while (inptr < in.length() && in [inptr] >= '0' && in [inptr] <= '9')
    {
        r = r * 10 + (in [inptr] - '0');
        inptr++;
    }
    return r;

} // uint64_t atou64 (string & in, int & inptr)



uint64_t eval_string (string & in, int & inptr)
{
//    cout << "Entering eval_string. ";
//    if (inptr < in.length())
//        cout << in[inptr];
//    cout << endl;
    uint64_t sum = 0;
    int op = 0;
    
    while (inptr < in.length())
    {
        if (in [inptr] == '+')
        {
//            cout << "+ op = 1" << endl;
            op = 1;
            inptr++;
        }
        else if (in [inptr] == '*')
        {
//            cout << "* op = 2" << endl;
            op = 2;
            inptr++;
        }
        else if (in [inptr] == '(')
        {
//            cout << "open paren" << endl;
            inptr++;
            uint64_t temp = eval_string (in, inptr);
//            cout << " temp = " << temp << " sum = " << sum << " op = " << op << endl;
            switch (op)
            {
                case 0 : sum  = temp; break;
                case 1 : sum += temp; break;
                case 2 : sum *= temp; break;
            }
            op = 0;
//            cout << " new sum  = " << sum << endl;
        }

        else if (in [inptr] >= '0' && in [inptr] <= '9')
        {
//            cout << " scanning num " << in [inptr];
            uint64_t temp = atou64 (in, inptr);
//            cout << " temp = " << temp << " sum = " << sum << " op = " << op << endl;
            switch (op)
            {
                case 0 : sum  = temp; break;
                case 1 : sum += temp; break;
                case 2 : sum *= temp; break;
            }
            op = 0;
//            cout << " new sum  = " << sum << endl;
        }
        else if (in [inptr] == ')')
        {
//            cout << "close paren" << endl;
            inptr++;
            return sum;
        }
        else
            inptr++;
        
    }
//    cout << "Exiting eval_string, sum = " << sum << endl;
    return sum;
} // 


int main (void)
{

    string inputline;

    uint64_t sum = 0;
    do
    {
        getline (cin, inputline);
        if (inputline.length() > 0)
        {
            int inptr = 0;
            sum += eval_string (inputline, inptr);
        }
    }
    while (!cin.eof());


    cout << "total  " << sum << endl;

} // int main (void)



#if 0
--- Day 18: Operation Order ---
As you look out the window and notice a heavily-forested continent slowly appear over the horizon, you are interrupted by the child sitting next to you. They're curious if you could help them with their math homework.

Unfortunately, it seems like this "math" follows different rules than you remember.

The homework (your puzzle input) consists of a series of expressions that consist of addition (+), multiplication (*), and parentheses ((...)). Just like normal math, parentheses indicate that the expression inside must be evaluated before it can be used by the surrounding expression. Addition still finds the sum of the numbers on both sides of the operator, and multiplication still finds the product.

However, the rules of operator precedence have changed. Rather than evaluating multiplication before addition, the operators have the same precedence, and are evaluated left-to-right regardless of the order in which they appear.

For example, the steps to evaluate the expression 1 + 2 * 3 + 4 * 5 + 6 are as follows:

1 + 2 * 3 + 4 * 5 + 6
  3   * 3 + 4 * 5 + 6
      9   + 4 * 5 + 6
         13   * 5 + 6
             65   + 6
                 71
Parentheses can override this order; for example, here is what happens if parentheses are added to form 1 + (2 * 3) + (4 * (5 + 6)):

1 + (2 * 3) + (4 * (5 + 6))
1 +    6    + (4 * (5 + 6))
     7      + (4 * (5 + 6))
     7      + (4 *   11   )
     7      +     44
            51
Here are a few more examples:

2 * 3 + (4 * 5) becomes 26.
5 + (8 * 3 + 9 + 3 * 4 * 3) becomes 437.
5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4)) becomes 12240.
((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 13632.
Before you can help with the homework, you need to understand it yourself. Evaluate the expression on each line of the homework; what is the sum of the resulting values?

To begin, get your puzzle input.

Answer: 
 

You can also [Share] this puzzle.

#endif
