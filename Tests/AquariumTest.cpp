#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Aquarium.h>
#include <FishBeta.h>
#include <ChestFish.h>
#include <DecorCastle.h>
#include <DovaFish.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     *  Populate an aquarium with three Beta fish
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);
        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    void TestThreeBetas(wxString filename)
    {

        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
    }

    void PopulateAllTypes(Aquarium *aquarium)
    {
        auto fish1 = make_shared<ChestFish>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(120, 220);

        auto fish2 = make_shared<DovaFish>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(420, 420);

        auto fish3 = make_shared<DecorCastle>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(620, 120);
    }

    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"120\" y=\"220\"")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"120\" y=\"220\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"420\" y=\"420\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"620\" y=\"120\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"chest\"/><item.* type=\"dova\"/><item.* type=\"castle\"/></aqua>")));
    }

};

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
        L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
          L"Testing fish at 100, 200";
    // Add second fish at the same location, it should be on top of fish1
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);

    // Test hit on second fish, which is on top of fish1
    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) << L"Testing top fish at 100, 200";

    // Test hit slightly outside the fish location to ensure no hit
    ASSERT_EQ(aquarium.HitTest(300, 400), nullptr) << L"Testing empty spot at 300, 400";

    // Move second fish away and test again to ensure the first fish is now detected
    fish2->SetLocation(150, 250);
    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) << L"Testing fish1 after moving fish2";

    // Test the new location of fish2 to ensure it's now hit
    ASSERT_TRUE(aquarium.HitTest(150, 250) == fish2) << L"Testing fish2 at new location 150, 250";
}

TEST_F(AquariumTest, Save) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
}


TEST_F(AquariumTest, Clear) {
    // Create an aquarium
    Aquarium aquarium;

    // Populate the aquarium with three Beta fish
    PopulateThreeBetas(&aquarium);

    // Ensure there are fish in the aquarium before clearing
    ASSERT_TRUE(aquarium.HitTest(100, 200) != nullptr) << L"Fish should be present before clearing";

    // Clear the aquarium
    aquarium.Clear();

    // Ensure the aquarium is empty after clearing
    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) << L"Aquarium should be empty after clearing";
    ASSERT_EQ(aquarium.HitTest(400, 400), nullptr) << L"Aquarium should be empty after clearing";
    ASSERT_EQ(aquarium.HitTest(600, 100), nullptr) << L"Aquarium should be empty after clearing";
}


TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);

    aquarium2.Load(file3);
    aquarium2.Save(file3);
    TestAllTypes(file3);
}

