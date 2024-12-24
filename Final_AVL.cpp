#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <iomanip> // Para formatação de saída

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int key) {
        data = key;
        left = NULL;  // Usando NULL para compatibilidade
        right = NULL; // Usando NULL para compatibilidade
        height = 1;   // Novo nó é inicialmente adicionado como folha
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = NULL; // Usando NULL para compatibilidade
    }

    int height(Node* N) {
        if (N == NULL) // Usando NULL para compatibilidade
            return 0;
        return N->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    Node* newNode(int key) {
        Node* node = new Node(key);
        return node;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        if (N == NULL) // Usando NULL para compatibilidade
            return 0;
        return height(N->left) - height(N->right);
    }

    Node* insert(Node* node, int key) {
        if (node == NULL) // Usando NULL para compatibilidade
            return newNode(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data)
            return rightRotate(node);

        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != NULL) // Usando NULL para compatibilidade
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == NULL) // Usando NULL para compatibilidade
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == NULL) // Usando NULL para compatibilidade
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* search(Node* root, int key) {
        if (root == NULL || root->data == key) // Usando NULL para compatibilidade
            return root;

        if (key < root->data)
            return search(root->left, key);

        return search(root->right, key);
    }

    void preOrder(Node* root) {
        if (root != NULL) { // Usando NULL para compatibilidade
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    void inOrder(Node* root) {
        if (root != NULL) { // Usando NULL para compatibilidade
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);
        }
    }

    void postOrder(Node* root) {
        if (root != NULL) { // Usando NULL para compatibilidade
            postOrder(root->left);
            postOrder(root->right);
            cout << root->data << " ";
        }
    }

    void printTree(Node* root, int space = 0, int height = 10) {
        if (root == NULL)
            return;

        space += height;
        printTree(root->right, space);

        cout << endl;
        for (int i = height; i < space; i++)
            cout << " ";
        cout << root->data << "\n";

        printTree(root->left, space);
    }

    void menu() {
        int opcao;
        do {
            cout << "\nMenu de Opcoes:\n";
            cout << "1. Inserir elemento\n";
            cout << "2. Excluir elemento\n";
            cout << "3. Buscar elemento\n";
            cout << "4. Exibir em pre-ordem\n";
            cout << "5. Exibir em ordem simetrica\n";
            cout << "6. Exibir em pos-ordem\n";
            cout << "7. Exibir em formato de grafos\n";
            cout << "8. Editar elemento\n";
            cout << "9. Balancear a arvore\n";
            cout << "10. Sair\n";
            cout << "Escolha uma opcao: ";
            cin >> opcao;

            switch (opcao) {
                case 1: {
                    int valor;
                    cout << "Digite o valor a ser inserido: ";
                    cin >> valor;
                    root = insert(root, valor);
                    break;
                }
                case 2: {
                    int valor;
                    cout << "Digite o valor a ser excluido: ";
                    cin >> valor;
                    root = deleteNode(root, valor);
                    break;
                }
                case 3: {
                    int valor;
                    cout << "Digite o valor a ser buscado: ";
                    cin >> valor;
                    if (search(root, valor) != NULL) // Usando NULL para compatibilidade
                        cout << "Valor encontrado!\n";
                    else
                        cout << "Valor nao encontrado!\n";
                    break;
                }
                case 4:
                    cout << "Pre-ordem: ";
                    preOrder(root);
                    cout << endl;
                    break;
                case 5:
                    cout << "Ordem simetrica: ";
                    inOrder(root);
                    cout << endl;
                    break;
                case 6:
                    cout << "Pos-ordem: ";
                    postOrder(root);
                    cout << endl;
                    break;
                case 7:
                    cout << "Exibindo arvore em formato de grafos:\n";
                    printTree(root);
                    break;
                case 8: {
                    int valor, novoValor;
                    cout << "Digite o valor a ser editado: ";
                    cin >> valor;
                    Node* node = search(root, valor);
                    if (node != NULL) {
                        cout << "Digite o novo valor: ";
                        cin >> novoValor;
                        deleteNode(root, valor);
                        root = insert(root, novoValor);
                        cout << "Elemento editado com sucesso!\n";
                    } else {
                        cout << "Elemento nao encontrado para edicao.\n";
                    }
                    break;
                }
                case 9:
                    cout << "Balanceando a arvore...\n";
                    // Para balancear uma árvore AVL, uma abordagem comum seria usar
                    // uma travessia em ordem para obter uma lista de elementos, e depois
                    // construir uma nova árvore AVL a partir dessa lista.
                    {
                        vector<int> elements;
                        inOrderCollect(root, elements);
                        root = buildBalancedTree(elements, 0, elements.size() - 1);
                        cout << "Arvore balanceada com sucesso!\n";
                    }
                    break;
                case 10:
                    cout << "Saindo...\n";
                    break;
                default:
                    cout << "Opcao invalida!\n";
            }
        } while (opcao != 10);
    }

    void inOrderCollect(Node* root, vector<int>& elements) {
        if (root == NULL)
            return;
        inOrderCollect(root->left, elements);
        elements.push_back(root->data);
        inOrderCollect(root->right, elements);
    }

    Node* buildBalancedTree(vector<int>& elements, int start, int end) {
        if (start > end)
            return NULL;

        int mid = (start + end) / 2;
        Node* node = newNode(elements[mid]);

        node->left = buildBalancedTree(elements, start, mid - 1);
        node->right = buildBalancedTree(elements, mid + 1, end);

        node->height = 1 + max(height(node->left), height(node->right));

        return node;
    }
};

int main() {
    AVLTree tree;
    tree.menu();
    return 0;
}

