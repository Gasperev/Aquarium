/**
 * @file DovaFish.cpp
 * @author Evan Gasper
 */

#include "pch.h"
#include "DovaFish.h"
#include "Aquarium.h"

using std::make_unique;

/// DovaFish filepath
const std::wstring DovaFishImageName = L"images/dovahfin.png";

/// X min speed
const double dovaXSpeedMin = 15;
/// Y min speed
const double dovaYSpeedMin = -5;
/// X max speed
const double dovaXSpeedMax = 30;
/// Y max speed
const double dovaYSpeedMax = 5;

/**
 * Constructor
 * @param aquarium Aquarium this fish exists in
 */
DovaFish::DovaFish(Aquarium *aquarium) : Fish(aquarium, DovaFishImageName)
{
 // Far faster speed of swimming
 std::uniform_real_distribution<> distributionX(dovaXSpeedMin, dovaXSpeedMax);
 SetSpeedX(distributionX(aquarium->GetRandom()));
 // Slightly slower vertical speed
 std::uniform_real_distribution<> distributionY(dovaYSpeedMin, dovaYSpeedMax);
 SetSpeedY(distributionY(aquarium->GetRandom()));
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* DovaFish::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);
 itemNode->AddAttribute(L"type", L"dova");
 return itemNode;
}