class camera{
public:
    vec3 viewpoint, upper_left_corner, left_side, upper_side;
    camera(){};
    camera(vec3 a, vec3 b, vec3 c, vec3 d){viewpoint = a; upper_left_corner = b; left_side = c, upper_side = d;}
    ray generateRay(double i, double j){
        vec3 direction = upper_left_corner - viewpoint + i * left_side + j * upper_side;
        return ray(viewpoint, direction);
    }
};
