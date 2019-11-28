//
// Created by Arche on 2019/11/27.
//

#include <cstring>

#include "tracer.h"
#include "include/Angel.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace nzk;
using namespace glm;
using namespace Angel;


using Color=vec3;
using Point=vec3;

unique_ptr<vec3> frame_base;
vec3 (*frame)[win_height][win_width];

Point eye_pos;

vector<unique_ptr<object>> scene;

Point L1;
vec3 I1;

vec3 Ia;

int depth_max = 1;

bool shadow_on = false;
bool reflection_on = false;
bool refraction_on = false;


constexpr int num_vertex = 6;

vec3 background_clr;
vec3 default_clr;

void scene1(){
    background_clr = {0.5, 0.5, 1};
    default_clr = {0, 0, 0};


    Ia = {0.2, 0.2, 0.2};

    eye_pos = {0.0, 0.0, 0.0};

    // set up light 1
    L1 = vec3(-7.0, 10.0, 1.0);
    I1 = vec3{1.0, 1.0, 1.0};


    // sphere 1
    Point sphere1_ctr = vec3(1.5, -1, -9);
    float sphere1_rad = 1.5;
    vec3 sphere1_kd = vec3(0, 1, 0.);
    vec3 sphere1_ks = vec3(1.0, 1.0, 1.0);
    float sphere1_q = 15;
    float sphere1_kr = 0;
    float sphere1_ni = 1.55;
    float sphere1_kt = 0;


    scene.emplace_back(new sphere(sphere1_kr,
                                  sphere1_kt,
                                  sphere1_kd,
                                  sphere1_ks,
                                  sphere1_q,
                                  sphere1_ctr,
                                  sphere1_rad,
                                  sphere1_ni)
    );


    // sphere 2
    Point sphere2_ctr = vec3(-1.5, 0.0, -7);
    float sphere2_rad = 1.5;
    vec3 sphere2_kd = vec3(0, 0.5, 0.5);
    vec3 sphere2_ks = vec3(1.0, 1.0, 1.0);
    float sphere2_q = 6;
    float sphere2_kr = 0;
    float sphere2_ni = 1.67;
    float sphere2_kt = 0;

    scene.emplace_back(new sphere{
            sphere2_kr,
            sphere2_kt,
            sphere2_kd,
            sphere2_ks,
            sphere2_q,
            sphere2_ctr,
            sphere2_rad,
            sphere2_ni}
    );

    // sphere 3
    Point sphere3_ctr = vec3(1, 2, -6);
    float sphere3_rad = 1;
//    vec3 sphere3_ambient = vec3(0.2, 0.2, 0.2);
    vec3 sphere3_kd = vec3(1, 1, 0);
    vec3 sphere3_ks = vec3(0, 0, 1);
    float sphere3_q = 40;
    float sphere3_kr = 0;
    float sphere3_ni = 2.1;
    float sphere3_kt = 0;

    scene.emplace_back(new sphere{
            sphere3_kr,
            sphere3_kt,
            sphere3_kd,
            sphere3_ks,
            sphere3_q,
            sphere3_ctr,
            sphere3_rad,
            sphere3_ni}
    );


    scene.emplace_back(new plane({0.0, -2.5, -15}, {0, 1, 0}, 20));
}

void scene2(){
    shadow_on=true;
    reflection_on= true;

    background_clr = {0.5, 0.5, 1};
    default_clr = {0, 0, 0};


    Ia = {0.2, 0.2, 0.2};

    eye_pos = {0.0, 0.0, 0.0};

    // set up light 1
    L1 = vec3(-7.0, 10.0, 1.0);
    I1 = vec3{1.0, 1.0, 1.0};


    // sphere 1
    Point sphere1_ctr = vec3(1.8, -1, -9);
    float sphere1_rad = 1.5;
    vec3 sphere1_kd = vec3(0, 0, 0);
    vec3 sphere1_ks = vec3(1.0, 1.0, 1.0);
    float sphere1_q = 60;
    float sphere1_kr = 0.8;
    float sphere1_ni = 1.55;
    float sphere1_kt = 0;


    scene.emplace_back(new sphere(sphere1_kr,
                                  sphere1_kt,
                                  sphere1_kd,
                                  sphere1_ks,
                                  sphere1_q,
                                  sphere1_ctr,
                                  sphere1_rad,
                                  sphere1_ni)
    );


    // sphere 2
    Point sphere2_ctr = vec3(-1.5, 0.0, -7);
    float sphere2_rad = 1.5;
    vec3 sphere2_kd = vec3(0.3, 0.3, 0);
    vec3 sphere2_ks = vec3(1.0, 1.0, 1.0);
    float sphere2_q = 60;
    float sphere2_kr = 0.6;
    float sphere2_ni = 1.67;
    float sphere2_kt = 0;

    scene.emplace_back(new sphere{
            sphere2_kr,
            sphere2_kt,
            sphere2_kd,
            sphere2_ks,
            sphere2_q,
            sphere2_ctr,
            sphere2_rad,
            sphere2_ni}
    );

    // sphere 3
    Point sphere3_ctr = vec3(1, 2, -6);
    float sphere3_rad = 1;
    vec3 sphere3_kd = vec3(1, 1, 0);
    vec3 sphere3_ks = vec3(0, 0, 1);
    float sphere3_q = 40;
    float sphere3_kr = 0.5;
    float sphere3_ni = 2.1;
    float sphere3_kt = 0;

    scene.emplace_back(new sphere{
            sphere3_kr,
            sphere3_kt,
            sphere3_kd,
            sphere3_ks,
            sphere3_q,
            sphere3_ctr,
            sphere3_rad,
            sphere3_ni}
    );


    scene.emplace_back(new plane({0.0, -2.5, -15}, {0, 1, 0}, 20));
}

