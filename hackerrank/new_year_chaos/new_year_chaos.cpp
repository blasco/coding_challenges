#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumBribes function below.
void minimumBribes(vector<int> queue) {
    bool too_chaotic = false;
    const int max_permutations = 2;
    auto expected_next_values = vector<int>(max_permutations);
    int permutations_count = 0;
    for (int index = 0; index < queue.size(); ++index) {
        auto distance_to_index = queue[index] - (index + 1);
        if (distance_to_index > max_permutations) {
            too_chaotic = true;
            break;
        } else if (distance_to_index == max_permutations) { 
            permutations_count += max_permutations;
            --expected_next_values[0]; 
            --expected_next_values[1];
        } else if (distance_to_index == expected_next_values[1] + 1) { 
            permutations_count += 1;
            --expected_next_values[0];
            expected_next_values[1] = 0;
        } else if (distance_to_index == expected_next_values[0]) {
            expected_next_values[0] = 0;
            std::rotate(
                std::begin(expected_next_values),
                std::prev(std::end(expected_next_values)),
                std::end(expected_next_values)
                );
        } else {
            too_chaotic = true;
            break;
        }
    }
    if (!too_chaotic) {
        std::cout << permutations_count << "\n";
    } else {
        std::cout << "Too chaotic" << "\n";
    }
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
