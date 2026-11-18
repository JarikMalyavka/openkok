#include <iostream>
#include <opencv2/geometry/2d.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
// #include <iomanip>
// #include <sstream>
// #include <ctime>
#include <opencv2/objdetect.hpp>
#include <opencv2/xobjdetect.hpp>

using namespace std;
using namespace cv;

int main()
{

    VideoCapture cap(0, CAP_V4L2);
    cout << cap.isOpened() << endl;

    if (!cap.isOpened())
    {
        cout << "Camera not found!" << endl;
        return -1;
    }
    vector<Mat> channels;
    vector<Rect> faces;
    bool colorCorrection = false;
    bool rotateImage = false;

    while (true)
    {
        Mat frame;
        cap.read(frame);
        split(frame, channels);
        if (frame.empty())
        {
            cout << "Empty frame!" << endl;
            break;
        }
        int key = waitKey(1);
        if (key == 27)
        {
            break;
        }
        if (key == 's')
        {
            colorCorrection = !colorCorrection;
        }
        if (key == 't')
        {
            rotateImage = !rotateImage;;
        }
        if (colorCorrection)
        {
            channels[2].convertTo(channels[2], -1, 1.1, 0);
        }
        merge(channels, frame);
        if (rotateImage)
        {
            rotate(frame, frame, ROTATE_180);
        }
        imshow("kill", frame);
    }


}