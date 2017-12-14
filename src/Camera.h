#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA

#include <glm/glm.hpp>

class Camera {

    public:
        Camera(float theta=0.0, float phi=0.0, float radius=0.0,
                glm::vec3 target);
        ~Camera();
        

    private:
        float theta;
        float phi;
        float radius;
        glm::vec3 target;
        glm::mat4 projection;
        glm::mat4 view;


        /* data */
};

#endif /* ifndef INCLUDED_CAMERA */
