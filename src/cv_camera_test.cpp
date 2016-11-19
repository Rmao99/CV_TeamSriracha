#include "VideoDevice.hpp"
#include "AppConfig.hpp"
#include "CmdLineInterface.hpp"
using namespace cv;
int main(int argc, char* argv[])
{

	VideoDevice camera;
	CmdLineInterface interface(argc, argv);
	AppConfig config = interface.getConfig();
	if(config.getIsDevice())
	{
		camera.startCapture(config.getDeviceID());
	}
	if(config.getIsDebug())
	{
		std::cout << "Camera is read";
	}
	
	namedWindow("Live Video Feed", cv::WINDOW_NORMAL);
	Mat img;
	//while(cv::waitKey(30) != 27)
	while(true)
	{
		img = camera.getImage();	
		imshow("Live Video Feed", img);
		waitKey(0);
	}	
}
