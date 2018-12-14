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
    int ns; // numero de saques
    int np; //numero de pagamentos
    int nd; // numero de depositos
    
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

bancarios dados_bancarios[MAX]; // declarando "dados_bancarios", do tipo bancarios

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
	
	
	for(k=0;k<MAX;k++){   /* zerando todos os componentes de todas as posições */
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
	
	cad = carregar_arq("Clientes.txt"); // carregando os dados do arquivo, onde "cad" recebe o numero de clientes cadastrados
	
	do{
		op=menu(); // "op" recebe a opção desejada no menu
		switch(op){
			case 1:{ // Opção de cadastro
				cad=cadastrar(&dados_bancarios[cad],cad); 
				cad++;
				salvar_arq("Clientes.txt",cad); // arquivo atualizado após cadastro
				break;
			}//fim case 1
			case 2:{ // Opção de pesquisa
				pesquisar(cad); // A função pesquisa um cliente específico 
				break;
			}//fim case 2
			case 3:{ // Opção de saque
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){  /* Verificando qual o indice do vetor da conta desejada */
					if(dados_bancarios[m].conta==numero_conta){
						indice_saque=m;
						contador++;
				}
				}
				if(contador!=0){
	
						printf("Insira senha: ");
						scanf("%i",&numero_senha);
						if(dados_bancarios[indice_saque].senha==numero_senha){ /* Verificando se a senha corresponde a senha do cliente */
							c++;
							printf("Insira valor a ser sacado: ");
							scanf("%f",&valor_saque);
					
							receita=SACAR(dados_bancarios[indice_saque].saldo,valor_saque); // "receita" recebe o saldo atual menos o valor a ser sacado
							if(receita>=0){ // verificando se o valor a ser sacado é menor ou igual ao saldo atual
								
								dados_bancarios[indice_saque].saldo-=valor_saque; //descontando o valor da conta
								while(dados_bancarios[indice_saque].saq.saque[c]!=0){ /*determinando qual indice da primeira posição do vetor que estiver vazia que armazenará o valor do saque*/
									c++;
								}
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_saque].saq.datasaq[c]); /*salvando a data do saque no mesmo indice do valor*/
								dados_bancarios[indice_saque].saq.saque[c]=valor_saque; /*salvando o valor do saque*/
								printf("SAQUE CONCLUIDO\n");
								dados_bancarios[indice_saque].ns++; //incrementando o numero de saques realizados na conta
								c=0; //zerando o contador para o proximo cliente
								salvar_arq("Clientes.txt",cad); // atualizando dados no arquivo
								break;
							}
							else{ //caso o saldo seja insuficiente
								c--;
								printf("SALDO INSUFICIENTE\n");
								break;
							}
						}
						else{ //caso a senha esteja incorreta
							printf("SENHA INCORRETA\n");
							break;
						}
					}
				else{ //caso o numero da conta n exista
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 3
			case 4:{ // Opção de depósito
				
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){ /*verificando se a conta existe*/
					if(dados_bancarios[m].conta==numero_conta){
						indice_dep=m;
						contador_dep++;
				}
				}
				
				if(contador_dep!=0){
					printf("Insira senha: ");
					scanf("%i",&numero_senha);
						if(dados_bancarios[indice_dep].senha==numero_senha){ /*verificando se a senha está correta*/
							c++;
							printf("Insira valor a ser depositado: ");
							scanf("%f",&valor_dep);
							if(valor_dep>0){ /*verificando se o valor a ser depositado é valido*/
								dados_bancarios[indice_dep].saldo+=valor_dep; // somando valor ao saldo
								
								while(dados_bancarios[indice_dep].dep.deposito[c]!=0){ /*determinando qual indice da primeira posição do vetor que estiver vazia que armazenará o valor do deposito*/
									c++;
								}
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_dep].dep.datadep[c]); /*salvando a data do deposito no mesmo indice do valor*/
								dados_bancarios[indice_dep].dep.deposito[c]=valor_dep; /*salvando o valor do depósito*/
								printf("DEPOSITO CONCLUIDO\n");
								dados_bancarios[indice_dep].nd++; //incrementando o numero de depositos realizados na conta
								c=0; //zerando o contador para o proximo cliente
								salvar_arq("Clientes.txt",cad); // atualizando dados no arquivo
								break;
							}
							else{ //caso o valor seja invalido
								c--;
								printf("VALOR DE DEPOSITO INVALIDO\n");
								break;
							}
						
						}					
					
						else{ //caso a senha esteja errada
							printf("SENHA INCORRETA\n");
							break;
						}
					}
					else{ //caso a conta não existir
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 4
			case 5:{ // Opção de Pagamento
				printf("Insira conta: ");
				scanf("%i",&numero_conta);
				
				for(m=0;m<=cad;m++){ /*verificando se a conta existe*/
					if(dados_bancarios[m].conta==numero_conta){
						indice_pag=m;
						contador_pag++;
				}
				}
				if(contador_pag!=0){
	
						printf("Insira senha: ");
						scanf("%i",&numero_senha);
						if(dados_bancarios[indice_pag].senha==numero_senha){ /* Verificando se a senha corresponde a senha do cliente */
							c++;
							printf("Insira nº do codigo de barras: ");
							scanf("%i",&numbol);
							printf("Insira valor do boleto: ");
							scanf("%f",&valor_pag);
					
							receita=SACAR(dados_bancarios[indice_pag].saldo,valor_pag); // "receita" recebe o saldo atual menos o valor a ser sacado
							if(receita>=0){ // verificando se o valor a ser sacado é menor ou igual ao saldo atual
								
								dados_bancarios[indice_pag].saldo-=valor_pag; //descontando o valor da conta
								while(dados_bancarios[indice_pag].saq.pag[c]!=0){ /*determinando qual indice da primeira posição do vetor que estiver vazia que armazenará o valor do pagamento*/
									c++;
								}
								
								printf("Insira data[dd/mm/aaaa]: ");
								fflush(stdin);
								gets(dados_bancarios[indice_pag].saq.datapag[c]); /*salvando a data do deposito no mesmo indice do valor*/
								dados_bancarios[indice_pag].saq.barras[c]=numbol; /*salvando o numero do boleto*/
								dados_bancarios[indice_pag].saq.pag[c]=valor_pag; /*salvando o valor do pagamento*/
								printf("PAGAMENTO CONCLUIDO\n");
								dados_bancarios[indice_pag].np++; //incrementando o numero de pagamentos realizados na conta
								c=0; //zerando o contador para o proximo cliente
								salvar_arq("Clientes.txt",cad); // atualizando dados no arquivo
								break;
							}
							else{ //caso o valor seja invalido
								c--;
								printf("SALDO INSUFICIENTE\n");
								break;
							}
						}
						else{ //caso a senha esteja errada
							printf("SENHA INCORRETA\n");
							break;
						}
					}
				else{ //caso a conta não existir
					printf("CONTA INCORRETA\n");
					break;
				}
				break;
			}//fim case 5
			case 6:{ // Opção de Extrato
				extrato(cad); 
				break;
			}
			case 7:{ // Opção de Listagem
				listar(cad);
				break;
			}
			case 8:{ // Opção de Excluir Conta	
					excluir(cad);
                	cad=carregar_arq("Clientes.txt"); // atualizando arquivo
				break;
			}
			case 9:{ // Opção de sair
				     printf("Ate logo!\n");
                 break;
                 }
                 
			default:{ // Caso seja digitada uma opção inexistente
				printf("OPCAO INVALIDA\n");
				break;
			}
		}
	}while(op!=9);

	system("pause"); // Pausa antes do programa fechar, caso não funcione, substitua por getchar();
	return 0;
}