void scene3(){
    refraction_on=true;

    background_clr = {0.5, 0.5, 1};
    default_clr = {0, 0, 0};


    Ia = {0.2, 0.2, 0.2};

    eye_pos = {0.0, 0.0, 0.0};

    // set up light 1
    L1 = vec3(-7.0, 10.0, 1.0);
    I1 = vec3{1.0, 1.0, 1.0};


    // sphere 1
    Point sphere1_ctr = vec3(1.8, -1, -14);
    float sphere1_rad = 1.5;
    vec3 sphere1_kd = vec3(0, 0, 0);
    vec3 sphere1_ks = vec3(1.0, 1.0, 1.0);
    float sphere1_q = 60;
    float sphere1_kr = 0.2;
    float sphere1_ni = 1.55;
    float sphere1_kt = 0.8;


    scene.emplace_back(new sphere(sphere1_kr,
                                  sphere1_kt,
                                  sphere1_kd,
                                  sphere1_ks,
                                  sphere1_q,
                                  sphere1_ctr,
                                  sphere1_rad,
                                  sphere1_ni)
    );


    // sphere 2
    Point sphere2_ctr = vec3(-1, 0.0, -8);
    float sphere2_rad = 1.5;
    vec3 sphere2_kd = vec3(0.1, 0.1, 0.1);
    vec3 sphere2_ks = vec3(1.0, 1.0, 1.0);
    float sphere2_q = 60;
    float sphere2_kr = 0.1;
    float sphere2_ni = 3;
    float sphere2_kt = 0.9;

    scene.emplace_back(new sphere{
            sphere2_kr,
            sphere2_kt,
            sphere2_kd,
            sphere2_ks,
            sphere2_q,
            sphere2_ctr,
            sphere2_rad,
            sphere2_ni}
    );

    // sphere 3
    Point sphere3_ctr = vec3(1, 1.5, -20);
    float sphere3_rad = 1;
    vec3 sphere3_kd = vec3(0.3, 0.3, 0.3);
    vec3 sphere3_ks = vec3(0, 0, 1);
    float sphere3_q = 40;
    float sphere3_kr = 0.1;
    float sphere3_ni = 2.1;
    float sphere3_kt = 0.7;

    scene.emplace_back(new sphere{
            sphere3_kr,
            sphere3_kt,
            sphere3_kd,
            sphere3_ks,
            sphere3_q,
            sphere3_ctr,
            sphere3_rad,
            sphere3_ni}
    );


    scene.emplace_back(new plane({0.0, -2.5, -15}, {0, 1, 0}, 20));
}

