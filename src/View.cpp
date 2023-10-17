#include "View.h"

#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include <math.h>

View::View() {

}

View::~View(){

}

View::View (View &t) {
    std::cout << "VIEW COPY CONSTRUCTOR CALLED" << std::endl;
}

bool View::shouldWindowClose() {
    return glfwWindowShouldClose(window);
}

void View::closeWindow() {
    for (map<string,util::ObjectInstance *>::iterator it=objects.begin();
           it!=objects.end();
           it++) {
          it->second->cleanup();
          delete it->second;
    } 
    glfwDestroyWindow(window);

    glfwTerminate();
}

void View::reshape(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);

    // last few point is for the z axis (something very close to something very far)
    projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);
}

void View::initObjects(map<string,util::PolygonMesh<VertexAttrib>>& meshes) {
    /*
        In the mesh we have attributes for each vertex. In the shader, 
        we have variables for each vertex attribute. We need to create a 
        connection between attribute name in the mesh and corresponding
        shader variable name.
    */
    map<string, string> shaderVarsToVertexAttribs;
    // currently there are only two per-vertex attribute: position and color
    shaderVarsToVertexAttribs["vPosition"] = "position";
    shaderVarsToVertexAttribs["vNormal"] = "normal";

    // meshes needs to be iterated like this because it is a map
    // create an ObjectInstance for each mesh by passing in the name and polygon mesh (stored in meshes map)
    for (typename map<string,util::PolygonMesh<VertexAttrib> >::iterator it=meshes.begin();
           it!=meshes.end();
           it++) {
        util::ObjectInstance * obj = new util::ObjectInstance(it->first);
        obj->initPolygonMesh(shaderLocations,shaderVarsToVertexAttribs,it->second);
        objects[it->first] = obj; // ObjectInstance stored in map
    }
}

