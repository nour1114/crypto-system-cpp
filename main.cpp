#include <bits/stdc++.h>
using namespace std;


   // Caesar Cipher

string caesarEncrypt(string text, int shift) {
    for (char &c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base + shift) % 26 + base;
        }
    }
    return text;
}

string caesarDecrypt(string text, int shift) {
    return caesarEncrypt(text, 26 - (shift % 26));
}


   // Rail Fence Cipher

string railEncrypt(string text, int rails) {
    if (rails == 1) return text;

    vector<string> fence(rails);
    int row = 0, dir = 1;

    for (char c : text) {
        fence[row] += c;
        row += dir;

        if (row == 0 || row == rails - 1)
            dir *= -1;
    }

    string result;
    for (auto &r : fence)
        result += r;

    return result;
}

string railDecrypt(string text, int rails) {
    if (rails == 1) return text;

    vector<vector<char>> mark(rails, vector<char>(text.size(), '\0'));

    int row = 0, dir = 1;

    for (int i = 0; i < text.size(); i++) {
        mark[row][i] = '*';
        row += dir;

        if (row == 0 || row == rails - 1)
            dir *= -1;
    }

    int idx = 0;
    for (int r = 0; r < rails; r++)
        for (int c = 0; c < text.size(); c++)
            if (mark[r][c] == '*')
                mark[r][c] = text[idx++];

    string result;
    row = 0, dir = 1;

    for (int i = 0; i < text.size(); i++) {
        result += mark[row][i];
        row += dir;

        if (row == 0 || row == rails - 1)
            dir *= -1;
    }

    return result;
}


   // Vigenère Cipher

string vigenereEncrypt(string text, string key) {
    string result;
    int j = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char k = tolower(key[j % key.size()]) - 'a';

            result += (c - base + k) % 26 + base;
            j++;
        } else {
            result += c;
        }
    }
    return result;
}

string vigenereDecrypt(string text, string key) {
    string result;
    int j = 0;

    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            char k = tolower(key[j % key.size()]) - 'a';

            result += (c - base - k + 26) % 26 + base;
            j++;
        } else {
            result += c;
        }
    }
    return result;
}


   // Row Transposition

vector<int> getOrder(string key) {
    vector<pair<char,int>> v;

    for (int i = 0; i < key.size(); i++)
        v.push_back({key[i], i});

    sort(v.begin(), v.end());

    vector<int> order(key.size());
    for (int i = 0; i < key.size(); i++)
        order[v[i].second] = i;

    return order;
}

string rowEncrypt(string text, string key) {
    int cols = key.size();
    int rows = ceil((double)text.size() / cols);

    vector<vector<char>> grid(rows, vector<char>(cols, 'X'));

    int idx = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (idx < text.size())
                grid[i][j] = text[idx++];

    vector<int> order = getOrder(key);

    string result;

    for (int k = 0; k < cols; k++) {
        for (int j = 0; j < cols; j++) {
            if (order[j] == k) {
                for (int i = 0; i < rows; i++)
                    result += grid[i][j];
            }
        }
    }

    return result;
}

   //MAIN MENU

int main() {
    int mode;
    cout << "1- Encrypt\n2- Decrypt\nChoose: ";
    cin >> mode;

    cin.ignore();
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    int choice;
    cout << "\n1- Caesar Cipher\n2- Rail Fence\n3- Vigenere\n4- Row Transposition\nChoose: ";
    cin >> choice;

    string result;

    if (choice == 1) {
        int key;
        cout << "Enter shift: ";
        cin >> key;

        result = (mode == 1)
            ? caesarEncrypt(text, key)
            : caesarDecrypt(text, key);
    }

    else if (choice == 2) {
        int key;
        cout << "Enter rails: ";
        cin >> key;

        result = (mode == 1)
            ? railEncrypt(text, key)
            : railDecrypt(text, key);
    }

    else if (choice == 3) {
        string key;
        cout << "Enter key: ";
        cin >> key;

        result = (mode == 1)
            ? vigenereEncrypt(text, key)
            : vigenereDecrypt(text, key);
    }

    else if (choice == 4) {
        string key;
        cout << "Enter key: ";
        cin >> key;

        if (mode == 1)
            result = rowEncrypt(text, key);
        else
            result = "Row decryption not implemented (can be added if required)";
    }

    cout << "\nResult: " << result << endl;

    return 0;
}