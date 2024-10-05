/**
 * @file AquariumView.cpp
 * @author Evan Gasper
 */

#include "pch.h"
#include "AquariumView.h"
#include "ids.h"
#include "FishBeta.h"
#include "DovaFish.h"
#include "ChestFish.h"
#include <wx/dcbuffer.h>
#include "DecorCastle.h"

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
 Create(parent, wxID_ANY);
 // Special Paint Background
 SetBackgroundStyle(wxBG_STYLE_PAINT);
 Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);
 // Binds the parent frame
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishDovaFish, this, IDM_ADDFISHDOVA);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishChestFish, this, IDM_ADDFISHCHEST);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastle, this, IDM_ADDDECORCASTLE);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this, wxID_SAVEAS);
 parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileOpen, this, wxID_OPEN);

 // Create a timer and set it to the const FrameDuration
 mTimer.SetOwner(this);
 mTimer.Start(FrameDuration);
 // Binding all the mouse events
 Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
 Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
 Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
 Bind(wxEVT_TIMER, &AquariumView::OnTimer, this);

 mStopWatch.Start();

}

/**
 * Refresh function for animation
 * @param event
 */
void AquariumView::OnTimer(wxTimerEvent& event)
{
 Refresh();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
 // Compute the time that has elapsed
 // since the last call to OnPaint.
 auto newTime = mStopWatch.Time();
 auto elapsed = (double)(newTime - mTime) * 0.001;
 mTime = newTime;

 mAquarium.Update(elapsed);

 wxAutoBufferedPaintDC dc(this);

 wxBrush background(*wxWHITE);
 dc.SetBackground(background);
 dc.Clear();

 mAquarium.OnDraw(&dc);
}

/**
 * Menu hander for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
 auto fish = std::make_shared<FishBeta>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * Menu handler for Add Fish > Dovahfin.
 * @param event Mouse event.
 */
void AquariumView::OnAddFishDovaFish(wxCommandEvent& event)
{
 auto fish = std::make_shared<DovaFish>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * Menu handler for Add Fish > Chest.
 * @param event Mouse event.
 */
void AquariumView::OnAddFishChestFish(wxCommandEvent& event)
{
 auto fish = std::make_shared<ChestFish>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * Menu handler for Add Fish > Chest.
 * @param event Mouse event.
 */
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
 auto fish = std::make_shared<DecorCastle>(&mAquarium);
 mAquarium.Add(fish);
 Refresh();
}

/**
 * Menu handler for SaveAs
 * @param event Mouse event.
 */
void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
 wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
        L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
 if (saveFileDialog.ShowModal() == wxID_CANCEL)
 {
  return;
 }

 auto filename = saveFileDialog.GetPath();
 mAquarium.Save(filename);
}

/**
 * File>Open menu handler
 * @param event Menu event
 */
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
 wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
         L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
 if (loadFileDialog.ShowModal() == wxID_CANCEL)
 {
  return;
 }

 auto filename = loadFileDialog.GetPath();
 mAquarium.Clear();
 mAquarium.Load(filename);
 Refresh();
}

/**
 * Handle the left mouse button down event.
 * @param event The mouse event triggered on left button down.
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
 mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
 if (mGrabbedItem != nullptr)
 {
  // Move grabbed item into function
  mAquarium.MoveItemToEnd(mGrabbedItem);
  Refresh();
 }
}

/**
 * Handle the left mouse button up event.
 * @param event The mouse event triggered on left button up.
 */
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
 OnMouseMove(event);
}

/**
 * Handle the mouse move event.
 * @param event The mouse event triggered during mouse movement.
 */
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
 // See if an item is currently being moved by the mouse
 if (mGrabbedItem != nullptr)
 {
  // If an item is being moved, we only continue to
  // move it while the left button is down.
  if (event.LeftIsDown())
  {
   mGrabbedItem->SetLocation(event.GetX(), event.GetY());
  }
  else
  {
   // When the left button is released, we release the
   // item.
   mGrabbedItem = nullptr;
  }

  // Force the screen to redraw
  Refresh();
 }
}