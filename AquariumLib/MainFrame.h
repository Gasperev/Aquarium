/**
* @file MainFrame.h
 * @author Evan Gasper
 *
 * The top-level (main) frame of the application
 */

#ifndef AQUARIUM_MAINFRAME_H
#define AQUARIUM_MAINFRAME_H

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:

public:
 void Initialize();
 void OnExit(wxCommandEvent& event);
 void OnAbout(wxCommandEvent& event);
};

#endif //AQUARIUM_MAINFRAME_H