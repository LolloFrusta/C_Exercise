#include <stdlib.h>
#include <string.h>

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

typedef struct dic_node
{
    const char *key;
    size_t key_len;
    void *value;
    struct set_node *next;
} node;

typedef struct dic_table
{
    node **nodes;
    size_t hashmap_size;
} dictionary;

dictionary *dic_table_new(const size_t hashmap_size)
{
    dictionary *table = malloc(sizeof(dictionary));
    if (!table)
    {
        return NULL;
    }
    table->hashmap_size = hashmap_size;
    table->nodes = calloc(table->hashmap_size, sizeof(node *));
    if (!table->nodes)
    {
        free(table);
        return NULL;
    }
    return table;
}

node *dic_insert_item(dictionary *table, const char *key, const size_t key_len, void *value)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    node *head = table->nodes[index];
    if (set_contains(&table, &key, &key_len))
    {
        printf("The key: %s is already in the set", key);
        return NULL;
    }
    if (!head)
    {
        table->nodes[index] = malloc(sizeof(node));
        if (!table->nodes[index])
        {
            return NULL;
        }
        table->nodes[index]->key = key;
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->value = value;
        table->nodes[index]->next = NULL;
        return table->nodes[index];
    }

    node *new_item = malloc(sizeof(node));
    if (!new_item)
    {
        return NULL;
    }
    new_item->key = key;
    new_item->key_len = key_len;
    new_item->value = value;
    new_item->next = NULL;
    node *tail = head;
    while (head)
    {
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
}

void *dic_get_item(dictionary *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    node *head = table->nodes[index];
    if (!head)
    {
        return NULL;
    }

    while (head != NULL)
    {
        if (hash == djb33x_hash(head->key, head->key_len) && key_len == head->key_len && strcmp(key, head->key))
        {
            return head->value;
        }
        else
        {
            head = head->next;
        }
    }
    return NULL;
}

int *dic_remove_item(dictionary *table, const char *key, const size_t key_len)
{
    size_t hash = djb33x_hash(key, key_len);
    size_t index = hash % table->hashmap_size;
    node *head, *prec = table->nodes[index];

    if (!head)
    {
        return -1;
    }

    while (head != NULL)
    {
        if (hash == djb33x_hash(head->key, head->key_len) && key_len == head->key_len && strcmp(key, head->key))
        {
            prec->next = head->next;
            free(head->key);
            free(head);
            return 0;
        }
        else
        {
            prec = head;
            head = head->next;
        }
    }
    return -1;
}