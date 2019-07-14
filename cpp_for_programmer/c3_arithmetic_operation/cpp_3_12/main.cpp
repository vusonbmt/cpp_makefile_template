/*Goal: Practice PreFix and PostFix
**
*/

#include <iostream>

using namespace std;

int main()
{
    int a, b = 0;
    int post, pre = 0;
    cout << "Inital values: \t\t\tpost = " << post << " pre= " << pre << "\n";
    post = a++;
    pre = ++b;
    cout << "After one postfix and prefix: \tpost = " << post << " pre= " << pre << "\n";
    post = a++;
    pre = ++b;
    cout << "After two postfix and prefix: \tpost = " << post << " pre= " << pre << "\n";
    return 0;
}