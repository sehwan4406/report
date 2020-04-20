#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

int main(void){
	void dbcreate;
	void dbqeury;
	void dbupdate;
	int menu;
	while(true)
	{
	printf("1:생성 2:질의 3:업데이트 \n");
	switch(menu){
		case 1:dbcreate();
		       break;
		case 2:dbqeury();
		       break;
		case 3:dbupdate();
		       break;
		 default:printf("1~3중 에입력하세요");
			 break;
	}
	}
	return 0;
	void dbcreate(int argc, char *argv[])
	{
		    int fd;
		        struct student rec;

			    if (argc < 2) {
				            fprintf(stderr,  "사용법 : %s file\n", argv[0]);
					            exit(1);
						        }

			        if ((fd = open(argv[1],O_WRONLY |O_CREAT, 0640))==-1) {
					        perror(argv[1]);
						        exit(2);
							    }

				    printf("%-9s %-8s %-4s", "학번",  "이름",  "점수"); 
				        while (scanf("%d %s %d", &rec.id, rec.name, &rec.score) ==  3) {
						        lseek(fd, (rec.id - START_ID) * sizeof(rec), SEEK_SET);
							        write(fd, &rec, sizeof(rec) );
								    }

					    close(fd);
					        exit(0);
	}


	void dbquery(int argc, char *argv[])
	{
		    int fd, id;
		        char c;
			    struct student rec;

			       if (argc < 2) {
				               fprintf(stderr,  "사용법 : %s file\n", argv[0]);
					               exit(1);
						          }

			          if ((fd = open(argv[1], O_RDONLY)) == -1) {
					          perror(argv[1]);
						          exit(2);
							      }

				      do {
					              printf("\n검색할 학생의 학번 입력:");
						              if (scanf("%d", &id) == 1) {
								                  lseek(fd, (id-START_ID)*sizeof(rec), SEEK_SET);
										              if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) 
												                      printf("학번:%d\t 이름:%s\t 점수:%d\n", 
																                              rec.id, rec.name, rec.score);
											                  else printf("레코드 %d 없음\n", id);
													          }
							              else printf("입력 오류"); 

								              printf("계속하겠습니까?(Y/N)");
									              scanf(" %c", &c);
										          } while (c == 'Y');
				         
				          close(fd);
				          exit(0);
	}

	void dbupdate(int argc, char *argv[])
	{
		    int fd, id;
		        char c;
			    struct student rec;

			        if (argc < 2) {
					        fprintf(stderr,  "사용법 : %s file\n", argv[0]);
						        exit(1);
							    }

				    if ((fd = open(argv[1], O_RDWR)) == -1) {
					            perror(argv[1]);
						            exit(2);
							        }

				        do {
						        printf("수정할 학생의 학번 입력: ");
							        if (scanf("%d", &id) == 1) {
									            lseek(fd,  (long) (id-START_ID)*sizeof(rec), SEEK_SET);
										                if ((read(fd, &rec, sizeof(rec)) > 0) && (rec.id != 0)) {
													                printf("학번:%8d\t 이름:%4s\t 점수:%4d\n", 
																	                       rec.id, rec.name, rec.score);
															           printf("새로운 점수: ");
																              scanf("%d", &rec.score);
																	                      lseek(fd, (long) -sizeof(rec), SEEK_CUR);
																			                      write(fd, &rec, sizeof(rec));
																					                  }
												            else printf("레코드 %d 없음\n", id);
													            }
								        else printf("입력오류\n");
									        printf("계속하겠습니까?(Y/N)");
										        scanf(" %c",&c);
											    } while (c == 'Y');

					    close(fd);
					    exit(0);
}

