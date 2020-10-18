/*
  Authors:
    - Sarthak Sehgal (2017B3A70452P)
    - Syed Ahsan Abbas (2017B3A70507P)
*/

#include "hash_map.h"

/*
  Hashes a string to a number
*/
int hash(char *string, int map_size)
{
  int hash = 0;
  for (int i = 0; string[i] != '\0'; i++)
  {
    hash += (int)string[i];
  }
  return hash % map_size;
}

/*
  Initialize hash map with buckets of size map_size.
  The has map handles collission by chaining. Initializes each bucket's linked list too.
*/
hash_map *init_map(int map_size)
{

  hash_map *map = (hash_map *)calloc(1, sizeof(hash_map));
  map->map_size = map_size;
  map->buckets = (map_bucket **)calloc(map_size, sizeof(map_bucket *));
  assert(map->buckets != NULL, "hash map bucket space allocated");
  for (int i = 0; i < map_size; i++)
  {
    map->buckets[i] = (map_bucket *)calloc(1, sizeof(map_bucket));
    (map->buckets[i])->head = NULL;
    (map->buckets[i])->capacity = 0;
  }

  return map;
}

/*
  Returns pointer to list containing all map nodes.
*/
map_node *get_all_map_nodes(hash_map *map)
{
  map_node *dummy = (map_node *)calloc(1, sizeof(map_node));
  dummy->next = NULL;
  map_node *prev = dummy;

  int map_size = map->map_size;
  for (int i = 0; i < map_size; i++)
  {
    map_node *head = map->buckets[i]->head;
    while (head != NULL)
    {
      prev->next = head;
      prev = prev->next;
      head = head->next;
    }
  }
  prev->next = NULL;

  map_node *res = dummy->next;
  free(dummy);
  return res;
}

/*
  Find an element in a particular bucket.
*/
void *find_in_bucket(map_bucket *bucket, char *to_find)
{
  if (bucket->capacity == 0)
    return NULL;

  map_node *temp = bucket->head;
  void *data = NULL;
  while (temp != NULL)
  {
    if (strcmp(to_find, temp->string) == 0)
    {
      data = temp->data;
      break;
    }
    temp = temp->next;
  }
  return data;
}

/*
  Find an element in the map.
*/
void *find_in_map(hash_map *map, char *to_find)
{
  int bucket_idx = hash(to_find, map->map_size);
  return find_in_bucket(map->buckets[bucket_idx], to_find);
}

/*
  Inserts data on the front of the bucket.
*/
void insert_into_bucket(map_bucket *bucket, char *string, void *data)
{
  map_node *node = (map_node *)calloc(1, sizeof(map_node));
  node->string = string;
  node->data = data;
  node->next = bucket->head;
  bucket->head = node;
  bucket->capacity += 1;
}

/*
  Insert data into the map.
*/
void insert_into_map(hash_map *map, char *string, void *data)
{
  assert(find_in_map(map, string) == NULL, "entry being added doesn't already exist in hash map");

  int bucket_idx = hash(string, map->map_size);
  insert_into_bucket(map->buckets[bucket_idx], string, data);
}

/*
  Delete data from particular bucket
*/
void *delete_from_bucket(map_bucket *bucket, char *to_delete)
{
  map_node *curr = bucket->head;
  map_node *prev = NULL;
  while (curr && strcmp(curr->string, to_delete) != 0)
  {
    prev = curr;
    curr = curr->next;
  }

  if (!curr)
  {
    assert(false, "node not found in hash map");
    return NULL;
  }
  else
  {
    if (prev == NULL)
    {
      bucket->head = curr->next;
    }
    else
    {
      prev->next = curr->next;
    }
    return curr->data;
    bucket->capacity -= 1;
  }
}

/*
  Delete key from map.
*/
void *delete_from_map(hash_map *map, char *to_delete)
{
  assert(find_in_map(map, to_delete) != NULL, "entry to be deleted exists in hash map");

  int bucket_idx = hash(to_delete, map->map_size);

  return delete_from_bucket(map->buckets[bucket_idx], to_delete);
}

/*
  Deallocate a map node.
*/
void deallocate_map_node(map_node *node)
{
  if (node->next != NULL)
  {
    deallocate_map_node(node->next);
  }
  free(node);
}

/*
  Deallocate a particular bucket.
*/
void deallocate_map_bucket(map_bucket *bucket)
{
  if (bucket->capacity != 0)
  {
    deallocate_map_node(bucket->head);
  }
  free(bucket);
}

/*
  Deallocate the complete map.
*/
void delete_map(hash_map *map)
{
  for (int i = 0; i < map->map_size; i++)
  {
    deallocate_map_bucket(map->buckets[i]);
  }
  free(map->buckets);
  free(map);
}