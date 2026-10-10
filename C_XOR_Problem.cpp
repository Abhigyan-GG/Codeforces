#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>
#include <utility>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int j;
        cin >> j;

        int k = 1;
        while (k <= j) {
            k <<= 1;
        }

        vector<int> answer;
        answer.reserve(2 * k - 1);

        for (int value = 0; value < k; ++value) {
            answer.push_back(0);

            if (value + 1 != k) {
                int first = value ^ (value >> 1);
                int next = value + 1;
                int second = next ^ (next >> 1);

                answer.push_back(first ^ second);
            }
        }

        cout << answer.size() << '\n';
        for (size_t index = 0; index < answer.size(); ++index) {
            cout << answer[index];
            cout << (index + 1 == answer.size() ? '\n' : ' ');
        }
    }

    return 0;
}