void scene4() {
    shadow_on = true;
    reflection_on = true;
    refraction_on = true;

    background_clr = {0.5, 0.5, 1};
    default_clr = {0, 0, 0};


    Ia = {0.2, 0.2, 0.2};

    eye_pos = {0.0, 0.0, 0.0};

    // set up light 1
    L1 = vec3(-10.0, 10.0, 1.0);
    I1 = vec3{1.0, 1.0, 1.0};


    // sphere 1
    Point sphere1_ctr = vec3(1.5, -1, -9);
    float sphere1_rad = 1.23;
    vec3 sphere1_kd = vec3(0.6, 0.6, 0.);
    vec3 sphere1_ks = vec3(1.0, 1.0, 1.0);
    float sphere1_q = 20;
    float sphere1_kr = 0.3;
    float sphere1_ni = 1.55;
    float sphere1_kt = 0;


    scene.emplace_back(new sphere(sphere1_kr,
                                  sphere1_kt,
                                  sphere1_kd,
                                  sphere1_ks,
                                  sphere1_q,
                                  sphere1_ctr,
                                  sphere1_rad,
                                  sphere1_ni)
    );


    // sphere 2
    Point sphere2_ctr = vec3(-1.5, -1, -8);
    float sphere2_rad = 1.5;
    vec3 sphere2_kd = vec3(0, 0, 0);
    vec3 sphere2_ks = vec3(1.0, 1.0, 1.0);
    float sphere2_q = 40;
    float sphere2_kr = 0.2;
    float sphere2_ni = 1.67;
    float sphere2_kt = 0.9;

    scene.emplace_back(new sphere{
            sphere2_kr,
            sphere2_kt,
            sphere2_kd,
            sphere2_ks,
            sphere2_q,
            sphere2_ctr,
            sphere2_rad,
            sphere2_ni}
    );

    // sphere 3
    Point sphere3_ctr = vec3(-0.5, 0, -15);
    float sphere3_rad = 0.5;
    vec3 sphere3_kd = vec3(0.0, 0.2, 0.05);
    vec3 sphere3_ks = vec3(0.0, 1.0, 0.0);
    float sphere3_q = 30;
    float sphere3_kr = 0.3;
    float sphere3_ni = 2.1;
    float sphere3_kt = 0.9;

    scene.emplace_back(new sphere{
            sphere3_kr,
            sphere3_kt,
            sphere3_kd,
            sphere3_ks,
            sphere3_q,
            sphere3_ctr,
            sphere3_rad,
            sphere3_ni}
    );


    scene.emplace_back(new plane({0.0, -2.5, -15}, {0, 1, 0}, 20));

}

void init() {
    vec4 points[num_vertex] = {
            {-1, -1, 0, 1}, //v1
            {1,  -1, 0, 1}, //v2
            {-1, 1,  0, 1}, //v3
            {-1, 1,  0, 1}, //v3
            {1,  -1, 0, 1}, //v2
            {1,  1,  0, 1}  //v4
    };

    // Texture coordinates
    vec2 tex_coords[num_vertex] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {0.0, 1.0},
            {0.0, 1.0},
            {1.0, 0.0},
            {1.0, 1.0}
    };

//    GLfloat newFrame[win_width][win_height][3];
//    for (int i = 0; i < WIN_WIDTH; ++i)
//    {
//        for (int j = 0; j < WIN_HEIGHT; ++j)
//        {
//            for (int k = 0; k < 3; ++k)
//            {
//                newFrame[i][j][k] = frame[i][j][k];
//            }
//        }
//    }

//    (*frame)[110][300]={1,0,0};


    // Initialize texture objects
    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, win_width, win_height, 0,
                 GL_RGB, GL_FLOAT, frame_base.get());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    vec4 borderColor{1, 1, 1, 1};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(borderColor));


    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(tex_coords), nullptr, GL_STATIC_DRAW);
//    GLintptr offset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
//    offset += sizeof(points);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(tex_coords), tex_coords);

    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // set up vertex arrays
//    offset = 0;
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                          (void *) (0));

//    offset += sizeof(points);
    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
                          (void *) (sizeof(points)));

    glUniform1i(glGetUniformLocation(program, "texture"), 0);

    glClearColor(1.0, 1.0, 1.0, 1.0);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);

    glDrawArrays(GL_TRIANGLES, 0, num_vertex);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
        case 'Q':
            exit(0);
            break;
        default:
            break;
    }
}


int main(int argc, char** argv ) {
    printf("please enter the depth to recursively trace (16 is enough):\n");
    scanf("%d",&depth_max);

    if(depth_max>40){
        depth_max=40;
    }

    int n;
    while (true){
        printf("please choose a scene (1-4):\n");
        scanf("%d",&n);
        if(n>0&&n<=4){
            break;
        }
    }
    switch (n){
        case 1:
            scene1();
            break;
        case 2:
            scene2();
            break;
        case 3:
            scene3();
            break;
        default:
            scene4();
            break;
    }
    printf("Rendering scene %d\npress q to exit\n",n);

    // initialize frame
    frame_base.reset(new vec3[win_width * win_height]);
    frame = reinterpret_cast<vec3 (*)[win_height][win_width]>(frame_base.get());



    auto rayTracer = make_unique<tracer>(
            *frame, scene, background_clr, default_clr, eye_pos, L1, I1, Ia,
            depth_max, shadow_on, reflection_on, refraction_on
    );


    rayTracer->trace(depth_max);


    // Show the result in glut via texture mapping
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("My Tracer");
    glewInit();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}