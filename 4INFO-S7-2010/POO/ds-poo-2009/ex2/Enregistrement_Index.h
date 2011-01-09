template <class T> class Enregistrement{

public:
	int critere;
	T* element;


public:
	Enregistrement(int valeur, T* elt){
		critere=valeur;
		element = elt;
	}

};


template <class T> class Index{

public:	
	vector<Enregistrement*> index ;
	
public:
	Index();
	void inserer(Enregistrement* e);
	List<T> recherche(int valeur);

};

template <class T> void Index::inserer(Enregistrement* e){
	Enregistrement* tmp;
	int k;
	for(int i = 0; i<index.size(); i++){
		if(e->critere > index[i]->critere && e->critere < index[i++]->critere){
			tmp = index[i++];
			k = i++;
		}
	for(int i=index.size(); i=k ;i--){
		index[i++]=index[i];
	}
	index[k]=tmp;	
	}
}

template <class T> List<T> Index::recherche(int valeur){
	List<T> liste;
	for(int i = 0;  i<index.size(); i++){
		if(index[i]->critere = valeur){
			liste.push_back(index[i]->element);
		}
	}
	return liste;
}

