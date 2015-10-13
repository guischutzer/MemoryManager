

void imprimeBin(FILE* arquivo, int arqsize);

Processo inputProcesso(char* linha);

void imprimeNode(Node* head);

void escreveBin(char pid, FILE* arquivo, int origem, int pags);

void imprimeProc (Processo proc);

Processo* carrega(char* nome, int* total, int* virtual, int* nproc);

void liberaListaAcessos(Acesso *head);

void liberaListaProcessos(Processo *lista_proc, int tamanho);
