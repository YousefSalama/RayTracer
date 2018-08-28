
static const int BUFFER_HEIGHT = 500;
static const int BUFFER_WIDTH = 1000;

vec3 buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
class sandbox{
public:
    vector <physicalObject> objects;
    vector <lightSource> lightSources;

    vec3 trace(ray &r, int depth = 0){
        if(depth > 5)return vec3(0, 0, 0);

        vec3 color(135, 206, 235);
        bool reflect = false;

        int object_index = -1;
        int simplex_index = -1;

        double min_distance = 100000000;
        vec3 pi;

        double orth_distance_from_light = 100000000;
        double distance_from_light = 100000000;


        for(int k = 0; k < lightSources.size(); k++){
            double pr = dot(lightSources[k].position - r.starting_point, r.direction);

            double d = pr / dot(r.direction, r.direction);
            double cur_distance = pr * pr / dot(r.direction, r.direction);

            if(d > eps){
                vec3 diff = (lightSources[k].position - r.starting_point) - d * r.direction;
                double dist = dot(diff, diff);

                if(dist < 0.005){
                    distance_from_light = min(distance_from_light, cur_distance);
                    orth_distance_from_light = max(0.002, min(distance_from_light, dist));
                }
            }
        }

        for(int k = 0; k < objects.size(); k++)
        for(int f = 0; f < objects[k].simplices.size(); f++){
            vec3 p;
            if(intersect(objects[k].simplices[f], r, p)){
                double cur_distance = dot(p - r.starting_point, p - r.starting_point);
                if(cur_distance < min_distance){
                    if(objects[k].global_color)color = objects[k].color;
                    else color = objects[k].simplices[f].color;

                    if(objects[k].reflective)reflect = true;
                    else reflect = objects[k].simplices[f].reflective;

                    object_index = k;
                    simplex_index = f;

                    pi = p;
                    min_distance = cur_distance;
                }
            }
        }

        if(min_distance < 10000000){
            if(distance_from_light < min_distance){
                color = 0.002 * vec3(255, 255, 255) / orth_distance_from_light;
            }else{
                if(reflect){
                    ray reflected_r;
                    reflected_r.starting_point = pi;

                    vec3 v = objects[object_index].simplices[simplex_index].find_plane();

                    reflected_r.direction = r.direction - 2 * dot(r.direction, v) / dot(v, v) * v;
                    return trace(reflected_r, depth + 1);
                }else{
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
            }
        }
        return color;
    }

    void render(int n, int m, camera &c){
        for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            ray r = c.generateRay(1.0 * i / n, 1.0 * j / m);
            vec3 color = trace(r);

            buffer[i][j] = color;
        }
    }
    void add_light_source(vec3 position, double intensity){
        lightSources.push_back(lightSource(position, intensity));
    }

    int make_object(physicalObject &a){
        objects.push_back(a);
        return (int)objects.size() - 1;
    }

    int make_quadrilateral(vec3 a, vec3 b, vec3 c, vec3 d, vec3 color, bool reflective){
        physicalObject o;
        o.global_color = true;
        o.color = color;

        o.reflective = reflective;

        simplex s1(a, b, c);
        simplex s2(a, c, d);
        o.simplices.push_back(s1);
        o.simplices.push_back(s2);
        return make_object(o);
    }

    int make_parallelepiped(vec3 corner, vec3 x, vec3 y, vec3 z, vec3 color, bool reflective){
        physicalObject a;

        a.global_color = true;
        a.color = color;
        a.reflective = reflective;

        simplex s1(corner, corner + x, corner + y);
        simplex s1_(corner + x + y, corner + x, corner + y);
        a.simplices.push_back(s1);
        a.simplices.push_back(s1_);

        simplex s2(corner, corner + x, corner + z);
        simplex s2_(corner + x + z, corner + x, corner + z);
        a.simplices.push_back(s2);
        a.simplices.push_back(s2_);

        simplex s3(corner, corner + y, corner + z);
        simplex s3_(corner + y + z, corner + y, corner + z);

        a.simplices.push_back(s3);
        a.simplices.push_back(s3_);

        simplex _s1(z + corner, z + corner + x, z + corner + y);
        simplex _s1_(z + corner + x + y, z + corner + x, z + corner + y);
        a.simplices.push_back(_s1);
        a.simplices.push_back(_s1_);

        simplex _s2(y + corner, y + corner + x, y + corner + z);
        simplex _s2_(y + corner + x + z, y + corner + x, y + corner + z);
        a.simplices.push_back(_s2);
        a.simplices.push_back(_s2_);

        simplex _s3(x + corner, x + corner + y, x + corner + z);
        simplex _s3_(x + corner + y + z, x + corner + y, x + corner + z);
        a.simplices.push_back(_s3);
        a.simplices.push_back(_s3_);

        return make_object(a);
    }
};
