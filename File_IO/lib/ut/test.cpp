#include <gtest/gtest.h>
#include <fstream>
#include "File_Io.h"

FileOps fileops;

TEST(FileOpsTest, TestReadFunction)
{
    // Create a test file with known contents
    std::ofstream testFile("test.txt");
    testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    // Call the read function and check the returned value
    std::vector<std::string> result = fileops.read("test.txt", 2);
    std::vector<std::string> expected = {"Line 1", "Line 2"};
    EXPECT_EQ(result, expected);
    // assume, that the size of vector "expected" will always greater or equal to result
    // i.t. expected.size() >= result.size()
    // iterate through vectors and comparing each string separately to be sure
    for (size_t idx = 0; idx < result.size(); ++idx)
    {
        EXPECT_EQ(expected[idx], result[idx]);
    }

    // Clean up the test file
    std::remove("test.txt");
}

TEST(FileOpsTest, TestWriteFunction)
{
    // Create a test file with known contents
    std::ofstream testFile("test.txt");
    testFile << "Hello\nI am a\nSoftware\nDeveloper\n";
    // testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    // Call the write function
    fileops.write("test.txt", "Hello\nI am a\nSoftware\nDeveloper", 1);

    // Check the contents of the file after the write
    std::ifstream updatedFile("test.txt");
    std::string updatedContents((std::istreambuf_iterator<char>(updatedFile)),
                                std::istreambuf_iterator<char>());
    std::string expectedContents = "Hello\nI am a\nSoftware\nDeveloper\n";
    // std::string expectedContents = "Line 1\nNew Line\nLine 3";
    EXPECT_EQ(updatedContents, expectedContents);

    // Clean up the test file
    std::remove("test.txt");
}

TEST(FileOpsTest, TestFileExistsFunction)
{
    // Create a test file
    std::ofstream testFile("test.txt");
    testFile << "Line 1\nLine 2\nLine 3";
    testFile.close();

    // Check that the fileExists function returns true for the test file
    EXPECT_TRUE(fileops.fileExists("test.txt"));

    // Check that the fileExists function returns false for a non-existent file
    EXPECT_FALSE(fileops.fileExists("nonexistent.txt"));

    // Clean up the test file
    std::remove("test.txt");
}

// /*
// A task: write a function, which simplifies a full phone number:
// - removes a code of the Country ( +46, +10, +1 .etc )
// - removes possible dashes ( 999-999-99  -> 99999999)
// - removes spaces in between numbers ( 99 99 -> 9999 )
// */
// std::string SimplifyPhoneNumber(std::string phoneNumber)
// {
//     if (phoneNumber.empty())
//     {
//         return "ERROR";
//     }
//     return phoneNumber.substr(1);
// }

// TEST(PhoneNumberChecks, InputIsNotOutput)
// {
//     // input data
//     std::string fakeNumber("+50 11 999 12-34");
//     // expected value
//     std::string expectedNumber("0119991234");
//     // logic
//     std::string output = SimplifyPhoneNumber(fakeNumber);
//     // comparing results
//     EXPECT_NE(fakeNumber, output);
// }

// TEST(PhoneNumberChecks, ReturnErrorOnEmptyString)
// {
//     std::string fakeNumber("");
//     std::string expectedResult("ERROR");
//     std::string output = SimplifyPhoneNumber(fakeNumber);
//     EXPECT_EQ(output, expectedResult);
// }

// // Test case has a "Test set name" and "Test case name"
// TEST(First_group, numbers_are_equal)
// {
//     EXPECT_EQ(1, 1);
// }
// // Test case has a "Test set name" and "Test case name"
// TEST(First_group, example_1)
// {
//     std::string wrongInput("Error");
//     std::string expectedInput("Error");
//     EXPECT_EQ(wrongInput, expectedInput);
// }
