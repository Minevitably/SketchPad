#pragma once
#include <string>
#include "GL/gl.h"
#include "GL/glu.h"

#define M_PI 3.1415926
class TGraphic {
public:
    virtual void Draw() = 0; 
    virtual ~TGraphic() {} 
};