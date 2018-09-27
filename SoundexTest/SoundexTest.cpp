#include "Soundex.h"

#include "gmock/gmock.h"

class SoundexEncoding : public testing::Test {
    public:
        Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord) {
    ASSERT_EQ(soundex.encode("A"), "A000");
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
    ASSERT_EQ(soundex.encode("I"), "I000");
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits) {
    EXPECT_EQ(soundex.encode("Ab"), "A100");
    EXPECT_EQ(soundex.encode("Ac"), "A200");
    EXPECT_EQ(soundex.encode("Ax"), "A200");
    EXPECT_EQ(soundex.encode("Ad"), "A300");
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics) {
    ASSERT_EQ(soundex.encode("A#"), "A000");
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits) {
    ASSERT_EQ(soundex.encode("Acdl"), "A234");
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters) {
    ASSERT_EQ(soundex.encode("Dcdlb"), "D234");
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters) {
    EXPECT_EQ(soundex.encode("Baeiouhycdl"), "B234");
    EXPECT_EQ(soundex.encode("BaAeEiIoOuUhycdl"), "B234");
    EXPECT_EQ(soundex.encode("BAEIOUhycdl"), "B234");
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {
    ASSERT_EQ(soundex.encode("Abfcgdt"), "A123");
}

TEST_F(SoundexEncoding, UppercasesFirstLetter) {
    ASSERT_EQ(soundex.encode("abcd"), "A123");
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {
    ASSERT_EQ(soundex.encode("BCDL"), "B234");
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {
    ASSERT_EQ(soundex.encode("Bbcd"), "B230");
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
    ASSERT_EQ(soundex.encode("Jbob"), "J110");
}

