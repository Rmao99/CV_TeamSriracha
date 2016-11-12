#include "VideoDevice.hpp"

int main(int argc, char* argv[])
{

	VideoDevice camera;
	
	if(config.getIsDevice())
	{
		camera.startCapture(config.getDeviceID());
	}

}
