class simplex{
public:
    vec3 p[3], color;
    simplex(){};
    simplex(vec3 a_, vec3 b_, vec3 c_){p[0] = a_; p[1] = b_; p[2] = c_;}
    simplex(vec3 a_, vec3 b_, vec3 c_, vec3 color_){p[0] = a_; p[1] = b_, p[2] = c_; color = color_;}

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
};
bool intersect(simplex &s, ray r, vec3 &p){
    matrix M(4, 4), dM(4, 4);
    for(int i = 0; i < 3; i++)
    for(int j = 0; j < 4; j++){
        M.M[i][j] = s.p[i].c[j];
        dM.M[i][j] = s.p[i].c[j];
    }
    for(int j = 0; j < 4; j++){
        M.M[3][j] = r.starting_point.c[j];

        if(j == 3)dM.M[3][j] = 0;
        else dM.M[3][j] = r.direction.c[j];
    }

    double det = M.determinant();
    double delta_det = dM.determinant();

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