void View::init(Callbacks* callbacks,map<string,util::PolygonMesh<VertexAttrib>>& meshes, map<string,MeshObject>& in_meshObjects, bool debugger, glm::vec3 camPos, glm::vec3 camTarget) {
    meshObjects = std::move(in_meshObjects);
    std::cout << "in View init()" << std::endl;
    std::cout << "meshObjects size: " << meshObjects.size() << std::endl;
    for (auto i : meshObjects) {
        std::cout << "new object: " << i.first << std::endl;
        i.second.printTriangles();
    }
    // This function initializes the GLFW library because before GLFW functions can be used, GLFW must be initialized
    if (!glfwInit())
        exit(EXIT_FAILURE);

    // ... 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Setup window and terminate the program if this is not successful
    window = glfwCreateWindow(800,800, "Raytracer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowUserPointer(window, (void *)callbacks); // set pointer of window to this

    //using C++ functions as callbacks to a C-style library
    // callback to onkey() method
    glfwSetKeyCallback(window, 
    [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        static_cast<Callbacks*>(glfwGetWindowUserPointer(window))->onkey(key,scancode,action,mods);
    });

    // callback to reshape() method
    glfwSetWindowSizeCallback(window, 
    [](GLFWwindow* window, int width,int height)
    {
        static_cast<View*>(glfwGetWindowUserPointer(window))->reshape(window,width,height);
    });

    // ...
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // create shader program with a vertex and fragment shader 
    if (debugger) {
        // using debugger
        program.createProgram(string("shaders/phong-multiple.vert"),
                        string("shaders/phong-multiple.frag"));
    }
    else {
        // using terminal
        program.createProgram(string("src/shaders/phong-multiple.vert"),
                          string("src/shaders/phong-multiple.frag"));
    }

    //program.enable(); // set this program to be in use
    shaderLocations = program.getAllShaderVariables();

    initObjects(meshes);

    int window_width,window_height;
    // gets the size of framebuffer of the window and stores it in 2nd and 3rd parameter
    // removes need to store window dimensions separately
    glfwGetFramebufferSize(window,&window_width,&window_height); 

    // CAN UNCOMMENT THIS IF YOU WANT ORTHOGRAPHIC INSTEAD OF PERSPECTIVE PROJECTION
    // projection = glm::ortho(-400.0f,400.0f,-400.0f,400.0f,0.1f,10000.0f);

    // perspective projection - makes objects farther away appear smaller 
    // 60 degrees is how much you can see (if you don't move your head)
    // next parameter: aspect vision - aspect ratio of dimension to make sure window doesn't distort
    projection = glm::perspective(cameraFOV, (float) window_width/window_height,
            0.1f, // near distance
            10000.0f); // far distance

    //prepare the projection matrix for orthographic projection
	glViewport(0, 0, window_width, window_height);

    renderer = new GLScenegraphRenderer(modelview, objects, shaderLocations);
    cameraPosition = camPos;
    cameraTarget = camTarget;

    frames = 0;
    time = glfwGetTime();
}

void View::initShaderVariables(vector<util::Light>& lights) {
    for (int i = 0; i < lights.size(); i++) {
    LightLocation ll;
    stringstream name;

    name << "light[" << i << "]";
    ll.ambient = shaderLocations.getLocation(name.str() + ".ambient");
    ll.diffuse = shaderLocations.getLocation(name.str() + ".diffuse");
    ll.specular = shaderLocations.getLocation(name.str() + ".specular");
    ll.position = shaderLocations.getLocation(name.str() + ".position");
    lightLocations.push_back(ll);
    }
}

void View::display(IScenegraph *scenegraph) {
    program.enable();
    glClearColor(1, 1, 1, 1); // set background color to white

    //clear the background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //send projection matrix to GPU    
    glUniformMatrix4fv(shaderLocations.getLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    while (!modelview.empty()) {
        modelview.pop();
    }

    modelview.push(glm::mat4(1.0));

    modelview.top() = modelview.top() * getLookAtMatrix();
      
    //draw scene graph here
    scenegraph->getRoot()->accept(renderer);
    
    vector<util::Light> sceneLights = renderer->getLights();

    initShaderVariables(sceneLights);

    for (int i = 0; i < sceneLights.size(); i++) {
        glm::vec4 pos = sceneLights[i].getPosition();
        glUniform4fv(lightLocations[i].position, 1, glm::value_ptr(pos));
    }

    //pass light color properties to shader
    glUniform1i(shaderLocations.getLocation("numLights"),sceneLights.size());

    //pass light colors to the shader
    for (int i = 0; i < sceneLights.size(); i++) {
        glUniform3fv(lightLocations[i].ambient, 1, glm::value_ptr(sceneLights[i].getAmbient()));
        glUniform3fv(lightLocations[i].diffuse, 1, glm::value_ptr(sceneLights[i].getDiffuse()));
        glUniform3fv(lightLocations[i].specular, 1,glm::value_ptr(sceneLights[i].getSpecular()));
    }

    renderer->clearLights();
    renderer->clearLightCollections();

    modelview.pop();
    glFlush();
    program.disable();

    glfwSwapBuffers(window);
    glfwPollEvents();
    frames++;
    double currenttime = glfwGetTime();
    if ((currenttime-time)>1.0) {
        printf("Framerate: %2.0f\r",frames/(currenttime-time));
        frames = 0;
        time = currenttime;
    }
}

void View::raytrace(bool debugging,IScenegraph *scenegraph) {
    ofstream out;
    if (debugging) {
        out.open("images/out.ppm");
    }
    else {
        out.open("src/images/out.ppm");
    }
    out << "P3" << std::endl;
    out << WIDTH << " " << HEIGHT << std::endl;
    out << "255" << std::endl;

    for (int hh = 0; hh < HEIGHT; hh++) {
        for (int ww = 0; ww < WIDTH; ww++) {
            std::cout << "(" << hh << "," << ww << ")" << std::endl;

            float dx = (float)ww - (0.5f * WIDTH);
            float dy =  (0.5f * HEIGHT) - (float)hh ;
            float dz = -(0.5f * HEIGHT) / tan(cameraFOV/2);

            // ray origin and direction (s,v)
            glm::vec4 origin(0.0f, 0.0f, 0.0f, 1.0f);
            glm::vec4 direction(dx, dy, dz, 0.0f);

            while (!raytracer_modelview.empty()) {
                raytracer_modelview.pop();
            }

            raytracer_modelview.push(glm::mat4(1.0));
            spdlog::debug("modelview top: " + glm::to_string(raytracer_modelview.top()));
            spdlog::debug("lookat: " + glm::to_string(getLookAtMatrix()));
            raytracer_modelview.top() = raytracer_modelview.top() * getLookAtMatrix();
            raytracerRenderer = new RaytracerRenderer(raytracer_modelview,origin,direction);
            spdlog::debug( "modelview top * lookat: " + glm::to_string(raytracer_modelview.top()));
            spdlog::debug("origin: " + glm::to_string(origin));
            spdlog::debug("direction: " + glm::to_string(direction));
            scenegraph->getRoot()->accept(raytracerRenderer); 

            HitRecord& hitRecord = dynamic_cast<RaytracerRenderer *>(raytracerRenderer)->getHitRecord();

            std::cout << "(" << hh << "," << ww << "): time: " << hitRecord.t << std::endl;

            if (isinf(hitRecord.t)) {
                out << "255 255 255" << endl;
            }
            else {
                util::Material* mat = hitRecord.object_mat;
                vector<util::Light> sceneLights = raytracerRenderer->getLights();
                vector<vector<util::Light>> lightCellCollections = raytracerRenderer->getLightCollections();
                glm::vec4 color = getColor(hitRecord, lightCellCollections, scenegraph, direction, 0, 0) * 255.0f;
                raytracerRenderer->clearLights();
                raytracerRenderer->clearLightCollections();
                while (!refractiveIndexStack.empty()) {
                    refractiveIndexStack.pop();
                }
                out << clipValue(color.x) << " " <<  clipValue(color.y) << " " <<  clipValue(color.z) << endl; 
            }

            spdlog::debug("----");
            std::cout << "------------------" << std::endl;
        }
    }
    std::cout << "Completed raytracing!" << std::endl;
}

// RGB values are between 0 and 1
glm::vec4 View::getColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection,int reflectiveBounces, int refractiveBounces) {
    float a = hitRecord.object_mat->getAbsorption();
    float r = hitRecord.object_mat->getReflection();
    float t = hitRecord.object_mat->getTransparency();
    spdlog::debug("material absorption: (int)" + (int) a);
    spdlog::debug("material reflection: (int)" + (int) r);
    spdlog::debug("material transparency: (int)" + (int) t);

    glm::vec4 absorption = glm::vec4(0,0,0,0);
    if (a > 0) {
        absorption = hitRecord.object_mat->getAbsorption() * getAbsorptionColor(hitRecord,sceneLightCollections,scenegraph);
    }

    glm::vec4 reflection = glm::vec4(0,0,0,0);
    spdlog::debug("reflective bounces: " + reflectiveBounces);
    if (r > 0) {
        if (reflectiveBounces < 5)  {
            reflection = r * getReflectionColor(hitRecord,sceneLightCollections,scenegraph,rayDirection,reflectiveBounces,refractiveBounces);
        }
        else {
            reflection = glm::vec4(1,1,1,0);
        }
    }

    spdlog::debug("refractive bounces: " + refractiveBounces);
    glm::vec4 transparency = glm::vec4(0,0,0,0);
    if (t > 0) {
        if (refractiveBounces <= 5) {
            transparency = t * getTransparencyColor(hitRecord,sceneLightCollections,scenegraph,rayDirection,reflectiveBounces,refractiveBounces);
        }
        else {
            transparency = reflection;
        }
    }

    glm::vec4 color = absorption + reflection + transparency;
    glm::vec4 textureColor = hitRecord.textureImage->getColor(hitRecord.textureCoordinates.x, hitRecord.textureCoordinates.y);
    glm::vec4 colorWithTexture = color * glm::vec4(textureColor.x/255, textureColor.y/255, textureColor.z/255, textureColor.w/255);

    spdlog::debug("color: " + glm::to_string(color));
    spdlog::debug("textureColor: " + glm::to_string(textureColor));
    spdlog::debug("colorWithTexture: " + glm::to_string(colorWithTexture));

    return colorWithTexture;
}

glm::vec4 View::getAbsorptionColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph) {
    spdlog::debug("in getAbsorptionColor()");
    glm::vec3 outColor(0,0,0);
    glm::vec3 lightVec;
    glm::vec4 fPosition = hitRecord.intersection_position;
    glm::vec3 ambient,diffuse,specular;
    util::Material* mat = hitRecord.object_mat;
    glm::vec4 fNormal = hitRecord.intersection_normal;
    glm::vec4 tNormal = fNormal;
    glm::vec3 normalView = normalize(tNormal);
    glm::vec3 viewVec = - fPosition;
    viewVec = glm::normalize(viewVec);

    spdlog::debug("sceneLightCollections size: " + sceneLightCollections.size());

    for (int i = 0; i < sceneLightCollections.size(); i++) {

        // this is the light in the bottom left corner that other cells in the light are generated from
        util::Light mainLight = sceneLightCollections[i][0]; 
        spdlog::debug("mainLight: " + glm::to_string(mainLight.getPosition())); 

        if (mainLight.getPosition().w != 0) {
            std::cout << "W IS 1" << std::endl;
            // this is the vector from the light position to the point of intersection
            lightVec = glm::normalize(mainLight.getPosition() - fPosition);
        }
        else {
            std::cout << "W IS 0" << std::endl;
            lightVec = glm::normalize(- mainLight.getPosition());
        }

        glm::vec3 direction = glm::normalize(mainLight.getPosition() - fPosition);
        glm::vec3 spotDir = glm::normalize(-mainLight.getSpotDirection());
        float lDotSpotDir = glm::dot(direction,spotDir);
        float spotCutOff = mainLight.getSpotCutoff();
        spdlog::debug("direction" + glm::to_string(direction));
        spdlog::debug("spotDir" + glm::to_string(spotDir));
        spdlog::debug("lDotSpotDir: (int) " + (int) acos(lDotSpotDir));
        spdlog::debug("spotCutOff: (int)" + (int) spotCutOff);

        float keepLighting = true;

        if (spotCutOff != 0.0f) {
            if (acos(lDotSpotDir) <= spotCutOff) {
                spdlog::debug("In spotlight");
            }
            else {
                spdlog::debug("out of spotlight, in darkness");
                keepLighting = false;
            }
        }

        if (keepLighting) {
    
            // nDotL is the dot product of the normal vector and the light vector 
            // nDotL = normal vector * light vector * angle between normal and light vector
            float nDotL = glm::dot(normalView,lightVec);

            /* glm::reflect calculates angle of reflection. -lightVec gives the vector of 
            point of intersection - light position. glm::reflect uses this formula - 
            result = I - 2.0 * dot(N, I) * N - where N is normal and I is -lightVec */
            glm::vec3 reflectVec = glm::reflect(-lightVec,normalView);
            reflectVec = glm::normalize(reflectVec);

            spdlog::debug("fPosition: " + glm::to_string(fPosition)); 
            spdlog::debug("viewVec: " + glm::to_string(viewVec));
            spdlog::debug("reflectVec: " + glm::to_string(reflectVec));

            /* A 1x3 * 1x3 matrix can give a 1x3 matrix or a single value. We avoid the single value  
            by multiplying the vectors together to give a 1x3 vector. If we wanted the single value, 
            we could take glm::dot of the two vectors */
            ambient = glm::vec3(mat->getAmbient()) * mainLight.getAmbient();

            float shadowIntensity;
            float lightIntensity;

            spdlog::debug("shadow Intensity = (int)" + (int) shadowIntensity);

            lightIntensity = 1.0f;

            if (!inShadow(hitRecord, mainLight,scenegraph)) {
                lightIntensity = 1.0f;
            }
            else {
                shadowIntensity = getShadowIntensity(hitRecord,sceneLightCollections[i],scenegraph);
                lightIntensity = 1.0f - shadowIntensity;
            }

            /* nDotL is greater > 0 only if angle between normal and light vector is between 
            0° and 90° and between 270° and 360°. This ensures that the light direction is coming in 
            front of point of intersection and not behind point of intersection. If behind, diffuse becomes 0
            (multiplied by 0). Otherwise, diffuse is calculated to it's full amount (multiplied by 1). It also 
            does not matter if lightVec is lightPosition - fPosition or fPosition - lightPosition because the dot 
            product of either is the same because the cos of the angle between both vectors is the same. */
            diffuse = lightIntensity * glm::vec3(mat->getDiffuse()) * mainLight.getDiffuse() * std::max(nDotL,0.0f);

            // fPosition vector = 0 - pointOfIntersection 
            // viewVec is the vector = pointOfIntersection - 0 in direction of the camera (from viewer's location)
            /* the logic behind calculating rDotV is that when the reflected vector and viewVec are pointing 
            in the same direction and angle between them = 0°, the light should be brightest. When the vectors are pointed
            opposite to each other and angle between them is closer to 180°, light should be reflected the least. 
            This is best represented by the cos graph. If the angle is between 180° and 270°, there should be no 
            lighting (specular) */
            float rDotV = std::max(dot(reflectVec,viewVec),0.0f);

            /* check to make sure that light is coming in front of object and not behind (rDotV > 0 includes light 
            coming from behind the object */
            if (nDotL > 0) {
                // The closer the viewVec and reflectVec, the higher the value of rDotV, the higher the specular value
                specular = lightIntensity * glm::vec3(mat->getSpecular()) * mainLight.getSpecular() * pow(rDotV,mat->getShininess());
            }
            else {
                specular = glm::vec3(0,0,0);
            }

            outColor = outColor + ambient + diffuse + specular;
            spdlog::debug("light #" + i);
            spdlog::debug("light ambient: " + glm::to_string(ambient));
            spdlog::debug("light diffuse: " + glm::to_string(diffuse));
            spdlog::debug("light specular: " + glm::to_string(specular));
            spdlog::debug("light outColor: " + glm::to_string(outColor));
        }
        
    }

    outColor = outColor;

    spdlog::debug("outColor: " + glm::to_string(outColor));

    return glm::vec4(outColor.x, outColor.y, outColor.z, 0);
}

