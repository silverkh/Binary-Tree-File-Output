#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE	 100
#define MAX_MEANING_SIZE 200
#define max(a,b) (((a)>(b))?(a):(b))
FILE* fp;

typedef struct
{
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
} element;
typedef struct TreeNode
{
	element key;
	struct TreeNode *left, *right;
} TreeNode;
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}
TreeNode * new_node(element item)
{
	TreeNode * temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
TreeNode * insert_node(TreeNode * node, element key)
{
	if (node == NULL) return new_node(key);

	if (compare(key, node->key)<0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key)>0)
		node->right = insert_node(node->right, key);
	return node;
}

void help()
{
	printf("i: 입력\nq: 종료\nr: 저장\n");
}

void savefile(TreeNode* root)
{
    if(root != NULL)
    {
        element convey;
        savefile(root->left);
        convey= root->key;
        printfile(&convey);
        savefile(root->right);
    }
}

void printfile(element* convey)
{
    fprintf(fp, "%s %s", convey->word, convey->meaning);
}
int main(void)
{
    char command;
	element e;
	TreeNode * root = NULL;
	TreeNode * tmp;

	do {
		help();
		command = getchar();
		getchar();
		switch (command) {
		case 'i':
			printf("단어:");
			gets(e.word);
			printf("의미:");
			gets(e.meaning);
			root = insert_node(root, e);
			break;

        case 'r':
            fp= fopen("oop_word.txt", "wt");
            savefile(root);
            fclose(fp);
		}
	} while (command != 'q');
	return 0;
}
