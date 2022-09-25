#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// ����ܾ�, �ǹ̸� ������ element ����ü
typedef struct dic {
	char *word;
	char *meaning;
}element;

// ��������� ���� Ʈ���� �����ϱ� ���� TreeNode
typedef struct TreeNode {
	element data;
	struct TreeNode*left, *right;
}TreeNode;

int compare(element x, element y);
TreeNode *search_node(TreeNode **root, element key);
TreeNode *insert_node(TreeNode *root, element  key);
void display(TreeNode *root);
void delete_node(TreeNode **root, element key);


int main() {
	FILE *fp;
	char w_buffer[30], m_buffer[30];	// �����Ҵ��� ���� �ӽ÷� ����
	element n;	// �ܾ� �ӽ� ���� ����ü
	char command; // ��ɾ� ���� ����
	TreeNode **root = NULL;

	int size[2]; // �ܾ� ���� �ӽ� ����
	int cnt = 0;

	fp = fopen("words.txt", "r");

	if (fp == NULL) {
		printf("������ �������� �ʽ��ϴ�.");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%c", &command);
		switch (command)
		{
			// ��� ����
		case 'i':
			strcpy(w_buffer, "");
			strcpy(m_buffer, "");
			// ���Ͽ��� word�� meaning�� �� �� �� �о��.
			fscanf(fp, "%s %s", w_buffer, m_buffer);
			size[0] = strlen(w_buffer);
			size[1] = strlen(m_buffer);

			// size[]�� �̿��� element �޸� ���� �Ҵ�
			n.word = (char*)malloc(sizeof(char)*(size[0]+1));
			n.meaning = (char*)malloc(sizeof(char)*(size[1] + 1));

			strcpy(n.word,w_buffer);
			strcpy(n.meaning, m_buffer);


			root = insert_node(root, n);
			printf("%s : %s ����\n", n.word, n.meaning);
			break;

			// Ʈ�� Ž��
		case 's':
			fscanf(fp, "%s", n.word);
			strcpy(n.meaning, "");
			TreeNode *tmp = search_node(root, n);
			printf("�ܾ� %s�� �ǹ� : %s\n", tmp->data.word, tmp->data.meaning);
			break;

			//��� ����
		case 'd':
			fscanf(fp, "%s", n.word);
			delete_node(root, n);
			printf("%s ����\n", n.word);

			break;

			// ���
		case 'p':
			display(root);
			break;

			// ������
		case 'q':
			exit(0);
			break;
		default:
			break;
		}
	}

}

int compare(element x, element y)
{
	// x�� y�� word �� ���Ͽ�
	// x�� ���������� �տ� ������ -1, ������ 0, �ڿ� ������ 1 ��ȯ
	return strcmp(x.word, y.word);
}

TreeNode * search_node(TreeNode **root, element key) {
	TreeNode* tmp;
	tmp = *root;	// root�� �������� ����.

	while (tmp != NULL) {
		int flag = compare(key, tmp->data);
		if (flag == 0)
			return tmp;
		else if (flag < 0)
			tmp = tmp->left;
		else
			tmp = tmp->right;

	}
	// ��ȸ�� ������ ��ȯ���� ���� ���
	if (tmp == NULL) {
		printf("ã������ �ܾ ������ �����ϴ�.");
		return;
	}
	

}

TreeNode* insert_node(TreeNode *root, element key) {
	TreeNode* tmp = root;
	TreeNode *p = NULL;	// ���� ������� ����� �θ���
	TreeNode *n;	// ���� ������� ���

	while (tmp != NULL) {
		p = tmp;
		int	flag = compare(key, tmp->data);
		if (flag == 0) {
			printf("�̹� ���� ����� �ֽ��ϴ�.");
			return;
		}
		else if (flag <0)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;	// �޸� �����Ҵ��� �����ϸ� return
	else {
		n->data = key;
		n->left = NULL;
		n->right = NULL;
	}
	if (p != NULL) {
		if (compare(n->data, p->data) < 0)
			p->left = n;
		else
			p->right = n;
	}
	else
		root = n;
	return root;
}

void display(TreeNode *root) {
	TreeNode* tmp = root;

	while (tmp != NULL) {
		display(tmp->left);
		printf("Ʈ�����(%s : %s)", tmp->data.word, tmp->data.meaning);
		display(tmp->right);
		printf("->");
	}

}

void delete_node(TreeNode **root, element key) {

}