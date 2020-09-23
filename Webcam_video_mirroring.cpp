#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"
#include <iostream>
using namespace cv;
using namespace std;

static void hello();
void mirror(Mat &map_x, Mat &map_y);

int main(int argc, char** argv)
{
    system("color 2");
    hello();
    VideoCapture live(argc > 1 ? atoi(argv[1]) : 0);
    Mat frame, frame_mirror;
    live >> frame;
    Mat map_x(frame.size(), CV_32FC1);
    Mat map_y(frame.size(), CV_32FC1);
    mirror(map_x, map_y);
    for (;;)
    {
        live >> frame;
        if (frame.empty())
        {
            break;
        }
        remap(frame, frame_mirror, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
        imshow("Initial", frame);
        imshow("Mirror", frame_mirror);
        char k=(char)waitKey(15);
        if (k == 27)
        {
            return 0;
        }
    }
    return 0;
}

static void hello()
{
    cout
        << "\n-----------------------------------------" << endl
        << "\nHi!The program aims to mirror video frames from you Webcam :) " << endl
        << "Press ESC to EXIT" << endl
        << "\n-----------------------------------------" << endl
        << "Regards" << endl
        << "Dmitriy Utev" << endl
        << "-------------------------------------------" << endl
        << endl;
}
void mirror(Mat &map_x, Mat &map_y)
{
    for(int i=0; i<map_x.rows; i++)
    {
        for (int j = 0; j < map_x.cols; j++)
        {
            map_x.at<float>(i, j) = (float)(map_x.cols - j);
            map_y.at<float>(i, j) = (float)i;
        }
    }
}