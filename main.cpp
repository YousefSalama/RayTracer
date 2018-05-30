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
        for(int j = 0; j < 3; j++)
        for(int k = 0; k < 3; k++)
            scanf("%lf", &s.p[j].c[k]);
        simplices.push_back(s);
    }

    freopen("image.ppm", "w", stdout);
    printf("P3\n");

    int n = 201, m = 100;
    printf("%d %d\n255\n", n, m);

    for(int i = 0; i < m; i++)
    for(int j = 0; j < n; j++){
        vec3 frame(1.0 * (j - n / 2) / (n / 2), 1.0 * (m - i - 1) / m, -4);
        vec3 camera(0, 0, -5);
        ray r(camera, frame - camera);

        bool found_intersection = false;
        for(int k = 0; k < nsimplices; k++){
            vec3 p;
            if(intersect(simplices[k], r, p))found_intersection = true;
        }

        if(found_intersection){
            printf("%d %d %d\n", 255, 0, 0);
        }else{
            printf("%d %d %d\n", 255, 255, 255);
        }
    }

    return 0;
}
