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




// my kludge
// ((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 23340.



void add_close_paren (string & in, int & inptr)
{
    cout << "Start of add_close_paren:" << in << ":" << endl;
    in.insert (inptr, "(");
    inptr++;
    int xp = inptr;
    int parencount = 0;
    while (xp < in.length() && parencount >= 0)
    {
        if (in [xp] == '(')
        {
            parencount++;
            cout << "At " << xp << " parencount++ = " << parencount << endl;
        }
        else if (in [xp] == ')')
        {
            parencount--;
            cout << "At " << xp << " parencount-- = " << parencount << endl;
        }
        xp++;
    }
    in.insert (xp, ")");
    cout << "End   of add_close_paren:" << in << ":" << endl;

} // void add_close_paren (string & in, int & inptr)



uint64_t eval_string (string & in, int & inptr)
{
    cout << "Entering eval_string. ";

    while (inptr < in.length() && in [inptr] == ' ')
        inptr++;

    if (inptr < in.length())
        cout << "First char is " << in[inptr];
    cout << endl;
    uint64_t sum = 0;
    int op = 0;
    
    while (inptr < in.length())
    {
        if (in [inptr] == '+')
        {
            cout << "+ op = 1" << endl;
            op = 1;
            inptr++;
        }
        else if (in [inptr] == '*')
        {
            cout << " * calling eval " << endl;
//            op = 2;
            inptr++;
            add_close_paren (in, inptr);
// kludge here. Pushing the stack mostly works, but not in all circumstances.
            uint64_t temp = eval_string (in, inptr);
            cout << " sum, temp = " << sum << " " << temp;
            sum *= temp;
            cout << "new sum " << sum << endl;
            op = 0;
        }
        else if (in [inptr] == '(')
        {
            cout << "open paren" << endl;
            inptr++;
            uint64_t temp = eval_string (in, inptr);
            cout << " temp = " << temp << " sum = " << sum << " op = " << op << endl;
            switch (op)
            {
                case 0 : sum  = temp; break;
                case 1 : sum += temp; break;
                case 2 : sum *= temp; break;
            }
            op = 0;
            cout << " end of open paren, new sum  = " << sum << endl;
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
            cout << " new sum  = " << sum << endl;
        }
        else if (in [inptr] == ')')
        {
            cout << "close paren, exiting." << endl;
            inptr++;
            return sum;
        }
        else
        {
//            cout << "Ignoring character: " << (uint16_t)in [inptr] << endl;
            inptr++;
        }
        
    } // while (inptr < in.length())

    cout << "End of/Exiting eval_string, sum = " << sum << endl;
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

--- Part Two ---
You manage to answer the child's questions and they finish part 1 of their homework, but get stuck when they reach the next section: advanced math.

Now, addition and multiplication have different precedence levels, but they're not the ones you're familiar with. Instead, addition is evaluated before multiplication.

For example, the steps to evaluate the expression 1 + 2 * 3 + 4 * 5 + 6 are now as follows:

1 + 2 * 3 + 4 * 5 + 6
  3   * 3 + 4 * 5 + 6
  3   *   7   * 5 + 6
  3   *   7   *  11
     21       *  11
         231
Here are the other examples from above:

1 + (2 * 3) + (4 * (5 + 6)) still becomes 51.
2 * 3 + (4 * 5) becomes 46.
5 + (8 * 3 + 9 + 3 * 4 * 3) becomes 1445.
5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4)) becomes 669060.
((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2 becomes 23340.
What do you get if you add up the results of evaluating the homework problems using these new rules?

Answer: 
 

Although it hasn't changed, you can still get your puzzle input.

You can also [Share] this puzzle.



#endif
