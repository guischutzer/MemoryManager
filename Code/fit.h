extern Node *nextNode;

void mergeNode(Node* head, Node **headquick);

int firstFit(FILE* arquivo, int pid, int tamanho, Node* lista);

int nextFit(FILE* arquivo, int pid, int tamanho, Node *lista);

int quickFit(FILE* arquivo, int pid, int tamanho, Node **lista, int tam_max);