glm::vec4 View::getReflectionColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection, int reflectiveBounces, int refractiveBounces) {
    spdlog::debug("in getReflectionColor()");
    
    glm::vec4 relectedRayOrigin = hitRecord.intersection_position;
    glm::vec4 incidentRay = normalize(rayDirection);
    spdlog::debug("incidentRay: " + glm::to_string(incidentRay));
    glm::vec4 reflectedRay = glm::reflect(incidentRay,normalize(hitRecord.intersection_normal));
    relectedRayOrigin = relectedRayOrigin + (reflectedRay * 0.001f);
    reflectedRay = glm::normalize(reflectedRay);

    while (!reflection_modelview.empty()) {
        reflection_modelview.pop();
    }

    spdlog::debug("hitRecord.intersectionPoint: " + glm::to_string(hitRecord.intersection_position));
    spdlog::debug("hitRecord.intersection_normal: " + glm::to_string(hitRecord.intersection_normal));

    spdlog::debug("relectedRayOrigin: " + glm::to_string(relectedRayOrigin));
    spdlog::debug("reflectedRay: " + glm::to_string(reflectedRay));

    reflection_modelview.push(glm::mat4(1.0));
    reflection_modelview.top() = reflection_modelview.top() * getLookAtMatrix();
    reflectionVisitor = new RaytracerRenderer(reflection_modelview,relectedRayOrigin,reflectedRay);
    scenegraph->getRoot()->accept(reflectionVisitor); 

    HitRecord& reflectedHitRecord = dynamic_cast<RaytracerRenderer *>(reflectionVisitor)->getHitRecord();

    if (isinf(reflectedHitRecord.t)) {
        spdlog::debug("reflected ray hit background");
        return glm::vec4(1,1,1,0);
    }
    else {
        util::Material* mat = reflectedHitRecord.object_mat;
        vector<util::Light> sceneLights = reflectionVisitor->getLights();
        vector<vector<util::Light>> lightCellCollections = reflectionVisitor->getLightCollections();
        glm::vec4 color = getColor(reflectedHitRecord, lightCellCollections, scenegraph, reflectedRay, reflectiveBounces+1,refractiveBounces);

        reflectionVisitor->clearLights();
        reflectionVisitor->clearLightCollections();
        spdlog::debug("reflected ray hit something. color: " + glm::to_string(color));
        return color;
    }
}

