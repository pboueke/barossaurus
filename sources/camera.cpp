#include "camera.h"

//----- aLine ---------------------------------------------------------------
// Data structure to store a line information
aLine::aLine(){p1.x=0;p2.x=0;p1.y=0;p2.y=0;} //default constructor

    //constructor declaring points
    aLine::aLine(int p1x, int p1y, int p2x, int p2y){
        p1.x = p1x;
        p1.y = p1y;
        p2.x = p2x;
        p2.y = p2y;
        height = p1y;
    }

    void aLine::drawaLine(Mat image, Scalar color){
        line(image, p1, p2, color);
    }

//----- lineSet ---------------------------------------------------------------
//A pair of lines, top and bottom, with a defined distance from the camera
    lineSet::lineSet(){
        aLine line0;
        set[0] = line0;
        set[1] = line0;
        hasDistance=false;
    }

    void lineSet::setDistance(double dist)
    {
        dc = dist;
        hasDistance = true;
    }

    void lineSet::setLine(int index, aLine myLine){
        if (index > 1){cout<<"Index out of range;";}
        set[index] = myLine;
        if(index == 0){bottom = true;}
        else if (index == 1){top = true;}
    }

    bool lineSet::hasBottom(){return bottom;}

    bool lineSet::hasTop(){return top;}

//----- fiveLineSets ---------------------------------------------------------------
//Five lineSets together with extra data for calibration purpose (calibration object height)
    fiveLineSets::fiveLineSets(){
        lineSet lineSetZero;
        objectHeight = 0.0;
        for (int i; i<5; i++){fset[i] = lineSetZero;}
        hasObHeight=false; one = false; two = false; three = false; four = false; five = false;
    }

    double fiveLineSets::listDistances()
    {
        for (int i=0; i<5; i++)
        {
            distanceList[i]=fset[i].dc;
        }
    }

    double fiveLineSets::listLinesHeight()
    {
        lineSet* temp_aux;
        aLine* temp_botton;
        aLine* temp_top;
        for (int i=0;i<5;i++)
        {
            temp_aux = & fset[i];                      // ponteiro auxiliar no endereço do set[i]
            temp_botton = & temp_aux->set[0];          //  " " no endereço da linha de baixo
            temp_top = & temp_aux->set[1];             //  " " da linha de cima
            bottonHeight[i]=  temp_botton->height;
            topHeight[i]=temp_top->height;
        }
    }

    void fiveLineSets::setSet(int index, lineSet mySet){
        if (index>4){cout<<"Index out of range;";}
        fset[index] = mySet;
        switch(index){
        case 0: one = true; break;
        case 1: two = true; break;
        case 2: three = true; break;
        case 3: four = true; break;
        case 4: five = true; break;
        }
    }

    void fiveLineSets::setObjectHeight(float obHeight){
        objectHeight = obHeight;
        hasObHeight = true;
    }

    bool fiveLineSets::isFull(){
        return one && two && three && four && five && hasObHeight &&
                fset[0].hasDistance &&
                fset[1].hasDistance &&
                fset[2].hasDistance &&
                fset[3].hasDistance &&
                fset[4].hasDistance;
    }

//----- Camera ---------------------------------------------------------------
//Camera class for the calibration and measuring calculus
Camera::Camera ()
{
    m_va = 0;
    m_vb = 0;
    m_ha = 0;
    m_hb = 0;
}

void Camera::set_Distances_CameraVsObject(double ex_realDist[])
{
    for (int i = 0; i < calibration_range; i++)
    {
        realDist[i] = ex_realDist[i];
    }
                                //debug
}

