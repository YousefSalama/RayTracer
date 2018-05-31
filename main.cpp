#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "vec3.h"
#include "matrix.h"
#include "ray.h"
#include "simplex.h"
#include "camera.h"
#include "physicalObject.h"
#include "sandbox.h"

int main(){
    freopen("input.in", "r", stdin);

    freopen("image.ppm", "w", stdout);
    printf("P3\n");

    camera c(vec3(0, 2, -1), vec3(-1, 3, -0.5), vec3(0, -2, 0), vec3(2, 0, 0));
    sandbox s;

    int id = s.make_parallelepiped(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(200, 0, 0));
    s.universe[id].translate(vec3(0.5, 0.5, 0.5));

    int id2 = s.make_parallelepiped(vec3(0, 1, 0), vec3(1, 0, 0), vec3(0, 0, 1), vec3(0, 200, 0));
    s.universe[id2].translate(vec3(0, 0, 2));
    s.universe[id2].rotateAroundYAxis(vec3(0, 0, 0), 45.0 / 180.0 * PI);

    int id3 = s.make_parallelepiped(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(0, 0, 200));
    s.universe[id3].translate(vec3(0, 2, 1));
    s.universe[id3].rotateAroundZAxis(vec3(0, 2, 1), 30.0 / 180.0 * PI);
    s.universe[id3].rotateAroundXAxis(vec3(0, 2, -1), 30.0 / 180.0 * PI);

    s.render(400, 200, c);

    return 0;
}
