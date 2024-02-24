#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2\face.hpp>
using namespace cv;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mat image = imread("D:/image/test.jpg", 3);
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);
    qDebug() << "test";
}

MainWindow::~MainWindow()
{
    delete ui;
}
