#include<string.h>
#include<stddef.h>
char *mygets(char *buf, size_t size) {
	if(buf!=NULL && size > 0){
		if(fgets(buf,size,strlen)){
			buf[strcspn(buf,"\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;
}
