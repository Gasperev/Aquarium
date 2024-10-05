/**
 * @file Aquarium.h
 * @author Evan Gasper
 *
 * The Aquarium class holding all relevant aquarium
 * information
 */
 
#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <memory>
#include <random>
#include "Item.h"

/**
 * Main Aquarium class used to construct, allocate, and draw
 */
class Aquarium {
private:
 /// The Aquarium class now has a place to remember that image it will draw as a background
 std::unique_ptr<wxBitmap> mBackground; ///< Background image being used
 /// List of all fish in the Aquarium
 std::vector<std::shared_ptr<Item>> mItems;
 /// Random number generator
 std::mt19937 mRandom;
public:
 Aquarium();
 void OnDraw(wxDC* dc);
 void Add(std::shared_ptr<Item> item);
 std::shared_ptr<Item> HitTest(int x, int y);
 void MoveItemToEnd(std::shared_ptr<Item> item);
 void Save(const wxString& filename);
 void Load(const wxString& filename);
 void XmlItem(wxXmlNode* node);
 void Clear();
 void Update(double elapsed);
 /**
 * Get the random number generator
 * @return Pointer to the random number generator
 */
 std::mt19937 &GetRandom() {return mRandom;}

 /**
 * Get the width of the aquarium
 * @return Aquarium width in pixels
 */
 int GetWidth() const { return mBackground->GetWidth(); }

 /**
  * Get the height of the aquarium
  * @return Aquarium height in pixels
  */
 int GetHeight() const { return mBackground->GetHeight(); }
};



#endif //AQUARIUM_H
