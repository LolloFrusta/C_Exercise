#include <stddef.h> // required for NULL

typedef struct list_node
{
    struct list_node *prev;
    struct list_node *next;
} node;

typedef node *List;

List list_append(struct list_node **head, struct list_node *item)
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
    item->prev = tail;
    item->next = NULL;
    return item;
}

List list_remove(node **head, node *item_to_remove)
{
    node *current_node = *head;
    while (current_node != item_to_remove || current_node != NULL)
    {
        current_node = (current_node)->next;
    }
    if (current_node != NULL)
    {
        current_node->prev->next = current_node->next;
        current_node->next->prev = current_node->prev;
        free(current_node);
    }

    return *head;
}

List list_insert_after(node **head, node *item_to_insert, node *item_after)
{
    node *current_node = *head;

    while (current_node != item_after || current_node != NULL)
    {
        current_node = current_node->next;
    }
    if (current_node != NULL)
    {
        item_to_insert->next = current_node->next;
        item_to_insert->prev = current_node;
        current_node->next = item_to_insert;
    }

    return item_to_insert;
}

List list_insert_before(node **head, node *item_to_insert, node *item_before)
{
    node *current_node = *head;

    while (current_node != item_before || current_node != NULL)
    {
        current_node = current_node->next;
    }
    if (current_node != NULL)
    {
        item_to_insert->next = current_node;
        item_to_insert->prev = current_node->prev;
        current_node->prev = item_to_insert;
    }

    return item_to_insert;
}