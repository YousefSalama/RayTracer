#include <stdio.h>
using namespace std;

#include "vec3.h"

int main(){
    vec3 v(1, 1, 0, 1);
    vec3 w(0, 1, 0, 1);
    printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);
    printf("%f %f %f\n", cross(v, w).x, cross(v, w).y, cross(v, w).z);
    printf("%f\n", dot(v, w));

    freopen("image.ppm", "w", stdout);
    printf("P3\n");

    int n = 200, m = 100;
    printf("%d %d\n255\n", n, m);

    for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++){
        printf("%d %d %d\n", (int)(255.0 * i / m), (int)(255.0 * j / n), (int)(255.0 * 0.2));
    }

    return 0;
}
