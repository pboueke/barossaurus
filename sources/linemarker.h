#ifndef LINEMARKER_H
#define LINEMARKER_H
#include  "camera.h"

void onMouse(int event, int x, int y, int flags, void* userdata);

class LineMarker
{ 
public:
    LineMarker(int camIndex);
    lineSet markLines();
    lineSet displayCamera(string windowName);
    void chooseLine(bool top);
    void stopMarking();
};

#endif // LINEMARKER_H
