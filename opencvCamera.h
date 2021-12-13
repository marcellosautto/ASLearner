#pragma once
#define BOOST_PYTHON_STATIC_LIB
#define BOOST_LIB_NAME "boost_numpy35"
#include "pch.h"
#include "TextManager.h"

using namespace cv;
namespace py = boost::python;
namespace np = boost::python::numpy;

class opencvCamera {
public:
	opencvCamera();
	~opencvCamera();
	void updateCamera(sf::RenderWindow& _window);
	char getInput();
	void getInputCon();
	
private:
	sf::Sprite videoSprite;
	sf::Image videoImg;
	sf::Texture videoTexture;
	cv::VideoCapture capture; //used to capture frames from camera
	cv::Mat frame, frameInv;// Variable for storing video frames
	int camera_device, num_frames;

	PyObject* pFunc, * pFuncMain, * pValue, * pModule, *pDict, *pArgs;
	PyObject* pImgFunc, * pImgValue, * pImgDict, * pImgArgs;

	np::ndarray ConvertMatToNDArray(const cv::Mat& mat);
	cv::Mat ConvertNDArrayToMat(const np::ndarray& ndarr);
};