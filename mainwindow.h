#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "camerathread.h"
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QVector>
#include <opencv2\face.hpp>
#include <opencv2\opencv.hpp>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void takeImgShow();
    void recognizeImgShow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void do_newImage(cv::Mat img, int num);
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow* ui;
    cameraThread* threadCamera;
    std::vector<cv::Mat> images;
    std::vector<int> trainLabels;
    cv::Mat matImage;
    QVector<QLabel*> uiLabels;
    int personNO_ = 1;
    int personNum = 0;
    std::map<int, std::string> Names;
    cv::Ptr<cv::face::LBPHFaceRecognizer> recognizer;
    bool isTakeImgShow = true;

protected:
    void closeEvent(QCloseEvent* event) override;
};
#endif // MAINWINDOW_H
