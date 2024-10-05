/**
 * @file Fish.cpp
 * @author Evan Gasper
 *
 * Fish swim around the aquarium
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"
#include <random>

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
    std::uniform_real_distribution<> distributionX(MinSpeedX, MaxSpeedX);
    mSpeedX = distributionX(aquarium->GetRandom());
    std::uniform_real_distribution<> distributionY(MinSpeedY, MaxSpeedY);
    mSpeedY = distributionY(aquarium->GetRandom());
}


/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);
    // Access the item image and bitmap through the protected accessors
    wxImage* fishImage = GetItemImage();

    double aquariumWidth = GetAquarium()->GetWidth();
    double aquariumHeight = GetAquarium()->GetHeight();

    double fishWidth = fishImage->GetWidth();
    double fishHeight = fishImage->GetHeight();

    if (mSpeedX > 0 && GetX() >= (aquariumWidth - 10 - fishWidth / 2))
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }
    else if (mSpeedX < 0 && GetX() <= (10 + fishWidth / 2))
    {
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }
    // Prevent fish from moving out of aquarium vertically
    if (GetY() < (10 + fishHeight) || GetY() > (aquariumHeight - 10 - fishHeight))
    {
        mSpeedY = -mSpeedY;  // Reverse vertical direction
    }
}

/**
 * Saving specific values pertaining to fish
 * @param node the base XmlNode that will be appended
 * @return wxXmlNode* the pointer to the node
 */
wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    auto itemNode =  Item::XmlSave(node);

    // Add speed attributes to the node
    itemNode->AddAttribute(L"speedx", wxString::FromDouble(mSpeedX));
    itemNode->AddAttribute(L"speedy", wxString::FromDouble(mSpeedY));

    return itemNode;
}

/**
 * Loading specific values pertaining to fish
 * @param node the base XmlNode that will be loaded
 *
 */
void Fish::XmlLoad(wxXmlNode* node)
{

    Item::XmlLoad(node);

    // Load speed from xml tag
    double speedX = 0.0;
    double speedY = 0.0;
    node->GetAttribute(L"speedx", L"0.0").ToDouble(&speedX);
    node->GetAttribute(L"speedy", L"0.0").ToDouble(&speedY);

    mSpeedX = speedX;
    mSpeedY = speedY;

    if (mSpeedX < 0) {
        SetMirror(true);  // Mirror if speedX is negative
    } else {
        SetMirror(false); // No mirror if speedX is positive
    }

}
