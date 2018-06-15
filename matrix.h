double determinantM[4][4];
struct matrix{
    double M[4][4];
    int n, m;

    matrix(){}
    matrix(int n_, int m_){n = n_; m = m_;}

    double determinant(){
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            determinantM[i][j] = M[i][j];

        double det = 1.0;
        for(int i = 0; i < n; i++){
            bool found = false;
            for(int j = i; j < n; j++)if(fabs(determinantM[j][i]) > eps){
                found = true;
                if(j == i)break;

                for(int k = 0; k < n; k++)swap(determinantM[j][k], determinantM[i][k]);
                det = -det;

                break;
            }

            if(found){
                det *= determinantM[i][i];
                for(int j = i + 1; j < n; j++)if(fabs(determinantM[j][i]) > eps){
                    double r = determinantM[j][i] / determinantM[i][i];
                    for(int k = 0; k < n; k++)determinantM[j][k] -= determinantM[i][k] * r;
                }
            }else{
                det = 0;
                break;
            }
        }
        return det;
    }
};
