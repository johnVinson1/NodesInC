#ifndef NODESTUFF
#define NODESTUFF

#include <stdbool.h>

enum NodeError { SUCCESS, DOES_NOT_EXIST, ALREADY_EXISTS, NODE_FULL, OUT_OF_MEMORY};

typedef enum NodeError NodeError;
typedef char NODE_DATA;

struct EndNode {
	NODE_DATA data;
};

struct InterNode {
	struct InterNode* inter_nodes;
	int inter_nodes_alloc;  // max number of inter nodes
	
	struct EndNode* end_nodes;
	int end_nodes_alloc;    // max number of end nodes
	
	NODE_DATA data;
	int inter_num_c; // number of inter children
	int end_num_c; // number of end children
};

typedef struct InterNode InterNode;
typedef struct EndNode EndNode;

/*
	Returns NULL if a node couldn't be allocated for, or space couldn't be made
	for children.
	
	Automatically allocates 32 spots for inter nodes and 8 spots for end nodes.
*/
InterNode* make_root();

/*
	Returns false if the node to search has no children, the data couldn't be found,
		or the node to search doesn't exist. Otherwise, returns the address of the
		node
*/
InterNode* inter_node_exists(InterNode* node_to_search, NODE_DATA data_to_find);
EndNode* end_node_exists(InterNode* node_to_search, NODE_DATA data_to_find);

/*
	
*/
NodeError add_inter_node(InterNode* node_to_add_to, InterNode* node_to_add);
NodeError add_end_node(InterNode* node_to_add_to, EndNode* node_to_add);

/*
	Returns:
		0 - success
		1 - arg doesn't exist
		2 - node doesn't have children allocated
		3 - unable to allocate more memory
*/
int alloc_more_inter_nodes(InterNode* node);
int alloc_more_end_nodes(InterNode* node);

#endif