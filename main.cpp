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

    int n = 400, m = 200;
    printf("%d %d\n255\n", n, m);

    for(int i = m - 1; i >= 0; i--)
    for(int j = 0; j < n; j++){
        vec3 scolor;
        for(int di = 0; di <= 1; di++)
        for(int dj = 0; dj <= 1; dj++){
            vec3 frame(2.0 * (j + dj) / n - 1, 2.0 * (i + di) / m - 1, -0.5);
            vec3 camera(0, 0, -1);
            ray r(camera, frame - camera);

            bool found_intersection = false;
            double min_distance = 100000000;
            vec3 color(135, 206, 235);

            for(int k = 0; k < nsimplices; k++){
                vec3 p;
                if(intersect(simplices[k], r, p)){
                    found_intersection = true;

                    double cur_distance = dot(p - r.starting_point, p - r.starting_point);
                    if(cur_distance < min_distance){
                        min_distance = cur_distance;
                        color = simplices[k].color;
                    }
                }
            }
            min_distance = min(sqrt(min_distance), 10.0);
            color.c[0] = (min_distance + 10) / 20 * color.c[0];
            color.c[1] = (min_distance + 10) / 20 * color.c[1];
            color.c[2] = (min_distance + 10) / 20 * color.c[2];
            scolor += color;
        }
        scolor /= 4;
        printf("%d %d %d\n", (int)scolor.c[0], (int)scolor.c[1], (int)scolor.c[2]);
    }

    return 0;
}
