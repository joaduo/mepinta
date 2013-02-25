/*
 * blank_bitmap.cpp
 *
 *  Created on: Dec 8, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>

#include "k3dv1_Bitmap.h"

extern "C" EXPORTED_SYMBOL
int create_blank_bitmap(MP_args_p args){
  //Inputs
  INPUT(uint,height,args);
  INPUT(uint,width,args);
  //Outputs
  OUTPUT(k3dv1_Bitmap*,bitmap,args);

  bitmap->recreate(width,height);

  return EXIT_NORMAL;
}
