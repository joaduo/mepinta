//Mepinta
//Copyright (c) 2011-2012, Joaquin G. Duo, mepinta@joaquinduo.com.ar
//
// K-3D
// Copyright (c) 1995-2006, Timothy M. Shead
//
//This file is part of Mepinta.
//
//Mepinta is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Mepinta is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Mepinta. If not, see <http://www.gnu.org/licenses/>.

#include <mepintasdk/sdk.h>
#include <mepintasdk/cpp/TypedPropertiesCollector.h>
#include <mepintasdk/cpp/TypedCollectorManager.h>

#include <iostream>
using namespace std;

int on_deform_mesh(MP_args_p args){
  INPUT(double,time,args);
  //Collect variables like the last one
  TypedPropertiesCollector<double> values_collector(args);
  INPUT(char*,time_name, args);
  //Collect variables like the last one
  TypedPropertiesCollector<char*> variables_collector(args);
  //Collecting inputs, then declare the collector after all the inputs
  TypedCollectorManager collector_manager(args);

  //Collect typed properties
  collector_manager.appendCollector(&values_collector);
  collector_manager.appendCollector(&variables_collector);
  collector_manager.collectProperties();
  return 0;
}


class CppProcessorBase{
//public:
// inline CppProcessorBase(MP_args* args){
//
// }
//private:
// MP_args* args;
};

class DeformationBase:
  public CppProcessorBase
{
public:
  inline int demux_signal(MP_args* args){
    return 0;
  }
private:
  inline void prepare_update_args(MP_args* args){

  }
  inline virtual void deform_mesh(MP_args* args) = 0;
};



class K3dv1ProcessorBase{

};


int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
