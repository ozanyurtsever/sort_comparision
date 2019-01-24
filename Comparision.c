#include<stdio.h>
#include<stdlib.h>
#include<time.h>

static int index = 0;

typedef struct NODE_s *NODE;
typedef struct NODE_s
{
    NODE right;
    NODE left;
    unsigned long long data;
    int height;
} NODE_t[1];

typedef struct TREE_s *TREE;
typedef struct TREE_s
{
    NODE root;
} TREE_t[1];

TREE tree_init();
NODE node_init(unsigned long long data);
void tree_free(TREE tree);
void node_free(NODE node);
int local_height(NODE node);
int max(int a, int b);
NODE rotate_right(NODE node);
NODE rotate_left(NODE node);
NODE avl_insert_recursive(NODE node, unsigned long long data);
void avl_insert(TREE tree, unsigned long long data);
void inorder_traversal(NODE node, unsigned long long *inorder);
void bubblesort(unsigned long long *arr, int n);

void test(char *fname, int n)
{
    TREE tree;
	tree = tree_init();
	
	time_t start, end;
	int avl_insertion_time = 0;
	
	FILE *fp;
    int i = 0;
    unsigned long long number;
    
    unsigned long long *inorder = (unsigned long long *)malloc(sizeof(unsigned long long)*n);
    fp = fopen(fname, "r+");
    time(&start);
    for(i = 0; i<n; i++){
    	fscanf(fp, "%llu\n", &number);
    	avl_insert(tree, number);
    }
    time(&end);
    fclose(fp);
    avl_insertion_time = end - start;
    
    time(&start);
    inorder_traversal(tree->root, inorder);
    time(&end);
    printf("inorder_traversal function's time spent is %ld second for %d number of elements.(AVL insertion was %ld secs)\n", (end - start), n, avl_insertion_time);
    tree_free(tree);
    free(inorder);
 
    unsigned long long *unsorted = (unsigned long long  *)malloc(sizeof(unsigned long long)*n);
    

    fp = fopen(fname, "r+");
    for(i = 0; i<n; i++)
    {
        fscanf(fp, "%llu\n", &number);
        unsorted[i] = number;

    }
    fclose(fp);
	
	
    time(&start);
    bubblesort(unsorted, n);
    time(&end);
    printf("bubblesort function's time spent is %ld second for %d number of elements.\n", (end - start), n);
    free(unsorted);
    

}

int main()
{
	
	
    test("10000.txt", 10000);
    index = 0;
    test("100000.txt", 100000);
    index = 0;
    test("1000000.txt", 1000000);
    index = 0;
    test("10000000.txt", 10000000);
    index = 0;
     

    return 0;
}


void bubblesort(unsigned long long *arr, int n)
{

    int i, j;
    unsigned long long temp = 0;

    for(i = 0; i<n; i++)
    {

        for(j = 0; j<n-i-1; j++)
        {

            if( arr[j] > arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }

	
}


NODE node_init(unsigned long long data)
{
		
	NODE newNode = (struct NODE_s*)malloc(sizeof(struct NODE_s));
	newNode->data = data;
	newNode->right = NULL;
	newNode->left = NULL;
	newNode->height = 1; 
	return newNode;
}


TREE tree_init()
{
	
	TREE tree = (struct TREE_s*)malloc(sizeof(struct TREE_s));
	
	tree->root = node_init(NULL);
	
	return tree;
}


void tree_free(TREE tree){
     
       
     node_free(tree->root);
        
         
}


int local_height(NODE node){
	
	if(node == NULL)
	return 0;
	
	return node->height;
	
}

int max(int a, int b){
	
	int maxNumber = 0;

	if( a > b ){
		
		maxNumber = a;
	}else{
		maxNumber = b;
	}
	
	return maxNumber;
}


NODE rotate_right(NODE node){
	
	NODE subNode_1 = node->left;
	NODE subNode_2 = subNode_1->right;
		
	subNode_1->right = node;
	node->left = subNode_2;
		
	node->height = max(local_height(node->left), local_height(node->right))+1;
	subNode_1->height = max(local_height(subNode_1->left),local_height(subNode_1->right))+1; 
	
	return subNode_1;
	
}

NODE rotate_left(NODE node){
	
	NODE subNode_1 = node->right; 
 	NODE subNode_2 = subNode_1->left; 
  
    
    subNode_1->left = node; 
   	node->right = subNode_2; 
  
  
 	node->height = max(local_height(node->left), local_height(node->right))+1; 
 	subNode_1->height = max(local_height(subNode_1->left), local_height(subNode_1->right))+1; 
 	
 	return subNode_1;
	
}

NODE avl_insert_recursive(NODE node, unsigned long long data){
	
	int balance = 0;
	
	
	if( node == NULL){
		
		return(node_init(data));
	}
		
	if( data < node->data ){
		
		
		node->left = avl_insert_recursive(node->left, data);
		
		
		
	}else if( data > node->data){
		
			
		node->right = avl_insert_recursive(node->right, data);
		
	
		
	}else{
		
		return node;
	}
	
	
	
	node->height = 1 + max(local_height(node->left), local_height(node->right));
	
	balance = local_height(node->left) - local_height(node->right); //check the balance
	
	if(balance > 1 && data < node->left->data){ //LL
		
		return rotate_right(node);
		
	}
	
	if (balance < -1 && data > node->right->data){ //RR
	
        return rotate_left(node);
        
	}
	
	if (balance > 1 && data > node->left->data) //LR
    { 
        node->left =  rotate_left(node->left); 
        return rotate_right(node); 
    } 
    
    if (balance < -1 && data < node->right->data) //RL
    { 
        node->right = rotate_right(node->right); 
        return rotate_left(node); 
    } 
    
    return node;
}

void avl_insert(TREE tree, unsigned long long data){
	
	
	tree->root = avl_insert_recursive(tree->root, data);
	
}



void inorder_traversal(NODE node, unsigned long long *inorder){
	
	
	if (node == NULL){
		return; 
	}
        
 
    inorder_traversal(node->left, inorder); 
  
      
    
    inorder[index] = node->data;
    index++;
   

 
    inorder_traversal(node->right, inorder); 
	
	
}

void node_free(NODE node){
	
	if(node == NULL)
		return;
	
		
	node_free(node->left); 
	node_free(node->right); 
	free(node);
	
	
}

