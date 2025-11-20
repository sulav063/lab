#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> stack;
string input;
int i = 0;

void print() {
    cout << "Stack: ";
    for (int k = 0; k < stack.size(); k++)  // use index instead of auto
        cout << stack[k] << " ";
    cout << "\tLeft: " << input.substr(i) << endl;
}

bool reduce() {
    int n = stack.size();

    // id -> F
    if (n >= 1 && stack[n-1] == "id") {
        cout << "Reduce: id -> F\n";
        stack[n-1] = "F";
        return true;
    }

    // F -> T
    if (n >= 1 && stack[n-1] == "F") {
        cout << "Reduce: F -> T\n";
        stack[n-1] = "T";
        return true;
    }

    // T * T -> T (handle * precedence)
    if (n >= 3 && stack[n-3] == "T" && stack[n-2] == "*" && stack[n-1] == "T") {
        cout << "Reduce: T * T -> T\n";
        stack.resize(n-3);
        stack.push_back("T");
        return true;
    }

    // T + T -> T (handle +)
    if (n >= 3 && stack[n-3] == "T" && stack[n-2] == "+" && stack[n-1] == "T") {
        cout << "Reduce: T + T -> T\n";
        stack.resize(n-3);
        stack.push_back("T");
        return true;
    }

    return false;
}

int main() {
    cout << "Enter expression (like id+id*id): ";
    cin >> input;

    cout << "\n=== SHIFT-REDUCE PARSING ===\n\n";

    while (i < input.length()) {
        // Shift 'id'
        if (i+1 < input.length() && input[i]=='i' && input[i+1]=='d') {
            cout << "Shift: id\n";
            stack.push_back("id");
            i += 2;
        } else {
            cout << "Shift: " << input[i] << "\n";
            string s(1, input[i]);
            stack.push_back(s);
            i++;
        }

        print();

        // Apply reductions as much as possible
        while (reduce()) print();
    }

    // Final reductions
    while (reduce()) print();

    if (stack.size() == 1 && stack[0] == "T")
        cout << "\nSTRING ACCEPTED!\n";
    else
        cout << "\nSTRING REJECTED!\n";

    return 0;
}
