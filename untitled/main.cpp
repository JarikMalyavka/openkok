#include <iostream>
#include <opencv2/opencv.hpp>
// #include <iomanip>
// #include <sstream>
// #include <ctime>
#include <opencv2/objdetect.hpp>
#include <opencv2/xobjdetect.hpp>

using namespace std;
using namespace cv;

int main()
{
    CascadeClassifier faceCascade;
    CascadeClassifier smileCascade;
    if (!faceCascade.load("/usr/share/opencv5/haarcascades/haarcascade_frontalface_default.xml"))
    {
        cout << "Ошибка классификатора" << endl;
        return -1;
    }
    if (!smileCascade.load("/usr/share/opencv5/haarcascades/haarcascade_smile.xml"))
    {
        cout << "Ошибка улыбки" << endl;
        return -1;
    }

    VideoCapture cap(0, CAP_V4L2);
    cout << cap.isOpened() << endl;

    if (!cap.isOpened())
    {
        cout << "Camera not found!" << endl;
        return -1;
    }

    Mat gray;
    vector<Rect> faces;


    while (true)
    {
        Mat frame;
        cap.read(frame);
        if (frame.empty())
        {
            cout << "Empty frame!" << endl;
            break;
        }
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        faceCascade.detectMultiScale(gray, faces);
        int key = waitKey(1);
        if (key == 27)
        {
            break;
        }
        string emotion = "Neutral";
        //emotion = "Neutral";
        for (Rect face : faces)
        {
            Mat faceROI = gray(face);
            Mat lowerFace = faceROI(
                Rect(0, faceROI.rows / 2,
                     faceROI.cols, faceROI.rows / 2)
                );
            vector<Rect> smiles;
            smileCascade.detectMultiScale(
                lowerFace,
                smiles,
                1.1,
                10,
                0,
                Size(20, 10)
                );
            rectangle(frame, face, Scalar(0, 255, 0), 2);


            for (Rect smile : smiles)
            {
                Rect smileRect(
                    face.x + smile.x,
                    face.y + faceROI.rows / 2 + smile.y,
                    smile.width,
                    smile.height
                    );
                emotion = "Smile";

                rectangle(frame, smileRect, Scalar(255, 0, 0), 2);
            }
        }
        putText(frame, emotion, Point(20, 40),
                FONT_HERSHEY_SIMPLEX, 1,
                Scalar(0, 255, 0), 2);
        imshow("kill", frame);
    }


}