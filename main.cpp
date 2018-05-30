#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

#include "vec3.h"
#include "ray.h"
#include "simplex.h"

int main(){
    freopen("input.in", "r", stdin);

    vector <simplex> simplices;
    int nsimplices;

    scanf("%d", &nsimplices);
    for(int i = 0; i < nsimplices; i++){
        simplex s;
        for(int j = 0; j < 3; j++){
            for(int k = 0; k < 3; k++){
                scanf("%lf", &s.p[j].c[k]);
            }
        }
        for(int k = 0; k < 3; k++){
            scanf("%lf", &s.color.c[k]);
        }
        simplices.push_back(s);
    }

    freopen("image.ppm", "w", stdout);
    printf("P3\n");

    int n = 401, m = 201;
    printf("%d %d\n255\n", n, m);

    for(int i = m - 1; i >= 0; i--)
    for(int j = 0; j < n; j++){
        //vec3 frame(-cos(PI * j / n) * sin(PI * i / m), cos(PI * i / m), sin(PI * j / n) * sin(PI * i / m) + 2);
        vec3 frame(2.0 * j / n - 1, 2.0 * i / m - 1, -0.5);
        vec3 camera(0, 0, -1);
        ray r(camera, frame - camera);

        bool found_intersection = false;
        double min_t = 100000000;
        vec3 color(135, 206, 235);

        for(int k = 0; k < nsimplices; k++){
            double t;
            if(intersect(simplices[k], r, t)){
                found_intersection = true;
                if(t < min_t){
                    min_t = t;
                    color = simplices[k].color;
                }
            }
        }
        printf("%d %d %d\n", (int)color.c[0], (int)color.c[1], (int)color.c[2]);
    }

    return 0;
}
