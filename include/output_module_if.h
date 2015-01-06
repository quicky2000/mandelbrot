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
#ifndef OUTPUT_MODULE_IF_H
#define OUTPUT_MODULE_IF_H

namespace mandelbrot
{
  class point_information;

  class output_module_if
  {
  public:
    virtual void clear(const uint32_t &)=0;
    virtual void treat(const point_information & p_poi)=0;
    virtual void terminate(void)=0;
    inline virtual ~output_module_if(void){}
  private:
  };
}

#endif //OUTPUT_MODULE_IF_H
//EOF 
