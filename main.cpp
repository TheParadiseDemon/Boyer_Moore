#include <bits/stdc++.h>

std::vector<int> StopCharTable (std::string pattern){

    std::vector<int> alphabet(26);
    for (auto i: alphabet){
        i = -1;
    }
    for (int i = 0; i < pattern.length(); i++){
        if ((i == pattern.length()-1) && alphabet[i] != -1)
            continue;
        alphabet[pattern[i]] = i;
    }
    return alphabet;
}

std::vector<int> SuffixTable(std::string pattern){

    std::vector<int> SuffixShift(pattern.length() + 1);
    for (auto& i: SuffixShift)
        i = pattern.length();
    SuffixShift[pattern.length()] = 1;
    for (int i = pattern.length() - 1; i >= 0;i--){
        for (int at = i; at < pattern.length(); at++) {
            std::string suffix = pattern.substr(at);
            for (int j = at - 1; j >= 0; j--) {
                std::string prefix = pattern.substr(j, suffix.length());
                if (suffix == prefix) {
                    SuffixShift[j] = at - i;
                    break;
                }
            }
        }
    }
    return SuffixShift;
}

int Search(std::string text, std::string pattern){

    std::vector<int> suffix = SuffixTable(pattern);
    std::vector<int> stoptable = StopCharTable(pattern);

    int count = 0;
    int current = 0;
    int last = pattern.length() - 1;
    while (current <= text.length() - last){
        int currentend = last;
        while (currentend >= 0 && text[current + currentend] == pattern[currentend])
            currentend--;
            if (currentend == -1) {
                count++;
            }
            current += std::max(currentend - stoptable[text[current + currentend]], suffix[currentend + 1]);
    }
    return count;
}

int main(){

    std::string text = "abcabcdcababab";
    std::string pattern = "ab";
    std::cout << Search(text, pattern);


}