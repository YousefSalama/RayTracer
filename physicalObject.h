class physicalObject{
public:
    vector <simplex> simplices;
    phsyicalObject(){};
    void translate(vec3 d){
        for(int i = 0; i < simplices.size(); i++)
        for(int j = 0; j < 3; j++)
            simplices[i].p[j] += d;
    }
    void rotateAroundXAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)
        for(int j = 0; j < 3; j++){
            vec3 p = simplices[i].p[j] - origin;
            vec3 np = p;

            np.c[1] = sin(angle) * p.c[2] + cos(angle) * p.c[1];
            np.c[2] = cos(angle) * p.c[2] - sin(angle) * p.c[1];
            np += origin;

            simplices[i].p[j] = np;
        }
    }
    void rotateAroundYAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)
        for(int j = 0; j < 3; j++){
            vec3 p = simplices[i].p[j] - origin;
            vec3 np = p;

            np.c[0] = cos(angle) * p.c[0] - sin(angle) * p.c[2];
            np.c[2] = sin(angle) * p.c[0] + cos(angle) * p.c[2];
            np += origin;

            simplices[i].p[j] = np;
        }
    }
    void rotateAroundZAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)
        for(int j = 0; j < 3; j++){
            vec3 p = simplices[i].p[j] - origin;
            vec3 np = p;

            np.c[0] = cos(angle) * p.c[0] - sin(angle) * p.c[1];
            np.c[1] = sin(angle) * p.c[0] + cos(angle) * p.c[1];
            np += origin;

            simplices[i].p[j] = np;
        }
    }
};
