//
//
// Class for camera calibration process
//
// m_va and m_vb are the parameters from y = a*x + b, which is the linear
// representation of the pixel density (y)
// (x) is the distance between the and the object.
//
// dataLenght is the number of photos/data taken
//
// m_ha and m_hb are the parameters from y = a*x^b, which is the non linear
// representation of the distance to the camera (y)
// (x) is the distance (in pixels) from the border of the picture to the object
//
// maxh and minh are arrays containing the pixel values from higher and lowest
// borders of the object. Each object shares the same index in each array.
//
// ex_realdist is an array containing the real distance between the camera and
// the object. Must be created through user's data input.
//
//m_Vcprecision is a coefficient that indicates how well was the linear
//compared to the original data. If it's equal to 1, it's a perfect fit.
//
// aLine, lineSet and fiveLineSets structs

#include <iostream>
#include <cmath>
#include <string>
#include <cv.h>

using namespace std;
using namespace cv;



#ifndef CAMERA_H
#define CAMERA_H

#define calibration_range 5

//declaration, needed for real distance and height output
struct aLine{
    Point p1;
    Point p2;
    double height;  // needed in struct fiveLineSets

    aLine();
    aLine(int p1x, int p1y, int p2x, int p2y);
    void drawaLine(Mat image, Scalar color);

};

// two aLines make a lineSet (0 bottom line, 1 top line)
struct lineSet{
    aLine set[2];
    double dc;
    bool bottom;
    bool top;
    bool hasDistance;

    lineSet();
    void setDistance(double dist);
    void setLine(int index, aLine myLine);
    bool hasBottom();
    bool hasTop();
};

struct fiveLineSets{
    lineSet fset[5];
    float objectHeight;
    double distanceList[5], bottonHeight[5], topHeight[5];
    bool one, two, three, four, five, hasObHeight;

    fiveLineSets();
    double listDistances();
    double listLinesHeight();
    void setSet(int index, lineSet mySet);
    void setObjectHeight (float obHeight);
    bool isFull();
};

class Camera
{
    double m_va, m_vb , m_ha, m_hb, objectRealHeight, m_Vcprecision, m_Hcprecision;
    double realDist[calibration_range];
    double objectRealHeightDividedByPixelHeight[calibration_range];
public:
    Camera();

    double calculate_RealHeight(double dist, lineSet set);

    // linear regression. y = a*x + b
    void calculate_VerticalParameters(double *maxh,
                                      double *minh);

    double calculate_HorizontalDistanceOfObject(lineSet set);

    // non-linear regression. y = a*x^b
    void calculate_HorizontalParameters(double *maxh);

    void set_Distances_CameraVsObject (double *ex_realdist);

    void set_objectHeight(double height) { objectRealHeight = height; };

    double get_a_VerticalParameter() {return m_va; };

    double get_b_VerticalParameter() {return m_vb; };

    double get_a_HorizontalParameter() {return m_ha; };

    double get_b_HorizontalParameter() {return m_hb; };

    double get_Vcprecision() {return m_Vcprecision; };

    double get_Hcprecision() {return m_Hcprecision; };
};


#endif  /* CAMERA_H */

