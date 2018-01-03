#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include <glm/glm.hpp>

class Camera {

    public:
        Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up,
                glm::mat4 projection);
        ~Camera();
        void rotate(float dTheta, float dPhi);
        void zoom(float distance);
        void pan(float dx, float dy);
        
        glm::mat4 getProjectionMatrix();
        glm::mat4 getViewMatrix();
        glm::vec3 toCartesian();
        static glm::vec3 toSpherical(float x, float y, float z,
                glm::vec3 center);
        static glm::vec3 toSpherical(glm::vec3 cartesian, glm::vec3 center);

        

    private:
        float theta;
        float phi;
        float radius;
        glm::vec3 position;
        glm::vec3 target;
        glm::vec3 up;
        glm::mat4 projection;
        glm::mat4 view;
        bool viewNeedsUpdate;

        void updateViewMatrix();

        /* data */
};

#endif /* ifndef INCLUDED_CAMERA */
