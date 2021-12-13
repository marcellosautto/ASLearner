#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define BOOST_PYTHON_STATIC_LIB
#define BOOST_LIB_NAME "boost_numpy35"
#include "pch.h"
#include "opencvCamera.h"

namespace py = boost::python;
namespace np = boost::python::numpy;

opencvCamera::opencvCamera()
{
	camera_device = 0; //0 -> primary camera device on computer
	num_frames = 60;// Number of frames to capture
	cv::Mat testFrame;

	//clear frame
	testFrame = cv::Mat::zeros(640, 480, CV_8UC3);

	//test if camera is present
	capture.open(camera_device);
	capture.grab();

	if (!capture.retrieve(testFrame, 0))
		errorMessageExit("No Camera Connected");

	Py_Initialize();
	np::initialize();
	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append(\".\")");

	pModule = PyImport_ImportModule("asl");
	pImgFunc = PyObject_GetAttrString(pModule, "get_detection_frame");
	pFunc = PyObject_GetAttrString(pModule, "get_detection_char");


}

opencvCamera::~opencvCamera() {
	Py_DECREF(pModule);
}

void opencvCamera::updateCamera(sf::RenderWindow& _window)
{
	capture.read(frame);

	/*
	//Draw video camera
	cv::Mat convMat;
	cv::Mat cloneImg = frame.clone();
	np::ndarray ndImg = ConvertMatToNDArray(cloneImg);

	pImgArgs = PyTuple_New(1);
	PyTuple_SetItem(pImgArgs, 0, ndImg.ptr());

	if (PyCallable_Check(pImgFunc))
	{
		pImgValue = PyObject_CallObject(pImgFunc, pImgArgs);
		//PyArrayObject *pyArray = reinterpret_cast<PyArrayObject*>(pImgValue);
		//printf_s("C: get_detection_char() = %ld\n", _PyLong_AsInt(pValue));
		//cInput = _PyLong_AsInt(pValue) + 97;
		//uchar* data = (uchar*)PyByteArray_AsString(pImgValue);
		//assert(PyArray_NDIM(pyArray) == 3 && PyArray_SHAPE(pyArray)[2] == 3);
		//int rows = PyArray_SHAPE(pyArray)[0];
		//int cols = PyArray_SHAPE(pyArray)[1];
		//void* frame_data = PyArray_DATA(pyArray);
		//cv::Mat img(rows, cols, CV_8UC3, frame_data);
		//frame = img;
		//return char(cInput);
		Py_XDECREF(pImgValue);
	}
	else
	{
		cout << "Function is not callable !" << endl;
	}

	Py_DECREF(pImgFunc);
	*/
	cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
	videoImg.create(frame.cols, frame.rows, frame.ptr());
	
	if (!videoTexture.loadFromImage(videoImg))
		errorMessageExit("ERROR: texture failed to load");
	videoSprite.setPosition(1350, 275);
	videoSprite.setTexture(videoTexture);
	_window.draw(videoSprite);
}

np::ndarray opencvCamera::ConvertMatToNDArray(const cv::Mat& mat) {
	py::tuple shape = py::make_tuple(mat.rows, mat.cols, mat.channels());
	py::tuple stride = py::make_tuple(mat.channels() * mat.cols * sizeof(uchar), mat.channels() * sizeof(uchar), sizeof(uchar));
	np::dtype dt = np::dtype::get_builtin<uchar>();
	np::ndarray ndImg = np::from_data(mat.data, dt, shape, stride, py::object());

	return ndImg;
}

cv::Mat opencvCamera::ConvertNDArrayToMat(const np::ndarray& ndarr) {
	//int length = ndarr.get_nd(); // get_nd() returns num of dimensions. this is used as a length, but we don't need to use in this case. because we know that image has 3 dimensions.
	const Py_intptr_t* shape = ndarr.get_shape(); // get_shape() returns Py_intptr_t* which we can get the size of n-th dimension of the ndarray.
	char* dtype_str = py::extract<char*>(py::str(ndarr.get_dtype()));

	// variables for creating Mat object
	int rows = shape[0];
	int cols = shape[1];
	int channel = shape[2];
	int depth;

	// you should find proper type for c++. in this case we use 'CV_8UC3' image, so we need to create 'uchar' type Mat.
	if (!strcmp(dtype_str, "uint8")) {
		depth = CV_8U;
	}
	else {
		std::cout << "wrong dtype error" << std::endl;
		return cv::Mat();
	}

	int type = CV_MAKETYPE(depth, channel); // CV_8UC3

	cv::Mat mat = cv::Mat(rows, cols, type);
	memcpy(mat.data, ndarr.get_data(), sizeof(uchar) * rows * cols * channel);

	return mat;
}

char opencvCamera::getInput()
{
	int cInput = 0;

	capture.read(frame);

	cv::Mat cloneImg = frame.clone();
	np::ndarray ndImg = ConvertMatToNDArray(cloneImg);

	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, ndImg.ptr());

	if (PyCallable_Check(pFunc))
	{
		pValue = PyObject_CallObject(pFunc, pArgs);
		printf_s("C: get_detection_char() = %ld\n", _PyLong_AsInt(pValue));
		cInput = _PyLong_AsInt(pValue) + 97;

		cout << "The letter you entered was " << char(cInput) << endl;
		return char(cInput);
		Py_XDECREF(pValue);
	}
	else
	{
		cout << "Function is not callable !" << endl;
	}

	Py_DECREF(pFunc);
	
	return ' ';
}


void opencvCamera::getInputCon()
{
	int cInput = 0;

	capture.read(frame);

	cv::Mat cloneImg = frame.clone(); // converting functions will access to same data between Mat and NDArray. so we should clone Mat object. This may important in your case.
	np::ndarray ndImg = ConvertMatToNDArray(cloneImg);

	pArgs = PyTuple_New(1);
	PyTuple_SetItem(pArgs, 0, ndImg.ptr());

	if (PyCallable_Check(pFunc))
	{
		try {
			pValue = PyObject_CallObject(pFunc, pArgs);
		}
		catch (py::error_already_set& e) {
			PyErr_Clear();
		}
	}
		
		
		//printf_s("C: get_detection_char() = %ld\n", _PyLong_AsInt(pValue));
		//cInput = _PyLong_AsInt(pValue) + 97;
		//cout << "The letter you entered was " << char(cInput) << endl;
		//return char(cInput);
		//Py_XDECREF(pValue);
	//}
	//else
	//{
	//	cout << "Function is not callable !" << endl;
	//}

	//Py_DECREF(pFunc);

	//return ' ';
}


