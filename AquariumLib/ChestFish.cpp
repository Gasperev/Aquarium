/**
 * @file ChestFish.cpp
 * @author Evan Gasper
 */

#include "pch.h"
#include "ChestFish.h"
#include "Aquarium.h"

/// Chest filename
const std::wstring ChestFishImageName = L"images/chest1.png";
/// X min speed
const double chestXSpeedMin = 0.1;
/// Y min speed
const double chestYSpeedMin = 0;
/// X max speed
const double chestXSpeedMax = 0.2;
/// Y max speed
const double chestYSpeedMax = 0;

/**
 * Constructor
 * @param aquarium Aquarium this chest is a member of
 */
ChestFish::ChestFish(Aquarium *aquarium) : Fish(aquarium, ChestFishImageName)
{
 // Chest barely moves across the screen horizontally
 std::uniform_real_distribution<> distributionX(chestXSpeedMin, chestXSpeedMax);
 SetSpeedX(distributionX(aquarium->GetRandom()));
 // no movement up and down
 std::uniform_real_distribution<> distributionY(chestYSpeedMin, chestYSpeedMax);
 SetSpeedY(distributionY(aquarium->GetRandom()));
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* ChestFish::XmlSave(wxXmlNode* node)
{
 auto itemNode = Fish::XmlSave(node);
 itemNode->AddAttribute(L"type", L"chest");
 return itemNode;
}