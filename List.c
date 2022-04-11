typedef struct List{ //Линейный список
    long int number;
    struct List * next;
} List;

List * AddList(List * list, long int num) {   //Добавление элемента в список
    if(list->next == NULL){ //Если список состоит только из корня
        list->next = (List * ) malloc (sizeof(List));
        list->next->next = NULL;
        list->next->number = num;
        return(list->next);
    } else {    //Если лист содержит хотя бы два элемента
        List * temp = (List * ) malloc (sizeof(List));
        temp->number = num;
        temp->next = list->next;
        list->next = temp;
        return(temp);
    }
}

void DellList(List * list){   //Удаление следеющего элемента списка, после данного
    List * temp = list->next;
    list->next = list->next->next;
    free(temp);
}

List * FoundList(List * list, long int num){    //Найти элемент в списке
    if(list->number == num)
        return(list);   //Если нашли элемент, то возвращаем указатель на узел, иначе ищем дальше
    else
        if(list->next != NULL)
            return(FoundList(list->next, num));
        else
            return (NULL);
}

List * DellAllList(List * list) {  //Удаление всего списка
    if (list->next != NULL)
        DellAllList(list->next);
    free(list);
    list = NULL;
    return(list);
}