glm::vec4 View::getTransparencyColor(HitRecord hitRecord, vector<vector<util::Light>> sceneLightCollections, IScenegraph* scenegraph, glm::vec4 rayDirection, int reflectiveBounces, int refractiveBounces) {
    spdlog::debug("in getTransparencyColor()");
    float refractiveIndex;
    glm::vec4 normal;
    spdlog::debug("leaf name: " + hitRecord.instanceName);
    if (refractiveIndexStack.size() == 0) {
        spdlog::debug("object_mat RI: (int)" + (int) hitRecord.object_mat->getRefractiveIndex());
        refractiveIndex = 1.0f / hitRecord.object_mat->getRefractiveIndex(); // if size == 0, the ray is coming from air into material
        refractiveIndexStack.push(hitRecord.object_mat->getRefractiveIndex());
        normal = normalize(hitRecord.intersection_normal);
    }
    else {
        spdlog::debug("refractiveIndexStack.top(): (int)" + (int) refractiveIndexStack.top());

        if (hitRecord.object_mat->getRefractiveIndex() == refractiveIndexStack.top()) {
            refractiveIndexStack.pop();
            if (refractiveIndexStack.size() == 0) {
                refractiveIndex = hitRecord.object_mat->getRefractiveIndex() / 1.0f; 
            }
            else {
                refractiveIndex = hitRecord.object_mat->getRefractiveIndex() / refractiveIndexStack.top(); 
            }
            normal = -1.0f * normalize(hitRecord.intersection_normal);
        }
        else {
            refractiveIndex = refractiveIndexStack.top() / hitRecord.object_mat->getRefractiveIndex(); 
            refractiveIndexStack.push(hitRecord.object_mat->getRefractiveIndex());
            normal = normalize(hitRecord.intersection_normal);
        }
        
    }
    spdlog::debug("size of refractiveIndexStack: " + refractiveIndexStack.size());
    spdlog::debug("refractiveIndex: (int)" + (int) refractiveIndex);

    glm::vec4 incidentRay = normalize(rayDirection);
   
    glm::vec4 perpR = refractiveIndex * (incidentRay - (glm::dot(normal,incidentRay) * normal));
    spdlog::debug("incidentRay: " + glm::to_string(incidentRay));
    spdlog::debug("normal: " + glm::to_string(normal));
    spdlog::debug("glm::dot(normal,incidentRay): " + (int) glm::dot(normal,incidentRay));
    spdlog::debug("normal: " + glm::to_string(normal));
    spdlog::debug("perpR: " + glm::to_string(perpR));

    float cosThetaI = -1.0f * glm::dot(normal,incidentRay);
    float sinThetaI = sqrt(1 - pow(cosThetaI,2));
    float sinThetaT = refractiveIndex * sinThetaI;
    float cosThetaT = sqrt(1 - pow(sinThetaT,2));
    glm::vec4 parallelR = cosThetaT * normal;
    spdlog::debug("cosThetaI: (int)" + (int) cosThetaI);
    spdlog::debug("sinThetaI: (int)" + (int) sinThetaI);
    spdlog::debug("sinThetaT: (int)" + (int) sinThetaT);
    spdlog::debug("cosThetaT: (int)" + (int) cosThetaT);
    spdlog::debug("parallelR: (int)" + glm::to_string(parallelR));

    glm::vec4 T = perpR - parallelR;

    spdlog::debug("intersection point: " + glm::to_string(hitRecord.intersection_position));
    spdlog::debug("T: " + glm::to_string(T));

    while (!transparency_modelview.empty()) {
        transparency_modelview.pop();
    }

    transparency_modelview.push(glm::mat4(1.0));
    transparency_modelview.top() = transparency_modelview.top() * getLookAtMatrix();
    glm::vec4 newOrigin = hitRecord.intersection_position + (T * 0.001f);
    transparencyVisitor = new RaytracerRenderer(transparency_modelview,newOrigin,T);
    scenegraph->getRoot()->accept(transparencyVisitor); 

    HitRecord& transparencyHitRecord = dynamic_cast<RaytracerRenderer *>(transparencyVisitor)->getHitRecord();

    if (isinf(transparencyHitRecord.t)) {
        spdlog::debug("refracted ray hit background");
        return glm::vec4(1,1,1,0);
    }
    else {
        util::Material* mat = transparencyHitRecord.object_mat;
        vector<util::Light> sceneLights = transparencyVisitor->getLights();
        vector<vector<util::Light>> lightCellCollections = transparencyVisitor->getLightCollections();
        glm::vec4 color = getColor(transparencyHitRecord, lightCellCollections, scenegraph, T, reflectiveBounces, refractiveBounces+1);

        transparencyVisitor->clearLights();
        transparencyVisitor->clearLightCollections();
        return color;
    }

}

