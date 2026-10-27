#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) { 
        const sf::Vector2f windowCenter = mWindowSize * 0.5f;
        sf::Vector2f windowOffset = pWindow - windowCenter;
        windowOffset *= mWorldUnitsPerPixel;

        return mViewCenterWorld + windowOffset; 
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) { 
        const sf::Vector2f windowCenter = mWindowSize * 0.5f;
        sf::Vector2f worldOffset = pWorld - mViewCenterWorld;
        worldOffset /= mWorldUnitsPerPixel;

        return windowCenter + worldOffset; 
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) { 
        const sf::Vector2f windowCenter = mWindowSize * 0.5f;
        sf::Vector2f windowOffset = mWindowSize * pWindowPercent - windowCenter;
        windowOffset *= mWorldUnitsPerPixel;

        return mViewCenterWorld + windowOffset; 
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) { 
        const sf::Vector2f windowCenter = mWindowSize * 0.5f;
        sf::Vector2f worldOffset = pWorld - mViewCenterWorld;
        worldOffset /= mWorldUnitsPerPixel;
    
        return (windowCenter + worldOffset) / mWindowSize; 
    };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        mViewCenterWorld += deltaWorld;
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        mViewCenterWorld += deltaScreen * mWorldUnitsPerPixel;
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        mViewCenterWorld += deltaScreenPercent * mWindowSize * mWorldUnitsPerPixel;
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        sf::Vector2f currWorld = windowToWorld(pWindow);
        translateWorld(pWorld - currWorld);
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        sf::Vector2f currWorld = windowPercentToWorld(pWindowPercent);
        translateWorld(pWorld - currWorld);
    };

    void setCameraCenter(const sf::Vector2f& pWorld) {
        mViewCenterWorld = pWorld;
    };

    sf::Vector2f getCameraCenter() const { 
        return mViewCenterWorld; 
    };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
