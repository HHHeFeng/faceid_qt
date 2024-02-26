#include "camerathread.h"
#include <QDebug>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
cameraThread::cameraThread()
{

    if (!faceCascade.load(path.toStdString())) {
        qDebug() << "Error loading face cascade";
    }
}

void cameraThread::closeCamera()
{
    cameraOpen = false;
}

void cameraThread::run()
{
    cameraOpen = true;
    QTimer timer;
    Mat image;
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        qDebug() << "摄像头打开失败";
    }
    while (cameraOpen) {
        faces.clear();
        cap >> image;
        faceCascade.detectMultiScale(image, faces);
        for (const auto& face : faces) {
            rectangle(image, face, Scalar(255, 0, 0), 2);
        }
        if (cameraOpen) {
            emit newImage(image, faces.size());
        } else
            break;
        timer.start(30);
    }
    cap.release();
    quit();
}
