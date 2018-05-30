class ray{
public:
    vec3 starting_point, direction;
    ray(){};
    ray(vec3 a, vec3 b){starting_point = a, direction = b;}
};
