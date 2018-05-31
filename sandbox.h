class sandbox{
public:
    vector <physicalObject> universe;
    void render(int n, int m, camera &c){
        printf("%d %d\n255\n", n, m);

        for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            vec3 scolor;
            for(int di = 0; di <= 1; di++)
            for(int dj = 0; dj <= 1; dj++){
                ray r = c.generateRay(1.0 * (i + di) / m, 1.0 * (j + dj) / n);

                double min_distance = 100000000;
                vec3 color(135, 206, 235);

                for(int k = 0; k < universe.size(); k++)
                for(int f = 0; f < universe[k].simplices.size(); f++){
                    vec3 p;
                    if(intersect(universe[k].simplices[f], r, p)){
                        double cur_distance = dot(p - r.starting_point, p - r.starting_point);
                        if(cur_distance < min_distance){
                            min_distance = cur_distance;
                            color = universe[k].simplices[f].color;
                        }
                    }
                }
                min_distance = min(sqrt(min_distance), 5.0);
                color.c[0] = (min_distance + 5) / 10 * color.c[0];
                color.c[1] = (min_distance + 5) / 10 * color.c[1];
                color.c[2] = (min_distance + 5) / 10 * color.c[2];
                scolor += color;
            }
            scolor /= 4;
            printf("%d %d %d\n", (int)scolor.c[0], (int)scolor.c[1], (int)scolor.c[2]);
        }
    }

    int make_parallelepiped(vec3 x, vec3 y, vec3 z, vec3 color){
        vec3 origin(0, 0, 0);
        physicalObject a;

        simplex s1(origin, origin + x, origin + y); s1.color = color;
        simplex s1_(origin + x + y, origin + x, origin + y); s1_.color = color;
        a.simplices.push_back(s1);
        a.simplices.push_back(s1_);

        simplex s2(origin, origin + x, origin + z); s2.color = color;
        simplex s2_(origin + x + z, origin + x, origin + z); s2_.color = color;
        a.simplices.push_back(s2);
        a.simplices.push_back(s2_);

        simplex s3(origin, origin + y, origin + z); s3.color = color;
        simplex s3_(origin + y + z, origin + y, origin + z); s3_.color = color;

        a.simplices.push_back(s3);
        a.simplices.push_back(s3_);

        simplex _s1(z + origin, z + origin + x, z + origin + y); _s1.color = color;
        simplex _s1_(z + origin + x + y, z + origin + x, z + origin + y); _s1.color = color;
        a.simplices.push_back(_s1);
        a.simplices.push_back(_s1_);

        simplex _s2(y + origin, y + origin + x, y + origin + z); _s2.color = color;
        simplex _s2_(y + origin + x + z, y + origin + x, y + origin + z); _s2_.color = color;
        a.simplices.push_back(_s2);
        a.simplices.push_back(_s2_);

        simplex _s3(x + origin, x + origin + y, x + origin + z); _s3.color = color;
        simplex _s3_(x + origin + y + z, x + origin + y, x + origin + z); _s3_.color = color;
        a.simplices.push_back(_s3);
        a.simplices.push_back(_s3_);

        universe.push_back(a);
        return (int)universe.size() - 1;
    }
};
