#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <ctype.h>

using namespace cv;
using namespace std;

Mat image,frame;

int main( )
{
    VideoCapture cap;
    
    
    cap.open(0);
    if( !cap.isOpened() )
    {
        cout << "***Could not initialize capturing...***\n";
        return -1;
    }

   
    namedWindow( "CamShift Demo", 0 );
    for(;;)
    {
      
      cap >> frame;
      //frame.copyTo(image);
      imshow( "CamShift Demo", frame );
      cv::waitKey(30);
    }

    return 0;
}


