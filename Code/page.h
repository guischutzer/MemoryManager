
Page* criaPaginas(Processo *lista_proc, int index);

int checaQuadro(FILE *arquivo, Page *head, int pos, int pid);

void NRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc);

void FIFO(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc);

void SCP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc);

void LRUP(int nproc, int total, int virtual, int intv, FILE *ftotal, FILE *fvirtual, Processo *lista_proc);
