#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCloseEvent>
#include <QMessageBox>

using namespace cv;
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    threadCamera = new cameraThread;
    connect(threadCamera, &cameraThread::newImage, this, &MainWindow::do_newImage);
}

MainWindow::~MainWindow()
{

    delete ui;
    if (threadCamera != NULL) {
        delete threadCamera;
        threadCamera = NULL;
    }
    for (QLabel* label : uiLabels) {
        delete label;
    }
    uiLabels.clear();
}
void MainWindow::do_newImage(Mat img, int num)
{
    personNum = num;
    matImage = img;
    if (isTakeImgShow)
        takeImgShow();
    else
        recognizeImgShow();
}
void MainWindow::takeImgShow()
{
    QImage image(matImage.data, matImage.cols, matImage.rows, matImage.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    QCoreApplication::processEvents();
}
void MainWindow::recognizeImgShow()
{
    std::string str;
    Mat grayImage;
    cvtColor(matImage, grayImage, cv::COLOR_BGR2GRAY);
    int predictedLabel;
    double confidence;
    recognizer->predict(grayImage, predictedLabel, confidence);
    // qDebug() << predictedLabel;
    // for (auto it = Names.begin(); it != Names.end(); ++it) {
    //     qDebug() << "Key: " << it->first << ", Value: " << it->second;
    // }
    qDebug() << confidence;
    if (confidence < 40) {
        std::map<int, std::string>::iterator iter = Names.find(predictedLabel);
        str = iter->second + std::to_string(predictedLabel);
    } else
        str = "None";

    Point textOrg(10, matImage.rows - 10);
    putText(matImage, str, textOrg, FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
    QImage image(matImage.data, matImage.cols, matImage.rows, matImage.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    QCoreApplication::processEvents();
}
void MainWindow::on_pushButton_clicked()
{
    threadCamera->start();
    ui->lineEdit->setEnabled(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    threadCamera->closeCamera();
    QImage img;
    ui->label->setPixmap(QPixmap::fromImage(img.rgbSwapped()));
    QCoreApplication::processEvents();
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    threadCamera->closeCamera();
    threadCamera->wait();
    event->accept();
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->lineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "input warning", "name is empty");
        return;
    }
    if (personNum == 0) {
        QMessageBox::warning(this, "iamge warning", "nothing,please try agian");
        return;
    }
    QImage image(matImage.data, matImage.cols, matImage.rows, matImage.step, QImage::Format_RGB888);
    QLabel* label = new QLabel;
    label->setFixedSize(260, 195);
    uiLabels.append(label);
    label->setPixmap(QPixmap::fromImage(image.rgbSwapped()));
    label->setScaledContents(true);
    ui->verticalLayout_3->addWidget(label);
    ui->verticalLayout_3->addStretch(1);

    Mat grayImage;
    cvtColor(matImage, grayImage, cv::COLOR_BGR2GRAY);
    images.push_back(grayImage);
    trainLabels.push_back(personNO_);
    Names[personNO_] = ui->lineEdit->text().toStdString();
    qDebug() << personNO_ << Names[personNO_];
    ui->lineEdit->setEnabled(false);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
}

void MainWindow::on_pushButton_6_clicked()
{
    personNO_++;
    ui->lineEdit->setEnabled(true);
    for (QLabel* label : uiLabels) {
        delete label;
    }
    uiLabels.clear();
}

void MainWindow::on_pushButton_7_clicked()
{
    personNO_++;
    on_pushButton_2_clicked();
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_7->setEnabled(false);
    for (QLabel* label : uiLabels) {
        delete label;
    }
    uiLabels.clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    recognizer = face::LBPHFaceRecognizer::create(1, 8, 8, 8, 200);
    recognizer->train(images, trainLabels);
    recognizer->write("face_model.yml");
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(true);
}

void MainWindow::on_pushButton_4_clicked()
{
    isTakeImgShow = false;
    on_pushButton_clicked();
    ui->pushButton_8->setEnabled(true);
    ui->pushButton_4->setEnabled(false);
}

void MainWindow::on_pushButton_8_clicked()
{
    isTakeImgShow = true;
    Names.clear();
    images.clear();
    trainLabels.clear();
}
