#include <iostream>
#include <opencv2/opencv.hpp>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;
using namespace cv;

int main()
{
    vector<Mat> gifFrames;

    for (int i = 0; i < 45; i++)
    {
        ostringstream filename;

        filename << "/home/zovlinux/kt1/frames/frame_" << setw(3) << setfill('0') << i << ".png";
        Mat img = imread(filename.str());
        if (img.empty())
        {
            cout << "Не удалось загрузить кадр: " << filename.str() << endl;
            continue;
        }

        gifFrames.push_back(img);
    }

    cout << "Загружено кадров: " << gifFrames.size() << endl;
    int gifIndex = 0;
    VideoCapture cap(0, CAP_V4L2);
    cout << cap.isOpened() << endl;
    if (!cap.isOpened())
    {
        cout << "Camera not found!" << endl;
        return -1;
    }
    bool coc = false;
    bool quest2 = false;
    while (true)
    {
        // switch(){

        // case 1:

        // }
        Mat frame;
        cap.read(frame);
        // cout << frame.cols << endl;
        // cout << frame.rows << endl;
        if (frame.empty())
        {
            cout << "Empty frame!" << endl;
            break;
        }
        // cout << "Camera: " << frame.cols << "x" << frame.rows << endl;
        // cout << "GIF: " << gifFrames[0].cols << "x" << gifFrames[0].rows << endl;

        int key = waitKey(1);
        if (key == 27)
        {
            break;
        }

        if (key == 'c')
        {
            coc = !coc;
        }
        time_t now = time(0);
        tm *ltm = localtime(&now);

        ostringstream timeText;
        timeText << setfill('0')
                 << setw(2) << ltm->tm_hour << ":"
                 << setw(2) << ltm->tm_min << ":"
                 << setw(2) << ltm->tm_sec;
        if (coc)
        {
            putText(frame, "HELLO NIGHT CITY", Point(200, 200), 0, 1, Scalar(255, 255, 255), 2);
            putText(frame, timeText.str(), Point(22, 52),
                    FONT_HERSHEY_DUPLEX, 1,
                    Scalar(30, 20, 10), 4);

            putText(frame, timeText.str(), Point(20, 50),
                    FONT_HERSHEY_DUPLEX, 1,
                    Scalar(80, 100, 255), 2);
        }
        if (key == 'i')
        {
            quest2 = !quest2;
        }
        if (quest2)
        {
            gifFrames[gifIndex % (gifFrames.size() - 1)].copyTo(frame(Rect(150, 100, 362, 362)));
        }
        imshow("kill", frame);
        gifIndex++;
    }


}