#include <stdio.h>
#include <stdlib.h>   
#include <string.h>
#define MAX 100       
#define SACAR(a,b) ((a)-(b))

typedef struct{
    char titular[100];
    int conta;
    float saldo;
    unsigned int senha;
    int ns;
    int np;
    int nd;
    
    struct{	
        float deposito[MAX];
        char datadep[MAX][12];
    }dep;
    struct{	
        float saque[MAX];
        char datasaq[MAX][12];
        int barras[MAX];
        char datapag[MAX][12];
        float pag[MAX];
    }saq;
				
}bancarios;

bancarios dados_bancarios[MAX];

int cadastrar(bancarios *x,int cad); 
void pesquisar(int cad);
void extrato(int cad);
void listar(int cad);
int menu();
void salvar_arq(char txt[],int n);
int carregar_arq(char txt[]);

void excluir();

int comparaNome(const void *a, const void *b);

int main(int argc, char *argv[]){  
	int op,x,cad=0,k,w,numero_conta,numero_senha,m,indice_saque=0,c=0,contador=0,contador_dep=0,indice_dep=0,contador_pag=0,indice_pag=0,numbol;
	
	float valor_saque,receita=0,valor_dep,valor_pag;
	
	
	for(k=0;k<MAX;k++){
		for(w=0;w<MAX;w++){
			dados_bancarios[k].conta=0;
			dados_bancarios[k].saldo=0;
			dados_bancarios[k].senha=0;
			dados_bancarios[k].ns=0;
			dados_bancarios[k].np=0;
			dados_bancarios[k].nd=0;
			dados_bancarios[k].dep.deposito[w]=0;
			dados_bancarios[k].saq.saque[w]=0;
			dados_bancarios[k].saq.barras[w]=0;
			dados_bancarios[k].saq.pag[w]=0;
		}
	}
	
	cad = carregar_arq("Clientes.txt");
	
	do{
		op=menu();
		switch(op){
			case 1:{
				cad=cadastrar(&dados_bancarios[cad],cad);
				cad++;
				salvar_arq("Clientes.txt",cad);
				break;
			}//fim case 1
			case 2:{
				pesquisar(cad);
				break;
			}//fim case 2
			case 3:{
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){
					if(dados_bancarios[m].conta==numero_conta){
						indice_saque=m;
						contador++;
				}
				}
				if(contador!=0){
	
						printf("Insira senha: ");
						scanf("%i",&numero_senha);
						if(dados_bancarios[indice_saque].senha==numero_senha){
							c++;
							printf("Insira valor a ser sacado: ");
							scanf("%f",&valor_saque);
					
							receita=SACAR(dados_bancarios[indice_saque].saldo,valor_saque);
							if(receita>=0){
								
								dados_bancarios[indice_saque].saldo-=valor_saque;
								while(dados_bancarios[indice_saque].saq.saque[c]!=0){
									c++;
								}
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_saque].saq.datasaq[c]);
								dados_bancarios[indice_saque].saq.saque[c]=valor_saque;
								printf("SAQUE CONCLUIDO\n");
								dados_bancarios[indice_saque].ns++;
								c=0;
								salvar_arq("Clientes.txt",cad);
								break;
							}
							else{
								c--;
								printf("SALDO INSUFICIENTE\n");
								break;
							}
						}
						else{
							printf("SENHA INCORRETA\n");
							break;
						}
					}
				else{
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 3
			case 4:{
				
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){
					if(dados_bancarios[m].conta==numero_conta){
						indice_dep=m;
						contador_dep++;
				}
				}
				
				if(contador_dep!=0){
					printf("Insira senha: ");
					scanf("%i",&numero_senha);
						if(dados_bancarios[indice_dep].senha==numero_senha){
							c++;
							printf("Insira valor a ser depositado: ");
							scanf("%f",&valor_dep);
							if(valor_dep>0){
								dados_bancarios[indice_dep].saldo+=valor_dep;
								
								while(dados_bancarios[indice_dep].dep.deposito[c]!=0){
									c++;
								}
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_dep].dep.datadep[c]);
								dados_bancarios[indice_dep].dep.deposito[c]=valor_dep;
								printf("DEPOSITO CONCLUIDO\n");
								dados_bancarios[indice_dep].nd++;
								c=0;
								salvar_arq("Clientes.txt",cad);
								break;
							}
							else{
								c--;
								printf("VALOR DE DEPOSITO INVALIDO\n");
								break;
							}
						
						}					
					
						else{
							printf("SENHA INCORRETA\n");
							break;
						}
					}
					else{
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 4
			case 5:{
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){
					if(dados_bancarios[m].conta==numero_conta){
						indice_pag=m;
						contador_pag++;
				}
				}
				if(contador_pag!=0){
	
						printf("Insira senha: ");
						scanf("%i",&numero_senha);
						if(dados_bancarios[indice_pag].senha==numero_senha){
							c++;
							printf("Insira nº do codigo de barras: ");
							scanf("%i",&numbol);
							printf("Insira valor do boleto: ");
							scanf("%f",&valor_pag);
					
							receita=SACAR(dados_bancarios[indice_pag].saldo,valor_pag);
							if(receita>=0){
								
								dados_bancarios[indice_pag].saldo-=valor_pag;
								while(dados_bancarios[indice_pag].saq.pag[c]!=0){
									c++;
								}
								
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_pag].saq.datapag[c]);
								dados_bancarios[indice_pag].saq.barras[c]=numbol;
								dados_bancarios[indice_pag].saq.pag[c]=valor_pag;
								printf("PAGAMENTO CONCLUIDO\n");
								dados_bancarios[indice_pag].np++;
								c=0;
								salvar_arq("Clientes.txt",cad);
								break;
							}
							else{
								c--;
								printf("SALDO INSUFICIENTE\n");
								break;
							}
						}
						else{
							printf("SENHA INCORRETA\n");
							break;
						}
					}
				else{
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 5
			case 6:{
				extrato(cad);
				break;
			}
			case 7:{
				listar(cad);
				break;
			}
			case 8:{	
					excluir(cad);
                	cad=carregar_arq("Clientes.txt");
				break;
			}
			case 9:{
				
                 break;
                 }
                 
			default:{
				printf("OPCAO INVALIDA\n");
				break;
			}
		}
	}while(op!=9);

	system("pause");
	return 0;
}

