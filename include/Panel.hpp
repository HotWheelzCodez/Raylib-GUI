#ifndef PANEL_HPP
#define PANEL_HPP

#include <string>
#include "raylib.h"
#include "gui.hpp"

// Style structure
// -----------------------------------
typedef struct PanelStyle 
{
  Color       backgroundColor;
  Color       backgrondColorTitle;
  Color       titleColor;
  int         titleHeight;
  int         textAlignment;
  int         fontSize;
  std::string title;
} PanelStyle;

// Panel class
// ----------------------------------------------------------------------------------------------------------------------
class Panel 
{
public:
  Panel(Rectangle bounds, PanelStyle style, bool resizeTop, bool resizeRight, bool resizeBottom, bool resizeLeft);

  // Main methods
  // ------------------------------
  void updateAndRender(void);    // Will display the panel, title area and title text
  void resize(Rectangle bounds); // Will set the bounds of the panel to the given bounds

  // Getter methods
  // ---------------------------
  Rectangle getBounds(void); // Will return the Rectangle bounds of the panel

  // Setter methods
  // ---------------------------
  void setWidth(int width);   // Will set the width of the bounds
  void setHeight(int height); // Will set the height of the bounds
  void setXPos(int x);        // Will set the x-position of the bounds
  void setYPos(int y);        // Will set the y-position of the bounds

private:
  // Member variables
  // --------------------------
  Rectangle  m_Bounds;
  PanelStyle m_Style;
  bool       m_ResizeTop;
  bool       m_ResizeRight;
  bool       m_ResizeBottom;
  bool       m_ResizeLeft;
};

#endif /* PANEL_HPP */
