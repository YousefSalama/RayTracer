class sandbox{
public:
    vector <physicalObject> objects;
    vector <lightSource> lightSources;

    void render(int n, int m, camera &c){
        printf("%d %d\n255\n", n, m);

        for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++){
            ray r = c.generateRay(1.0 * i / m, 1.0 * j / n);

            double min_distance = 100000000;
            vec3 color(135, 206, 235);
            vec3 pi;

            for(int k = 0; k < objects.size(); k++)
            for(int f = 0; f < objects[k].simplices.size(); f++){
                vec3 p;
                if(intersect(objects[k].simplices[f], r, p)){
                    double cur_distance = dot(p - r.starting_point, p - r.starting_point);
                    if(cur_distance < min_distance){
                        pi = p;
                        min_distance = cur_distance;
                        color = objects[k].simplices[f].color;
                    }
                }
            }

            if(min_distance < 10000000){
                double visibility = 0.0;
                for(int l = 0; l < lightSources.size(); l++){
                    ray light_ray(pi, lightSources[l].position - pi);
                    double light_distance = dot(light_ray.direction, light_ray.direction);

                    bool blocked = false;
                    for(int k = 0; k < objects.size(); k++)
                    for(int f = 0; f < objects[k].simplices.size(); f++){
                        vec3 p;
                        if(intersect(objects[k].simplices[f], light_ray, p)){
                            double cur_distance = dot(p - light_ray.starting_point, p - light_ray.starting_point);
                            if(cur_distance < light_distance)blocked = true;
                        }
                    }

                    if(!blocked)visibility = max(visibility, min(1.0, lightSources[l].intensity / light_distance));
                }
                color = visibility * color;
            }
            printf("%d %d %d\n", (int)color.c[0], (int)color.c[1], (int)color.c[2]);
        }
    }
    void add_light_source(vec3 position, double intensity){
        lightSources.push_back(lightSource(position, intensity));
    }

    int make_object(physicalObject &a){
        objects.push_back(a);
        return (int)objects.size() - 1;
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

        return make_object(a);
    }
};
