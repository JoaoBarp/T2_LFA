#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <locale>


using namespace std;
//saida do programa
typedef struct pilha{
	int estado;
	string entrada;
	string Epilha;
	int posicao;
	int posicaoMax;

}pilha;
//Estrutura das regras e transiçoes lidas no arquivo
typedef struct regra{
    int max;
    string ent;
    string emp;
    vector <string> transicao;
}regra;

//vetor que armazena as regras e transiçoes
vector <regra> regras;

vector <pilha> SAIDA;


int BuscaMax(string reg){
	int i;
	for(i=0;i<regras.size();i++){
		if(regras[i].emp==reg){return regras[i].max;}
	}
    cout << "Regra <"<<reg<<"> não encontrada"<<endl;
    exit(0);
return -1;
}

string GetT(string linha){
	string str;
	int i=0;
	while(linha[i] != ','){i++;}
	i++;
	while (linha[i] != ')'){
            str+=linha[i];
        i++;
    }
return str;
}

//string GetR(string linha)

//funçao que pega uma linha do arquivo e separa e armazena no vetor
void tradusLinha(string linha){

	regra TEMP;
    	string regra;
    	string transicao;
    	int i=0,j=0;
    	while(linha[i] != ','){i++;}
    	i++;
    	//busca a regra
    	while (linha[i] != ',' && '\n'){
		if(linha[i] != ' '){
            	regra+=linha[i];
		}
		i++;
    	}
    	i++;
    	TEMP.ent=regra;
    	regra="";
    	while (linha[i] != ')'){
		if(linha[i] != ' '){
            	regra+=linha[i];
		}
		i++;
	}
    	TEMP.emp=regra;

    	//busca a primeira transicao que comeca no '('
	while(linha[i] != '('){i++;}

    	//enquanto não achar o delimitador final das transicoes '}'
	while(linha[i] != '}'){
    	//vai buscar as transiçoes 1 ou mais.
	while(linha[i] != ')'){
      	if(linha[i] != ' '){
            	transicao+=linha[i];
            }
            i++;
	}
	j++;
	TEMP.max=j;
	transicao+=linha[i];
	transicao=GetT(transicao);
	//insere no fim do vetor temporario
	TEMP.transicao.push_back (transicao);
	transicao="";
      // para o caso de ter mais de uma transicao verifica se encontro uma virgula
      // que sugere que tem mais transicoes, ou o fim das transicoes '}'
	while(linha[i] != ',' && linha[i] != '}'){i++;}
		if(linha[i] == ','){i++;}
	}
	regras.push_back(TEMP);

}

//printa as transicoes e regras
void print(){
	int i,j;
	for(i=0;i<regras.size();i++){
		cout <<endl << regras[i].ent << "  "<< regras[i].emp << "  ";
            for(j=0;j<regras[i].transicao.size();j++){
            	cout<< regras[i].transicao[j] << " ";
            }
		cout<< regras[i].max << " ";
	}
	cout << endl;
}

string BuscaRegra(string bus,int pos){
	int i,x;
	x=pos-1;
	string temp;
	for(i=0;i<regras.size();i++){
		if(bus==regras[i].emp){
			temp=regras[i].transicao[x];
		}
	}
	if(temp.empty()){std::cout << "Regra '"<<bus <<"' não encontrada" << '\n';exit(0);}
	return temp;
}

string erase(string x){
	string temp;
	int i=0;
	while(x[i] != '>'){
		if(x[i] != ' '&& x[i] != '<'){
		temp+=x[i];
		}
		i++;
	}
	i=0;
	return temp;
}

void trocaNterm(int pos) {
	string temp,temp2;
	int i=0;
	pilha TEMP;
	TEMP.estado=0;
  	TEMP.entrada=SAIDA[pos].entrada;
	temp=erase(SAIDA[pos].Epilha);
	temp2=SAIDA[pos].Epilha;

	while(temp2[0] != '>'){
		temp2.erase(temp2.begin());
	}
	temp2.erase(temp2.begin());

	TEMP.Epilha=BuscaRegra(temp,1);
	if(TEMP.Epilha == "£"){
		TEMP.Epilha="";
	}
	TEMP.Epilha+=temp2;

	if(TEMP.Epilha[0]=='<'){
		temp=erase(TEMP.Epilha);
		TEMP.posicaoMax=BuscaMax(temp);
		TEMP.posicao=1;
	}else{
		TEMP.posicaoMax=1;
		TEMP.posicao=1;
	}

	SAIDA.push_back(TEMP);
}
void retiraTerm(string ent, string emp, int pos){
	int i;
	int j=0;
	pilha TEMP;
	string temp;
	TEMP.estado=0;
  	TEMP.entrada=SAIDA[pos].entrada;
  	TEMP.posicao=1;
	TEMP.posicaoMax=1;
	TEMP.Epilha=SAIDA[pos].Epilha;
	for(i=0;i<regras.size();i++){
		if(emp==regras[i].emp && ent==regras[i].ent){
			TEMP.Epilha.erase(TEMP.Epilha.begin());
			TEMP.entrada.erase(TEMP.entrada.begin());
			j++;
			break;
		}
	}

	if(TEMP.Epilha[0]=='<'){
		temp=erase(TEMP.Epilha);
		TEMP.posicaoMax=BuscaMax(temp);
		TEMP.posicao=1;
	}else{
		TEMP.posicaoMax=1;
		TEMP.posicao=1;
	}

	if(j==0){cout << "Regra para '" <<ent <<"' e '"<< emp<<"' Não encontrada" <<'\n';exit(0);}
	else{SAIDA.push_back(TEMP);}
}

