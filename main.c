#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct shop{
	int goods;
	int muted;
};

#define count 5

struct shop place[count];
int costumers = 3;

void load(){
	int index;
	while(costumers > 0){
		index = rand() % count;
		printf("--------------------------------------------------------\n");
		printf("Loader comes to shop number %d.\n", index + 1);
		if(place[index].muted){
			printf("It's busy. Loader went away.\n");
			sleep(2);
			continue;
		}
		place[index].muted = 1;
		printf("Loader locked shop and starts to work.\n");
		int goods = 400 + rand() % 200;//500 +- 100
		for(int i = 0; i < goods; i++)
			place[index].goods += 1;
		place[index].muted = 0;
		printf("Loader finished the job added %d goods and goes away.\nThere is %d.\nShop number %d is open again.\n", goods, place[index].goods, index + 1);
		printf("--------------------------------------------------------\n");
		sleep(2);
	}
	pthread_exit(0);
}

void buy(int id){
	int need = 10000;
	while(need > 0){
		int index = rand() % count;
		printf("--------------------------------------------------------\n");
		printf("Costumer number %d comes to shop number %d.\n", id, index + 1);
		if(place[index].muted != 0){
			printf("It's busy. Costumer %d went away.\n", id);
			sleep(1);
			continue;
		}
		place[index].muted = 1;
		printf("Costumer %d locked shop and starts to buy.\n", id);
		while(need > 0 && place[index].goods > 0){
			--need;
			--place[index].goods;
		}
		place[index].muted = 0;
		printf("Costumer %d finished buying.\nHe is needs %d goods more.\nThere is %d in this shop.\nShop number %d is open again.\n", id, need, place[index].goods, index + 1);
		printf("--------------------------------------------------------\n");
		sleep(1);
	}
	printf("Costumer number %d has finished. He's die.\n", id);
	--costumers;
}

void init(){
	for(int i = 0; i < count; i++){
		place[i].goods = 900 + rand() % 200;//1000 +- 100
		place[i].muted = 0;
	}
}

int main(int argc, char **argv)
{
	init();
	pthread_t loader;
	pthread_t buyer1, buyer2, buyer3;
	pthread_create(&loader, NULL, load, NULL);
	pthread_create(&buyer1, NULL, buy, 1);
	pthread_create(&buyer2, NULL, buy, 2);
	pthread_create(&buyer3, NULL, buy, 3);
	pthread_join(&loader, NULL);
	printf("give me a bottle of rum!\n");
	return 0;
}
