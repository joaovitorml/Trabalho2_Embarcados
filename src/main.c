#include <stdio.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void menu(){
    int opcao,equip;
    float temp;
    
    printf("1 - Ligar/Desligar lampadas ou ar-condicionados\n");
    printf("2 - Escolher temperatura ideal\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");

    scanf("%d",&opcao);

    if(opcao == 0){
        exit(1);
    }
    else if(opcao == 1){
        printf("1 - lampada da cozinha\n");
        printf("2 - lampada da sala\n");
        printf("3 - lampada quarto 01\n");
        printf("4 - lampada quarto 02\n");
        printf("5 - ar-condicionado quarto 01\n");
        printf("6 - ar-condicionado quarto 02\n");
        printf("Escolha o equipamento: ");

        scanf("%d",&equip);
    }
    else if(opcao == 2){
        printf("Digite a temperatura: ");
        scanf("%lf",&temp);
    }
}


int main(int argc, char *argv[]) {
	int clienteSocket;
	struct sockaddr_in servidorAddr;
	unsigned short servidorPorta;
	char *IP_Servidor;
	char *mensagem;
	char buffer[16];
	unsigned int tamanhoMensagem;

	int bytesRecebidos;
	int totalBytesRecebidos;

	if ((argc < 3) || (argc > 4)) {
        printf("argv[0] = %c\n",argv[0]);
        printf("argv[1] = %c\n",argv[1]);
        printf("argv[2] = %c\n",argv[2]);
        printf("argv[2] = %c\n",argv[3]);
        printf("argv[2] = %c\n",argv[4]);
		printf("Uso: %s <IP do Servidor> <Porta> <Mensagem>\n", argv[0]);
		exit(1);
	}

	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	mensagem = argv[3];

	// Criar Socket
	if((clienteSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("Erro no socket()\n");

	// Construir struct sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);

	// Connect
	if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
		printf("Erro no connect()\n");

	tamanhoMensagem = strlen(mensagem);

	if(send(clienteSocket, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
		printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

	totalBytesRecebidos = 0;
	while(totalBytesRecebidos < tamanhoMensagem) {
		if((bytesRecebidos = recv(clienteSocket, buffer, 16-1, 0)) <= 0)
			printf("Não recebeu o total de bytes enviados\n");
		totalBytesRecebidos += bytesRecebidos;
		buffer[bytesRecebidos] = '\0';
		printf("%s\n", buffer);
	}
	close(clienteSocket);
	exit(0);

    menu();
}
