/**
 * @file AquariumView.h
 * @author Evan Gasper
 *
 * The main view of the window and app
 */
 
#ifndef AQUARIUMVIEW_H
#define AQUARIUMVIEW_H

#include "Aquarium.h"

/**
 * Class that creates and modifies a Window Frame
 */
class AquariumView : public wxWindow{
private:
 /// An object that describes our aquarium
 Aquarium  mAquarium;
 /// Any item we are currently dragging
 std::shared_ptr<Item> mGrabbedItem;
 /// Timer used to refresh
 wxTimer mTimer;
 /// Stopwatch used to measure elapsed time
 wxStopWatch mStopWatch;
 /// The last stopwatch time
 long mTime = 0;

 /// Paint background
 void OnPaint(wxPaintEvent& event);
 /// Add a Beta Fish to Aquarium
 void OnAddFishBetaFish(wxCommandEvent& event);
 /// Add a Dovahfin to Aquarium
 void OnAddFishDovaFish(wxCommandEvent& event);
 /// Add a Chest to Aquarium
 void OnAddFishChestFish(wxCommandEvent& event);
 /// Add a Castle to Aquarium
 void OnAddDecorCastle(wxCommandEvent& event);
 /// Save file as
 void OnFileSaveAs(wxCommandEvent& event);
 void OnTimer(wxTimerEvent& event);
 void OnFileOpen(wxCommandEvent& event);
 /// Handle mouse event click
 void OnLeftDown(wxMouseEvent& event);
 /// Handle mouse event release
 void OnLeftUp(wxMouseEvent& event);
 /// Handle mouse movement
 void OnMouseMove(wxMouseEvent& event);

public:
 /// Initializer
 void Initialize(wxFrame* parent);
};



#endif //AQUARIUMVIEW_H
