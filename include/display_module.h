/*    This file is part of mandelbrot
      The aim of this software is to compute Mandelbrot fractal
      Copyright (C) 2013  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "output_module_if.h"
#include "simple_gui.h"

namespace mandelbrot
{
  class display_module: public output_module_if, public simple_gui
  {
  public:
    inline display_module(void);
    // Methods inherited from interface
    inline void clear(const uint32_t & p_nb_iter);
    inline void treat(const point_information & p_poi);
    inline void terminate(void);
  private:
    uint32_t m_black_color;
  };

  //----------------------------------------------------------------------------
  display_module::display_module(void):
    simple_gui()
    {
      createWindow(640,480);
      m_black_color = getColorCode(0,0,0);
    }

    //----------------------------------------------------------------------------
    void display_module::clear(const uint32_t & p_nb_iter)
    {
      // Nothing to do
    }
    //----------------------------------------------------------------------------
    void display_module::treat(const point_information & p_poi)
    {
      if(p_poi.is_in())
        {
          uint32_t l_color = getColorCode((p_poi.get_module() & 0xF) << 4,p_poi.get_module() & 0xF0,~((p_poi.get_module() & 0xF00)>> 4));
          set_pixel_without_lock(p_poi.get_x(),p_poi.get_y(),l_color);
        }
      else
        {
          set_pixel_without_lock(p_poi.get_x(),p_poi.get_y(),m_black_color);
        }
    }

    //----------------------------------------------------------------------------
    void display_module::terminate(void)
    {
      lock();
      refresh();
      unlock();    
    }
}
#endif //DISPLAY_MODULE_H
//EOF
