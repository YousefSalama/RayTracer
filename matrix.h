struct matrix{
    double M[4][4];
    int n, m;

    matrix(){}
    matrix(int n_, int m_){n = n_; m = m_;}

    double determinant(){
        double det = 1.0;
        for(int i = 0; i < n; i++){
            bool found = false;
            for(int j = i; j < n; j++)if(fabs(M[j][i]) > eps){
                found = true;
                if(j == i)break;

                for(int k = 0; k < n; k++)swap(M[j][k], M[i][k]);
                det = -det;

                break;
            }

            if(found){
                det *= M[i][i];
                for(int j = i + 1; j < n; j++)if(fabs(M[j][i]) > eps){
                    double r = M[j][i] / M[i][i];
                    for(int k = 0; k < n; k++)M[j][k] -= M[i][k] * r;
                }
            }else{
                det = 0;
                break;
            }
        }
        return det;
    }
};
