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
  void updateAndRender();
  void resize(Rectangle bounds);

  // Getter methods
  // ---------------------------
  Rectangle getBounds(void);

  // Setter methods
  // ---------------------------
  void setWidth(int width);
  void setHeight(int height);
  void setXPos(int x);
  void setYPos(int y);

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
