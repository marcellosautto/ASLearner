#pragma once

//Define
#define PROG_NAME "Gazer_Eyes"
#define NOMINMAX

//OpenCV Lib
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/imgcodecs.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/video.hpp>
#include "opencv2/videoio.hpp"
#include <opencv2/core/cvstd.hpp>

//SFML Lib
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>

//Python Lib
#include <Python.h>
#include <boost/python/numpy.hpp>
#include <boost/python.hpp>
#include <numpy/arrayobject.h>

//C++ Lib Required for Python

//C++ Lib
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;
using namespace filesystem;

//Global Commands
#ifndef GUARD_H
#define GUARD_H

void errorMessageExit(string message);
void message(string message, string title);
struct fCOORD { float X = 0, Y = 0; };

#endif 