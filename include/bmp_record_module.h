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
#ifndef BMP_RECORD_MODULE_H
#define BMP_RECORD_MODULE_H

#include "output_module_if.h"
#include "my_bmp.h"
#include <sstream>

namespace mandelbrot
{
  class bmp_record_module: public output_module_if
  {
  public:
    inline bmp_record_module(void);
    // Methods inherited from interface
    inline void clear(const uint32_t & p_nb_iter);
    inline void treat(const point_information & p_poi);
    inline void terminate(void);
  private:
    std::string m_name;
    lib_bmp::my_bmp m_img;
  };

  //----------------------------------------------------------------------------
  bmp_record_module::bmp_record_module(void):
    m_img(640,480,24)
    {
    }

    //----------------------------------------------------------------------------
    void bmp_record_module::clear(const uint32_t & p_nb_iter)
    {
      std::stringstream l_number ;
      l_number << p_nb_iter;
      m_name = "test_"+l_number.str()+".bmp";
    }
    //----------------------------------------------------------------------------
    void bmp_record_module::treat(const point_information & p_poi)
    {
      if(p_poi.is_in())
        {
	  lib_bmp::my_color_alpha l_color((p_poi.get_module() & 0xF) << 4,p_poi.get_module() & 0xF0,~((p_poi.get_module() & 0xF00)>> 4));
          m_img.set_pixel_color(p_poi.get_x(),p_poi.get_y(),l_color);
        }
      else
        {
          m_img.set_pixel_color(p_poi.get_x(),p_poi.get_y(),lib_bmp::my_color_alpha(0,0,0));
        }
    }

    //----------------------------------------------------------------------------
    void bmp_record_module::terminate(void)
    {
      m_img.save(m_name);
    }
}
#endif //BMP_RECORD_MODULE_H
//EOF
