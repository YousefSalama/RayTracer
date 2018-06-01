class physicalObject{
public:
    vector <simplex> simplices;
    phsyicalObject(){};
    void translate(vec3 d){
        for(int i = 0; i < simplices.size(); i++)
            simplices[i].translate(d);
    }
    void rotateAroundXAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)simplices[i].rotateAroundXAxis(origin, angle);
    }
    void rotateAroundYAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)simplices[i].rotateAroundYAxis(origin, angle);
    }
    void rotateAroundZAxis(vec3 origin, double angle){
        for(int i = 0; i < simplices.size(); i++)simplices[i].rotateAroundZAxis(origin, angle);
    }
};