int menu(){
	int op;
	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB");
	printf("\n\xBA       ---BANCO DA UPE---   	 \xBA");
	printf("\n\xBA feito em C.                    \xBA");
	printf("\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	
	printf("1- Cadastrar\n2- Pesquisar\n3- Sacar\n4- Depositar\n5- Pagar\n6- Extrato\n7- Listar\n8- Deletar Conta\n9- Sair\n\n--> ");
	scanf("%i",&op); // recebe a opção desejada
	
	return op;
}

int cadastrar(bancarios *x, int cad){ //ponteiro do tipo bancarios, inteiro "cad" que receberá o numero de cadastros
	int y = 0, erro_cadc = 0;

	printf("=== Cadastrar ===\n");
    while(x!=0){
        printf("Nome do titular: ");
        fflush(stdin);
        gets(x->titular);
        printf("Insira um numero de conta(apenas numeros): ");
        scanf("%i",&x->conta);
        
        for(y=0;y<cad;y++){ // verificando se o numero da conta já está sendo usado
            if(dados_bancarios[cad].conta == dados_bancarios[y].conta){   
                erro_cadc++;
            }
        }
        if(erro_cadc!=0){ // caso ja esteja sendo usado
            printf("Numero de conta indisponivel\n");
            cad--; 
            break;
        }else{ // caso nao esteja sendo utilizado
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
	printf("Insira chave de acesso para prosseguir: "); // essa "chave" simboliza um "controle" apenas para pessoal autorizado
	scanf("%i",&chave);
	
    if(chave==777){
	
		printf("Insira o numero da conta: ");
		scanf("%i",&num);
		
		for(y=0;y<cad;y++){ // verificando a qual conta corresponde o numero digitado
            if(num == dados_bancarios[y].conta){   
              ok++;
            }
        }
        if(ok==1){ //caso exista
            for(i=0;i<cad;i++){ // identificando o indice dessa conta no vetor
			if(dados_bancarios[i].conta==num){
				indice=i;
			}
		}
		printf("\n--------------------------\n"); // mostrando os dados da conta- Nome, Senha
		printf("Titular: ");
		puts(dados_bancarios[indice].titular);
		printf("Senha: %i\n",dados_bancarios[indice].senha);
		printf("\nDepositos: \n");
		if(dados_bancarios[indice].nd>0){ // caso o numero de depositos seja maior que 0
			for(x=1;x<=dados_bancarios[indice].nd;x++){ // mostrar os valores dos depositos e suas datas
				printf("+ %.2f	",dados_bancarios[indice].dep.deposito[x]);
				printf("Data: %s\n",dados_bancarios[indice].dep.datadep[x]);
				
			}
		}
		printf("Saques: \n");
		if(dados_bancarios[indice].ns>0){ // caso o numero de saques seja maior que 0
			for(x=1;x<=dados_bancarios[indice].ns;x++){ // mostrar os  valores dos saques e suas datas
				printf("- %.2f	",dados_bancarios[indice].saq.saque[x]);
				printf("Data: %s\n",dados_bancarios[indice].saq.datasaq[x]);
				
			}
		}
		printf("Pagamentos: \n");
		if(dados_bancarios[indice].np>0){ // caso o numero de pagamentos seja maior que 0
			for(x=1;x<=dados_bancarios[indice].np;x++){ // mostrar os valores dos pagamentos, suas datas, e numero do "codigo de barras"
				printf("- %.2f		",dados_bancarios[indice].saq.pag[x]);
				printf("Data: %s	",dados_bancarios[indice].saq.datapag[x]);
				printf("Codigo de barras: %i\n",dados_bancarios[indice].saq.barras[x]);
				
			}
		}
		printf("\nSaldo: %.2f\n",dados_bancarios[indice].saldo); // mostrar o saldo da conta
	}else{ // caso o numero da conta esteja incorreto
    printf("NUMERO DE CONTA INEXISTENTE\n");
      }
      
  }
  else{ // caso a chave de acesso esteja errada
	    	printf("ACESSO NEGADO\n");
        	}
        	
}

void extrato(int cad){
	int m=0,i,indice=0,contador=0,num,senha,x;
	
	printf("Insira conta: ");
	scanf("%i",&num);
				
	for(m=0;m<=cad;m++){ // verificando se a conta existe e qual sua posição no vetor
		if(dados_bancarios[m].conta==num){
				indice=m;
				contador++;
			}
				}
		if(contador!=0){ // caso exista
			printf("Insira senha: ");
			scanf("%i",&senha);
			if(dados_bancarios[indice].senha==senha){ // verifica se a senha esta correta
				printf("\nDepositos: \n");
		if(dados_bancarios[indice].nd>0){ // caso o numero de depositos for maior que 0
			for(x=1;x<=dados_bancarios[indice].nd;x++){ // mostra os valores dos depositos e suas datas
				printf("+ %.2f	",dados_bancarios[indice].dep.deposito[x]);
				printf("Data: %s\n",dados_bancarios[indice].dep.datadep[x]);
				
			}
		}
		printf("Saques: \n");
		if(dados_bancarios[indice].ns>0){ // caso o numero de saques for maior que 0
			for(x=1;x<=dados_bancarios[indice].ns;x++){ // mostra os valores de saques e suas datas
				printf("- %.2f	",dados_bancarios[indice].saq.saque[x]);
				printf("Data: %s\n",dados_bancarios[indice].saq.datasaq[x]);
				
			}
		}
		printf("Pagamentos: \n");
		if(dados_bancarios[indice].np>0){ // caso o numero de pagamentos for maior que 0
			for(x=1;x<=dados_bancarios[indice].np;x++){ // mostrar os valores dos pagamentos, suas datas e o numero dos "codigos de barras"
				printf("- %.2f		",dados_bancarios[indice].saq.pag[x]);
				printf("Data: %s	",dados_bancarios[indice].saq.datapag[x]);
				printf("Codigo de barras: %i\n",dados_bancarios[indice].saq.barras[x]);
				
			}
		}
		printf("\nSaldo: %.2f\n",dados_bancarios[indice].saldo); // mostra o saldo da conta
	}
		else{ // caso a senha esteja errada
				printf("SENHA INCORRETA\n");
			}
		}
		
		else{ // caso o numero de conta esteja errada
			printf("CONTA INCORRETA\n");
		}	
}

void listar(int cad){
	int chave,x,cont=0;
	printf("Insira chave de acesso para prosseguir: ");
	scanf("%i",&chave);

	if(chave==777){ // essa "chave" simboliza um "controle" apenas para pessoal autorizado
		
		qsort(dados_bancarios,cad,sizeof(bancarios),comparaNome); // função qsort que irá ordenar os clientes cadastrados por ordem alfabetica
		
		for(x = 0; x < cad; x++){ // mostra todos os nomes dos clientes cadastrados, seus numeros de conta e seu saldo
        	cont++;
			printf("\nTitular: ");
			puts(dados_bancarios[x].titular);
			printf("Conta: %i\n",dados_bancarios[x].conta);
			printf("Saldo: %.2f\n",dados_bancarios[x].saldo);
			printf("------------------------\n");
		}
		printf("Numero de contas cadastradas: %i\n",cont); // mostra o numero d econtas cadastradas
	}else{ // caso a chave de acesso esteja errada
		printf("ACESSO NEGADO\n");
	}
}

void salvar_arq(char txt[],int n){ // função que salva os dados do vetor no arquivo
    
	FILE *arq; // declarando ponteiro do tipo arquivo (FILE)
	arq=fopen(txt,"w"); // criando/abrindo arquivo no modo "escrita" ( w sobrescreve dados )
	
	if(arq==NULL){ // caso ocorra algum erro na abertura/criação do arquivo
		printf("Impossivel abrir o arquivo\n");
	}
	
	
	fwrite(dados_bancarios,sizeof(bancarios),n,arq); // salvando dados no arquivo

	fclose(arq); // fechando arquivo
}

int carregar_arq(char txt[]){ // função para ler os dados salvos no arquivo
	
	int k=0;
	
    FILE *arq; // declarando ponteiro do tipo arquivo (FILE)
	arq=fopen(txt,"a+"); // criando/abrindo arquivo no modo "adicionar" (a+ adiciona dados ao arquivo)
	
	if(arq==NULL){ // caso ocorra algum erro na abertura/criação do arquivo
		printf("IMPOSSIVEL ABRIR O ARQUIVO\n");
	}
	
	while(fread(&dados_bancarios[k],sizeof(bancarios),1,arq)){  // lendo os dados do arquivo (a cada posição do vetor "bancarios" lido, soma 1 no contador, que representa o numero de cadastramentos)  
		k++;
	}
	
	fclose(arq); // fechando arquivo
	return k; // retornando numero de cadastrados
    }
     
 void excluir(int x){ // função para excluir cliente
      
      FILE *arq; // declarando ponteiro do tipo arquivo (FILE)
	  
	  int cont,i,indice,somador=0,chave;
	  
	printf("Insira chave de acesso para prosseguir: ");
	scanf("%i",&chave); // essa "chave" simboliza um "controle" apenas para pessoal autorizado
	
    if(chave==777){ 
	  
	  printf("Insira numero da conta: ");
	  scanf("%i",&cont);
	  
	  for(i=0;i<x;i++){ // verificando se o numero de conta existe e qual o indice do vetor correspondente
	  	if(cont==dados_bancarios[i].conta){
	  		indice=i;
			somador++;
		  }
	  }
	  if(somador==1){ // caso a conta exista
	  	arq=fopen("Clientes.txt","w"); // criando/abrindo arquivo no modo "escrita" ( w sobrescreve dados )
	  	dados_bancarios[indice]=dados_bancarios[x-1]; // sobrescrevendo os dados da posição do vetor a ser deletado, com os dados existentes na ultima posição do vetor cadastrado
	  	fwrite(dados_bancarios,sizeof(bancarios),(x-1),arq); // sobrescrevendo os dados no arquivo
	  	fclose(arq); // fechando arquivo
	  	printf("CONTA APAGADA\n");
	  }
	  else{ // caso o numero da conta esteja errada
	  	printf("NUMERO DE CONTA INVALIDO\n");
	  }
	}
	else{ // caso a chave de acesso esteja errada
		printf("CHAVE DE ACESSO INVALIDA\n");
	}
}

int comparaNome(const void *a, const void *b){ // função que compara os nomes dos titulares das contas, essa função será utilizada como parâmetro da função "qsort"
	int r=strcmp((*(bancarios*)a).titular,(*(bancarios*)b).titular);  // os ponteiros do tipo void serão convertidos em ponteiros do tipo "bancarios" (bancarios é o tipo da estrutura declarada no começo do programa)
                                                                     // "r" receberá inteiro retornado da função strcmp, que irá comparar as duas strings correspondentes aos nomes dos titularesdas contas
	if(r==0)return 0; //  caso o primeiro elemento for igual ao segundo elemento
	else if(r<0)return -1; // caso o primeiro elemento deva vir antes do segundo elemento
	else return 1; //  caso o primeiro elemento deva vir depois do sgeundo elemento
}
