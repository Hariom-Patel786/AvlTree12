//Video NO.59 - 60 AVL(PART-1 & 2)

#include<stdio.h>
#include<stdlib.h>
struct Node;
struct QueueNode
{
struct Node *ptr;
struct QueueNode *next;
};
struct QueueNode *queueStart;
struct QueueNode *queueEnd;
void addToQueue(struct Node *elem)
{
struct QueueNode *t;
t=(struct QueueNode *)malloc(sizeof(struct QueueNode));
t->ptr=elem;
t->next=NULL;
if(queueStart==NULL)
{
queueStart=t;
queueEnd=t;
}
else
{
queueEnd->next=t;
queueEnd=t;
}
}
struct Node * removeFromQueue()
{
struct QueueNode *t;
struct Node *elem;
t=queueStart;
queueStart=queueStart->next;
if(queueStart==NULL) queueEnd=NULL;
elem=t->ptr;
free(t);
return elem;
}
int isQueueEmpty()
{
return queueStart==NULL;
}
struct StackNode
{
struct Node *ptr;
struct StackNode *next;
};
struct StackNode *stackStart;
void push(struct Node *elem)
{
struct StackNode *t;
t=(struct StackNode *)malloc(sizeof(struct StackNode));
t->ptr=elem;
t->next=stackStart;
stackStart=t;
}
struct Node *pop()
{
struct StackNode *t;
struct Node *elem;
t=stackStart;
elem=t->ptr;
stackStart=stackStart->next;
free(t);
return elem;
}
struct Node *elementAtTop()
{
return stackStart->ptr;
}
int isEmpty()
{
return stackStart==NULL;
}
struct Node
{
int num;
struct Node *left,*right;
};
struct Node *start;
int getHeightOfTreeUsingRecursion(struct Node *);
void balanceTheAVLTree()
{
struct Node *root,*rc,*rclc,*lc,*lcrc,*parent;
struct Node **p2p;
int lch,rch,diff;
while(!isEmpty())
{
root=pop();
lch=getHeightOfTreeUsingRecursion(root->left);
rch=getHeightOfTreeUsingRecursion(root->right);
diff=lch-rch;
if(diff>=-1 && diff<=1) continue;
if(root==start)
{
p2p=&start;
}
else
{
parent=elementAtTop();
if(root==parent->left)
{
p2p=&(parent->left);
}
else
{
p2p=&(parent->right);
}
}
if(lch<rch) //left is heavy
{
rc=root->right;
if(getHeightOfTreeUsingRecursion(rc->left)>getHeightOfTreeUsingRecursion(rc->right)) //right os left heavy
{
//logic to convert right is left heavy to right is right heavy
rclc=rc->left;
rc->left=rclc->right;
rclc->right=rc;
root->right=rclc;
rc=root->right;
}
//now 100% right is right heavy
root->right=rc->left;
rc->left=root;
*p2p=rc;
}
else //right is heavy
{
lc=root->left;
if(getHeightOfTreeUsingRecursion(lc->right)>getHeightOfTreeUsingRecursion(lc->left)) //left is right heavy
{
//logic to convert left is right heavy to left is left heavy
lcrc=lc->right;
lc->right=lcrc->left;
lcrc->left=lc;
root->left=lcrc;
lc=root->left;
}
//now 100% left is left heavy
root->left=lc->right;
lc->right=root;
*p2p=lc;
}
} // stack not empty loop end
}
int insert(int num)
{
struct Node *t,*j;
if(start==NULL)
{
t=(struct Node *)malloc(sizeof(struct Node));
t->num=num;
t->left=NULL;
t->right=NULL;
start=t;
return 1;
}
j=start;
while(1)
{
if(num==j->num) return 0;
push(j);
if(num<j->num)
{
if(j->left==NULL)
{
t=(struct Node *)malloc(sizeof(struct Node));
t->num=num;
t->left=NULL;
t->right=NULL;
j->left=t;
break;
}
else
{
j=j->left;
}
}
else
{
if(j->right==NULL)
{
t=(struct Node*)malloc(sizeof(struct Node));
t->num=num;
t->left=NULL;
t->right=NULL;
j->right=t;
break;
}
else
{
j=j->right;
}
}
}
balanceTheAVLTree();
return 1;
}
void traverseInOrderWithoutRecursion()
{
struct Node *t,*j;
if(start==NULL)
{
printf("No element in AVLTree\n");
return;
}
for(j=start;j!=NULL;j=j->left) push(j);
while(!isEmpty())
{
t=pop();
printf("%d\n",t->num);
if(t->right!=NULL)
{
for(j=t->right;j!=NULL;j=j->left) push(j);
}
}
}
int removeElement(int num)
{
struct Node *j,*t,*e,*f;
t=start;
while(t!=NULL)
{
if(num==t->num)break;
j=t;
if(num<t->num) t=t->left; else t=t->right;
}
if(t==NULL)
{
while(!isEmpty())
{
pop();
}
return 0;
}
if(t->left==NULL && t->right==NULL)
{
if(t==start) start=NULL;
else if(j->left==t) j->left=NULL;
else j->right=NULL;
free(t);
balanceTheAVLTree();
return 1;
}
if(t->right!=NULL)
{
for(e=t->right;e->left!=NULL;e=e->left)
{
f=e;
addToQueue(f);
}
push(e);
while(!isQueueEmpty())
{
push(removeFromQueue());
}
if(t->right==e)
{
e->left=t->left;
}
else
{
f->left=e->right;
e->left=t->left;
e->right=t->right;
}
if(start==t) start=e;
else if(j->left==t) j->left=e;
else j->right=e;
}
else
{
for(e=t->left;e->right!=NULL;e=e->right)
{
f=e;
addToQueue(f);
}
push(e);
while(!isEmpty())
{
pop(removeFromQueue());
}
if(t->left==e)
{
e->right=t->right;
}
else
{
f->right=e->left;
e->right=t->right;
e->left=t->left;
}
if(start==t) start=e;
else if(j->right==t) j->right=e;
else j->left=e;
}
free(t);
balanceTheAVLTree();
return 1;
}
void traversePreOrderWithoutRecursion()
{
struct Node *t;
if(start==NULL)
{
printf("No elements in AVL\n");
return;
}
t=start;
push(t);
while(!isEmpty())
{
t=pop();
printf("%d\n",t->num);
if(t->right!=NULL) push(t->right);
if(t->left!=NULL) push(t->left);
}
}
void traversePostOrderWithoutRecursion()
{
struct Node *t;
if(start==NULL)
{
printf("No elements in AVL\n");
return;
}
t=start;
while(1)
{
while(t!=NULL)
{
if(t->right!=NULL) push(t->right);
push(t);
t=t->left;
}
t=pop();
if(!isEmpty() && t->right!=NULL && t->right==elementAtTop())
{
pop();
push(t);
t=t->right;
}
else
{
printf("%d\n",t->num);
t=NULL;
}
if(isEmpty()) break;
}
}
void levelOrderTraversalWithoutRecursion()
{
int levelNumber;
struct Node *t;
int insertionCount;
int j,x;
if(start==NULL)
{
printf("No Elements in AVL\n");
return;
}
levelNumber=0;
addToQueue(start);
insertionCount=1;
while(!isQueueEmpty())
{
levelNumber++;
printf("--------------------------\n");
printf("Level NUmber %d\n",levelNumber);
printf("--------------------------\n");
x=0;
j=1;
while(j<=insertionCount)
{
t=removeFromQueue();
printf("%d\n",t->num);
if(t->left!=NULL)
{
addToQueue(t->left);
x++;
}
if(t->right!=NULL)
{
addToQueue(t->right);
x++;
}
j++;
}
insertionCount=x;
}
}
int getHeightOfTreeWithoutRecursion()
{
struct Node *t;
int insertionCount;
int j,x,h;
if(start==NULL) return 0;
addToQueue(start);
insertionCount=1;
h=0;
while(!isQueueEmpty())
{
h=h+1;
x=0;
j=1;
while(j<=insertionCount)
{
t=removeFromQueue();
if(t->left!=NULL)
{
addToQueue(t->left);
x++;
}
if(t->right!=NULL)
{
addToQueue(t->right);
x++;
}
j++;
}
insertionCount=x;
}
return h;
}
void traverseInOrderUsingRecursion(struct Node *t)
{
if(t==NULL) return;
traverseInOrderUsingRecursion(t->left);
printf("%d\n",t->num);
traverseInOrderUsingRecursion(t->right);
}
void traversePreOrderUsingRecursion(struct Node *t)
{
if(t==NULL) return;
printf("%d\n",t->num);
traversePreOrderUsingRecursion(t->left);
traversePreOrderUsingRecursion(t->right);
}
void traversePostOrderUsingRecursion(struct Node *t)
{
if(t==NULL) return;
traversePostOrderUsingRecursion(t->left);
traversePostOrderUsingRecursion(t->right);
printf("%d\n",t->num);
}
int getHeightOfTreeUsingRecursion(struct Node *t)
{
int lch,rch;
if(t==NULL) return 0;
lch=getHeightOfTreeUsingRecursion(t->left);
rch=getHeightOfTreeUsingRecursion(t->right);
if(lch>rch) return lch+1;
else return rch+1;
}
int main()
{
int num,ch;
start=NULL;
stackStart=NULL;
queueStart=NULL;
queueEnd=NULL;
while(1)
{
printf("1. Insert number in AVLTRee\n");
printf("2. Traverse (Inorder without recursion)\n");
printf("3. Traverse (Inorder using recursion)\n");
printf("4. Traverse (Preorder without recursion)\n");
printf("5. Traverse (Preorder using recursion)\n");
printf("6. Traverse (Postorder without recursion)\n");
printf("7. Traverse (Postorder using recursion)\n");
printf("8. Traverse (Level order without recursion)\n");
printf("9. Traverse (Level order using recursion)\n");
printf("10. Get Height of tree (Without recursion)\n");
printf("11. Get Height of tree (Using recursion)\n");
printf("12. Remove\n");
printf("13. Search\n");
printf("14. Exit\n");
printf("Enter your choice : ");
scanf("%d",&ch);
fflush(stdin);
if(ch==1)
{
printf("Enter a number to insert in AVLTree:");
scanf("%d",&num);
fflush(stdin);
if(insert(num))
{
printf("%d inserted in AVLTree\n",num);
}
else
{
printf("%d already exists in AVLTree,hence not inserted\n",num);
}
}
if(ch==2)
{
traverseInOrderWithoutRecursion();
}
if(ch==3)
{
traverseInOrderUsingRecursion(start);
}
if(ch==4)
{
traversePreOrderWithoutRecursion();
}
if(ch==5)
{
traversePreOrderUsingRecursion(start);
}
if(ch==6)
{
traversePostOrderWithoutRecursion();
}
if(ch==7)
{
traversePostOrderUsingRecursion(start);
}
if(ch==8)
{
levelOrderTraversalWithoutRecursion();
}
if(ch==10)
{
printf("Height of Tree is %d\n",getHeightOfTreeWithoutRecursion());
}
if(ch==11)
{
printf("Height of Tree is %d\n",getHeightOfTreeUsingRecursion(start));
}
if(ch==12)
{
printf("Enter a number to remove from AVLTree : ");
scanf("%d",&num);
fflush(stdin);
if(removeElement(num))
{
printf("%d is removed\n",num);
}
else
{
printf("%d is not removed, bcs num not exist in AVLTree\n",num);
}
}
if(ch==14)
{
break;
}
}
return 0;
}