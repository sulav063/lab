#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> stack;
string input;
int pos = 0;

void print()
{
    cout << "Stack: ";
    for(int i=0; i<stack.size(); i++) cout << stack[i] << " ";
    cout << "\tLeft: " << input.substr(pos) << endl;
}

bool reduce()
{
    int n = stack.size();

    // 1. T * F -> T
    if(n >= 3 && stack[n-3] == "T" && stack[n-2] == "*" && stack[n-1] == "F")
    {
        cout << "Reduce: T * F -> T\n";
        stack.erase(stack.end()-3, stack.end());
        stack.push_back("T");
        return true;
    }

    // 2. E + T -> E
    if(n >= 3 && stack[n-3] == "E" && stack[n-2] == "+" && stack[n-1] == "T")
    {
        cout << "Reduce: E + T -> E\n";
        stack.erase(stack.end()-3, stack.end());
        stack.push_back("E");
        return true;
    }

    // 3. id -> F
    if(n >= 1 && stack[n-1] == "id")
    {
        cout << "Reduce: id -> F\n";
        stack[n-1] = "F";
        return true;
    }

    // 4. F -> T
    if(n >= 1 && stack[n-1] == "F")
    {
        cout << "Reduce: F -> T\n";
        stack[n-1] = "T";
        return true;
    }

    // 5. T -> E  ONLY when there is exactly one T left (or after + reduction)
    //    This prevents premature T -> E on the right side
    if(n == 1 && stack[0] == "T")
    {
        cout << "Reduce: T -> E\n";
        stack[0] = "E";
        return true;
    }

    return false;
}

int main()
{
    cout << "Enter string (e.g. id+id*id): ";
    cin >> input;

    cout << "\n=== SHIFT-REDUCE PARSING ===\n\n";

    while(pos < input.length())
    {
        if(pos + 1 < input.length() && input.substr(pos, 2) == "id")
        {
            cout << "Shift: id\n";
            stack.push_back("id");
            pos += 2;
        }
        else
        {
            cout << "Shift: " << input[pos] << "\n";
            stack.push_back(string(1, input[pos]));
            pos++;
        }

        print();
        while(reduce()) print();
    }

    while(reduce()) print();

    if(stack.size() == 1 && stack[0] == "E")
        cout << "\nSTRING ACCEPTED!\n";
    else
        cout << "\nSTRING REJECTED!\n";

    return 0;
}