int menu(){
	int op;
	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
	printf("\n\xBA       ---BANCO DA UPE---   	 \xBA");
	printf("\n\xBA feito em C.                    \xBA");
	printf("\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	
	printf("1- Cadastrar\n2- Pesquisar\n3- Sacar\n4- Depositar\n5- Pagar\n6- Extrato\n7- Listar\n8- Deletar Conta\n9- Sair\n\n--> ");
	scanf("%i",&op);
	
	return op;
}

int cadastrar(bancarios *x, int cad){
	int y = 0, erro_cadc = 0;

	printf("=== Cadastrar ===\n");
    while(x!=0){
        printf("Nome do titular: ");
        fflush(stdin);
        gets(x->titular);
        printf("Insira um numero de conta(apenas numeros): ");
        scanf("%i",&x->conta);
        
        for(y=0;y<cad;y++){
            if(dados_bancarios[cad].conta == dados_bancarios[y].conta){   
                erro_cadc++;
            }
        }
        if(erro_cadc!=0){
            printf("Numero de conta indisponivel\n");
            cad--;
            break;
        }else{
            printf("Insira uma senha(apenas numeros): ");
            scanf("%i",&x->senha);
        }

        printf("Cadastro realizado com sucesso!\n");
        break;
    }
    return cad;
}
void pesquisar(int cad){
	int num=0,i,indice=0,chave,x,y,ok=0;
	printf("Insira chave de acesso para prosseguir: ");
	scanf("%i",&chave);
	
    if(chave==777){
	
		printf("Insira o numero da conta: ");
		scanf("%i",&num);
		
		for(y=0;y<cad;y++){
            if(num == dados_bancarios[y].conta){   
              ok++;
            }
        }
        if(ok==1){
            for(i=0;i<cad;i++){
			if(dados_bancarios[i].conta==num){
				indice=i;
			}
		}
		printf("\n--------------------------\n");
		printf("Titular: ");
		puts(dados_bancarios[indice].titular);
		printf("Senha: %i\n",dados_bancarios[indice].senha);
		printf("\nDepositos: \n");
		if(dados_bancarios[indice].nd>0){
			for(x=1;x<=dados_bancarios[indice].nd;x++){
				printf("+ %.2f	",dados_bancarios[indice].dep.deposito[x]);
				printf("Data: %s\n",dados_bancarios[indice].dep.datadep[x]);
				
			}
		}
		printf("Saques: \n");
		if(dados_bancarios[indice].ns>0){
			for(x=1;x<=dados_bancarios[indice].ns;x++){
				printf("- %.2f	",dados_bancarios[indice].saq.saque[x]);
				printf("Data: %s\n",dados_bancarios[indice].saq.datasaq[x]);
				
			}
		}
		printf("Pagamentos: \n");
		if(dados_bancarios[indice].np>0){
			for(x=1;x<=dados_bancarios[indice].np;x++){
				printf("- %.2f		",dados_bancarios[indice].saq.pag[x]);
				printf("Data: %s	",dados_bancarios[indice].saq.datapag[x]);
				printf("Codigo de barras: %i\n",dados_bancarios[indice].saq.barras[x]);
				
			}
		}
		printf("\nSaldo: %.2f\n",dados_bancarios[indice].saldo);
	}else{
    printf("NUMERO DE CONTA INEXISTENTE\n");
      }
      
  }
  else{
	    	printf("ACESSO NEGADO\n");
        	}
        	
}

void extrato(int cad){
	int m=0,i,indice=0,contador=0,num,senha,x;
	
	printf("Insira conta: ");
	scanf("%i",&num);
				
	for(m=0;m<=cad;m++){
		if(dados_bancarios[m].conta==num){
				indice=m;
				contador++;
			}
				}
		if(contador!=0){
			printf("Insira senha: ");
			scanf("%i",&senha);
			if(dados_bancarios[indice].senha==senha){
				printf("\nDepositos: \n");
		if(dados_bancarios[indice].nd>0){
			for(x=1;x<=dados_bancarios[indice].nd;x++){
				printf("+ %.2f	",dados_bancarios[indice].dep.deposito[x]);
				printf("Data: %s\n",dados_bancarios[indice].dep.datadep[x]);
				
			}
		}
		printf("Saques: \n");
		if(dados_bancarios[indice].ns>0){
			for(x=1;x<=dados_bancarios[indice].ns;x++){
				printf("- %.2f	",dados_bancarios[indice].saq.saque[x]);
				printf("Data: %s\n",dados_bancarios[indice].saq.datasaq[x]);
				
			}
		}
		printf("Pagamentos: \n");
		if(dados_bancarios[indice].np>0){
			for(x=1;x<=dados_bancarios[indice].np;x++){
				printf("- %.2f		",dados_bancarios[indice].saq.pag[x]);
				printf("Data: %s	",dados_bancarios[indice].saq.datapag[x]);
				printf("Codigo de barras: %i\n",dados_bancarios[indice].saq.barras[x]);
				
			}
		}
		printf("\nSaldo: %.2f\n",dados_bancarios[indice].saldo);
	}
		else{
				printf("SENHA INCORRETA\n");
			}
		}
		
		else{
			printf("CONTA INCORRETA\n");
		}	
}

void listar(int cad){
	int chave,x,cont=0;
	printf("Insira chave de acesso para prosseguir: ");
	scanf("%i",&chave);

	if(chave==777){
		
		qsort(dados_bancarios,cad,sizeof(bancarios),comparaNome);
		
		for(x = 0; x < cad; x++){
        	cont++;
			printf("\nTitular: ");
			puts(dados_bancarios[x].titular);
			printf("Conta: %i\n",dados_bancarios[x].conta);
			printf("Saldo: %.2f\n",dados_bancarios[x].saldo);
			printf("------------------------\n");
		}
		printf("Numero de contas cadastradas: %i\n",cont);
	}else{
		printf("ACESSO NEGADO\n");
	}
}

void salvar_arq(char txt[],int n){
    
	FILE *arq;
	arq=fopen(txt,"w");
	
	if(arq==NULL){
		printf("Impossivel abrir o arquivo\n");
	}
	
	
	fwrite(dados_bancarios,sizeof(bancarios),n,arq);  

	fclose(arq);
}

int carregar_arq(char txt[]){
	
	int k=0;
	
    FILE *arq;
	arq=fopen(txt,"a+");
	
	if(arq==NULL){
		printf("IMPOSSIVEL ABRIR O ARQUIVO\n");
	}
	
	while(fread(&dados_bancarios[k],sizeof(bancarios),1,arq)){    
		k++;
	}
	
	fclose(arq);
	return k;
    }
     
 void excluir(int x){
      
      FILE *arq;
	  
	  int cont,i,indice,somador=0,chave;
	  
	printf("Insira chave de acesso para prosseguir: ");
	scanf("%i",&chave);
	
    if(chave==777){
	  
	  printf("Insira numero da conta: ");
	  scanf("%i",&cont);
	  
	  for(i=0;i<x;i++){
	  	if(cont==dados_bancarios[i].conta){
	  		indice=i;
			somador++;
		  }
	  }
	  if(somador==1){
	  	arq=fopen("Clientes.txt","w");
	  	dados_bancarios[indice]=dados_bancarios[x-1];
	  	fwrite(dados_bancarios,sizeof(bancarios),(x-1),arq);
	  	fclose(arq);
	  	printf("CONTA APAGADA\n");
	  }
	  else{
	  	printf("NUMERO DE CONTA INVALIDO\n");
	  }
	}
	else{
		printf("CHAVE DE ACESSO INVALIDA\n");
	}
}

int comparaNome(const void *a, const void *b){
	int r=strcmp((*(bancarios*)a).titular,(*(bancarios*)b).titular);
	
	if(r==0)return 0;
	else if(r<0)return -1;
	else return 1;
}
