//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	// ListNode라는 타입의 넥스트 라는 포이터 변수 선언.
	// 다음에 올 노드의 값 => next자체는 그 값의 주소
	// 그렇다면 주소를 받아야 함. 주소를 받지 않으면 오류
	// * 때문에 next가 주소를 받아야 하기 때문
	struct _listnode *next;
} ListNode;

// 그렇다면 연결리스트 구조체는?
	// 
typedef struct _linkedlist{
	int size;
	// ListNode라는 타입()의 헤드라는 포인터 변수 선언 
	ListNode *head;
} LinkedList;


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	// ll 이라는 연결리스트 하나 선언
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			// j는 insertSortedLL에 링크드리스트와 i
				// 
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			// removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// 삽입 정렬 연결 리스트를 구현하는 함수

// 파라미터
	// 위에서 링크드 리스트를 하나 ll로 선언함.
	// 그렇다면 우리가 만든 함수의 파라미터는 *ll
	// *ll은 ll이 할당 받는 링크드 리스트의 주소 값의 실제 값
	// ll은 주소
	// item 은 유저가 입력한 숫자
int insertSortedLL(LinkedList *ll, int item)
{
	// next도 주소를 받아야 하고
	// head도 주소를 받아야 함

	// 필요 없는 거 아닌가?
	// 이미 위에서 선언 후 넣어 줬잖아..
	// NULL일 이유가 없잖아.
	if(ll == NULL) return -1;
	
	// 변수 호출 시 새로운 노드 하나 생성
	// 노드의 값은 입력받은 수
	// 다음 노드는 일단 NULL로 초기화
	//ListNode 타입을 가진 new_node라는 포인터 변수 선언
	ListNode* new_node = malloc(sizeof(ListNode));
	// (*new_node).item = item;
	new_node->item = item;
	new_node->next = NULL;	

	// 만약 연결리스트가 비었다면?
	if(ll->size == 0){
		// 해드에 만든 노드를 연결 후 노드의 사이즈 키우기
		ll->head = new_node;
		ll->size++;
		return 0;
	}
	else{
		// 노드가 존재한다면

		int idx = 0;
		ListNode* cur_node = ll->head;
		ListNode* prev_node = NULL;
		while(cur_node != NULL && cur_node->item < item){
			prev_node = cur_node;
			idx++;
			cur_node = cur_node->next;
		}
		// printf("%i",idx);
		if(cur_node == NULL){
			if(prev_node->item == item){
				// printf("%i\n", cur_node->next->item);
				printf("same value\n");
				free(new_node);
				return -1;
				
			}
			prev_node->next = new_node;
			ll->size++;
			return idx;
		}
		else{
			if(prev_node == NULL){			// 맨앞
				if(cur_node->item == item){
					// printf("%i\n", cur_node->next->item);
					printf("same value\n");
					free(new_node);
					return -1;
					
				}
				new_node->next = cur_node;
				ll->head = new_node;
				ll->size++;
				return 0;
			}
			else{
				if(prev_node->item == item){
					// printf("%i\n", cur_node->next->item);
					printf("same value\n");
					free(new_node);
					return -1;
				}
				if(cur_node->item == item){
					// printf("%i\n", cur_node->next->item);
					printf("same value\n");
					free(new_node);
					return -1;
				}
				prev_node->next = new_node;
				new_node->next = cur_node;
				ll->size++;
				return idx;
			}
		}

	}
	
}



///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}