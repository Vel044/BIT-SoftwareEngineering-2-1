#include "stdio.h"
#include "stdlib.h"
 
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;
 
BiTree Search(BiTree p, int key){
    if(key < p->data){
        if(p->lchild == NULL) return p;
        else return Search(p->lchild, key);
    }
    else{
        if(p->rchild == NULL) return p;
        else return Search(p->rchild, key);
    }
}
 
void Print(BiTree p, int step){
    if(p->lchild != NULL) Print(p->lchild, step+1);
    for(int i = 0; i < step; i++)
            printf("    ");
        printf("%d\n", p->data);
    if(p->rchild != NULL) Print(p->rchild, step+1);
}
 
void MidPrint(BiTree p){
    if(p->lchild != NULL) MidPrint(p->lchild);
    printf(" %d",p->data);
    if(p->rchild != NULL) MidPrint(p->rchild);
}
 
int main(int argc, char const *argv[])
{
    int key;
    BiTree root = NULL;
    scanf("%d", &key);
    root = (BiTree)malloc(sizeof(BiTNode));
    root->data = key;
    root->lchild = NULL;
    root->rchild = NULL;
    while(scanf("%d", &key) && key != 0){
        BiTree p = Search(root, key);
        if(key < p->data){
            p->lchild = (BiTree)malloc(sizeof(BiTNode));
            p->lchild->data = key;
            p->lchild->lchild = NULL;
            p->lchild->rchild = NULL;
        }
        else{
            p->rchild = (BiTree)malloc(sizeof(BiTNode));
            p->rchild->data = key;
            p->rchild->lchild = NULL;
            p->rchild->rchild = NULL;
        }
    }
    Print(root, 0);
    putchar('\n');
    MidPrint(root);
    putchar('\n');
    return 0;
}