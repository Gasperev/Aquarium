/**
 * @file Item.h
 * @author Evan Gasper
 *
 * Base class for any item in the Aquarium
 */

#ifndef ITEM_H
#define ITEM_H

class Aquarium;

/**
 * Base Class representing any item in the Aquarium
 */
class Item {
private:
 /// The aquarium this item is contained in
 Aquarium   *mAquarium;

 // Item location in the aquarium
 double  mX = 0;     ///< X location for the center of the item
 double  mY = 0;     ///< Y location for the center of the item

 /// The underlying fish image
 std::unique_ptr<wxImage> mItemImage;

 /// The bitmap we can display for this fish
 std::unique_ptr<wxBitmap> mItemBitmap;

 bool mMirror = false;   ///< True mirrors the item image

protected:
 Item(Aquarium* aquarium, const std::wstring& filename);
 /**
  * Get the underlying wxImage for this item.
  * @return Pointer to the wxImage object.
  */
 wxImage* GetItemImage() const { return mItemImage.get(); }

public:
 ~Item();

 /// Default constructor (disabled)
 Item() = delete;

 /// Copy constructor (disabled)
 Item(const Item &) = delete;

 /// Assignment operator
 void operator=(const Item &) = delete;

 /**
 * The X location of the item
 * @return X location in pixels
 */
 double GetX() const { return mX; }

 /**
  * The Y location of the item
  * @return Y location in pixels
  */
 double GetY() const { return mY; }

 /**
  * Set the item location
  * @param x X location in pixels
  * @param y Y location in pixels
  */
 virtual void SetLocation(double x, double y) { mX = x; mY = y; }

 virtual void Draw(wxDC *dc);

 virtual wxXmlNode* XmlSave(wxXmlNode* node);

 virtual void XmlLoad(wxXmlNode* node);
 void SetMirror(bool m);

 virtual bool HitTest(int x, int y);

 /**
  * Get the pointer to the Aquarium object
  * @return Pointer to Aquarium object
  */
 Aquarium *GetAquarium() { return mAquarium;  }

 /**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
 virtual void Update(double elapsed) {}
};

#endif //ITEM_H