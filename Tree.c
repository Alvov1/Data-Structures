typedef struct BinaryTree{  //Двоичное дерево
    long int number;
    struct BinaryTree * left;
    struct BinaryTree * right;
} BinaryTree;

BinaryTree * AddTree(BinaryTree * tree, long int num) {  //Добавление элемента в дерево
    if (tree->number == num) return (NULL); //Если элемент уже есть в дереве
    else {
        if (tree->number > num)
            if (tree->left != NULL)
                AddTree(tree->left, num);
            else {
                tree->left = (BinaryTree * ) malloc (sizeof(BinaryTree));
                tree->left->left = NULL;
                tree->left->right = NULL;
                tree->left->number = num;
                return(tree->left);
            }

        if (tree->number < num)
            if (tree->right != NULL)
                AddTree(tree->right, num);
            else {
                tree->right = (BinaryTree * ) malloc (sizeof(BinaryTree));
                tree->right->left = NULL;
                tree->right->right = NULL;
                tree->right->number = num;
                return (tree->right);
            }
    }
}

BinaryTree * FoundTree(BinaryTree * tree, long int num){    //Поиск элемента в дереве
    if (tree->number == num)
        return (tree); //Возвращаем указатель на узел дерева
    else {
        if (tree->number > num)
            if (tree->left != NULL)
                return (FoundTree(tree->left, num));
            else
                return (NULL);

        if (tree->number < num)
            if (tree->right != NULL)
                return (FoundTree(tree->right, num));
            else
                return (NULL);
    }
}

BinaryTree * Min(BinaryTree * root, BinaryTree * tree){    //Нахождение узла, потомок которого - наименьший в этом поддереве
    if (tree->left == NULL)
        return root;
    return Min(tree, tree->left);
}

BinaryTree * DellTree(BinaryTree * root, BinaryTree * tree){    //Удаление определенного узла корня

    if(tree->left == NULL && tree->right == NULL){  //У узла нет потомков

        if(root->left == tree) {  //Обнуляем указатель в корне
            root->left = NULL;
            free(tree);
        } else {
            root->right = NULL;
            free(tree);
        }
        tree = NULL;
        return(NULL);
    }

    if(tree->left != NULL && tree->right == NULL){  //У узла есть только левый потомок
        tree->number = tree->left->number;
        BinaryTree * temp = tree->left;

        if(temp->right != NULL)
            tree->right = temp->right;

        if(temp->left != NULL)
            tree->left = temp->left;

        if(temp->left == NULL && temp->right == NULL)
            tree->left = NULL;

        free(temp);
        temp = NULL;

        return(NULL);
    }

    if(tree->left == NULL && tree->right != NULL){  //У узла есть только правый потомок
        tree->number = tree->right->number;
        BinaryTree * temp = tree->right;

        if(temp->right != NULL)
            tree->right = temp->right;

        if(temp->left != NULL)
            tree->left = temp->left;

        if(temp->left == NULL && temp->right == NULL)
            tree->right = NULL;

        free(temp);
        temp = NULL;

        return(NULL);
    }

    if(tree->right != NULL && tree->left != NULL){  //У узла есть оба потомка
        //На место узла ставится самый левый потомок правого поддерева, или самый правый потомок левого поддерева
        //Поставим самый левый потомок правого дерева
        BinaryTree * temp = Min(tree, tree->right);
        tree->number = temp->left->number;
        DellTree(temp, temp->left);
        temp = NULL;
    }
}


void DellAllTree(BinaryTree * tree){   //Удаление всего дерева
    if(tree != NULL){
        if(tree->left != NULL)  DellAllTree(tree->left);
        if(tree->right != NULL)  DellAllTree(tree->right);
        free(tree);
    }
}

void TreePrint(BinaryTree * tree){  //Вывод всех элементов дерева, в префиксной форме
    printf("    %li", tree->number);
    if(tree->left != NULL)  TreePrint(tree->left);
    if(tree->right != NULL) TreePrint(tree->right);
}
