class camera{
public:
    vec3 viewpoint, upper_left_corner, left_side, upper_side;
    camera(){};
    camera(vec3 a, vec3 b, vec3 c, vec3 d){viewpoint = a; upper_left_corner = b; left_side = c, upper_side = d;}
    ray generateRay(double i, double j){
        vec3 direction = upper_left_corner - viewpoint + i * left_side + j * upper_side;
        return ray(viewpoint, direction);
    }

    void translate(vec3 d){
        viewpoint += d;
        upper_left_corner += d;
    }
    void rotateAroundXAxis(vec3 origin, double angle){
        viewpoint.rotateAroundXAxis(origin, angle);
        upper_left_corner.rotateAroundXAxis(origin, angle);
        left_side.rotateAroundXAxis(origin, angle);
        upper_side.rotateAroundXAxis(origin, angle);
    }
    void rotateAroundYAxis(vec3 origin, double angle){
        viewpoint.rotateAroundYAxis(origin, angle);
        upper_left_corner.rotateAroundYAxis(origin, angle);
        left_side.rotateAroundYAxis(origin, angle);
        upper_side.rotateAroundYAxis(origin, angle);
    }
    void rotateAroundZAxis(vec3 origin, double angle){
        viewpoint.rotateAroundZAxis(origin, angle);
        upper_left_corner.rotateAroundZAxis(origin, angle);
        left_side.rotateAroundZAxis(origin, angle);
        upper_side.rotateAroundZAxis(origin, angle);
    }
};
