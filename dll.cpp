#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono> 

#include <string.h>
#include <string>

#define size 50021

#ifndef NULL
#define NULL 0
#endif

using namespace std;
using namespace std::chrono;

typedef enum
{
	CMD_INIT,
	CMD_ADD,
	CMD_DELETE,
	CMD_CHANGE,
	CMD_SEARCH
} COMMAND;


typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char *str;
} RESULT;

int getSize(char *a){
	char *t;
	t = a;
	int n = 0;
	while (*t != '\0'){
		n++;
		t++;
	}
	return n + 1;
}

char* copy(char* source){
	int n = getSize(source);
	char* t = new char[n];
	for (int i = 0; i < n; i++){
		t[i] = source[i];
	}
	return t;
}

typedef struct linkedNodes linkedNodes;

struct linkedNodes{
	char *value = NULL;
	int index;
	bool valid = true;
	linkedNodes *next=NULL;
};

typedef struct headNode headNode;

struct headNode{
	linkedNodes *head = NULL;
};

class node{
public:
	char all[5][20];
	bool used = false;
	node(){

	}
	node(char name[], char number[], char birthday[], char email[], char memo[]){
		for (int i = 0; i < getSize(name); i++){
			all[0][i] = name[i];
		}
		for (int i = 0; i < getSize(number); i++){
			all[1][i] = number[i];
		}
		for (int i = 0; i < getSize(birthday); i++){
			all[2][i] = birthday[i];
		}
		for (int i = 0; i < getSize(email); i++){
			all[3][i] = email[i];
		}
		for (int i = 0; i < getSize(memo); i++){
			all[4][i] = memo[i];
		}
		used = true;
	}
};

node *allNode;
headNode **fields;
bool firstTime = true;
int curr = 0;

int cmpChar(char *a, char *b){
	char *t1;
	char *t2;
	t1 = a;
	t2 = b;
	while (*t1 != '\0' && *t2 != '\0'){
		if (*t1 == *t2){
			t1++;
			t2++;
		}
		else{
			return 0;
		}
	}
	if (*t1 == '\0' && *t2 == '\0'){
		return 1;
	}
	else{
		return 0;
	}
}

unsigned long genHash(char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++) hash = ((hash << 5) + hash) + c; // hash*33 + c
	return hash%size;
}

void InitDB(){
	if (!firstTime){
		for (int i = 0; i < 5; i++){
			delete fields[i];
		}
		delete fields;
		delete allNode;
	}
	curr = 0;
	allNode = new node[size];
	fields = new headNode*[5];
	for (int i = 0; i < 5; i++){
		fields[i] = new headNode[size];
	}
	firstTime = false;
	//cout << "Inited" << endl;
}

void insert(int field, char *c,int parent){
	linkedNodes *t = new linkedNodes;
	t->value = copy(c);
	t->index = parent;
	//cout << "Inserting into field: " << field << "at position: " << genHash(c) << endl;
	linkedNodes *head=fields[field][genHash(c)].head;
	if (head == NULL){
		fields[field][genHash(c)].head = t;
		return;
	}
	//cout << field<<" COLLISION!!!! "<<c<<endl;
	linkedNodes *temp = head->next;
	linkedNodes *prev = head;
	while (temp != NULL){
		prev = temp;
		temp = temp->next;
	}
	prev->next = t;
}

void Add(char* name, char* number, char* birthday, char* email, char* memo){
	//cout << curr << endl;
	if (curr >= size || allNode[curr].used){
		for (int i = 0; i < 50000; i++){
			if (!allNode[i].used){
				curr = i;
			}
		}
	}
	allNode[curr] = node(name, number, birthday, email, memo);

	for (int i = 0; i < 5; i++){
		insert(i, allNode[curr].all[i],curr);
	}
	curr++;
	
	//cout << "\n\n\n\n";
}

