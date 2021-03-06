const double eps = 1e-7;
const double PI = 3.14159265359;

class vec3{
public:
    double c[4];
    vec3(){c[0] = 0, c[1] = 0, c[2] = 0, c[3] = 1;}
    vec3(double x_, double y_, double z_){c[0] = x_, c[1] = y_, c[2] = z_, c[3] = 1;}
    vec3(double x_, double y_, double z_, double w_){c[0] = x_, c[1] = y_, c[2] = z_, c[3] = w_;}

    vec3 operator -(){
        return vec3(-c[0], -c[1], -c[2], c[3]);
    }

    vec3& operator +=(const vec3 &b){
        c[0] += b.c[0];
        c[1] += b.c[1];
        c[2] += b.c[2];
        return *this;
    }
    vec3& operator -=(const vec3 &b){
        c[0] -= b.c[0];
        c[1] -= b.c[1];
        c[2] -= b.c[2];
        return *this;
    }
    vec3& operator *=(const vec3 &b){
        c[0] *= b.c[0];
        c[1] *= b.c[1];
        c[2] *= b.c[2];
        return *this;
    }
    vec3& operator /=(const vec3 &b){
        c[0] /= b.c[0];
        c[1] /= b.c[1];
        c[2] /= b.c[2];
        return *this;
    }
    vec3& operator *=(double a){
        c[0] *= a;
        c[1] *= a;
        c[2] *= a;
        return *this;
    }
    vec3& operator /=(double a){
        c[0] /= a;
        c[1] /= a;
        c[2] /= a;
        return *this;
    }
    void rotateAroundXAxis(vec3 origin, double angle){
        *this -= origin;
        vec3 p = *this;

        p.c[1] = sin(angle) * c[2] + cos(angle) * c[1];
        p.c[2] = cos(angle) * c[2] - sin(angle) * c[1];

        p += origin;
        *this = p;
    }
    void rotateAroundYAxis(vec3 origin, double angle){
        *this -= origin;
        vec3 p = *this;

        p.c[0] = cos(angle) * c[0] - sin(angle) * c[2];
        p.c[2] = sin(angle) * c[0] + cos(angle) * c[2];

        p += origin;
        *this = p;
    }
    void rotateAroundZAxis(vec3 origin, double angle){
        *this -= origin;
        vec3 p = *this;

        p.c[0] = cos(angle) * c[0] - sin(angle) * c[1];
        p.c[1] = sin(angle) * c[0] + cos(angle) * c[1];

        p += origin;
        *this = p;
    }
};

vec3 operator +(const vec3 &a, const vec3 &b){
    return vec3(a.c[0] + b.c[0], a.c[1] + b.c[1], a.c[2] + b.c[2], 1);
}
vec3 operator -(const vec3 &a, const vec3 &b){
    return vec3(a.c[0] - b.c[0], a.c[1] - b.c[1], a.c[2] - b.c[2], 1);
}
vec3 operator *(const vec3 &a, const vec3 &b){
    return vec3(a.c[0] * b.c[0], a.c[1] * b.c[1], a.c[2] * b.c[2], 1);
}
vec3 operator /(const vec3 &a, const vec3 &b){
    return vec3(a.c[0] / b.c[0], a.c[1] / b.c[1], a.c[2] / b.c[2], 1);
}
vec3 operator *(double a, const vec3 &b){
    return vec3(a * b.c[0], a * b.c[1], a * b.c[2], 1);
}
vec3 operator /(const vec3 &b, double a){
    return vec3(b.c[0] / a, b.c[1] / a, b.c[2] / a, 1);
}
double dot(const vec3 &a, const vec3 &b){
    return (a.c[0] * b.c[0] + a.c[1] * b.c[1] + a.c[2] * b.c[2]);
}
vec3 cross(const vec3 &a, const vec3 &b){
    return vec3((a.c[1] * b.c[2] - a.c[2] * b.c[1]),
                 (a.c[2] * b.c[0] - a.c[0] * b.c[2]),
                 (a.c[0] * b.c[1] - a.c[1] * b.c[0]));
}
