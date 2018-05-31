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

                /*
                if(min_distance < 100000000){
                    min_distance = min(sqrt(min_distance), 3.0);
                    color.c[0] = (min_distance + 2) / 5.0 * color.c[0];
                    color.c[1] = (min_distance + 2) / 5.0 * color.c[1];
                    color.c[2] = (min_distance + 2) / 5.0 * color.c[2];
                }
                */
                scolor += color;
            }
            scolor /= 4;
            printf("%d %d %d\n", (int)scolor.c[0], (int)scolor.c[1], (int)scolor.c[2]);
        }
    }

    int make_parallelepiped(vec3 corner, vec3 x, vec3 y, vec3 z, vec3 color){
        physicalObject a;

        simplex s1(corner, corner + x, corner + y); s1.color = color;
        simplex s1_(corner + x + y, corner + x, corner + y); s1_.color = color;
        a.simplices.push_back(s1);
        a.simplices.push_back(s1_);

        simplex s2(corner, corner + x, corner + z); s2.color = color;
        simplex s2_(corner + x + z, corner + x, corner + z); s2_.color = color;
        a.simplices.push_back(s2);
        a.simplices.push_back(s2_);

        simplex s3(corner, corner + y, corner + z); s3.color = color;
        simplex s3_(corner + y + z, corner + y, corner + z); s3_.color = color;

        a.simplices.push_back(s3);
        a.simplices.push_back(s3_);

        simplex _s1(z + corner, z + corner + x, z + corner + y); _s1.color = color;
        simplex _s1_(z + corner + x + y, z + corner + x, z + corner + y); _s1_.color = color;
        a.simplices.push_back(_s1);
        a.simplices.push_back(_s1_);

        simplex _s2(y + corner, y + corner + x, y + corner + z); _s2.color = color;
        simplex _s2_(y + corner + x + z, y + corner + x, y + corner + z); _s2_.color = color;
        a.simplices.push_back(_s2);
        a.simplices.push_back(_s2_);

        simplex _s3(x + corner, x + corner + y, x + corner + z); _s3.color = color;
        simplex _s3_(x + corner + y + z, x + corner + y, x + corner + z); _s3_.color = color;
        a.simplices.push_back(_s3);
        a.simplices.push_back(_s3_);

        universe.push_back(a);
        return (int)universe.size() - 1;
    }
};
