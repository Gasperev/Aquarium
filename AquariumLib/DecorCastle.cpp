/**
 * @file DecorCastle.cpp
 * @author evang
 */

#include "pch.h"
#include "DecorCastle.h"
#include "Aquarium.h"

using std::make_unique;



/// DovaFish filepath
const std::wstring DecorCastleImageName = L"images/castle.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish exists in
 */
DecorCastle::DecorCastle(Aquarium *aquarium) : Item(aquarium, DecorCastleImageName)
{
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* DecorCastle::XmlSave(wxXmlNode* node)
{
 auto itemNode = Item::XmlSave(node);
 itemNode->AddAttribute(L"type", L"castle");
 return itemNode;
}