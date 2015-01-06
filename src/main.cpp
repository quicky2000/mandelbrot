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
#include "mandelbrot.h"
#include "fixed_point.h"
#include "display_module.h"
#include "bmp_record_module.h"
#include "parameter_manager.h"


using namespace std;
using namespace parameter_manager;

int main(int argc,char ** argv)
{
  // Defining application command line parameters
  parameter_manager::parameter_manager l_param_manager("mandelbrot.exe","--",0);
  parameter_if l_display("display",true);
  parameter_if l_bmp_record("bmp_record",true);
  l_param_manager.add(l_display);
  l_param_manager.add(l_bmp_record);

  // Treating parameters
  l_param_manager.treat_parameters(argc,argv);

  mandelbrot::mandelbrot l_mandelbrot;

  // Management of output modules
  mandelbrot::display_module * l_display_module = NULL;
  mandelbrot::bmp_record_module * l_bmp_record_module = NULL;
  bool l_module_activated = false;
  if(l_display.get_value<uint32_t>())
    {
      l_display_module = new mandelbrot::display_module();
      l_mandelbrot.add_output_module(*l_display_module);
      l_module_activated = true;
    }
  if(l_bmp_record.get_value<uint32_t>())
    {
      l_bmp_record_module = new mandelbrot::bmp_record_module();
      l_mandelbrot.add_output_module(*l_bmp_record_module);
      l_module_activated = true;
    }

  if(!l_module_activated)
    {
      std::cout << "ERROR : no output module activated" << std::endl ;
      l_param_manager.display();
      exit(-1);
    }

  // Computing part
  uint16_t l_nb_iter = 32;
  for(uint16_t l_iter_index = 1 ; l_iter_index < l_nb_iter; ++ l_iter_index)
    {
      l_mandelbrot.set_nb_iter(l_iter_index);
      l_mandelbrot.compute();
    }
  delete l_bmp_record_module;
  delete l_display_module;
}
