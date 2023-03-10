#include <gtest/gtest.h>
#include <fstream>
#include <exception>
#include "File_IO.h"

FileOps fileops;

TEST(FileOpsTest, TestReadFunction)
{
    std::string fileName = "CAN_file.txt";
    // Create a test file with known contents
    std::ofstream testFile(fileName);

    ASSERT_TRUE(testFile.is_open());
    testFile << "Line one\nHello\n";
    testFile.close();
    // Check if testFile is really closed
    EXPECT_EQ(testFile.is_open(), false);

    // Call the read function and check the returned value
    std::vector<std::string> result = fileops.read(fileName);
    std::vector<std::string> expected = {"Line one", "Hello"};

    EXPECT_EQ(result, expected);
    // iterate through vectors and comparing each string separately to be sure
    for (size_t idx = 0; idx < result.size(); ++idx)
    {
        EXPECT_EQ(expected[idx], result[idx]);
    }

    // Clean up the test file
    std::remove(fileName.c_str());
}

TEST(FileOpsTest, TestWriteFunction)
{
    // Prepare the data to be written
    std::vector<std::string> data = {"Hello", "I am a", "Software", "Developer"};

    // Call the write function
    try
    {
        fileops.write("test.txt", data);
    }
    catch (const std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }

    // Verify that the file was written correctly
    std::vector<std::string> written_data = fileops.read("test.txt");
    EXPECT_EQ(data, written_data);

    // Clean up the test file
    std::remove("test.txt");
}

TEST(FileOpsTest, TestFileExistsFunction)
{
    if (!fileops.fileExists("test.txt"))
    {
        // Create a test file
        std::ofstream testFile("test.txt");
        testFile.close();
        // Check if testFile is really closed
        EXPECT_EQ(testFile.is_open(), false);
    }
    // Check that the fileExists function returns true for the test file
    EXPECT_TRUE(fileops.fileExists("test.txt"));

    // Check that the fileExists function returns false for a non-existent file
    EXPECT_FALSE(fileops.fileExists("nonexistent.txt"));

    // Clean up the test file
    std::remove("test.txt");
}
