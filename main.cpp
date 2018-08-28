#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <thread>
#include <chrono>
using namespace std;

#include "vec3.h"
#include "matrix.h"
#include "ray.h"
#include "simplex.h"
#include "camera.h"
#include "physicalObject.h"
#include "lightSource.h"
#include "sandbox.h"

int main(){
    ofstream img;
    img.open("image.ppm");

    camera c(vec3(0, 2, -1), vec3(-2, 3, -0.5), vec3(0, -2, 0), vec3(4, 0, 0));
    c.translate(vec3(0, 0, -1));
    c.rotateAroundXAxis(vec3(0, 0, 0), -30.0 / 180.0 * PI);
    c.rotateAroundYAxis(vec3(0, 0, 0), 30.0 / 180.0 * PI);

    sandbox s;

    int id = s.make_parallelepiped(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(200, 0, 0), false);
    s.objects[id].translate(vec3(0.8, 0.0, 0.5));

    int id2 = s.make_parallelepiped(vec3(0, 0, 0), vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), vec3(0, 200, 0), false);
    s.objects[id2].translate(vec3(0, 0, 2));
    s.objects[id2].rotateAroundYAxis(vec3(0, 0, 0), 45.0 / 180.0 * PI);

    int id3 = s.make_parallelepiped(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(0, 0, 200), false);
    s.objects[id3].translate(vec3(0, 2, 1));
    s.objects[id3].rotateAroundZAxis(vec3(0, 2, 1), 30.0 / 180.0 * PI);
    s.objects[id3].rotateAroundXAxis(vec3(0, 2, -1), 30.0 / 180.0 * PI);

    int id4 = s.make_parallelepiped(vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 0.5), vec3(200, 200, 0), false);
    s.objects[id4].translate(vec3(-0.5, 0, 0));

    int id5 = s.make_quadrilateral(vec3(-10000, 0, -10000), vec3(-10000, 0, 10000), vec3(10000, 0, 10000), vec3(10000, 0, -10000),
                                   vec3(228, 228, 228), false);

    int id6 = s.make_quadrilateral(vec3(-6, 0, 4.2), vec3(-6, 6, 4.2), vec3(6, 6, 4.2), vec3(6, 0, 4.2), vec3(0, 0, 0),
                                   false);
    int id7 = s.make_quadrilateral(vec3(-5, 0.2, 4), vec3(-5, 5, 4), vec3(5, 5, 4), vec3(5, 0.2, 4), vec3(255, 255, 255),
                                   true);

    int id8 = s.make_quadrilateral(vec3(-6, 0, -4.2), vec3(-6, 6, -4.2), vec3(6, 6, -4.2), vec3(6, 0, -4.2), vec3(0, 0, 0),
                                   false);
    int id9 = s.make_quadrilateral(vec3(-5, 0.2, -4), vec3(-5, 5, -4), vec3(5, 5, -4), vec3(5, 0.2, -4), vec3(255, 255, 255),
                                   true);

    s.add_light_source(vec3(1.0, 0.7, 0.2), 0.2);
    s.add_light_source(vec3(-0.5, 2, 1), 2.0);

    auto start = std::chrono::steady_clock::now();
    cout << "Rendering Start" << endl;

    s.render(BUFFER_HEIGHT, BUFFER_WIDTH, c);

    img << "P3" << endl;
    img << BUFFER_WIDTH << ' ' << BUFFER_HEIGHT << endl << 255 << endl;

    for(int i = 0; i < BUFFER_HEIGHT; i++)
    for(int j = 0; j < BUFFER_WIDTH; j++)
        img << (int)buffer[i][j].c[0] << ' ' << (int)buffer[i][j].c[1] << ' ' << (int)buffer[i][j].c[2] << endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    cout << "Rendering End. Duration: " << (duration).count() << endl;

    return 0;
}
