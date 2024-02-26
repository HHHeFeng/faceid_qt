#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H
// #include <QMutex>
#include <QThread>
#include <atomic>
#include <opencv2/face.hpp>
class cameraThread : public QThread {
    Q_OBJECT
public:
    cameraThread();
    void closeCamera();

protected:
    void run();
    // QMutex mutex;
signals:
    void newImage(cv::Mat img, int num);

private:
    std::atomic<bool> cameraOpen = true;
    QString path = "D:\\opencv\\opencv-4.9.0\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
    cv::CascadeClassifier faceCascade;
    std::vector<cv::Rect> faces;
};

#endif // CAMERATHREAD_H
