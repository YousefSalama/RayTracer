struct matrix{
    double M[4][4];
    int n, m;

    matrix(){}
    matrix(int n_, int m_){n = n_; m = m_;}

    double determinant(){
        double tM[n][n];
        for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            tM[i][j] = M[i][j];

        double det = 1.0;
        for(int i = 0; i < n; i++){
            bool found = false;
            for(int j = i; j < n; j++)if(fabs(tM[j][i]) > eps){
                found = true;
                if(j == i)break;

                for(int k = 0; k < n; k++)swap(tM[j][k], tM[i][k]);
                det = -det;

                break;
            }

            if(found){
                det *= tM[i][i];
                for(int j = i + 1; j < n; j++)if(fabs(tM[j][i]) > eps){
                    double r = tM[j][i] / tM[i][i];
                    for(int k = 0; k < n; k++)tM[j][k] -= tM[i][k] * r;
                }
            }else{
                det = 0;
                break;
            }
        }
        return det;
    }
};