bool View::inShadow(HitRecord hitRecord, util::Light light,IScenegraph* scenegraph) {
    // ray origin and direction (s,v) from intersectionPoint to light
    glm::vec4 origin(hitRecord.intersection_position.x, hitRecord.intersection_position.y, hitRecord.intersection_position.z, 1.0f);
    glm::vec4 direction = (light.getPosition() - origin);
    origin = origin + (direction * 0.001f);

    stack<glm::mat4> inShadow_modelview;
    inShadow_modelview.push(glm::mat4(1.0));
    inShadow_modelview.top() = inShadow_modelview.top() * getLookAtMatrix();
    SGNodeVisitor *inShadowVisitor = new RaytracerRenderer(inShadow_modelview,origin,direction);
    scenegraph->getRoot()->accept(inShadowVisitor); 

    HitRecord& otherHitRecord = dynamic_cast<RaytracerRenderer *>(inShadowVisitor)->getHitRecord();

    if (otherHitRecord.t < hitRecord.t) {
        spdlog::debug("in shadow");
        return true;
    }
    else {
        spdlog::debug("not in shadow");
        return false;
    }
}

float View::getShadowIntensity(HitRecord hitRecord, vector<util::Light> lightCollection, IScenegraph* scenegraph) {
    float total = 1.0f; // accounts for main light so that is not processed again

    spdlog::debug("lightCollection size: " + lightCollection.size());

    for (int i = 1; i < lightCollection.size(); i++) {
        spdlog::debug("light " + i);
        glm::vec4 origin(hitRecord.intersection_position.x, hitRecord.intersection_position.y, hitRecord.intersection_position.z, 1.0f);
        spdlog::debug("light position: " + glm::to_string(lightCollection[i].getPosition()));
        glm::vec4 direction = (lightCollection[i].getPosition() - origin);
        origin = origin + (direction * 0.001f);

        stack<glm::mat4> inShadow_modelview;
        inShadow_modelview.push(glm::mat4(1.0));
        inShadow_modelview.top() = inShadow_modelview.top() * getLookAtMatrix();
        SGNodeVisitor *inShadowVisitor = new RaytracerRenderer(inShadow_modelview,origin,direction);
        scenegraph->getRoot()->accept(inShadowVisitor); 

        HitRecord& otherHitRecord = dynamic_cast<RaytracerRenderer *>(inShadowVisitor)->getHitRecord();

        if (otherHitRecord.t < hitRecord.t) {
            spdlog::debug("in shadow");
            total = total + (1.0f * (1 - otherHitRecord.object_mat->getTransparency()));
        }
        else {
            spdlog::debug("not in shadow");
        }
    }

    float avg = total / lightCollection.size();
    return avg;
}

int View::clipValue(int val) {
    if (val > 255) {
        return 255;
    }
    else if (val < 0) {
        return 0;
    }
    else {
        return val;
    }
}

glm::highp_mat4 View::getLookAtMatrix() {
    return glm::lookAt(cameraPosition,cameraTarget,glm::vec3(0.0f,1.0f,0.0f));
}

void View::error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void View::dispose(GLFWwindow* window)
{
    closeWindow();
}