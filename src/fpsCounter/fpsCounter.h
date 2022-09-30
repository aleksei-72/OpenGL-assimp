#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <ctime>
struct FpsCounter
{
    clock_t frameStart;

    unsigned int countOfFrames = 8;

    unsigned int frameIdx = 0;

    int *frames;

    void init(clock_t startTime)
    {
        frameStart = startTime;
        frames = new int [countOfFrames];
    }

    void frameEnd(clock_t endTime)
    {
        frameIdx ++;

        if(frameIdx == countOfFrames)
            frameIdx = 0;

        frames[frameIdx] = endTime - frameStart;

        frameStart = endTime;
    }

    float getCurrentFrameTime()
    {
        float frameTime = 0.f;

        for(unsigned int i = 0; i < countOfFrames; i ++)
        {
            frameTime += frames[i];
        }

        frameTime /= (float) countOfFrames;
        frameTime /= (float) CLOCKS_PER_SEC;
        frameTime *= 1000.0;

        return frameTime;
    }
};
#endif // FPS_COUNTER_H
