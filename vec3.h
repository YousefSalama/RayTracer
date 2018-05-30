class vec3{
public:
    double x, y, z, w;
    vec3(){x = 0, y = 0, z = 0, w = 1;}
    vec3(double x_, double y_, double z_){x = x_, y = y_, z = z_, w = 1;}
    vec3(double x_, double y_, double z_, double w_){x = x_, y = y_, z = z_, w = w_;}

    vec3 operator -(){
        return vec3(-x, -y, -z, w);
    }

    vec3& operator +=(const vec3 &b){
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    vec3& operator -=(const vec3 &b){
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }
    vec3& operator *=(const vec3 &b){
        x *= b.x;
        y *= b.y;
        z *= b.z;
        return *this;
    }
    vec3& operator /=(const vec3 &b){
        x /= b.x;
        y /= b.y;
        z /= b.z;
        return *this;
    }
    vec3& operator *=(double a){
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
    vec3& operator /=(double a){
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }
};

vec3 operator +(const vec3 &a, const vec3 &b){
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z, 1);
}
vec3 operator -(const vec3 &a, const vec3 &b){
    return vec3(a.x - b.x, a.y - b.y, a.z - b.z, 1);
}
vec3 operator *(const vec3 &a, const vec3 &b){
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z, 1);
}
vec3 operator /(const vec3 &a, const vec3 &b){
    return vec3(a.x / b.x, a.y / b.y, a.z / b.z, 1);
}
double dot(const vec3 &a, const vec3 &b){
    return (a.x * b.x + a.y * b.y + a.z * b.z) / a.w / b.w;
}
vec3 cross(const vec3 &a, const vec3 &b){
    return vec3((a.y * b.z - a.z * b.y) / a.w / b.w, (a.z * b.x - a.x * b.z) / a.w / b.w, (a.x * b.y - a.y * b.x) / a.w / b.w);
}
