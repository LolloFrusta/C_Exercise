#include <stddef.h> // required for NULL

typedef struct list_node
{
    struct list_node *next;
} node;

typedef node* List;

List list_get_tail(node **head)
{
    node *current_node = *head;
    node *last_node = NULL;
    while (current_node)
    {
        last_node = current_node;
        current_node = current_node->next;
    }
    return last_node;
}

List list_append(node **head, node *item)
{
    node *tail = list_get_tail(head);
    if (!tail)
    {
        *head = item;
    }
    else
    {
        tail->next = item;
    }
    item->next = NULL;
    return item;
}

List list_remove(node **head, node *item_to_remove)
{
    node *prec = *head;
    node *current_head = *head;
    while (current_head != item_to_remove || current_head != NULL)
    {
        prec = current_head;
        current_head = (current_head)->next;
    }
    
    if (current_head != NULL)
    {
        prec->next = current_head->next;
        free(current_head);
    }

    return *head;    
}

List list_pop(node **head)
{
    node *current_head = *head;
    if (!current_head)
    {
        return NULL;
    }
    *head = (*head)->next;
    current_head->next = NULL;
    return current_head;
}

typedef struct string_item
{
    struct list_node node;
    const char *string;
} str_item;

str_item *string_item_new(const char *string)
{
    str_item *item = malloc(sizeof(struct string_item));
    if (!item)
    {
        return NULL;
    }
    item->string = string;
    return item;
}

int main()
{
    str_item *my_linked_list = NULL;
    list_append((node **)&my_linked_list, (node *)string_item_new("Hello World"));
    list_append((node **)&my_linked_list, (node *)string_item_new("Test001"));
    list_append((node **)&my_linked_list, (node *)string_item_new("Test002"));
    list_append((node **)&my_linked_list, (node *)string_item_new("Last Item of the Linked List"));
    str_item *string_item = my_linked_list;
    while (string_item)
    {
        printf("%s\n", string_item->string);
        string_item = (str_item *)string_item->node.next;
    }
    return 0;
}