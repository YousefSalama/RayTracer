
class simplex{
public:
    matrix plane;
    int indices[3];
    vec3 p[3], color;
    bool reflective;

    simplex(): plane(3, 4), indices{-1, -1, -1} {};
    simplex(vec3 a_, vec3 b_, vec3 c_) : plane(3, 4) {p[0] = a_; p[1] = b_; p[2] = c_; reflective = false;}
    simplex(vec3 a_, vec3 b_, vec3 c_, vec3 color_) : plane(3, 4) {p[0] = a_; p[1] = b_, p[2] = c_; color = color_; reflective = false;}

    void translate(vec3 d){
        for(int i = 0; i < 3; i++)p[i] += d;
    }
    void rotateAroundXAxis(vec3 origin, double angle){
        for(int i = 0; i < 3; i++)p[i].rotateAroundXAxis(origin, angle);
    }
    void rotateAroundYAxis(vec3 origin, double angle){
        for(int i = 0; i < 3; i++)p[i].rotateAroundYAxis(origin, angle);
    }
    void rotateAroundZAxis(vec3 origin, double angle){
        for(int i = 0; i < 3; i++)p[i].rotateAroundZAxis(origin, angle);
    }

    vec3 normal_vector;

    void find_plane(){
        for(int i = 0; i < 3; i++)
        for(int j = 0; j < 4; j++){
            plane.M[i][j] = p[i].c[j];
        }

        vec3 v;
        for(int i = 0; i < 3; i++)indices[i] = -1;

        int l = 0;
        for(int i = 0; i < 3; i++){
            bool found = false;
            for(int j = l; j < 3; j++)if(fabs(plane.M[j][i]) > 0){
                if(l != j){
                    for(int k = i; k < 4; k++)swap(plane.M[j][k], plane.M[l][k]);
                }
                found = true;
                break;
            }
            if(found){
                indices[l] = i;
                for(int j = l + 1; j < 3; j++)if(fabs(plane.M[j][i]) > 0){
                    double r = plane.M[j][i] / plane.M[l][i];
                    for(int k = i; k < 4; k++)plane.M[j][k] -= plane.M[l][k] * r;
                }
                l++;
            }
        }

        if(l == 3)v.c[3] = 1;
        else v.c[3] = 0;

        l--;
        for(int i = 2; i >= 0; i--){
            if(indices[l] == i){
                v.c[i] = 0;
                for(int j = i + 1; j < 4; j++)v.c[i] -= v.c[j] * plane.M[l][j];
                v.c[i] /= plane.M[l][i];

                l--;
            }else{
                v.c[i] = 1;
            }
        }

        normal_vector = v;
    }
};

bool intersect(simplex &s, ray &r, vec3 &p){
    vec3 v = s.normal_vector;

    double det = 0.0;
    double delta_det = 0.0;

    for(int i = 0; i < 4; i++){
        if(i != 3)delta_det += v.c[i] * r.direction.c[i];
        det += v.c[i] * r.starting_point.c[i];
    }

    if(fabs(det) < eps)return false;
    if(fabs(delta_det) < eps)return false;
    if(det / delta_det > eps)return false;

    p = r.starting_point - (det / delta_det) * r.direction;

    int gsign = 0;
    for(int i = 0; i < 3; i++){
        double c = dot(r.direction, cross(s.p[i] - r.starting_point, s.p[(i + 1) % 3] - r.starting_point));

        int csign = 0;
        if(c < -eps)csign = -1;
        if(c > eps)csign = 1;

        if(csign == 0)continue;
        else if(gsign == 0)gsign = csign;
        else if(gsign != csign)return false;
    }
    return true;
}
