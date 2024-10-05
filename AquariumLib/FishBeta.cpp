/**
 * @file FishBeta.cpp
 * @author Evan Gasper
 *
 * Class for Beta Fish in Aquarium
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"
#include <string>

using std::make_unique;

/// Fish filename
const std::wstring FishBetaImageName = L"images/beta.png";

/// X min speed
const double betaXSpeedMin = 1;
/// Y min speed
const double betaYSpeedMin = -10;
/// X max speed
const double betaXSpeedMax = 10;
/// Y max speed
const double betaYSpeedMax = 10;

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium *aquarium) : Fish(aquarium, FishBetaImageName)
{
 // Slower speed range for Beta fish
 std::uniform_real_distribution<> distributionX(betaXSpeedMin, betaXSpeedMax);
 SetSpeedX(distributionX(aquarium->GetRandom()));
 // average vertical speed
 std::uniform_real_distribution<> distributionY(betaYSpeedMin, betaYSpeedMax);
 SetSpeedY(distributionY(aquarium->GetRandom()));
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);
 itemNode->AddAttribute(L"type", L"beta");
 return itemNode;
}