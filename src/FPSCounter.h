/**
 * @file FPSCounter.h
 * @brief Timer class used to track the rendering time of one frame.
 * @author Samuel Gauthier
 */
#ifndef INCLUDED_FPSCOUNTER
#define INCLUDED_FPSCOUNTER

/**
 * @brief Time tracker
 */
class FPSCounter {

    public:
        /**
         * @brief Default constructor
         */
        FPSCounter();
        /**
         * @brief Default destructor
         */
        ~FPSCounter();
        /**
         * @brief Update the timer and prints the time used to render the frame.
         */
        void update();
        /**
         * @brief Get the current time
         *
         * @return The current time
         */
        double getCurrentTime();
        

    private:
        double lastTime;
        double currentTime;
        int nbrFrames;
};

#endif /* ifndef INCLUDED_FPSCOUNTER */
