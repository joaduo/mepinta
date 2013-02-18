/*
 * bitmap_checker.cpp
 *
 *  Created on: Dec 8, 2011
 *      Author: jduo
 */

#include <mepintasdk/sdk.h>

#include <k3dsdk/bitmap.h>

#include "k3dv1_Color.h"
#include "k3dv1_Bitmap.h"

extern "C" EXPORTED_SYMBOL
int create_checker(MP_args_p args){
  //Inputs
  INPUT_VALIDATED_DEFAULT(uint,check_height,args, check_height > 0, 1);
  INPUT_VALIDATED_DEFAULT(uint,check_width,args, check_width > 0, 1);
  INPUT(k3dv1_Color*,color1,args);
  INPUT(k3dv1_Color*,color2,args);

  //Outputs
  OUTPUT(k3dv1_Bitmap*,bitmap,args);

  k3d::checkerboard_fill(view(*bitmap), check_width, check_height, k3d::pixel(color1->red, color1->green, color1->blue, 1.0), k3d::pixel(color2->red, color2->green, color2->blue, 1.0));

  return EXIT_NORMAL;
}
