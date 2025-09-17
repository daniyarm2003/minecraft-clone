#include "game_time_tracker.h"

namespace Utils {
    void GameTimeTracker::update(double time) {
        this->lastTime = this->isInitialized ? this->curTime : time;
        this->curTime = time;
        this->isInitialized = true;
    }

    double GameTimeTracker::getDeltaTime() const {
        double dt = this->curTime - this->lastTime;
        return dt != 0.0 ? dt : DEFAULT_DELTA_TIME;
    }

    double GameTimeTracker::getLastCheckTime() const {
        return this->curTime;
    }
}