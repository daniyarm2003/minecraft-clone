#ifndef GAME_TIME_TRACKER_H
#define GAME_TIME_TRACKER_H

namespace Utils {
    class GameTimeTracker {
    public:
        void update(double time);

        double getDeltaTime() const;
        double getLastCheckTime() const;

    private:
        static constexpr double DEFAULT_DELTA_TIME = 1.0 / 60.0;

        bool isInitialized = false;
        
        double lastTime = 0.0;
        double curTime = 0.0;
    };
}

#endif // GAME_TIME_TRACKER_H