RESULT Search(FIELD field, char* str, FIELD returnfield){
	//cout<<field<<endl;
	RESULT r;
	r.count = 0;
	linkedNodes *head = fields[field][genHash(str)].head;
	if (head == NULL){
		return r;
	}
	while (head != NULL){
		if (cmpChar(head->value, str) == 1 && head->valid){
			r.count++;
			if (r.count == 1){
				r.str = copy(allNode[head->index].all[returnfield]);
			}
		}
		head = head->next;
	}
	if (r.count != 1){
		r.str = NULL;
	}
	return r;
}

void deleteChilds(int field, char *str, int index){
	linkedNodes *temp = fields[field][genHash(str)].head;
	linkedNodes *head = temp;
	while (head != NULL){
		if (cmpChar(head->value, str) == 1 && head->valid && head->index == index){
			head->valid = false;
			return;
		}
		head = head->next;
	}
	fields[field][genHash(str)].head = temp;
}

int Delete(FIELD field, char* str){
	int c = 0;
	linkedNodes *temp = fields[field][genHash(str)].head;
	linkedNodes *head = temp;
	if (head == NULL){
		return c;
	}
	while (head != NULL){
		if (cmpChar(head->value, str) == 1 && head->valid){
			c++;
			head->valid = false;
			allNode[head->index].used = false;
			for (int i = 0; i < 5; i++){
				if (i != field){
					deleteChilds(i, allNode[head->index].all[i], head->index);
				}
			}
		}
		head = head->next;
	}
	fields[field][genHash(str)].head = temp;
	return c;
}

int Change(FIELD field, char* str, FIELD changefield, char* changestr){
	int c = 0;
	linkedNodes *temp = fields[field][genHash(str)].head;
	linkedNodes *head = temp;
	if (head == NULL){
		return c;
	}
	while (head != NULL){
		if (cmpChar(head->value, str) == 1 && head->valid){
			c++;
			deleteChilds(changefield, allNode[head->index].all[changefield], head->index);
			//cout << allNode[head->index].all[changefield] << endl;
			for (int i = 0; i < getSize(changestr); i++){
				allNode[head->index].all[changefield][i] = changestr[i];
			}
			//cout << allNode[head->index].all[changefield] << endl;
			//cout << "change is calling insert" << endl;
			insert(changefield, changestr, head->index);
		}
		head = head->next;
	}
	fields[field][genHash(str)].head = temp;
	return c;
}

/*
int main(){
	InitDB();
	while (1){
			char a[5][20];
			for (int i = 0; i < 5; i++){
				cin >> a[i];
			}
			Add(a[0], a[1], a[2], a[3], a[4]);
	}
	return 0;
}*/







static int dummy[100];
static int Score, ScoreIdx;
static char name[20], number[20], birthday[20], email[20], memo[20];

static char lastname[10][5] = { "kim", "lee", "park", "choi", "jung", "kang", "cho", "oh", "jang", "lim" };
static int lastname_length[10] = { 3, 3, 4, 4, 4, 4, 3, 2, 4, 3 };

static int mSeed;
static int mrand(int num)
{
	mSeed = mSeed * 1103515245 + 37209;
	if (mSeed < 0) mSeed *= -1;
	return ((mSeed >> 8) % num);
}