void desempilha() {
	pilha TEMP;
	string temp,temp2;
	int i,j;
	SAIDA.pop_back();
	while(1){
		i=distance(SAIDA.begin(),SAIDA.end())-1;
		if(i<0){cout<<endl << "A entrada é invalida"<<endl;exit(0);}

		cout <<"[ "<<SAIDA[i].estado<<" , "<<SAIDA[i].entrada <<" , " << SAIDA[i].Epilha <<"]"<< endl;// <<" Max: " <<SAIDA[i].posicaoMax<<" Att: "<<SAIDA[i].posicao<<endl;
		if(SAIDA[i].posicaoMax == 1){
			SAIDA.pop_back();
		}
		else if(SAIDA[i].posicao < SAIDA[i].posicaoMax ){
			TEMP.estado=0;
			TEMP.entrada=SAIDA[i].entrada;
			temp=erase(SAIDA[i].Epilha);
			temp2=SAIDA[i].Epilha;
			while(temp2[0] != '>'){
				temp2.erase(temp2.begin());
			}
			temp2.erase(temp2.begin());
			//cout<<"TOOO NO ELSE"<<endl<<temp<<endl;
			//cout<<SAIDA[i].posicao+1<<endl;
			SAIDA[i].posicao++;
			TEMP.Epilha=BuscaRegra(temp,SAIDA[i].posicao);
			//cout<<"TOOO NO ELSE"<<endl<<temp2<<endl;
			if(TEMP.Epilha == "£"){
				TEMP.Epilha="";
			}
			TEMP.Epilha+=temp2;

			if(TEMP.Epilha[0]=='<'){
				temp=erase(TEMP.Epilha);
				TEMP.posicaoMax=BuscaMax(temp);
				TEMP.posicao=1;
			}else{
				TEMP.posicaoMax=1;
				TEMP.posicao=1;
			}
			break;
		}else if(SAIDA[i].posicao == SAIDA[i].posicaoMax){
			SAIDA.pop_back();
		}
	}
	SAIDA.push_back(TEMP);

}

void teste(string ent){
		pilha TEMP;
		string ter1,ter2;
    	int i=0;
    	TEMP.estado=0;
    	TEMP.entrada=ent;
    	TEMP.Epilha="<S>";
    	TEMP.posicao=1;
    	TEMP.posicaoMax=BuscaMax("S");
    	SAIDA.push_back(TEMP);
    	i=distance(SAIDA.begin(),SAIDA.end());
    	while(!SAIDA[i-1].entrada.empty() || !SAIDA[i-1].Epilha.empty()){
				cout <<"[ "<<SAIDA[i-1].estado<<" , "<<SAIDA[i-1].entrada <<" , " << SAIDA[i-1].Epilha <<"]"<<endl;//<<" Max: " <<SAIDA[i-1].posicaoMax<<" Att: "<<SAIDA[i-1].posicao<<endl;
				//cout << "O IIII eh "<< i<<endl;
				if(SAIDA[i-1].Epilha[0]== '<'){
					trocaNterm(i-1);
				}else if(SAIDA[i-1].entrada[0] == SAIDA[i-1].Epilha[0]){
					ter1=SAIDA[i-1].entrada[0];
					ter2=SAIDA[i-1].Epilha[0];
					retiraTerm(ter1,ter2,i-1);
				}else if(SAIDA[i-1].entrada[0] != SAIDA[i-1].Epilha[0]){
					desempilha();
				}
				i=distance(SAIDA.begin(),SAIDA.end());

    	}


}

int main(int argc, char **argv){
      ifstream fp,Efp;
      string linha, entrada;
      Efp.open("entrada.txt");
      fp.open("tr.txt");
      if(!fp){
            cout<<"Não abriu o arquivo com o conjunto de regras"<<"\n";
            exit(1);
      }
      if(!Efp){
            cout<<"Não abriu o arquivo com a entrada"<<"\n";
            exit(1);
      }
      getline(Efp,entrada);
      //enquanto não acaba o arquivo, leio uma linha
      while (!fp.eof()) {
             getline(fp,linha);
             if(linha.empty()){break;}
             cout << linha << endl;
             tradusLinha(linha);
      }

//print();
cout<<endl<<"Entrada: "<<entrada<<endl;
teste(entrada);
cout<<"FINAL"<<endl;
for(int j=0;j<SAIDA.size();j++){
	cout <<"[ "<<SAIDA[j].estado<<" , "<<SAIDA[j].entrada <<" , " << SAIDA[j].Epilha <<"]"<<endl;
}

    	return 0;
}
