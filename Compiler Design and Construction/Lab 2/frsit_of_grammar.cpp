// Program to find FIRST set of a grammar
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

vector<string> productions;

// Add character only if not already present
void addUnique(string &res, char ch) {
    if (res.find(ch) == string::npos) {
        res += ch;
    }
}

// Recursive FIRST function
void findFIRST(string &res, char symbol) {

    // If terminal (not uppercase)
    if (!isupper(symbol)) {
        addUnique(res, symbol);
        return;
    }

    // Loop through each production rule
    for (int p = 0; p < productions.size(); p++) {

        string prod = productions[p];

        // Production format: A->aB
        // Find "->" and get RHS starting position
        int arrowPos = prod.find("->");
        char lhs = prod[0];

        if (lhs != symbol)
            continue;

        int rhsStart = arrowPos + 2; // index of first RHS symbol

        // If production is like A->$
        if (prod[rhsStart] == '$') {
            addUnique(res, '$');
        }
        else {
            string temp;

            // Simple for loop for RHS symbols: aB, BCd, etc.
            for (int i = rhsStart; i < prod.size(); i++) {
                temp.clear();

                findFIRST(temp, prod[i]); // FIRST of this symbol

                // Add everything from temp to result
                for (int j = 0; j < temp.size(); j++) {
                    addUnique(res, temp[j]);
                }

                // Check if epsilon exists
                bool hasEpsilon = false;
                for (int j = 0; j < temp.size(); j++) {
                    if (temp[j] == '$') hasEpsilon = true;
                }

                // If no epsilon, stop further checking
                if (!hasEpsilon)
                    break;
            }
        }
    }
}

int main() {

    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cin.ignore();

    productions.resize(n);

    cout << "\nEnter productions like A->aB or A->$\n";
    for (int i = 0; i < n; i++) {
        cout << "Production " << i + 1 << ": ";
        getline(cin, productions[i]);
    }

    char symbol, again;

    do {
        string result;

        cout << "\nFind FIRST of: ";
        cin >> symbol;

        findFIRST(result, symbol);

        // Print FIRST set
        cout << "FIRST(" << symbol << ") = { ";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " ";
        }
        cout << "}\n";

        cout << "Find another? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    return 0;
}

/*
Enter number of productions: 3

Enter productions like A->aB or A->$
Production 1: A->aB
Production 2: B->b
Production 3: A->$
*/
