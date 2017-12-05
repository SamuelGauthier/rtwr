#ifndef INCLUDED_FPSCOUNTER
#define INCLUDED_FPSCOUNTER

class FPSCounter {

    public:
        FPSCounter();
        ~FPSCounter();
        void update();
        double getCurrentTime();
        

    private:
        double lastTime;
        double currentTime;
        int nbrFrames;
};

#endif /* ifndef INCLUDED_FPSCOUNTER */
