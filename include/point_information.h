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
#ifndef POINT_INFORMATION_H
#define POINT_INFORMATION_H

#include <inttypes.h>

namespace mandelbrot
{
  class point_information
  {
  public:
    inline point_information(const uint32_t & p_x,
                             const uint32_t & p_y);
    inline const uint32_t & get_x(void)const;
    inline const uint32_t & get_y(void)const;
    inline void set_result(bool p_in,
                           const uint16_t & p_final_x,
                           const uint16_t & p_final_y,
                           const uint16_t & p_module,
                           const uint16_t & p_nb_iter);
    inline bool is_in(void)const;
    inline const uint16_t & get_module(void)const;
  private:

    const uint32_t m_x;
    const uint32_t m_y;
    bool m_in;
    uint16_t m_final_x;
    uint16_t m_final_y;
    uint16_t m_module;
    uint16_t m_nb_iter;
  };

  //----------------------------------------------------------------------------
  point_information::point_information(const uint32_t & p_x,
                                       const uint32_t & p_y):
    m_x(p_x),
    m_y(p_y),
    m_in(false)
      {
      }

    //----------------------------------------------------------------------------
    const uint32_t & point_information::get_x(void)const
      {
        return m_x;
      }

    //----------------------------------------------------------------------------
    const uint32_t & point_information::get_y(void)const
      {
        return m_y;
      }

    //----------------------------------------------------------------------------
    void point_information::set_result(bool p_in,
                                       const uint16_t & p_final_x,
                                       const uint16_t & p_final_y,
                                       const uint16_t & p_module,
                                       const uint16_t & p_nb_iter)
    {
      m_in = p_in;
      m_final_x = p_final_x;
      m_final_y = p_final_x;
      m_module = p_module;
      m_nb_iter = p_nb_iter;
    }

    //----------------------------------------------------------------------------
    bool point_information::is_in(void)const
    {
      return m_in;
    }

    //----------------------------------------------------------------------------
    const uint16_t & point_information::get_module(void)const
      {
        return m_module;
      }
}
#endif // POINT_INFORMATION_H
//EOF
