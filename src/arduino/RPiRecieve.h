#ifndef PI_RECIEVE_H
#define RPI_RECIEVE_H


        void rpiInit();

        void rpiRead();

        bool foundCross();
        bool foundGoal();
        double goalGetDistance();
        double goalGetAzimuth();
        double goalGetAltitude();
        double crossGetDistance();
        double crossGetAzimuth();
        double crossGetAltitude();

   

#endif // RPI_RECIEVE_H
