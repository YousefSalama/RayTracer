class simplex{
public:
    vec3 p[3], color;
    simplex(){};
    simplex(vec3 a_, vec3 b_, vec3 c_){p[0] = a_; p[1] = b_; p[2] = c_;}
};

int perm_sign(int n, int p[]){
    int p_[n];
    for(int i = 0; i < n; i++)
        p_[i] = p[i];

    int p_sign = 1;
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(p_[j] == i){
                if(j != i){
                    swap(p_[j], p_[i]);
                    p_sign *= -1;
                }
                break;
            }
        }
    }
    return p_sign;
}
bool intersect(simplex &s, ray r, vec3 &p){
    double det = 0.0, delta_det = 0.0;

    int perm[] = {0, 1, 2, 3};
    do{
        int p_sign = perm_sign(4, perm);

        double d1 = 1.0, d2 = 1.0;
        for(int i = 0; i < 3; i++){
            d1 *= s.p[i].c[perm[i]];
            d2 *= s.p[i].c[perm[i]];
        }
        d1 *= r.starting_point.c[perm[3]];
        if(perm[3] == 3)d2 = 0;
        else d2 *= r.direction.c[perm[3]];

        det += p_sign * d1;
        delta_det += p_sign * d2;
    }while(next_permutation(perm, perm + 4));

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
