class lightSource{
public:
    vec3 position;
    double intensity;

    lightSource(){}
    lightSource(vec3 p, double i){position = p; intensity = i;}
};
