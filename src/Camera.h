#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include <glm/glm.hpp>

class Camera {

    public:
        Camera(float theta=0.0, float phi=0.0, float radius=0.0,
                glm::vec3 target=glm::vec3(0.0, 0.0, 0.0));
        Camera(float x, float y, float z);
        ~Camera();
        void rotate(float dTheta, float dPhi);
        void zoom(float distance);
        void pan(float dx, float dy);
        
        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
        glm::vec3 toCartesian();
        glm::vec3 toSpherical(float x, float y, float z);

        

    private:
        float theta;
        float phi;
        float radius;
        glm::vec3 target;
        glm::mat4 projection;
        glm::mat4 view;
        bool viewNeedsUpdate;

        void updateViewMatrix();

        /* data */
};

#endif /* ifndef INCLUDED_CAMERA */
