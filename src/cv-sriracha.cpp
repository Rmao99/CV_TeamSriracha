#include <opencv2/opencv.hpp>
#include <boost/lexical_cast.hpp>

#include "CmdLineInterface.hpp"
#include "AppConfig.hpp"
#include "Target.hpp"
#include "TargetDetector.hpp"
#include "TargetProcessor.hpp"
#include "NetworkController.hpp"
#include "VideoDevice.hpp"

int main(int argc, char* argv[])
{

	TargetDetector detectorCross;
	TargetDetector detectorHighGoal;
	TargetProcessor processor;
	NetworkController networkController;
  VideoDevice camera;
	CmdLineInterface interface(argc, argv);
	AppConfig config = interface.getConfig();

	if(config.getIsDevice())
	{
		camera.startCapture(config.getDeviceID());
		if(config.getIsDebug())
		std::cout << "Camera is ready\n";
	}

    if(config.getIsNetworking())
        networkController.startServer();

    cv::Mat image;

    int loop = 1;
    cv::namedWindow("Live Video Feed", cv::WINDOW_NORMAL);
    cv::namedWindow("General", cv::WINDOW_NORMAL);

    while(cv::waitKey(30) != 27)
    {
			cv::Mat background(Size(1000,1000), CV_8UC1, Scalar(255, 255, 255 ));

	        if(config.getIsDebug())
	            std::cout << "While Loop #" << loop << std::endl;

			if(config.getIsNetworking())
	      	networkController.waitForPing();

			image = camera.getImage();

			if(!image.data) // check if image is valid
	        {
	            if(config.getIsDebug())
	                std::cout << "failed to read image" << std::endl;
	            return -1;
	        }

	        if(config.getIsDebug())
	            std::cout << "Image Read" << std::endl;
	        Target* targetC = new Target(detectorCross.getTarget(image, 12));
					//Detects an image of cross with 12
					Target* targetS =  new Target(detectorHighGoal.getTarget(image, 4));
					//Detects an image of the high goal with 4 corners

	        if(config.getIsDebug())
	            std::cout << "Image Processed by Target Detector" << std::endl;

	        bool foundCross = false;

	        if ((*targetC).m_contour.size() != 0)
	        {
	            foundCross = true;
	        }

					bool foundHighGoal = false;
	        if ((*targetS).m_contour.size() != 0)
	        {
	            foundHighGoal = true;
	        }

			std::cout <<"About to check the value of foundTarget" << std::endl;
	        if(foundCross)
	        {


	            std::cout <<"Cross was found " << std::endl;

	            if(config.getIsDebug())
	                std::cout << "Image Being Processed" << std::endl;

	            processor.loadTarget(targetC, 35);
							// 56 should be changed to the object's real width

	            if(config.getIsDebug())
	                std::cout << "Target Loaded" << std::endl;

	            double distance = processor.calcDistance();

	            if(config.getIsDebug())
	                std::cout << "Distance Calculated" << std::endl;

				double azimuth = processor.calcAzimuthX();
	            if(config.getIsDebug())
	                std::cout << "Azimuth Calculated" << std::endl;

				double altitude = processor.calcAzimuthY();
	            if(config.getIsDebug())
	                std::cout << "Altitude Calculated" << std::endl;

	            if(config.getIsDebug())
	                std::cout << "Image Processed by TargetProcessor" << std::endl;

	                std::string dis = "distance: " + std::to_string(distance);
	                std::string alt = "altitude: " + std::to_string(altitude);
	                std::string azi = "azimuth: " + std::to_string(azimuth);

	                cv::putText(background, dis, cv::Point(50,100),
	                cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
	                1);

	                cv::putText(background, alt, cv::Point(50,200),
	                cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
	                1);

	                cv::putText(background, azi, cv::Point(50,400),
	                cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
	                1);

	                imshow("General", background);

	                if (config.getIsNetworking())
				    {
			            networkController.sendMessage("true;" +
			            boost::lexical_cast<std::string> (distance) + ";" +
						boost::lexical_cast<std::string> (azimuth) + ";" +
						boost::lexical_cast<std::string> (altitude));
				}

				if(config.getIsDebug()){
	            	std::cout << "Target Found! Distance: " << distance;
	                std::cout << "Altitude: " << altitude << std::endl;
	                std::cout << "Azimuth: " << azimuth << std::endl;
	            }

	        }
	        else
	        {
	            if (config.getIsNetworking())
	                networkController.sendMessage("false;");
	        }

					if(foundHighGoal)
					{


							std::cout <<"High goal was found " << std::endl;

							if(config.getIsDebug())
									std::cout << "Image Being Processed" << std::endl;

							processor.loadTarget(targetS, 41.5);
							// 56 should be changed to object's real width

							if(config.getIsDebug())
									std::cout << "Target Loaded" << std::endl;

							double distance = processor.calcDistance();

							if(config.getIsDebug())
									std::cout << "Distance Calculated" << std::endl;

				double azimuth = processor.calcAzimuthX();
							if(config.getIsDebug())
									std::cout << "Azimuth Calculated" << std::endl;

				double altitude = processor.calcAzimuthY();
							if(config.getIsDebug())
									std::cout << "Altitude Calculated" << std::endl;

							if(config.getIsDebug())
									std::cout << "Image Processed by TargetProcessor" << std::endl;

									std::string dis = "distance: " + std::to_string(distance);
									std::string alt = "altitude: " + std::to_string(altitude);
									std::string azi = "azimuth: " + std::to_string(azimuth);

									cv::putText(background, dis, cv::Point(50,100),
									cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
									1);

									cv::putText(background, alt, cv::Point(50,200),
									cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
									1);

									cv::putText(background, azi, cv::Point(50,400),
									cv::FONT_HERSHEY_COMPLEX_SMALL, 2, cv::Scalar(0, 255, 0),
									1);

									imshow("General", background);

						      if (config.getIsNetworking())
						{
									networkController.sendMessage("true;" +
									boost::lexical_cast<std::string> (distance) + ";" +
						boost::lexical_cast<std::string> (azimuth) + ";" +
						boost::lexical_cast<std::string> (altitude));
				}

				if(config.getIsDebug()){
								std::cout << "Target Found! Distance: " << distance;
									std::cout << "Altitude: " << altitude << std::endl;
									std::cout << "Azimuth: " << azimuth << std::endl;
							}

					}
					else
					{
							if (config.getIsNetworking())
									networkController.sendMessage("false;");
					}




	        imshow("Live Video Feed", image);


	        loop++;
	        delete targetC;
					delete targetS;
    }

    return 0;
}