void Camera::calculate_VerticalParameters(double *maxh, double *minh)
// This is a linear fit
// y = a*x + b
{
    double xm = 0, ym = 0;
    for (int i = 0; i < calibration_range; i++)
    {
        objectRealHeightDividedByPixelHeight[i]         // rt(dc))
                = objectRealHeight/(maxh[i] - minh[i]); // y array
    }

    for (int i = 0; i < calibration_range; i++)  //average values
    {
        xm += realDist[i];                                // from x array
        ym += objectRealHeightDividedByPixelHeight[i];    // from y array
    }
    xm /= calibration_range;                                     // average value from
    ym /= calibration_range;                                     // each array

    double sum_xx = 0, sum_yy = 0, sum_xy = 0;
    for (int i = 0; i< calibration_range; i++)
    {
        double temp_x = realDist[i] - xm;
        double temp_y = objectRealHeightDividedByPixelHeight[i] - ym;
        sum_xx += temp_x*temp_x;
        sum_yy += temp_y*temp_y;
        sum_xy += temp_x*temp_y;
    }
    if (sum_xx == 0)
    {
        cout <<"\nError, infinite slope" << endl;
        // More actions can be taken if appropriate.
    }
    m_va = sum_xy/sum_xx;
    m_vb = ym - m_va*xm;
    if (abs(sum_yy) == 0)
    {
     m_Vcprecision = 1;
    }
     else
     {
        m_Vcprecision = sum_xy/sqrt(sum_xx*sum_yy);
     }
    //cout << "m_va = " << m_va << "  \n m_vb = " << m_vb << "\n m_Vcprecision = "
    //        << m_Vcprecision <<"  \n ym = " << ym
    //        << "  \n xm = " << xm << " \n sum_xx = " << sum_xx << "  \n  sum yy = "
    //        << sum_yy << "  \n sum_xy = " << sum_xy <<"\n";

//    for (int i = 0; i < calibration_range; i++)
//    {
//        cout << realDist[i] << " / ";
//    }
//    cout << endl;
//    for (int i = 0; i < calibration_range; i++)
//    {
//        cout << objectRealHeightDividedByPixelHeight[i] << " / ";
//    }
//    cout << endl;

}

void Camera::calculate_HorizontalParameters(double *maxh)
// This is a non linear fit transformed into a linear fit
// y = a*x^b   =>  ln(y) = ln(a) + b*ln(x)
{
    double xm = 0, ym = 0;
    double maxh2[calibration_range], realDist2[calibration_range];
    for (int i = 0; i < calibration_range; i++)
    {
        maxh2[i] = log(maxh[i]);           // transforming from non-linear
        realDist2[i] = log(realDist[i]);   // to linear
    }

    for (int i = 0; i < calibration_range; i++)   // average values
    {
        xm += realDist2[i];                 // from x array
        ym += maxh2[i];                     // from y array
    }
    xm /= calibration_range;
    ym /= calibration_range;


    double sum_xx = 0, sum_yy = 0, sum_xy = 0;
    for (int i = 0; i< calibration_range; i++)
    {
        double temp_x = realDist2[i] - xm,
               temp_y = maxh2[i] - ym;
        sum_xx += temp_x*temp_x;
        sum_yy += temp_y*temp_y;
        sum_xy += temp_x*temp_y;
    }

    if (sum_xx == 0)
    {
        cout <<"Error, infinite slope." << endl;
        // More actions can be taken if appropriate.
    }
    double aux_a = 0;
    m_hb = sum_xy/sum_xx;
    aux_a = ym - m_hb*xm;
    //m_ha = ym - m_hb*xm;
    m_ha = exp(aux_a);
    if (abs(sum_yy) == 0)
    {
     m_Vcprecision = 1;
    }
     else
     {
        m_Vcprecision = sum_xy/sqrt(sum_xx*sum_yy);
     }

        //cout << "h_ha = " << m_ha << "  \n m_hb = " << m_hb << "\n";//m_Vcprecision = "
            //<< m_Hcprecision <<"  \n ym = " << ym
            //<< "  \n xm = " << xm << " \n sum_xx = " << sum_xx << "  \n  sum yy = "
            //<< sum_yy << "  \n sum_xy = " << sum_xy <<"\n";


}

double Camera::calculate_HorizontalDistanceOfObject(lineSet set)
// returns the distance between the object and the camera using hpx = ha*dc^hb
// => dc = raiz(em hb)de(hpx/ha) = (hpx/ha)^(1/hb))
//using ln(hpx)=ln(a) + b*ln(dc) => ln(dc) = [ln(hpx/a)]/b
{
    aLine* temp_botton = & set.set[0];
    aLine* temp_top = & set.set[1];
    double hpx = temp_botton->height - temp_top->height; // botton - top, botton always > top
    return pow(hpx/m_ha,1/m_hb);
    //double v_aux = log(hpx/m_ha)/m_hb;
    //return v_aux;
}

double Camera::calculate_RealHeight(double dist, lineSet set)
// returns the real height using realHeight/hpx = a*dist + b
// => realHeight = (a*dist - b)*hpx
{
    aLine* temp_botton = & set.set[0];
    aLine* temp_top = & set.set[1];
    double hpx = temp_botton->height - temp_top->height;
    return (m_va*dist + m_vb)*hpx;


}

