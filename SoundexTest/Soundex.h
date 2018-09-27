/*
An algorithm for encoding words using the Soundex algorithm

Encoding steps are as follows:

    1. Retain the first letter. Drop all other occurrences of a, e, i, o, u, y, h, w

    2. Replace consonants with digits (after the first letter):
         b, f, p, v : 1
         c, g, j, k, q, s, x, z : 2
         d, t : 3
         l : 4
         m, n : 5
         r : 6

    3. If two adjacent letters encode to the same number, encode them instead as
       a single number. Also, do so if two letters with the same number are
       separated by h or w (but code them twice if separated by a vowel). This
       rule also applies to the first letter.

    4. Stop when you have a letter and three digits. Zero-pad if needed.
*/

#ifndef SOUNDEX_H
#define SOUNDEX_H

#include <cctype>

#include <string>
#include <unordered_map>

class Soundex {

    static const size_t MaxCodeLength{4};

    public:
        std::string encode(const std::string& word) const {
            return zeroPadToMaxLength(UpperCase(head(stripInitialDuplicates(word))) +
                encodedDigits(tail(stripInitialDuplicates(word))));
        }

    private:
        std::string stripInitialDuplicates(std::string word) const {
            if (word.length() <= 1) return word;
            while (std::tolower(word[0]) == std::tolower(word[1]))
                word = word.substr(1);
            return word;
        }

        std::string zeroPadToMaxLength(std::string word) const {
            while (word.length() < MaxCodeLength)
                word += "0";
            return word.substr(0, MaxCodeLength);
        }

        std::string UpperCase(const std::string& string) const {
            return std::string(1, std::toupper(static_cast<unsigned char>(string.front())));
        }

        std::string head(const std::string& word) const {
            return word.substr(0, 1);
        }

        std::string tail(const std::string& word) const {
            return word.substr(1);
        }

        std::string encodedDigits(const std::string& word) const {
            return removeVowels(encodedDigitsIncludingVowels(word));
        }

        std::string encodedDigitsIncludingVowels(const std::string& word) const {
            if (word.empty())
                return "";
            if (word.length() == 1)
                return encodedDigit(word[0]);
            std::string first_char = encodedDigit(word[0]);
            std::string remainder = encodedDigitsIncludingVowels(tail(word));
            while (first_char == remainder.substr(0, 1)) 
                remainder = remainder.substr(1);
            return first_char + remainder;
        }

        std::string encodedDigit(char letter) const {
            std::unordered_map<char, std::string> encodings {
                {'a', "*"}, {'e', "*"}, {'i', "*"}, {'o', "*"}, {'u', "*"},
                {'b', "1"}, {'f', "1"}, {'p', "1"}, {'v', "1"},
                {'c', "2"}, {'g', "2"}, {'j', "2"}, {'k', "2"}, {'q', "2"}, {'s', "2"}, {'x', "2"}, {'z', "2"},
                {'d', "3"}, {'t', "3"},
                {'l', "4"},
                {'m', "5"}, {'n', "5"},
                {'r', "6"}
            };
            return encodings[std::tolower(letter)];
        }

        std::string removeVowels(std::string word) const {
            while (word.find("*") != std::string::npos)
                word.erase(word.find("*"), 1);
            return word;
        }
};

#endif

