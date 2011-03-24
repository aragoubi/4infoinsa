/*
		***********************
			CODE Q1
		***********************
	
	int cptIteration = 0;
		
	while(delta >= SEUIL){
		delta = 0;
		
		for(i = 1; i <= LARGEUR; i++){
			for(j = 1; j <= HAUTEUR; j++){
				T1[i][j] = (T[i][j+1] + T[i][j-1] + T[i+1][j] + T[i-1][j] + T[i][j]) / 5;
				delta = delta + abs(T1[i][j] - T[i][j]);
				
				
				int cptL;
				int cptC;
				for(cptL = 0; cptL <= LARGEUR+1; cptL++){
					for(cptC = 0; cptC <= HAUTEUR+1; cptC++){
						T[cptL][cptC] = T1[cptL][cptC];
					}
				}
			}
		}
		
		if( (cptIteration % K) == 0){
			afficherMatrice(T);
		}
		
		cptIteration++;
	}
	*/