static void make_field(int seed)
{
	int name_length, email_length, memo_length;
	int idx, num;

	mSeed = (unsigned int)seed;

	name_length = 6 + mrand(10);
	email_length = 10 + mrand(10);
	memo_length = 5 + mrand(10);

	num = mrand(10);
	for (idx = 0; idx < lastname_length[num]; idx++) name[idx] = lastname[num][idx];
	for (; idx < name_length; idx++) name[idx] = 'a' + mrand(26);
	name[idx] = 0;

	for (idx = 0; idx < memo_length; idx++) memo[idx] = 'a' + mrand(26);
	memo[idx] = 0;

	for (idx = 0; idx < email_length - 6; idx++) email[idx] = 'a' + mrand(26);
	email[idx++] = '@';
	email[idx++] = 'a' + mrand(26);
	email[idx++] = '.';
	email[idx++] = 'c';
	email[idx++] = 'o';
	email[idx++] = 'm';
	email[idx] = 0;

	idx = 0;
	number[idx++] = '0';
	number[idx++] = '1';
	number[idx++] = '0';
	for (; idx < 11; idx++) number[idx] = '0' + mrand(10);
	number[idx] = 0;

	idx = 0;
	birthday[idx++] = '1';
	birthday[idx++] = '9';
	num = mrand(100);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	num = 1 + mrand(12);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	num = 1 + mrand(30);
	birthday[idx++] = '0' + num / 10;
	birthday[idx++] = '0' + num % 10;
	birthday[idx] = 0;
}

static void cmd_init()
{
	scanf("%d", &ScoreIdx);

	InitDB();
}

static void cmd_add()
{
	int seed;
	scanf("%d", &seed);

	make_field(seed);

	Add(name, number, birthday, email, memo);
	//cout << "[INSERT] " << name << "\n" << number << "\n" << birthday << "\n" << email << "\n" << memo <<"\n\n\n\n";
}

static void cmd_delete()
{
	int field, check, result;
	char str[20];
	scanf("%d %s %d", &field, str, &check);

	result = Delete((FIELD)field, str);

	if (result != check){
		Score -= ScoreIdx;
		cout << "[ERROR]\n";
		cout << "[DELETE] " << field << " " << str << " Result: " << check << endl;
		cout << "[DELETE] " << "Output: " << result << endl;
	}

}

static void cmd_change()
{
	int field, changefield, check, result;
	char str[20], changestr[20];
	scanf("%d %s %d %s %d", &field, str, &changefield, changestr, &check);

	result = Change((FIELD)field, str, (FIELD)changefield, changestr);
	if (result != check){
		Score -= ScoreIdx;
		cout << "[ERROR]\n";
		cout << "[CHANGE] " << field << " " << str << " " << changefield << " Result: " << changestr << " " << check << endl;
	}

}

static void cmd_search()
{
	int field, returnfield, check;
	char str[20], checkstr[20];
	scanf("%d %s %d %s %d", &field, str, &returnfield, checkstr, &check);

	RESULT result = Search((FIELD)field, str, (FIELD)returnfield);


	if (result.count != check || (result.count == 1 && (strcmp(checkstr, result.str) != 0))){
		cout << "[ERROR]\n";
		cout << "[SEARCH] " << field << " " << str << " " << returnfield << " Result: " << checkstr << " " << check << endl;
		if (result.str != NULL){
			cout << "[SEARCH] Output: " << result.str << " " << result.count << endl;
		}
		int hashK = genHash(str);
		linkedNodes *t = fields[field][hashK].head;
		while (t != NULL){
			cout << t->value << " " << t->valid << endl;
			t = t->next;
		}
		Score -= ScoreIdx;
	}

}

static void run()
{
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		int cmd;
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:   cmd_init();   break;
		case CMD_ADD:    cmd_add();    break;
		case CMD_DELETE: cmd_delete(); break;
		case CMD_CHANGE: cmd_change(); break;
		case CMD_SEARCH: cmd_search(); break;
		default: break;
		}
	}
}

static void init()
{
	Score = 1000;
	ScoreIdx = 1;
}


int main()
{
	auto start = high_resolution_clock::now();
	setbuf(stdout, NULL);
	freopen("test.txt", "r", stdin);

	int T;
	scanf("%d", &T);

	int TotalScore = 0;
	for (int tc = 1; tc <= T; tc++)
	{
		init();

		run();

		if (Score < 0)
			Score = 0;

		TotalScore += Score;
		printf("#%d %d\n", tc, Score);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	cout << "Execution time: "<< (float)duration.count()/1000 <<"s"<< endl;
	printf("TotalScore = %d\n", TotalScore);
	
	return 0;
}
