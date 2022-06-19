// #include "Control.h"
// #include "../P_Impressao.h"

// int execute_control(){
//   int fd[2],fd_s[2]; 
//   pid_t pid;

//   char sent[BUFFER], received[BUFFER];
//   Instructions inst;
//   FILE *f;
//   int inst_amount = 0;
//   Program prog;
//   if(pipe(fd) < 0){ 
//     perror("pipe");
//     return -1; 
//   }
//   if((pid = fork()) < 0){ 
//     perror("fork");
//     exit(1);
//   }
  
//   if(pid > 0){
    
//     close(fd[0]);
//     int a=0;
//     while(a!=1 && a!=2){
//     printf("\nDeseja ler do arquivo de entrada ou pelo teclado?\n\t1 - Arquivo de entrada\n\t2 - Teclado\nEntre: ");
//     scanf("%d",&a);
//     if(a!=1 && a!=2){
//       printf("\nErro! Entrada invalida!\n");
//     }}
//     if(a==1){
//       LerArquivo(str_enviada); 
//     }else{
//       LerTerminal(str_enviada);
//     }
//     printf("String enviada pelo Controle(PID %i) para o Gerenciador: %s \n", getpid(),str_enviada);

    
//     write(fd[1], str_enviada,sizeof(str_enviada)+1);
//     exit(0);
//     return 1; 
//   } else {
//     EstadoEmExec estadoexec;
//     EstadoPronto estadopronto;
//     EstadoBloqueado estadobloqueado;
//     PcbTable pcbTable;
//     Cpu cpu;
//     Time time;

//     Processo processoDesbloqueado;
//     int desenfileirou;

//     if (pipe(fd_s) < 0) {
//         perror("pipe");
//         return -1;
//     }
//     Inicializa(&estadoexec, &estadopronto, &estadobloqueado, &pcbTable, &cpu, &time);

//     f = fopen("./Arquivos_Entrada/Program.txt", "r");

//     if (f == NULL) {
//         printf("Erro, nao foi possivel abrir o arquivo ArquivoProgramaIni.txt\n");
//     } else {
//         while((fgets(Instrucao, sizeof(Instrucao), f)) != NULL ){
//                 AdicionaProgramaFila(&Prog, Instrucao);
//                 inst_amount++;
//               }
//       fclose(f);
//     }

//     Prog.Tam = inst_amount;

//     Processo processo = criarPrimeiroSimulado(&Prog, &time, inst_amount, getpid());

//     close(fd[1]);

//     read(fd[0],  received, sizeof( received));
//     printf("String recebida pelo Gerenciador de PID %i enviada pelo Controle: '%s'\n\n", getpid(),  received);

//     EnfileiraPronto(&estadopronto, &processo);

//     InserePcbTable(&pcbTable, processo);

//     processo = colocarProcessoCPU(&cpu, &estadopronto);
//     for (unsigned int j = 0; j < strlen( received); j++) {
//         switch ( received[j]) {
//             case 'I':
//                 ImprimeSistemaCompleto(&cpu,&pcbTable,&estadobloqueado,&estadopronto);
//                 break;
//             case 'L':
//                 desenfileirou = DesenfileiraBloqueado(&estadobloqueado, &processoDesbloqueado);
//                 if(desenfileirou){
//                   EnfileiraPronto(&estadopronto, &processoDesbloqueado);
//                 }
//                 break;
//             case 'M':
//                 ImprimeTempoMedioCiclo(&time);
//                 exit(0);
//                 break;
//             case 'U':
//                 ExecutaCPU(&cpu, &time, &pcbTable, &estadoexec, &estadobloqueado, &estadopronto, &processo);
//                 break;
//             default:
//                 break;
//         }
//     }
//     return 0;
//   }
// }

// int LerArquivo(char *str_enviada){
//     FILE *ArquivoControle;
//     char str[2];
//     ArquivoControle = fopen("./Arquivos_Entrada/Controle.txt","r");
//     if( ArquivoControle == NULL){
//       printf("Erro ao abrir arquivo de entrada Controle.txt\n");
//       return 0; //ERRO
//     }
//     else{
//       while(fscanf(ArquivoControle,"%s",str) != EOF){
//         strcat(str_enviada,str);
//         strcat(str_enviada," ");
//       }
//       fclose(ArquivoControle);
//     }
//     return 1;
// }

// void LerTerminal(char *str_enviada){
//     char comando;
//     int i = 0;
//     printf("Entre com o comando um a um (M finaliza leitura):\n");
//     do{
//         scanf("%c",&comando);
//         str_enviada[i] = comando;
//         strcat(str_enviada," ");
//         i+=2;
//     }while(comando != 'M');
// }

// int RetiraProgramaFila(Program *prog,char *instrucao,int indice){  
//   if(EstaVazia(*prog)){
//     printf("\n\tErro! Fila de programa Vazia!\n");
//     return -1;
//   }
//   else if (indice >= prog->Tras) {
//       return 0;
//   }
//   strcpy(instrucao,prog->instrucoes[indice]);
//   return 1;
// }
