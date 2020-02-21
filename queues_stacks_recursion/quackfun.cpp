/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{

    // Your code here
    //base case
    if(s.empty())
        return 0;

    //init sum and temp var to hold top var of stack
    T runningSum = 0;
    T topVal = s.top();

    //pops value and recursively calls sum to find total sum of things on stack
    s.pop();
    runningSum = (topVal + ::QuackFun::sum<T>(s));

    //push top val back onto stack
    s.push(topVal);

    return runningSum; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    // stack<char> temp;
    stack<char> temp;

    while(input.empty() == false)
    {    
        //if we have an open [,  we push it to our stack
        if(input.front() == '[')
            temp.push('[');
        //if its a close ]. we pop from our stack if it isn't empty (meaning there's a matching close bracket)
        if(input.front() == ']')
        {
            if(temp.empty())
                return false;
            else
                temp.pop();
        }
        //pop the top of the input
        input.pop();
    }
    //if the stack is empty, we know it's balanced, otherwise, it is imbalanced
    return temp.empty();
    /*
    method without stack
    int numOpen = 0;
    while(input.empty() == false)
    {    
        if(input.front() == '[')
            numOpen++;
        if(input.front() == ']')
            numOpen--;
        input.pop();
    }
    bool isBalanced = (numOpen == 0) ? true : false;
    return isBalanced;
    */
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    queue<T> q2;

    // Your code here
    //init counter to reverse blocks (we only reverse even number sized blocks)
    unsigned long loop = 1;

    while(q.empty() == false)
    {
        //if its an odd number, we just dont flip the order
        if(loop % 2 == 1)
        {
            //handles incomplete block
            (loop > q.size()) ?  loop = q.size() : loop += 0;

            //puts things from q directly onto q2
            //std::cout << q.size() << endl << q.front() << endl;
            for(unsigned i = 0; i < loop; i++)
            {
                if(!q.empty())
                {
                    q2.push(q.front());
                    q.pop();
                    //std::cout << q.size() << endl << q.front() << endl;
                }
            }
        }
        //if its an even number block, we flip the elements
        if(loop % 2 == 0)
        {
            //handles incomplete block
            (loop > q.size()) ?  loop = q.size() : loop += 0;
            //pops from q and puts it on stack (for reversing)
            //std::cout << q.size() << endl << q.front() << endl;
            for(unsigned long i = 0; i < loop; i++)
            {
                s.push(q.front());
                q.pop();
            //std::cout << q.size() << endl << q.front() << endl;
            }
            //things from q that are on stack are added to q2 in reverse order (due to LIFO stack nature)
            for(unsigned long i = 0; i < loop; i++)
            {
                q2.push(s.top());
                s.pop();
            }
        }
        //increments loop so we go from 1 size block to 2 size block etc.
        loop++;
    }

    //makes q = q2 
    q = q2;

}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retVal = true; // optional
    T sTop; // rename me
    //T qFront; // rename :)

    
    // Your code here
    //algorithm: 
    //tear down stack until stack is empty
    //when stack is empty, push the values back on the stack
    //then, stack top should = q front (b/c the stack top is the last item in the original stack)
    //if sTop == qFront, we pop a value off the queue and add it to the back, so we can compare the next value of the queue to the next value of the stack
    //base case
    //stack 
    if(s.empty() || q.empty())
    {
        return true;
    }
    else
    {
        //gathers stack top and queue front
        sTop = s.top();
        
        //pops top off stack, uses recursion to pop ALL values off stack
        //due to base case, will return true when stack is empty
        s.pop();
        if(verifySame(s,q) == true && q.front() == sTop)
        {
            retVal = true;
        }
        else
        {
            retVal = false;
        }

        //based on this, we then move the first item of the queue to the back (by popping and pushing)
        //this allows us to continue using recursion to compare the queue and stack
        //i.e., the next time, it will be comparing the second element of the queue to the second last element of the stack
        q.push(q.front()); 
        q.pop();
        //push the stack value back on to compare the next element         
        s.push(sTop);
       
    }
    
    //recursive case
    return retVal;
}

}
