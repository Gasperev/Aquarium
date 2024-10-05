/**
 * @file Fish.h
 * @author Evan Gasper
 *
 * Base class for all FISH (not decor)
 */
 
#ifndef FISH_H
#define FISH_H

#include "Item.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;
/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;
/// Maximum speed in the Y direction in
/// in pixels per second
const double MaxSpeedY = 15;
/// Minimum speed in the Y direction in
/// in pixels per second
const double MinSpeedY = -15;

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
private:
 /// Fish speed in the X direction
 /// in pixels per second
 double mSpeedX;

 /// Fish speed in the Y direction
 /// in pixels per second
 double mSpeedY;

protected:
 Fish(Aquarium* aquarium, const std::wstring& filename);

 /// Allow derived classes to set speed of X
 /// @param speedX the speed to set X to
 void SetSpeedX(double speedX) { mSpeedX = speedX; }
 /// Allow derived classes to set speed of Y
 /// @param speedY the speed to set Y to
 void SetSpeedY(double speedY) { mSpeedY = speedY; }
 /// Call refresh on the fish
 void Update(double elapsed);

public:
 /// Default constructor (disabled)
 Fish() = delete;

 /// Copy constructor (disabled)
 Fish(const Fish &) = delete;

 /// Assignment operator
 void operator=(const Fish &) = delete;

 /// Upcall original save but also save fish specific info
 wxXmlNode* XmlSave(wxXmlNode* node) override;

 /// Call specific load for fish type to set speed
 void XmlLoad(wxXmlNode* node) override;

};



#endif //FISH_H
