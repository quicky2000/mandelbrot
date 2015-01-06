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
#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "point_information.h"
#include "fixed_point.h"
#include "output_module_if.h"
#include <vector>

namespace mandelbrot
{
  class mandelbrot
  {
  public:
    inline mandelbrot(void);
    inline void compute(void);
    inline void set_nb_iter(const uint32_t & p_nb_iter); 
    inline void add_output_module(output_module_if &);
  private:
    inline void compute(point_information & p_poi);
    uint32_t m_nb_iter;
    const uint16_t m_width;
    const uint16_t m_height;

    const uint16_t m_fixed_min_x;
    const uint16_t m_fixed_min_y;
    const uint16_t m_fixed_limit; // 4
    std::vector<output_module_if *> m_output_modules;

  };


  //----------------------------------------------------------------------------
  mandelbrot::mandelbrot(void):
    m_nb_iter(16),
    m_width(640),
    m_height(480),
    m_fixed_min_x(0xFE00),//0xFFFFFE00; // -2
    m_fixed_min_y(0xFF10),//0xFFFFFF10; // -0.9355
    m_fixed_limit(0x400)  // 4
      {
      }

  //----------------------------------------------------------------------------
  void mandelbrot::compute(void)
  {
    for(std::vector<output_module_if *>::iterator l_iter = m_output_modules.begin();
        l_iter != m_output_modules.end();
        ++l_iter)
      {
        (*l_iter)->clear(m_nb_iter);
      }

    for(uint16_t y = 0 ; y < m_height ; ++y)
      {
	for(uint16_t x = 0 ; x < m_width ; ++x)
	  {
            point_information l_poi(x,y);
            compute(l_poi);
            for(std::vector<output_module_if *>::iterator l_iter = m_output_modules.begin();
                l_iter != m_output_modules.end();
                ++l_iter)
              {
                (*l_iter)->treat(l_poi);
              }	  
          }
      }
    for(std::vector<output_module_if *>::iterator l_iter = m_output_modules.begin();
        l_iter != m_output_modules.end();
        ++l_iter)
      {
        (*l_iter)->terminate();
      }

 }

  //----------------------------------------------------------------------------
  void mandelbrot::compute(point_information & p_poi)
  {
    uint16_t fixed_x_iter = 0;
    uint16_t fixed_y_iter = 0;

    // Compute mandelbrot coordinates
    uint16_t l_fix_x = m_fixed_min_x + p_poi.get_x();
    uint16_t l_fix_y = m_fixed_min_y + p_poi.get_y();

    uint16_t l_fixed_module = 0;
    uint16_t l_iter =0;
    bool l_in = true;
    do
      {
        uint16_t l_fixed_tmp_x = fixed_mult16(fixed_x_iter,fixed_x_iter,8) - fixed_mult16(fixed_y_iter,fixed_y_iter,8) + l_fix_x;
        uint16_t l_fixed_tmp_y = fixed_mult16(0x200,fixed_mult16(fixed_x_iter,fixed_y_iter,8),8) + l_fix_y;
        fixed_x_iter = l_fixed_tmp_x ;
        fixed_y_iter = l_fixed_tmp_y ;
        l_fixed_module = fixed_mult16(fixed_x_iter,fixed_x_iter,8) + fixed_mult16(fixed_y_iter,fixed_y_iter,8);
        l_in = l_fixed_module < m_fixed_limit;
        ++l_iter;
      } while(l_in && l_iter < m_nb_iter);
    p_poi.set_result(l_in,fixed_x_iter,fixed_y_iter,l_fixed_module,l_iter);
  }

  //----------------------------------------------------------------------------
  void mandelbrot::set_nb_iter(const uint32_t & p_nb_iter)
  {
    m_nb_iter = p_nb_iter;
  }
  //----------------------------------------------------------------------------
  void mandelbrot::add_output_module(output_module_if & p_module)
  {
    m_output_modules.push_back(&p_module);
  }
}
#endif // MANDELBROT_H
//EOF
