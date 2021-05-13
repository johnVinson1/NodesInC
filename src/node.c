#include "a.h"
#include <string.h>
#include <stdlib.h>

#define MIN_INTER_NODE_ALLOC 32
#define MIN_END_NODE_ALLOC 32
#define INTER_NODE_EXT_SIZE 16
#define END_NODE_EXT_SIZE 16

int alloc_more_inter_nodes(InterNode* node)
{
	if(node == NULL) return 1;
	if(node->inter_nodes == NULL) return 2;
	
	InterNode* new_inter_nodes = calloc(node->inter_nodes_alloc + INTER_NODE_EXT_SIZE, sizeof(InterNode));
	
	if(new_inter_nodes == NULL) return 3;
	
	memcpy(new_inter_nodes, node->inter_nodes, node->inter_nodes_alloc);
	free(node->inter_nodes);
	node->inter_nodes = new_inter_nodes;
	node->inter_nodes_alloc += INTER_NODE_EXT_SIZE;
	
	return 0;
}

int alloc_more_end_nodes(InterNode* node) 
{
	if(node == NULL) return 1;
	if(node->end_nodes == NULL) return 2;
	
	EndNode* new_end_nodes = calloc(node->end_nodes_alloc + END_NODE_EXT_SIZE, sizeof(EndNode));
	
	if(new_end_nodes == NULL) return 3;
	
	memcpy(new_end_nodes, node->end_nodes, node->end_nodes_alloc);
	free(node->end_nodes);
	node->end_nodes = new_end_nodes;
	node->end_nodes_alloc += END_NODE_EXT_SIZE;
	
	return 0;
}

// End node allocs

// maybe use the alloc functions here? it might be more difficult though.
InterNode* make_root() 
{
	InterNode* root = malloc(sizeof(InterNode));
	if(root == NULL) return NULL;
	
	root->inter_nodes = calloc(MIN_INTER_NODE_ALLOC, sizeof(InterNode));
	
	if(root->inter_nodes == NULL) return NULL;
	
	root->end_nodes = calloc(MIN_END_NODE_ALLOC, sizeof(EndNode));
	
	if(root->end_nodes == NULL) return NULL;
	
	root->inter_num_c = 0;
	root->end_num_c = 0;
	
	root->inter_nodes_alloc = MIN_INTER_NODE_ALLOC;
	root->end_nodes_alloc = MIN_END_NODE_ALLOC;
	
	return root;
}

// node exists functions
InterNode* inter_node_exists(InterNode* node_to_search, NODE_DATA data_to_find) 
{
	if(node_to_search == NULL) return NULL;
	
	for(int i = 0; i < node_to_search->inter_num_c; i++) {
		if(node_to_search->inter_nodes[i].data == data_to_find) 
			return &node_to_search->inter_nodes[i];
	}
	
	return NULL;
}

EndNode* end_node_exists(InterNode* node_to_search, NODE_DATA data_to_find) 
{
	if(node_to_search == NULL) return NULL;
	
	for(int i = 0; i < node_to_search->end_num_c; i++) {
		if(node_to_search->end_nodes[i].data == data_to_find) { 
			return &node_to_search->end_nodes[i];
			
		}
	}
	
	return NULL;
}

// node adding functions
// assumes the node_to_add_to is correct
NodeError add_inter_node(InterNode* node_to_add_to, InterNode* node_to_add) 
{
	if(node_to_add_to == NULL || node_to_add == NULL) return DOES_NOT_EXIST;
	
	if(node_to_add_to->inter_num_c >= node_to_add_to->inter_nodes_alloc) 
	{
		int i = alloc_more_inter_nodes(node_to_add_to);
		if(i == 0) {
			// only copies 1 node, node_to_add -> node_to_add_to
			memcpy(&node_to_add_to->inter_nodes[node_to_add_to->inter_num_c++], node_to_add, sizeof(InterNode));
			return SUCCESS;
		} else {
			return OUT_OF_MEMORY;
		}
	} else
	{
		memcpy(&node_to_add_to->inter_nodes[node_to_add_to->inter_num_c++], node_to_add, sizeof(InterNode));
		return SUCCESS;
	}
}

NodeError add_end_node(InterNode* node_to_add_to, EndNode* node_to_add)
{
	if(node_to_add_to == NULL || node_to_add == NULL) return DOES_NOT_EXIST;
	
	if(node_to_add_to->end_num_c >= node_to_add_to->end_nodes_alloc) 
	{
		int i = alloc_more_end_nodes(node_to_add_to);
		if(i == 0) {
			// only copies 1 node, node_to_add -> node_to_add_to
			memcpy(&node_to_add_to->end_nodes[node_to_add_to->end_num_c++], node_to_add, sizeof(EndNode));
			return SUCCESS;
		} else {
			return OUT_OF_MEMORY;
		}
	} else
	{
		memcpy(&node_to_add_to->end_nodes[node_to_add_to->end_num_c++], node_to_add, sizeof(EndNode));
		return SUCCESS;
	}
}