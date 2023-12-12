#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define max_u 10 //最多10間大學
#define CNT 8 //最多8種條件，以下8種
//NC CT NS NM BC NL HL GF

typedef struct un{
	char name[11]; //存放大學名字
	int props; //屬性是什麼 用十進位存放 但算的時候會變二進位制算
	int match; //符合搜尋條件的次數
}university; //大學的屬性

typedef struct qr{
	int flags[9]; //每組or條件要用int表示 最多9組
	int cnt; //有幾組條件資料(一組接代表用or區隔)(GN BC+NC為兩組資料)
}query;

//做一個func，找條件時可以快速得知該條件所代表的值
//傳進來為char(條件)，所以應為array，因此input為pointer of char
//回傳值為條件的index，也是條件的2進位制之位置
int get_index(char* name){
	char prop[8][2] = {"NC", "CT", "NS", "NM", "BC", "NL", "HL", "GF"};
	for(int i=0;i<8;i++){
		if(name[0]==prop[i][0] && name[1]==prop[i][1]){
			return i;
		}
	}
	return -1;
}

//為了知道誰最多符合
//因此要有一個檢測符合屬性數量的func
//input為bigwise結果 return為符合數量
int matchpropcnt(int flags){
	int re = 0, mask = 1;
	for(int i=0;i<8;i++){
		if(flags & mask) re++;
		mask = mask << 1;
	}
	return re;
}

//mode 0 時，要全部條件符合
//mode 1 時，只要部份條件符合
//此func是為了配對看看
//input為(各大學陣列, 幾間大學, 條件陣列, 0 or 1)
void match(university *u, int u_cnt, query *q, int mode){
	int best_cnt = 0;//紀錄符合最多條件者
	int m_flag;

	//初始化每個大學的符合數
	//mode不同時，"符合"的定義也會不一樣，但一開始皆要為0
	for(int i=0;i<u_cnt;i++){
		u[i].match = 0;
	}
	//q->cnt 代表有幾組條件(GN BC + NC為兩組資料)
	//printf("q->cnt = %d\n", q->cnt);
	for(int j=0;j<q->cnt;j++){
		int q_flag = q->flags[j];//引入一組
		//printf("q_flag = %d\n", q_flag);
		for(int i=0;i<u_cnt;i++){
			//u[i].props 為大學有的屬性 假設是36 => 00100100
			//q_flag  為查詢的條件屬性  假設是12 => 00001100
			m_flag = u[i].props & q_flag;
			/*printf("u[i].props = %d\n", u[i].props);
			printf("m_flag = %d\n", m_flag);
			printf("q_flag = %d\n\n", q_flag);
			*/
			//則 m_flag 為00000100
			if(m_flag!=0){
				//printf("m_flag = %d\n", m_flag);
				//mode == 0 代表要全部符合
				if(mode==0){
					//m_flag完全跟q_flag一樣的時候，才可算是"全部符合"
					//類似上述例子 m_flag 00000100 不完全等於 q_flag 00001100
					//不是mode 0的查詢成功案例
					if(m_flag==q_flag){
						if(u[i].match==0){
							printf("%s ", u[i].name);
						}
						u[i].match ++;
					}
				}
				//mode == 1 代表要輸出部分符合最多項的
				else if(mode==1){
					//將各個大學的match數加上看符合幾個小條件
					//上述例子m_flag 00000100 即為u[i].match+=1
					u[i].match+=matchpropcnt(m_flag);
					if(best_cnt<u[i].match) best_cnt = u[i].match;//更新最大數
					//printf("best_cnt = %d\n", best_cnt);
				}
			}
		}
	}
	if(mode==1){
		for(int i=0;i<u_cnt;i++){
			if(u[i].match==best_cnt){
				printf("%s ", u[i].name);
			}
		}
	}
	printf("\n");
}

int main(){
	/*
	n為有幾所大學	
	大學後是各個屬性
	m為查詢個數
	空格代表都要 +代表或者
	由b決定要輸出
	0 => 符合條件之大學
	1 => 輸出滿足"最多"子屬性的大學
	*/

	int m, n, mode;
	int index;
	char buffer[256], *p;
	university u[max_u];
	query q[10];
	scanf("%d\n", &n);
	for(int i=0;i<n;i++){
		//拿整排存進八佛
        gets(buffer);
		//將p裡放巴佛到空格之前
		p = strtok(buffer, " ");
		strcpy(u[i].name, p);
		u[i].props = 0;//聽說是初始化

		p = strtok(NULL, " ");
		index = 0;
		while(p!=NULL){
			index = get_index(p);
			if(index>=0){//確定為合法位置
				//將1*(2的index次方)
				//再用or加進去該大學的屬性中
				//例如：
				/*
				(1)輸入 CT NS
				(2)先處理CT
				(3)index = 1
				(4)(1<<index) = 00000010
				(5)u[i].props |= (1<<index)後， u[i].props = 00000010
				(6)再處理NS
				(7)index = 2
				(8)(1<<index) = 00000100
				(9)u[i].props |= (1<<index)後， u[i].props = 00000110
				*/
				u[i].props |= (1<<index);
			}
			p = strtok(NULL, " ");
		}
	}
	//q的元素皆為0了，所以cnt以設為0
	memset(q, 0, sizeof(q));
	scanf("%d\n", &m);
	for(int i=0;i<m;i++){
		gets(buffer);
		p = strtok(buffer, " ");
		while(p!=NULL){
			if(*p=='+')	q[i].cnt++;
			//結算至加號的前一個屬性
			else{
				index = get_index(p);
				if(index>=0){//合法的index
					//跟前面一樣的道理
					q[i].flags[q[i].cnt] |= (1<<index);
				}
			}
			p = strtok(NULL, " ");
		}
		//加上最後一個屬性
		q[i].cnt++;
	}
	//search
	scanf("%d", &mode);
	for(int i=0;i<m;i++){
		//printf("i = %d\n", i);
		match(u, n, &q[i], mode);
	}
	return 0;
}
