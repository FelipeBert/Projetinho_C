#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "unistd.h"

typedef struct {
	char nome_c[30];
	char codigo_c[5];
	int idade;
	char telefone[20];
	char cpf[15], cnpj[15];
	char login[30], senha[30];
	int administrador;
} Cliente;

typedef struct {
	char nome_l[30];
	char codigo_l[10];
	char categoria[30];
	int qtd;
	float preco;
	char fornecedor[30];
	int pego;
} Livro;

typedef struct {
	char nome_pediu[30];
	char nome_pedido[30];
	char codigo_p[5];
	int dia, mes, ano;
	int prazo;
} Pedido;

Cliente *cli;
Livro *liv;
Pedido *ped;

FILE *arquivo_c;
FILE *arquivo_l;
FILE *arquivo_p;

int contCliente = 0;
int contLivro = 0;
int contPedido = 0;
int comando_admin = 998756;

void menu_c();
void menu_admin();

Cliente cadastrar_cliente(Cliente cli, int contCliente);
void imprimir_c();
void atualizar_c();
void excluir_c();
void cliente_c();
void cliente_admin();
void atualizar_c_admin();
void imprimir_c_admin();

Livro registrar_livro(Livro liv, int contLivro);
void imprimir_l();
void atualizar_l();
void excluir_l();
void livro_c();
void livro_admin();
void imprimir_l_admin();
void busca_l();
void busca_l_admin();
void lista_pego();
void lista_pego_admin();

Pedido registrar_pedido(Pedido ped, int contPedido);
void imprimir_p();
void imprimir_p_admin();
void atualizar_p();
void excluir_p();
void pedido_admin();
void atualizar_p_admin();

int tamcl = 10;
int tamli = 10;
int tampe = 10;

/*atribuição das funçoes*/
void login() {
	printf("\nPressione (C) para se cadastra, (L) para fazer login e qualquer "
		   "tecla para sair: ");
}

