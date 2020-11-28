#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct Node {
	int totalDay;
	int day;
	char month[100];
	int year;
	char name[100];
	
	Node *next, *prev;
} *head, *tail, *curr;

Node *createNode(int totalDay, int day, int year, char *month, char*name) {
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->totalDay = totalDay;
	temp->day=day;
	strcpy(temp->name, name);
	strcpy(temp->month, month);
	temp->year=year;
	temp->next = temp->prev = NULL;
	return temp;
}

void pushHead(int totalDay, int day, int year, char *month, char*name) {
	Node *temp = createNode(totalDay,day, year, month,name);
	if(!head) head=tail=temp; 
	else { 
	head->prev = temp; 
	temp->next = head; 
	head = temp;
	}
}

void pushTail(int totalDay, int day, int year, char *month, char*name) {
	Node *temp = createNode(totalDay, day, year, month, name);
	if(!head) { 
	head = tail = temp; 
	} else { 
	tail->next = temp; 
	temp->prev = tail; 
	tail = temp; 
	}
}

void pushMid(int totalDay, int day, int year, char*month, char*name) {
	if(!head) { 
	Node *temp = createNode(totalDay, day, year, month, name);
	head = tail = temp;
	} else if(totalDay < head->totalDay) {
	pushHead(totalDay, day, year, month,name);
	} else if(totalDay > tail->totalDay) {
	pushTail(totalDay, day, year, month,name);
	} else { 
	Node *temp = createNode(totalDay, day, year, month,name);
	curr = head;
	
	while(curr->totalDay < totalDay) {
	  curr = curr->next;
	}
	temp->prev = curr->prev; 
	temp->next = curr; 
	curr->prev->next = temp; 
	curr->prev = temp; 
	}
}

void popHead() {
	if(head && head == tail) { 
		head = tail = NULL;
		free(head);
	} 
	else { 
		Node *newHead = head->next; 
		head->next = newHead->prev = NULL; 
		free(head); 
		head = newHead; 
	}
}
	
void popTail() {
	if(head && head == tail) { 
	head = tail = NULL;
	free(head);
	} else { 
	Node *newTail = tail->prev; 
	tail->prev = newTail->next = NULL; 
	free(tail); 
	tail = newTail; 
  }
}

void printLinkedList() {
	curr=tail;
	while(curr) {
		printf("%d %s %d - %s", curr->day, curr->month, curr->year, curr->name);
		curr=curr->prev;
		puts("");
	}
}

int hitungBulan(char *bulan){
	if(strcmp(bulan, "january")==0) return 12*30;
	if(strcmp(bulan, "february")==0) return 11*30;
	if(strcmp(bulan, "march")==0) return 10*30;
	if(strcmp(bulan, "april")==0) return 9*30;
	if(strcmp(bulan, "may")==0) return 8*30;
	if(strcmp(bulan, "june")==0) return 7*30;
	if(strcmp(bulan, "july")==0) return 6*30;
	if(strcmp(bulan, "august")==0) return 5*30;
	if(strcmp(bulan, "september")==0) return 4*30;
	if(strcmp(bulan, "october")==0) return 3*30;
	if(strcmp(bulan, "november")==0) return 2*30;
	if(strcmp(bulan, "december")==0) return 1*30;
}


int totalDays(int day, char *month, int year){
	return (2020-year)*365 + hitungBulan(month) + (30-day);
}

int main() {
	int x, y;
	int day, year;
	char month[100], name[100];
	scanf("%d %d", &x, &y);
	
	for(int i=0; i<x; i++){
		scanf("%d %[^ ] %d - %[^\n]", &day, month, &year, name);
	
		int value=totalDays(day,month,year);
		pushMid(value, day, year, month, name);
	}
	puts("");
	if(x-y!=0) printf("Need %d more cure\n", x-y);
	for(int i=0; i<y; i++){
		popTail();
	}

	printLinkedList();	
}