void menu_c() {
	do {
		char opcao3;
		printf("\nV - Verificar informações da Conta");
		printf("\nA - Atualizar informações");
		printf("\nL - Livros");
		printf("\nS - Sair");
		printf("\n\nDigite a tecla correspondente ao que deseja: ");
		scanf("%c", &opcao3);
		getchar();

		system("clear");

		switch (opcao3) {
		case 'v':
		case 'V':
			imprimir_c();
			break;

		case 'a':
		case 'A':
			atualizar_c();
			break;

		case 'l':
		case 'L':
			livro_c();
			break;

		case 's':
		case 'S':
      return;
			login();
			break;

		default:

			printf("\nComando Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

		break;
	} while (1);
}

void menu_admin() {
	do {
		char opcao4;
		printf("\nC - Clientes");
		printf("\nL - Livros");
		printf("\nP - Pedidos");
		printf("\nS - Sair");
		printf("\n\nDigite a letra correspondente ao que deseja: ");
		scanf("%c", &opcao4);
		getchar();

		system("clear");

		switch (opcao4) {
		case 'c':
		case 'C':
			cliente_admin();
			break;

		case 'l':
		case 'L':
			livro_admin();
			break;

		case 'p':
		case 'P':
			pedido_admin();
			break;

		case 's':
		case 'S':
      return;
      login();
			break;

		default:

			printf("\n\nComando Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

		break;
	} while (1);
}

void cliente_admin() {
	do {
		char opcao5;
		printf("\nC - Cadastrar Cliente");
		printf("\nA - Atualizar Cliente");
		printf("\nI - Imprimir Cliente");
		printf("\nE - Excluir Cliente");
		printf("\nV - Voltar");
		printf("\n\nDigite a letra correspondente ao que deseja: ");
		scanf("%c", &opcao5);
		getchar();

		system("clear");

		switch (opcao5) {
		case 'c':
		case 'C':

			arquivo_c = fopen("backup.txt", "a+");
			cli[contCliente] = cadastrar_cliente(cli[contCliente], 0);

			fprintf(
				arquivo_c,
				"Nome: %s;Lgin: %s\n;Senha: %s\n;Codigo: %s\n;Idade: "
				"%i\n;Telefone: %s\n;Cpf: %s\n;Cnpj: %s\n;Administrador: "
				"%i\n\n",
				cli[contCliente].nome_c,
				cli[contCliente].login,
				cli[contCliente].senha,
				cli[contCliente].codigo_c,
				cli[contCliente].idade,
				cli[contCliente].telefone,
				cli[contCliente].cpf,
				cli[contCliente].cnpj,
				cli[contCliente].administrador);
			fclose(arquivo_c);

			contCliente += 1;
			if (contCliente == 10) {
				cli = realloc(cli, (contCliente + 1) * sizeof(Cliente));
			}
			break;

		case 'a':
		case 'A':
			atualizar_c_admin();
			break;

		case 'i':
		case 'I':
			imprimir_c_admin();
			break;

		case 'e':
		case 'E':
			excluir_c();
			break;

		case 'v':
		case 'V':
			menu_admin();
			break;

		default:

			printf("\n\nComando Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

		break;
	} while (1);
}

void livro_admin() {
	do {
		char opcao6;
		printf("\nR - Registrar Livro");
		printf("\nA - Atualizar Livro");
		printf("\nI - Imprimir Livro");
		printf("\nP - Procurar Livro");
    printf("\nL - Lista dos mais Pegos");
		printf("\nE - Excluir Livro");
		printf("\nV - Voltar");
		printf("\n\nDigite a letra correspondente ao que deseja: ");
		scanf("%c", &opcao6);
		getchar();

		system("clear");

		switch (opcao6) {
		case 'r':
		case 'R':

			arquivo_l = fopen("backup_l.txt", "a+");
			liv[contLivro] = registrar_livro(liv[contLivro], 0);

			fprintf(
				arquivo_l,
				"Nome: %s;Codigo: %s\n;Categoria: %s\n;Fornecedor: "
				"%s\n;Quantidade: %i\n;Valor Unitario: %f\n;Quantidade Pega: "
				"%i\n\n",
				liv[contLivro].nome_l,
				liv[contLivro].codigo_l,
				liv[contLivro].categoria,
				liv[contLivro].fornecedor,
				liv[contLivro].qtd,
				liv[contLivro].preco,
				liv[contLivro].pego);
			fclose(arquivo_l);

			contLivro += 1;
			if (contLivro == tamli) {
				liv = realloc(liv, (contLivro + 1) * sizeof(Livro));
        tamli++;
			}
			break;

		case 'a':
		case 'A':
			atualizar_l();
			break;

		case 'i':
		case 'I':
			imprimir_l_admin();
			break;

		case 'e':
		case 'E':
			excluir_l();
			break;

		case 'v':
		case 'V':
			menu_admin();
			break;

		case 'p':
		case 'P':
			busca_l_admin();
			break;

    case 'l':
    case 'L': lista_pego_admin(); break;

		default:

			printf("\n\nComado Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

	} while (1);
}

void pedido_admin() {
	do {
		char opcao7;
		printf("\nR - Registrar Pedido");
		printf("\nA - Atualizar Pedido");
		printf("\nI - Imprimir Pedido");
		printf("\nE - Excluir Pedido");
		printf("\nV - Voltar");
		printf("\n\nDigite a tecla correspondente ao que deseja: ");
		scanf("%c", &opcao7);
		getchar();

		system("clear");

		switch (opcao7) {
		case 'r':
		case 'R':

			arquivo_p = fopen("backup_p.txt", "a+");
			ped[contPedido] = registrar_pedido(ped[contPedido], 0);

			fprintf(
				arquivo_p,
				"Nome Cliente: %s;Nome Pedido: %s;Codigo: "
				"%s\n;Data:%i/%i/%i\n;Prazo: %i\n\n",
				ped[contPedido].nome_pediu,
				ped[contPedido].nome_pedido,
				ped[contPedido].codigo_p,
				ped[contPedido].dia,
				ped[contPedido].mes,
				ped[contPedido].ano,
				ped[contPedido].prazo);
			fclose(arquivo_p);

			contPedido += 1;
			if (contPedido == tampe) {
				ped = realloc(ped, (contPedido + 1) * sizeof(Pedido));
        tampe++;
			}
			break;

		case 'a':
		case 'A':
			atualizar_p();
			break;

		case 'i':
		case 'I':
			imprimir_p_admin();
			break;

		case 'e':
		case 'E':
			excluir_p();
			break;

		case 'v':
		case 'V':
			menu_admin();
			break;

		default:

			printf("\n\nComando Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

	} while (1);
}

void livro_c() {
	do {
		char opcao8;
		printf("\nB - Buscar Livro");
		printf("\nI - Imprimir Livro");
		printf("\nL - Lista dos mais Pegos");
		printf("\nF - Fazer Pedido");
    printf("\nP - Imprimir Pedido");
		printf("\nV - Voltar");
		printf("\n\nDigite a letra correspondente ao que deseja: ");
		scanf("%c", &opcao8);
		getchar();

		system("clear");

		switch (opcao8) {
		case 'b':
		case 'B':
			busca_l();
			break;

		case 'f':
		case 'F':

			arquivo_p = fopen("backup_p.txt", "a+");
			ped[contPedido] = registrar_pedido(ped[contPedido], 0);

			fprintf(
				arquivo_p,
				"%s;%s;%s;%i;%i;%i;%i",
				ped[contPedido].nome_pediu,
				ped[contPedido].nome_pedido,
				ped[contPedido].codigo_p,
				ped[contPedido].dia,
				ped[contPedido].mes,
				ped[contPedido].ano,
				ped[contPedido].prazo);
			fclose(arquivo_p);

			contPedido += 1;
			if (contPedido == 10) {
				ped = realloc(ped, (contPedido + 1) * sizeof(Pedido));
			}
			break;

		case 'v':
		case 'V':
			menu_c();
			break;

		case 'i':
		case 'I':
			imprimir_l();
			break;

		case 'l':
		case 'L':
			lista_pego();
			break;

    case 'p':
    case 'P': 
      imprimir_p(); 
      break;

		default:

			printf("\n\nComando Invalido, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

	} while (1);
}

void imprimir_c() {
	char codigo5[5];
	char senha5[30];
	int marcador8 = -2;
	printf("\nDigite o codigo da conta:");
	scanf("%s", codigo5);

	printf("\nDigite a senha: ");
	scanf("%s", senha5);

	for (int x = 0; x < contCliente; x++) {
		if (strcmp(codigo5, cli[x].codigo_c) == 0 &&
			strcmp(senha5, cli[x].senha) == 0) {
			printf("\nNome: %s", cli[x].nome_c);

			printf("\nCodigo: %s", cli[x].codigo_c);

			printf("\nIdade: %i", cli[x].idade);

			printf("\nCpf: %s", cli[x].cpf);

			printf("\nCnpj: %s", cli[x].cnpj);

			printf("\nTelefone: %s", cli[x].telefone);

			printf("\nLogin: %s", cli[x].login);

			printf("\nSenha: %s", cli[x].senha);

			marcador8 = x;

			char voltar;
			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltar);
		}
	}

	if (marcador8 == -2) {
		printf("\nCliente não Cadastrado");
	}

	sleep(2);
	system("clear");
	menu_c();
}

void imprimir_c_admin() {
	char nome5[30];
	char voltar2;
	int marcador9 = -2;
	printf("\nDigite o nome do Cliente: ");
	fgets(nome5, 30, stdin);

	for (int x = 0; x < contCliente; x++) {
		if (strcmp(nome5, cli[x].nome_c) == 0) {
			printf("\nNome: %s", cli[x].nome_c);

			printf("\nCodigo: %s", cli[x].codigo_c);

			printf("\nIdade: %i", cli[x].idade);

			printf("\nCpf: %s", cli[x].cpf);

			printf("\nCnpj: %s", cli[x].cnpj);

			printf("\nTelefone: %s", cli[x].telefone);

			printf("\nLogin: %s", cli[x].login);

			printf("\nSenha: %s", cli[x].senha);

      if(cli[x].administrador == 0)
      {
        printf("\nConta Cliente");
      }
      else 
      {
        printf("\nConta Administrador");
      }

			marcador9 = x;

			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltar2);
		}
	}

	if (marcador9 == -2) {
		printf("\nCliente não Cadastrado\n");
	}

	sleep(2);
	system("clear");
	cliente_admin();
}

void imprimir_l() {
	char movimento;
	for (int x = 0; x < contLivro; ) {
		printf("\nNome: %s", liv[x].nome_l);

		printf("\nCategoria: %s", liv[x].categoria);

		printf("\nCodigo: %s", liv[x].codigo_l);

		printf("\nPreço: %f", liv[x].preco);

		printf("\nNº de vezes pego: %i", liv[x].pego);

		printf("\n\nPressione (d) para ver o proximo livro, (v) para voltar e "
			   "qualquer outra tecla para sair: ");
		scanf("%c", &movimento);

		if (movimento == 'd' || movimento == 'D') {
			if(x + 1 < contLivro)
      {
        x++;
      }
		} else if (movimento == 'v' || movimento == 'V') {
			if (x - 1 >= 0) {
				x--;
			} 
			}
		 else {
			break;
		}
	}

	sleep(2);
  system("clear");
	menu_c();
}

void imprimir_l_admin() {
	char movimentol;
	for (int x = 0; x < contLivro; ) {
		printf("\nNome: %s", liv[x].nome_l);

		printf("\nCategoria: %s", liv[x].categoria);

		printf("\nCodigo: %s", liv[x].codigo_l);

		printf("\nFornecedor: %s", liv[x].fornecedor);

		printf("\nQuantidade: %i", liv[x].qtd);

		printf("\nQuantidade Pega: %i", liv[x].pego);

		printf("\nValor Unitario: %f", liv[x].preco);

		printf("\n\nPressione (d) para ver o proximo livro, (v) para voltar e "
			   "qualquer outra tecla para sair: ");
		scanf("%c", &movimentol);

		if (movimentol == 'd' || movimentol == 'D') {
			if(x + 1 < contLivro)
      {
        x++;
      }
		} else if (movimentol == 'v' || movimentol == 'V') {
			if (x - 1 >= 0) {
				x--;
			}
		} else {
			break;
		}
	}

	sleep(2);
  system("clear");
	livro_admin();
}

void imprimir_p() {
	char codigop[5];
	char voltar3;
	int marcador10 = -3;
	printf("\nDigite o codigo do pedido: ");
	scanf("%s", codigop);

	for (int x = 0; x < contPedido; x++) {
		if (strcmp(codigop, ped[x].codigo_p) == 0) {
			printf("\nNome do Cliente: %s", ped[x].nome_pediu);

			printf("\nNome do Pedido: %s", ped[x].nome_pedido);

			printf("\nCodigo: %s", ped[x].codigo_p);

			printf("\nPrazo: %i", ped[x].prazo);

			marcador10 = x;

			printf(
				"\nData do Registro: %i/%i/%i",
				ped[x].dia,
				ped[x].mes,
				ped[x].ano);

			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltar3);
		}
	}

	if (marcador10 == -3) {
		printf("\nPedido não Encontrado\n");
	}

	sleep(2);
  system("clear");
	livro_c();
}

void imprimir_p_admin() {
	char codigop1[5];
	char voltar4;
	int marcador11 = -3;
	printf("\nDigite o codigo do pedido: ");
	scanf("%s", codigop1);

	for (int x = 0; x < contPedido; x++) {
		if (strcmp(codigop1, ped[x].codigo_p) == 0) {
			printf("\nNome do Cliente: %s", ped[x].nome_pediu);

			printf("\nNome do Pedido: %s", ped[x].nome_pedido);

			printf("\nCodigo: %s", ped[x].codigo_p);

			printf("\nPrazo: %i", ped[x].prazo);

			marcador11 = x;

			printf(
				"\nData do Registro: %i/%i/%i",
				ped[x].dia,
				ped[x].mes,
				ped[x].ano);

			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltar4);
		}
	}

	if (marcador11 == -3) {
		printf("\nPedido não Encontrado\n");
	}

	sleep(2);
  system("clear");
	pedido_admin();
}

void atualizar_c() {
	char login3[30];
	char senha3[30];
	int troca = -3;
	printf("\nDigite seu Login: ");
	scanf("%s", login3);

	printf("\nDigite sua Senha: ");
	scanf("%s", senha3);

	for (int x = 0; x < contCliente; x++) {
		if (strcmp(login3, cli[x].login) == 0 &&
			strcmp(senha3, cli[x].senha) == 0) {
			troca = x;
			break;
		}
	}

	if (troca == -3) {
		printf("\nLogin ou Senha Incorretos");
	} else {
		printf("\nAtualização de Dados");

		printf("\n\nNome: ");
		fgets(cli[troca].nome_c, 30, stdin);

		printf("\nLogin: ");
		scanf("%s", cli[troca].login);

		printf("\nSenha: ");
		scanf("%s", cli[troca].senha);

		printf("\nIdade: ");
		scanf("%i", &cli[troca].idade);

		printf("\nTelefone: ");
		scanf("%s", cli[troca].telefone);

		printf("\nCpf: ");
		scanf("%s", cli[troca].cpf);

		printf("\nCnpj: ");
		scanf("%s", cli[troca].cnpj);

		printf("\n\nAtualização Realizada com Sucesso\n");
	}

	sleep(2);
  system("clear");
	menu_c();
}

void atualizar_c_admin() {
	char nome5[30];
	int marcador6 = -3;
	printf("\nNome do Cliente: ");
	fgets(nome5, 30, stdin);

	for (int x = 0; x < contCliente; x++) {
		if (strcmp(nome5, cli[x].nome_c) == 0) {
			printf("\nAtualização de Dados");

			printf("\n\nNome: ");
			fgets(cli[x].nome_c, 30, stdin);

			printf("\nLogin: ");
			scanf("%s", cli[x].login);
      getchar();

			printf("\nSenha: ");
			scanf("%s", cli[x].senha);
      getchar();

			printf("\nIdade: ");
			scanf("%i", &cli[x].idade);
      getchar();

			printf("\nTelefone: ");
			scanf("%s", cli[x].telefone);
      getchar();

			printf("\nCpf: ");
			scanf("%s", cli[x].cpf);
      getchar();

			printf("\nCnpj: ");
			scanf("%s", cli[x].cnpj);
      getchar();

			marcador6 = x;

			printf("\n\nAtualização Realizada com Sucesso\n");
		}
	}

	if (marcador6 == -3) {
		printf("\nCliente não Encontrado\n");
	}

	sleep(2);
  system("clear");
	cliente_admin();
}

void atualizar_l() {
	char nomel2[30];
	int marcador2 = -3;
	printf("\nNome do Livro: ");
	fgets(nomel2, 30, stdin);

	for (int x = 0; x < contLivro; x++) {
		if (strcmp(nomel2, liv[x].nome_l) == 0) {
			printf("\nNome: ");
			fgets(liv[x].nome_l, 30, stdin);

			printf("\nCodigo: ");
			scanf("%s", liv[x].codigo_l);

			printf("\nCategoira: ");
			scanf("%s", liv[x].categoria);

			printf("\nQuantidade: ");
			scanf("%i", &liv[x].qtd);

			printf("\nFornecedor: ");
			scanf("%s", liv[x].fornecedor);

			printf("\nValor Unitario: ");
			scanf("%f", &liv[x].preco);

			marcador2 = x;

			printf("\n\nAtualização realizada com Sucesso\n");
		}
	}

	if (marcador2 == -3) {
		printf("\nLivro não Encontrado\n");
	}

	sleep(2);
  system("clear");
	livro_admin();
}

void atualizar_p() {
	char codigop2[5];
	int marcador12 = -3;
	printf("\nCodigo do pedido: ");
	scanf("%s", codigop2);
	getchar();

	for (int x = 0; x < contPedido; x++) {
		if (strcmp(codigop2, ped[x].codigo_p) == 0) {
			printf("\nNome do Cliente: ");
			fgets(ped[x].nome_pediu, 30, stdin);

			printf("\nNome do Pedido: ");
			fgets(ped[x].nome_pedido, 30, stdin);

			printf("\nCodigo: ");
			scanf("%s", ped[x].codigo_p);

			printf("\nData: ");
			scanf("%i %i %i", &ped[x].dia, &ped[x].mes, &ped[x].ano);

			marcador12 = x;

			printf("\nPrazo: ");
			scanf("%i", &ped[x].prazo);

			printf("\n\nPedido atualizado com Sucesso\n");
		}
	}

	if (marcador12 == -3) {
		printf("\nPedido não Encontrado\n");
	}

	sleep(2);
  system("clear");
	pedido_admin();
}

void excluir_p() {
	char delp[5];
	int delp2 = -3;
	int confel = 0;
	printf("\nCodigo do Pedido: ");
	scanf("%s", delp);

	for (int x = 0; x < contPedido; x++) {
		if (strcmp(delp, ped[x].codigo_p) == 0) {
			delp2 = x;
			break;
		}
	}

	if (delp2 != -3) {
		for (int y = delp2; y < contPedido; y++) {
			ped[y] = ped[y + 1];
			confel = 1;
		}
	} else if (delp2 == -3) {
		printf("\nPedido não encontrado\n");
	}

	if (confel == 1) {
		contPedido -= 1;
		printf("\nPedido excluido com Sucesso\n");
	}

	sleep(2);
  system("clear");
	pedido_admin();
}

void excluir_c() {
	char delpn[30];
	int delpn2 = -3;
	int condeln = 0;
	printf("\nNome do Cliente: ");
	fgets(delpn, 30, stdin);

	for (int x = 0; x < contCliente; x++) {
		if (strcmp(delpn, cli[x].codigo_c) == 0) {
			delpn2 = x;
			break;
		}
	}

	if (delpn2 != -3) {
		for (int y = delpn2; y < contCliente; y++) {
			cli[y] = cli[y + 1];
			condeln = 1;
		}
	} else if (delpn2 == -3) {
		printf("\nCliente não Encontrado\n");
	}

	if (condeln == 1) {
		contCliente -= 1;
		printf("\nCliente excluido com Sucesso\n");
	}

	sleep(2);
  system("clear");
	cliente_admin();
}

void excluir_l() {
	char delpl[30];
	int delpl2 = -3;
	int conl2 = 0;
	printf("\nNome do Livro: ");
	fgets(delpl, 30, stdin);

	for (int x = 0; x < contLivro; x++) {
		if (strcmp(delpl, liv[x].nome_l) == 0) {
			delpl2 = x;
			break;
		}
	}

	if (delpl2 != -3) {
		for (int y = delpl2; y < contLivro; y++) {
			liv[y] = liv[y + 1];
			conl2 = 1;
		}
	} else if (delpl2 == -3) {
		printf("\nLivro não Encontrado");
	}

	if (conl2 == 1) {
		contLivro -= 1;
		printf("\nPedido excluido com Sucesso\n");
	}

	sleep(2);
  system("clear");
	livro_admin();
}

void busca_l() {
	char noml[30];
	char voltal;
	int marcadol = -3;
	printf("\nNome do Livro: ");
	fgets(noml, 30, stdin);

	for (int x = 0; x < contLivro; x++) {
		if (strcmp(noml, liv[x].nome_l) == 0) {
			printf("\nNome: %s", liv[x].nome_l);

			printf("\nCategoria: %s", liv[x].categoria);

			printf("\nCodigo: %s", liv[x].codigo_l);

			printf("\nPreço: %f", liv[x].preco);

			printf("\nNº de vezes pego: %i", liv[x].pego);

			marcadol = x;

			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltal);
		}
	}

	if (marcadol == -3) {
		printf("\nLivro não Encontrado\n");
	}

	sleep(2);
  system("clear");
	livro_c();
}

void busca_l_admin() {
	char noml2[30];
	int marcadorl2 = -3;
	char voltal2;

	printf("\nNome do Livro: ");
	fgets(noml2, 30, stdin);

	for (int x = 0; x < contLivro; x++) {
		if (strcmp(noml2, liv[x].nome_l) == 0) {
			printf("\nNome: %s", liv[x].nome_l);

			printf("\nCategoria: %s", liv[x].categoria);

			printf("\nCodigo: %s", liv[x].codigo_l);

			printf("\nPreço: %f", liv[x].preco);

			printf("\nNº de vezes pego: %i", liv[x].pego);

			printf("\nFornecedor: %s", liv[x].fornecedor);

			printf("\nEstoque: %i", liv[x].qtd);

			marcadorl2 = x;

			printf("\n\nPressione enter para voltar: ");
			scanf("%c", &voltal2);
		}
	}

	if (marcadorl2 == -3) {
		printf("\nLivro não Encontrado");
	}

	sleep(2);
  system("clear");
	livro_admin();
}

void lista_pego() {
	int maior = 0;
  int maior2 = 0;
  char continuar;

  do{

    for(int x = 0; x <= contLivro; x++)
    {
      if(liv[maior].pego < liv[maior + x].pego)
      {
        liv[maior] = liv[maior + x];
      }
    }

    if(maior == maior2 && maior <= contLivro)
    {
      maior++;
      maior2++;
      continue;
    }

    break;
  }while(1);

  for(int y = 0; y <= contLivro;)
  {
    printf("\nNome: %s", liv[y].nome_l);

    printf("\nCategoira: %s", liv[y].categoria);

    printf("\nPreço: %f", liv[y].preco);

    printf("\nNº de vezes Pego: %i", liv[y].pego);

    printf("\n\nPressione (d) para avançar,(v) para voltar e (s) para sair: ");
    scanf("%c", &continuar);

    if(continuar == 'd' || continuar == 'D')
    {
      if(y + 1 < contLivro)
      {
        y++;
      }
    }
    else if(continuar == 'v' || continuar == 'V')
    {
      if(y - 1 >= 0)
      {
        y--;
      }
    }
    else 
    {
      break;
    }
  }


	sleep(2);
	livro_c();
}

void lista_pego_admin()
{
  int maiora = 0;
  int maiora2 = 0;
  char continuar;

  do{

    for(int x = 0; x <= contLivro; x++)
    {
      if(liv[maiora].pego < liv[maiora + x].pego)
      {
        liv[maiora] = liv[maiora + x];
      }
    }

    if(maiora == maiora2 && maiora <= contLivro)
    {
      maiora++;
      maiora2++;
      continue;
    }

    break;
  }while(1);

  for(int y = 0; y <= contLivro; )
  {
    printf("\nNome: %s", liv[y].nome_l);

    printf("\nCategoira: %s", liv[y].categoria);

    printf("\nPreço: %f", liv[y].preco);

    printf("\nNº de vezes Pego: %i", liv[y].pego);

    printf("\nCodigo: %s", liv[y].codigo_l);

    printf("\nFornecedor: %s", liv[y].fornecedor);

    printf("\nEstoque: %i", liv[y].qtd);

    printf("\n\nPressione (d) para avançar,(v) para voltar e (s) para sair: ");
    scanf("%c", &continuar);
    getchar();

    if(continuar == 'd' || continuar == 'D')
    {
      if(y + 1 <= contLivro)
      {
        y++;
      }
      else
      {
        y = y;
      }
    }
    else if(continuar == 'v' || continuar == 'V')
    {
      if(y - 1 >= 0)
      {
        y--;
      }
      else 
      {
        y = y;
      }
    }
    else 
    {
      break;
    }
  }


	sleep(2);
  system("clear");
	livro_admin();
}

int main(void) {

	cli = calloc(tamcl, sizeof(Cliente));
	liv = calloc(tamli, sizeof(Livro));
	ped = calloc(tampe, sizeof(Pedido));

	do {
    login();
    char opcao;
		scanf("%c", &opcao);
		getchar();
		system("clear");

		switch (opcao) {
		case 'c':
		case 'C':

			arquivo_c = fopen("backup_c.txt", "a+");
			cli[contCliente] = cadastrar_cliente(cli[contCliente], 0);

			fprintf(
				arquivo_c,
				"%s;%s;%s;%s;%i;%s;%s;%s;%i\n\n",
				cli[contCliente].nome_c,
				cli[contCliente].login,
				cli[contCliente].senha,
				cli[contCliente].codigo_c,
				cli[contCliente].idade,
				cli[contCliente].telefone,
				cli[contCliente].cpf,
				cli[contCliente].cnpj,
				cli[contCliente].administrador);
			fclose(arquivo_c);

			contCliente += 1;
			if (contCliente == tamcl) {
				cli = realloc(cli, (contCliente + 1) * sizeof(Cliente));
        tamcl++;
			}      
			break;

		case 'l':
		case 'L':

			do {
				char login2[30], senha2[30];

				printf("\nCaso queira voltar pressione (N) 3 vezes caso contrario Digite seu Login:");
				scanf("%s", login2);
				getchar();

				printf("\nSenha: ");
				scanf("%s", senha2);
				getchar();

				int marcador = -5;

				for (int x = 0; x < contCliente; x++) {
					if (strcmp(cli[x].login, login2) == 0 &&
						strcmp(cli[x].senha, senha2) == 0 &&
						cli[x].administrador == 0) {
						system("clear");
						marcador = x;
						menu_c();
					} else if (
						strcmp(cli[x].login, login2) == 0 &&
						strcmp(cli[x].senha, senha2) == 0 &&
						cli[x].administrador == 1) {
						system("clear");
						marcador = x;
						menu_admin();
					}
				}

				if (marcador == -5) {
					char denovo12;
					printf("\n\nLogin ou Senha Incorretos, Deseja Tentar "
						   "Novamente(s): ");
					scanf("%c", &denovo12);
					getchar();

					if (denovo12 == 's' || denovo12 == 'S') {
						system("clear");
						continue;
					} else {
						system("clear");
            break;
						login();
					}
				}

			} while (1);
			break;

		default:
			system("clear");
			exit(1);
		}

	} while (1);

	return 0;
}

Cliente cadastrar_cliente(Cliente cli, int conCliente) {
	char opcao2;
	printf("\nCadastro de Usuario");

	printf("\n\n\nNome: ");
	fgets(cli.nome_c, 30, stdin);

  do{
	printf("\nLogin: ");
	scanf("%s", cli.login);
	getchar();

  if(strlen(cli.login) < 5)
  {
    printf("\nDigite pelo menos 5 caracteres para usar como login");
    system("clear");
    continue;
  }

  break;
  }while(1);

	printf("\nSenha: ");
	scanf("%s", cli.senha);
	getchar();

	int verificar;
	do {
		printf("\nCodigo de 5 Nº: ");
		scanf("%s", cli.codigo_c);
		getchar();

		verificar = atoi(cli.codigo_c);

		if (strlen(cli.codigo_c) > 5) {
			printf("\nVocê digitou um quantia acima do lmite");
			sleep(2);
			system("clear");
			continue;
		} else if (verificar == 0) {
			printf("\nDigite somente numeros");
			sleep(3);
			continue;
		}
		if (strlen(cli.codigo_c) <= 5 && verificar != 0) {
			break;
		}

	} while (1);

	printf("\nIdade: ");
	scanf("%i", &cli.idade);
	getchar();

  int telefo;
  do{
	printf("\nTelefone: ");
	scanf("%s", cli.telefone);
	getchar();

  telefo = atoi(cli.telefone);

  if(telefo == 0)
  {
    printf("\nDigite apenas numeros");
    system("clear");
    continue;
  }

  break;
  }while(1);

	printf(
		"\nDigite (c) para inserir o cpf e qualquer outra tecla para cnpj: ");
	scanf("%c", &opcao2);
	getchar();

	if (opcao2 == 'c' || opcao2 == 'C') {
    int cp;
    do{
		printf("\nCPF: ");
		scanf("%s", cli.cpf);
		getchar();

    cp = atoi(cli.cpf);

    if(cp == 0)
    {
      printf("\nDigite apenas numeros");
      system("clear");
      continue;
    }
  
    break;
    }while(1);

	} else {
    int cnp;
    do{
		printf("\nCNPJ: ");
		scanf("%s", cli.cnpj);
		getchar();

    cnp = atoi(cli.cnpj);

    if(cnp == 0)
    {
      printf("\nDigite apenas numeros");
      system("clear");
      continue;
    }

    break;
    }while(1);
	}

	char escolha;
	printf("\nEssa conta sera de administrador(a) ou de cliente(c): ");
	scanf("%c", &escolha);
	getchar();

	if (escolha == 'a' || escolha == 'A') {
		int comando2;
		printf("\nDigite o comando de administrador: ");
		scanf("%i", &comando2);
		getchar();

		if (comando2 == comando_admin) {
			cli.administrador = 1;
		} else {
			printf("\nVocê errou o comando e sua conta foi criada como uma de "
				   "cliente");
			cli.administrador = 0;
		}
	} else {
		cli.administrador = 0;
	}

	printf("\n\nCadastro realizado com sucesso\n");
	sleep(3);
	system("clear");
	return cli;
}

Livro registrar_livro(Livro liv, int contLivro) {
	printf("\nRegistro de Livro");

	printf("\n\n\nNome: ");
	fgets(liv.nome_l, 30, stdin);

	int verificar2;
	do {
		printf("\nCodigo: ");
		scanf("%s", liv.codigo_l);
		getchar();

		verificar2 = atoi(liv.codigo_l);
		if (verificar2 == 0) {
			printf("\nDigite apenas numeros");
			sleep(2);
			system("clear");
			continue;
		} else if (strlen(liv.codigo_l) > 5) {
			printf("\nNumero digitado excede o espaço\n");
			sleep(2);
			system("clear");
			continue;
		}

	} while (verificar2 == 0 && strlen(liv.codigo_l) > 5);

	printf("\nCategoria: ");
	scanf("%s", liv.categoria);
	getchar();

	printf("\nFornecedor: ");
	scanf("%s", liv.fornecedor);
	getchar();

	printf("\nQuantidade: ");
	scanf("%i", &liv.qtd);
	getchar();

	printf("\nValor Unitario: ");
	scanf("%f", &liv.preco);
	getchar();

	liv.pego = 0;

	printf("\n\nRegistro realizado com sucesso\n");
	sleep(3);
	system("clear");
	return liv;
	livro_admin();
}

Pedido registrar_pedido(Pedido ped, int contPedido) {
	printf("\nRegistro de Pedido");

	int faci = 0;
	int marcador = -3;
	do {
		printf("\n\n\nNome do Cliente: ");
		fgets(ped.nome_pediu, 30, stdin);

		for (int x = 0; x < contCliente; x++) {
			if (strcmp(ped.nome_pediu, cli[x].nome_c) == 0) {
				faci = cli[x].administrador;
				marcador = x;
				break;
			}
		}

		if (marcador == -3) {
			printf("\nCliente não encontrado, Tente Novamente");
			sleep(3);
			system("clear");
			continue;
		}

	} while (marcador == -3);

	int marcador2 = -3;
	do {
		printf("\nNome do Pedido: ");
		fgets(ped.nome_pedido, 30, stdin);

		for (int x = 0; x < contLivro; x++) {
			if (strcmp(ped.nome_pedido, liv[x].nome_l) == 0) {
				if (liv[x].qtd > 0) {
					liv[x].pego += 1;
					liv[x].qtd -= 1;
					marcador2 = x;
					break;
				}
			}
		}

		if (marcador2 == -3) {
			printf("Livro não Encontrado, tente novamente");
			system("clear");
			continue;
		}

	} while (marcador2 == -3);

	int verificar3;
	do {
		printf("\nCodigo: ");
		scanf("%s", ped.codigo_p);
		getchar();

		verificar3 = atoi(ped.codigo_p);
		if (verificar3 == 0) {
			printf("\nDigite apenas numeros");
			sleep(2);
			system("clear");
			continue;
		} else if (strlen(ped.codigo_p) > 5) {
			printf("\nO Numero digitado excede o espaço\n");
			sleep(2);
			system("clear");
			continue;
		}

	} while (verificar3 == 0);

	printf("\nData: ");
	scanf("%i %i %i", &ped.dia, &ped.mes, &ped.ano);
	getchar();

	ped.prazo = 20;
	printf("\nPrazo para devolução: %i dias\n", ped.prazo);
	sleep(2);

	printf("\n\nPedido realizado com Sucesso\n");
	sleep(3);
  system("clear");
	return ped;
	if (faci == 0) {
		livro_c();
	} else {
		pedido_admin();
	}
}
